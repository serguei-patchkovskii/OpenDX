/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#include <pthread.h>

#include <dx/dx.h>
#include <dxconfig.h>

#include "config.h"
#include "rq.h"
#include "instrument.h"
#include "swap.h"
#include "dxmain.h"
#include "parse.h"

#define MARK_TIME(s) /* DXMarkTimeLocal(s) */

typedef struct _EXRQJob         *EXRQJob; 

typedef struct _EXRQJob
{
    EXRQJob	next;			/* list pointers		*/
    EXRQJob	prev;
    int		highpri;		/* run this NOW			*/
    long	gid;			/* group id			*/
    int		JID;			/* job   id			*/
    PFI		func;			/* function to call		*/
    Pointer	arg;			/* argument to pass		*/
    int		repeat;			/* number of repetitions for job*/
} _EXRQJob;

typedef struct
{
    volatile int        count;
    volatile EXRQJob    free;
    volatile EXRQJob    head;
    volatile EXRQJob    tail;
} _EXRQ, *EXRQ;

static EXRQ runQueue = NULL;
static int send_RQ_message = 1;

static pthread_mutex_t rql = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t rqw = PTHREAD_COND_INITIALIZER;

static pthread_t rq_holder;

void
rq_lock()
{
    pthread_mutex_lock(&rql);
    rq_holder = pthread_self();
}

void
rq_unlock()
{
    if (rq_holder != pthread_self())
	DXSetError(ERROR_INTERNAL, "non-holder unlocking rq lock\n");

    rq_holder = 0;
    pthread_mutex_unlock(&rql);
}

void
rq_wait()
{
    if (rq_holder != pthread_self())
	DXSetError(ERROR_INTERNAL, "non-holder waiting on rq lock\n");

    rq_holder = 0;
    pthread_cond_wait(&rqw, &rql);
    rq_holder = pthread_self();
}

void
rq_broadcast()
{
    if (rq_holder != pthread_self())
	DXSetError(ERROR_INTERNAL, "non-holder signalling rq\n");

    pthread_cond_broadcast(&rqw);
}

static int kill_slaves = 0;

Error _dxf_ExRQInit (void)
{
    Error tmp;
    if (runQueue != NULL)
	return (ERROR);

    runQueue = (EXRQ) DXAllocate (sizeof (_EXRQ)); 
    if (runQueue == NULL)
	return (ERROR);

    runQueue->count = 0;
    runQueue->free = NULL;
    runQueue->head = NULL;
    runQueue->tail = NULL;

    return (OK);
}

int _dxf_ExRQPending(void)
{
    return (runQueue->count > 0);
}


static pthread_mutex_t alloc_lock = PTHREAD_MUTEX_INITIALIZER;

static EXRQJob 
alloc_job()
{
    EXRQJob job;

    pthread_mutex_lock(&alloc_lock);
    if (runQueue->free)
    {
	job = runQueue->free;
	runQueue->free = job->next;
    }
    else
	job = (EXRQJob)DXAllocate(sizeof(struct _EXRQJob));
    pthread_mutex_unlock(&alloc_lock);

    return job;
}

static void 
free_job(EXRQJob job)
{
    pthread_mutex_lock(&alloc_lock);
    job->next = runQueue->free;
    runQueue->free = job;
    pthread_mutex_unlock(&alloc_lock);
}

#if defined(CHECK_RQ)
static void
check_rq()
{
    EXRQJob j; int i;
    fprintf(stderr, "runQueue->head: 0x%08lx\n", runQueue->head);
    for (i = 0, j = runQueue->head; i < 20 && j; i++, j = j->next)
	fprintf(stderr, "    job: 0x%08lx next: 0x%08lx\n", j, j->next);
        
    fprintf(stderr, "runQueue->tail: 0x%08lx\n", runQueue->tail);
    for (i = 0, j = runQueue->tail; i < 20 && j; i++, j = j->prev)
	fprintf(stderr, "    job: 0x%08lx prev: 0x%08lx\n", j, j->prev);
        
    fprintf(stderr, "runQueue->free: 0x%08lx\n", runQueue->free);
    for (i = 0, j = runQueue->free; i < 20 && j; i++, j = j->next)
	fprintf(stderr, "    job: 0x%08lx next: 0x%08lx\n", j, j->next);
}
#endif

static EXRQJob 
getjob_id(int id)
{
    EXRQJob job, last;

    job = runQueue->head;
    last = NULL;
    while (job)
    {
	if (job->JID == id)
	    break;

	last = job;
	job = job->next;
    }

    if (job)
    {
	runQueue->count--;

	if (job->repeat > 1)
	{
	    EXRQJob newjob = alloc_job();
	    *newjob = *job;
	    job->repeat--;
	    job = newjob;
	}
	else
	{
	    EXRQJob nextnext = job->next;

	    if (job->next) job->next->prev = job->prev;
	    if (job->prev) job->prev->next = job->next;
	    if (runQueue->head == job) runQueue->head = job->next;
	    if (runQueue->tail == job) runQueue->tail = job->prev;
	}
    }

    return job;
}

static EXRQJob 
getjob()
{
    /*
     * scan the queue first for one that has to be run
     * on this thread, then for one that can be run anywhere
     */
    EXRQJob job = getjob_id(DXGetThreadPid());
    if (! job)
	job = getjob_id(-1);

#if defined(CHECK_RQ)
    check_rq();
#endif

    return job;
}

int
_dxf_ExRQDequeue()
{
    EXRQJob job;

    rq_lock();

    job = getjob();

    rq_unlock();

    if (job)
    {
	job->func(job->arg, 0);
	free_job(job);
	return 1;
    }
    else
	return 0;

}

void
_dxf_ExRQKillSlaves()
{
    rq_lock();
    kill_slaves = 1;
    pthread_cond_broadcast(&rqw);
    rq_unlock();
}

int 
_dxf_ExRQHandler()
{
    EXRQJob job;


    while (1)
    {
	rq_lock();

	while (!kill_slaves && ((job = getjob()) == NULL))
	    rq_wait();

	rq_unlock();

	if (kill_slaves)
	    break;
	
	if (job)
	    job->func(job->arg, 0);
    
	free_job(job);
    }

    return 1;
}

void
_dxf_ExRQEnqueue (PFI func, Pointer arg, int repeat,
		       long gid, int JID, int highpri)
{
    EXRQJob job = alloc_job();

    DXsyncmem();

    job->next    = NULL;
    job->prev    = NULL;
    job->highpri = highpri;
    job->gid     = gid;
    job->JID     = JID;
    job->func    = func;
    job->arg     = arg;
    job->repeat  = repeat;

    /*
     * Prepare a job block.  If we can then get one from the runqueue's
     * own free list.  If someone else sneaks in and gets the last one
     * or there aren't any then we'll just allocate a new one.  Once
     * we've gotten the block then fill it in.
     */

    rq_lock();

    /*
     * Now that the job block is set up insert it into the general list.
     * If the list is currently empty then this job becomes both the head
     * and the tail of the list and we can quit.
     *
     * NOTE: 	high priority jobs are placed at the head of the list, all
     *		others at the tail.
     */
    if (highpri)
    {
	if (runQueue->head) 
   	{
	    runQueue->head->prev = job;
	    job->next = runQueue->head;
	    runQueue->head = job;
	}
	else runQueue->head = runQueue->tail = job;

	runQueue->head = job;
    }
    else
    {
	if (runQueue->tail) 
   	{
	    runQueue->tail->next = job;
	    job->prev = runQueue->tail;
	    runQueue->tail = job;
	}
	else runQueue->head = runQueue->tail = job;
    }

    runQueue->count += repeat;

#if 0
    if(!_dxf_ExReclaimingMemory()) {
        /* child 1 adding something to child 0's queue */
        if(DXGetThreadPid() == 1 && JID == 1)
            _dxf_parent_RQ_message(); 
        else {
            if(send_RQ_message) {
                send_RQ_message = 0;
                _dxf_ExRunOn (1, _dxf_child_RQ_message, &JID, sizeof(int));
                send_RQ_message = 1;
            }
        }
    }
#else
    _dxf_ExReclaimingMemory();
#endif

#if defined(CHECK_RQ)
    check_rq();
#endif

    rq_broadcast();
    rq_unlock();
}

/*
 * Enqueue several jobs.  All allocations and queue building happens up front
 * into a queuePart.
 * the queue is then locked, and the jobs are enqueued all at once.
 */

void _dxf_ExRQEnqueueMany (int n, PFI func[], Pointer arg[], 
			int repeat[], long gid, int JID, int highpri)
{
    int i;
    for (i = 0; i < n; i++)
	_dxf_ExRQEnqueue(func[i], arg[i], repeat[i], gid, JID, highpri);
}

