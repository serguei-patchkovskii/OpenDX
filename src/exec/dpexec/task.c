/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



/* Task.c containes the routines that implement the tasks.  
 * There is a task block structure, which contains various fields including 
 * a list of tasks.  The task groups may be nested.  The common 
 * sequence of calls * is DXCreateTaskGroup, AddTasks, and 
 * DXExecuteTaskGroup.  All calls for a
 * particular task group must be executed on the same processor.  Task groups
 * are stacked per processor, and a free list is maintained per processor.
 * Because task groups may
 * be executed in a dump-and-run style, the last processor must schedule the
 * process group cleanup on the correct processor.
 *
 * Note that for performance reasons, the task work fields of the tasks are 
 * copied into a local list (with the indices), and this is sorted, not the 
 * tasks themselves.
 */

#include <dx/dx.h>

#include "task.h"
#include "rq.h"
#include "status.h"
#include "config.h"
#include "graph.h"

#define	EMPTY		(_tasks == NULL)
#define	POP(_tg)	{_tg = _tasks; _tasks = _tg->link;}
#define	PUSH(_tg)	{_tg->link = _tasks; _tasks = _tg;}

/* Note that these structures (the task stack and free list)
 * are PER PROCESSOR.
 */
static EXTaskGroup	_tasks = NULL;

static EXTaskGroup	freeTasks = NULL;
static int		numFreeTasks = 0;

static int		taskNprocs = -1;

static EXTaskGroup	runningTG = NULL;


/* Internal function prototypes */
static Error    ExDestroyTaskGroup      (EXTaskGroup tg);
static Error    ExProcessTask           (EXTask t, int iteration);
static Error    ExProcessTaskGroup      (int sync);

int
DXProcessorId(void)
{
    return DXGetThreadPid();
}

#if 0
static int
ParentProcessId(void)
{
    return(_dxd_exPPID);
}
#endif

int
DXProcessors (int n)
{
    if (taskNprocs == -1 && n > 0) 
	taskNprocs = n;

    return (taskNprocs);
}


static int trace = 0;
void DXTraceTask(int t)
{
    trace = t;
    
    if (trace > 0) {
	if (EMPTY)
	    DXMessage("no active task group");
	else
	    _dxf_ExPrintTaskGroup(_tasks);
    }
}

Error _dxf_ExInitTask(int n) 
{
    taskNprocs = n;
    /*if (! _mfork_init ())
        return (ERROR);*/
    return (OK);
}

Error _dxf_ExInitTaskPerProc() 
{
    if (DXCreateTaskGroup() == ERROR)
	return (ERROR);
    if (DXAbortTaskGroup() == ERROR)
	return (ERROR);
    return (OK);
}

Error _dxf_ExCleanupTask() 
{
    return (OK);
}

/*
 * Opens a new task group.  If one is already open then it is pushed
 * onto a stack of open task groups.
 */

Error DXCreateTaskGroup ()
{
    EXTaskGroup		tg	= NULL;
    EXTask		t	= NULL;
    int			size;
    Error		l	= ERROR;

    if (numFreeTasks == 0) 
    {
	size = sizeof (_EXTaskGroup);
	tg = (EXTaskGroup) DXAllocate (size);
	if (! tg)
	    goto error;
	ExZero (tg, size);
	
	size = sizeof (_EXTask) * EX_TASK_BLOCKS;
	t = (EXTask) DXAllocate (size);
	if (! t)
	    goto error;
	ExZero (t, size);

	l = DXcreate_lock (&tg->lock, "Tasks");
	if (l != OK)
	    goto error;

	l = DXcreate_wait (&tg->wait, "Tasks");
	if (l != OK)
	    goto error;

	tg->procId = DXProcessorId();
	tg->nalloc = EX_TASK_BLOCKS;
	tg->tasks  = t;
	tg->error  = ERROR_NONE;
    }
    else
    {
	tg = freeTasks;
	freeTasks = tg->link;
	--numFreeTasks;
	if (tg->nalloc == 0) 
	{
	    size = sizeof (_EXTask) * EX_TASK_BLOCKS;
	    t = (EXTask) DXAllocate (size);
	    if (! t)
		goto error;
	    ExZero (t, size);
	    tg->tasks = t;
	    tg->nalloc = EX_TASK_BLOCKS;
	}

	tg->nused = 0;			/* # of tasks used	*/
	tg->ntodo = 0;
	tg->sync = 0;			/* synchronous flag	*/
	tg->error  = ERROR_NONE;
    }

    PUSH (tg);
    return (OK);

error:
    if (l == OK && tg != NULL)
	DXdestroy_lock (&tg->lock);
    DXFree ((Pointer) tg);
    DXFree ((Pointer) t);
    return (ERROR);
}


/*
 * Adds a task to the current task group.  If there is no task group open,
 * but this is called from within a task, then this task is added to the 
 * end of the current task group and "work" is ignored.
 */

Error DXAddLikeTasks (PFE func, Pointer arg, int size, double work, int repeat)
{
    EXTaskGroup	tg	= NULL;
    int		s;
    EXTask	t;
    Pointer	a;
    int 	locked	= FALSE;

    if (repeat <= 0)
    {
	DXSetError (ERROR_INTERNAL, "#8330");
	goto error;
    }

    if (EMPTY)
    {
	if (runningTG)
	{
	    tg = runningTG;
	    locked = TRUE;
	    DXlock (&tg->lock, DXProcessorId());
	}
	else
	{
	    DXSetError (ERROR_INTERNAL, "#8340");
	    goto error;
	}
	t = (EXTask) DXAllocateZero (sizeof (_EXTask));
	if (! t)
	    goto error;
	t->exdelete = TRUE;
    }
    else
    {
	tg = _tasks;
	locked = FALSE;
	/*
	 * Extend the task group by adding blocks if necessary
	 */
	if (tg->nalloc == tg->nused)
	{
	    tg->nalloc <<= 1;
	    s = tg->nalloc * sizeof (_EXTask);

	    t = (EXTask) DXReAllocate ((Pointer) tg->tasks, s);
	    if (! t)
		goto error;
	    tg->tasks = t;
	}
	t = tg->tasks + tg->nused++;
	t->exdelete = FALSE;
    }
    

    /*
     * Remember the relevant information about the task
     */
    t->tg   = tg;
    t->work = work;
    t->func = func;
    t->repeat = repeat;

    /*
     * If the argument data fits locally then copy it here, otherwise
     * allocate some space and put it there.
     */
    if (size == 0)
    {
	t->arg = arg;
	t->nocopy = TRUE;
    }
    else if (size <= EX_TASK_DATA)
    {
	ExCopy (t->data, arg, size);
	t->nocopy = FALSE;
	t->arg = NULL;
    }
    else
    {
	a = DXAllocate (size);
	if (! a)
	    goto error;
	ExCopy (a, arg, size);
	t->arg = a;
	t->nocopy = FALSE;
    }

    if (locked)
    {
	tg->ntodo += repeat;
	DXunlock (&tg->lock, DXProcessorId());
        /* copy global context data to ExTask structure */
#if 0
        t->taskContext = _dxd_exContext;
#endif
        _dxfCopyContext(&(t->taskContext), _dxd_exContext);
	_dxf_ExRQEnqueue (ExProcessTask, (Pointer)t, repeat, 
			  (long) tg, 0, FALSE);
    }
    else
    {
	if (tg->nused == 1 || work < tg->minwork)
	    tg->minwork = work;
	if (tg->nused == 1 || work > tg->maxwork)
	    tg->maxwork = work;
    }

    return (OK);

error:
    if (locked && tg != NULL)
	DXunlock (&tg->lock, DXProcessorId());
    return (ERROR);
}

Error DXAddTask (PFE func, Pointer arg, int size, double work)
{
    return DXAddLikeTasks (func, arg, size, work, 1);
}


/*
 * Executes the current task group.  If any errors occur during the execution
 * of the tasks the earliest error is reported.
 */

Error DXExecuteTaskGroup (void)
{
    Error	ret;

    ret = ExProcessTaskGroup (TRUE);
    return (ret);
}


/*
 * Queues all of the tasks in the current task group for execution and 
 * immediately returns.
 */

Error DXExecuteTaskGroupNoWait (void)
{
    ExProcessTaskGroup (FALSE);
    return (OK);
}


/*
 * Aborts the current task group without executing it.
 */

Error DXAbortTaskGroup (void)
{
    EXTaskGroup		tg;

    if (EMPTY)
	return (OK);
    POP (tg);
    ExDestroyTaskGroup (tg);
    return (OK);
}


/*
 * Aborts the current task group without executing it. (Another entrypoint)
 */

Error DXDeleteTaskGroup ()
{

    DXAbortTaskGroup ();
    return (OK);
}


/*
 * Destroys a task group.
 */

static int
ExDestroyTaskGroup (EXTaskGroup tg)
{
    int		i;
    int		n;
    EXTask	t;

    for (t = tg->tasks, n = tg->nused, i = 0; i < n; t++, i++)
	if (t->arg && ! t->nocopy)
	    DXFree ((Pointer) t->arg);
    if (tg->emsg)
    {
	DXFree ((Pointer) tg->emsg);
	tg->emsg = NULL;
    }

    if (numFreeTasks >= FREE_THRESHOLD)
    {
	DXdestroy_lock (&tg->lock);
	DXFree ((Pointer) tg->tasks);
	DXFree ((Pointer) tg);
    }
    else
    {
	++numFreeTasks;
	tg->link = freeTasks;
	freeTasks = tg;
	if (tg->nalloc > MAX_SAVED_TASKS) 
	{
	    DXFree((Pointer)tg->tasks);
	    tg->nalloc = 0;
	}
    }
    return (OK);
}


/*
 * Processes a single task.  If we find that this is the last task in the	
 * group to finish and it is an asynchronous task group then we must take
 * care to delete it.  If this is a synchronous task group then we must
 * store any errors that occur in the task group's descriptor block.
 */

static Error ExProcessTask (EXTask t, int iteration)
{
    EXTaskGroup		tg;
    Pointer		arg;		/* task argument pointer	*/
    ErrorCode		ecode;		/* error code			*/
    char		*emsg;
    Error		returnVal;
    int			status;
    EXTaskGroup		oldTG;
    Context             savedContext;
    int		  	lastTask;

    oldTG = runningTG;
    ecode = ERROR_NONE;
    emsg  = NULL;

    runningTG = tg    = t->tg;

    arg = (t->nocopy || t->arg) ? t->arg : (Pointer) t->data;

    DXResetError ();

    _dxfCopyContext(&savedContext, _dxd_exContext);
    _dxfCopyContext(_dxd_exContext, &(t->taskContext));
    status = get_status ();
    set_status (PS_RUN);
    DXMarkTimeLocal ("start task");

    returnVal = (*t->func) (arg, iteration);
#if 0
    _dxd_exContext = savedContext; /* restore original context */
#endif
    _dxfCopyContext(_dxd_exContext, &savedContext);

    DXMarkTimeLocal ("end task");
    set_status (status);

    /*
     * Check for errors, if we are running without waiting, skip
     * error checking.  If the user didn't DXSetError and he didn't return
     * ERROR, no error checking.  If we have had an error in the past, 
     * don't bother getting the error stuff.
     */
    if (! tg->sync)
	goto countdown;

    ecode = DXGetError ();
    if (ecode == ERROR_NONE && returnVal == OK)
	goto countdown;

    if (ecode != ERROR_NONE && returnVal == OK)
    {
	returnVal = ERROR;
	DXWarning ("#4720",t->taskContext.graphId,
		_dxf_ExGFuncPathToString(_dxd_exCurrentFunc));
    }
    if (ecode == ERROR_NONE && returnVal == ERROR)
    {
	ecode = ERROR_INTERNAL;
	emsg = "#8350";
	goto copymessage;
    }

    if (tg->error != ERROR_NONE)
	goto countdown;

    emsg = DXGetErrorMessage ();

#define	L_ERROR		2048
copymessage:
    if (emsg)
    {
	char	lbuf[L_ERROR];
	int	len;

	len = strlen (emsg);
	len = len >= L_ERROR ? L_ERROR - 1 : len;
	strncpy (lbuf, emsg, len);
	lbuf[len] = 0;
	emsg = _dxf_ExCopyString (lbuf);
    }

countdown:
    /*
     * Decrement the task group task counter.  Was this the last task?
     */
    DXlock (&tg->lock, DXProcessorId());
    tg->ntodo --;
    lastTask = (tg->ntodo == 0);

    if (tg->sync == 0)
    {
	DXunlock (&tg->lock, DXProcessorId());

        /*
         * Its an asynchronous task group.
         * Forget about errors... no-one is waiting for them.
         */
        DXFree ((Pointer) emsg);

        /*
         * If this was the last task in the task group then arrange for the
         * task group to be deleted.
         */
        if (lastTask)
	{   // GDA
            // _dxf_ExRQEnqueue (ExDestroyTaskGroup, (Pointer)tg, 1, 0, tg->procId, FALSE);
	    ExDestroyTaskGroup(tg);
 	}
    }
    else
    {
        /*
         * A synchronous task group... the creator is waiting for
         * ntodo to go to zero (and the lock to be available).
         * If there's an error conditition with the current task and
         * there wasn't one stashed in the task group, then stash
         * this one.
         */
        if (ecode != ERROR_NONE && tg->error == ERROR_NONE)
        {
            tg->error = ecode;
            tg->emsg  = emsg;
            emsg      = NULL;
        }
	DXsignal(&tg->wait);
	DXunlock(&tg->lock, DXProcessorId());
    }

    if (t->exdelete)
	DXFree ((Pointer) t);

    runningTG = oldTG;
    return (ecode == ERROR_NONE ? OK : ERROR);
}


/*
 * Processes a task group.  If the sync flag is true then all tasks must
 * complete before this routine terminates.  If not then they are just
 * queued for execution.
 * Note that for sorting reasons, a list of WorkIndex pairs is created.
 * This list is sorted, and then all references to the list that require
 * sorting must be done using this intermediate form.
 */

#define TYPE WorkIndex
#define LT(a,b)	((a)->work>(b)->work)
#define GT(a,b)	((a)->work<(b)->work)
#define QUICKSORT	ExWorkIndexSort
#include "../libdx/qsort.c"

static Error ExProcessTaskGroup (int sync)
{
    Error               ret	= ERROR;
    EXTaskGroup		tg;
    EXTask		task;
    int			i, j;
    int			todo;
#if 0
    volatile int	*count;		/* task group counter		*/
#endif
    int			totalTodo;
#define NUM_TASKS_ALLOCED 256
    Pointer		_args[NUM_TASKS_ALLOCED];
    PFI			_funcs[NUM_TASKS_ALLOCED];
    int			_repeats[NUM_TASKS_ALLOCED];
    Pointer		*args	= _args;
    PFI			*funcs	= _funcs;
    int			*repeats = _repeats;
    int			status;
    WorkIndex 		_ilist[NUM_TASKS_ALLOCED];
    WorkIndex 		*ilist	= _ilist;
    ErrorCode		ecode;
    char		*emsg;
    
    if (EMPTY)
	return (OK);
    
    POP (tg);
    if (tg->nused == 0)
    {
	ExDestroyTaskGroup (tg);
	return (OK);
    }

    DXMarkTime ("start parallel");
    /*
     * Remember whether or not this is a syncronous task group.
     */

    ecode = DXGetError ();
    emsg  = DXGetErrorMessage ();

    if (ecode != ERROR_NONE || *emsg != '\0')
    {
	if (ecode != ERROR_NONE)
	    DXWarning ("#4840");
	else
	    DXWarning ("#4850");
	
	tg->error = ecode;
	tg->emsg  = _dxf_ExCopyString (emsg);
    }

    tg->sync  = sync;
    todo = tg->nused;

    status = get_status ();

    /*
     * Only bother to sort if the tasks actually have different cost
     * estimates associated with them.
     */
    if (todo > NUM_TASKS_ALLOCED)
    {
	ilist = (WorkIndex *) DXAllocate (todo * sizeof (WorkIndex));
	if (ilist == NULL)
	    goto error;
    }
    task = tg->tasks;
    for (i = 0; i < todo; ++i)
    {
	ilist[i].task = task + i;
	ilist[i].work = task[i].work;
        _dxfCopyContext(&(task[i].taskContext), _dxd_exContext);
    }

    if (tg->minwork != tg->maxwork)
	QUICKSORT (ilist, todo);
#ifdef TASK_TIME
    DXMarkTimeLocal ("finish sort");
#endif

    /*
     * Schedule/Execute the tasks appropriately.
     */
    if (todo > NUM_TASKS_ALLOCED) 
    {
	funcs   = (PFI     *) DXAllocate (todo * sizeof (PFI    ));
	args    = (Pointer *) DXAllocate (todo * sizeof (Pointer));
	repeats = (int     *) DXAllocate (todo * sizeof (int    ));
	if (funcs == NULL || args == NULL || repeats == NULL)
	    goto error;
    }

    totalTodo = 0;
    for (i = 0; i < todo; i++)
    {
	funcs[i] = ExProcessTask;
	args[i] = (Pointer) ilist[i].task;
	totalTodo += (repeats[i] = ilist[i].task->repeat);
    }

    tg->ntodo = totalTodo;

#ifdef TASK_TIME
    DXMarkTimeLocal ("queue all tasks");
#endif
    _dxf_ExRQEnqueueMany (todo, funcs, args, repeats, (long) tg, -1, FALSE);
#ifdef TASK_TIME
    DXMarkTimeLocal ("queued all tasks");
#endif

    if (funcs != _funcs)
	DXFree ((Pointer)funcs);
    if (args != _args)
	DXFree ((Pointer)args);
    if (repeats != _repeats)
	DXFree ((Pointer)repeats);
    if (ilist != _ilist)
	DXFree ((Pointer)ilist);

    if (! sync)
    {
	ret = OK;
    }
    else 
    {
        int knt;

#ifdef TASK_TIME
	DXMarkTimeLocal ("tasks enqueued");
#endif

        while (_dxf_ExRQDequeue());
	
	DXlock(&tg->lock, DXProcessorId());
	while (tg->ntodo)
	    DXwait(&tg->wait, &tg->lock);
	DXunlock(&tg->lock, DXProcessorId());

	DXMarkTimeLocal ("joining");

	set_status (status);

	ret = (tg->error == ERROR_NONE) ? OK : ERROR;
	if (ret != OK)
	    DXSetError (tg->error, tg->emsg? tg->emsg: "#8360");

	ExDestroyTaskGroup (tg);
    }

    DXMarkTime ("end parallel");
    return (ret);

error:
    if (funcs != _funcs)
	DXFree ((Pointer) funcs);
    if (args != _args)
	DXFree ((Pointer) args);
    if (repeats != _repeats)
	DXFree ((Pointer) repeats);
    if (ilist != _ilist)
	DXFree ((Pointer) ilist);
    return (ret);
}


void _dxf_ExPrintTask (EXTask t)
{
    DXMessage ("%08x:  [%08x] (* %08x) (%08x) = [%08x ...] %g",
	     t, t->tg, t->func,
	     t->arg ? t->arg : t->data,
	     t->arg ? * ((int *) t->arg) : * ((int *) t->data),
	     t->work);
}


void _dxf_ExPrintTaskGroup (EXTaskGroup tg)
{
    int		i;

    DXMessage ("%08x:  %08x %08x %2d/%2d %g:%g %c %2d/%s",
	     tg, tg->link, tg->tasks,
	     tg->nused, tg->nalloc,
	     tg->minwork, tg->maxwork,
	     tg->sync ? 'S' : 'A',
	     tg->error, tg->emsg);

    for (i = 0; i < tg->nused; i++)
	_dxf_ExPrintTask (tg->tasks + i);
}


typedef struct
{
    lock_type	lock;
    wait_type	wait;
    int		done;			/* set to true when job is done */

    PFE		func;			/* function to call on processor*/
    Pointer	arg;			/* argument block for the func	*/
    int		size;			/* size of allocated argument	*/
    ErrorCode	code;			/* returned error code		*/
    char	*emsg;			/* returned error message	*/
} _EXROJob, *EXROJob;


static Error ExRunOnWorker (EXROJob job, int n)
{
    DXResetError ();
    (* job->func) (job->arg);
    job->code = DXGetError ();
    job->emsg = _dxf_ExCopyString (DXGetErrorMessage ());
    DXlock(&job->lock, DXProcessorId());
    job->done = 1;
    DXsignal(&job->wait);
    DXunlock(&job->lock, DXProcessorId());
    return (OK);
}


/*
 * If the size is set to 0 then just pass a pointer as the argument, no
 * need to construct the argument block.
 */

Error _dxf_ExRunOn (int JID, PFE func, Pointer arg, int size)
{
    EXROJob		job	= NULL;
    ErrorCode		ecode;
#if solaris
    int			cnt = 0;
#endif

    DXResetError ();
    if (taskNprocs == 1 || JID == DXProcessorId())
	return ((* func) (arg));
    
    job = (EXROJob) DXAllocate (sizeof (_EXROJob));
    if (job == NULL)
	goto error;
    job->func = func;
    job->arg  = size > 0 ? DXAllocate (size) : arg;
    job->size = size > 0 ? size : 0;
    job->code = ERROR_NONE;
    job->emsg = NULL;

    if (job->size > 0)
    {
	if (job->arg == NULL)
	    goto error;
	memcpy (job->arg, arg, size);
    }
    
    if (JID < 0)
	JID = 0;
    if (JID > taskNprocs)
	JID = taskNprocs;

    DXcreate_lock(&job->lock, "Job");
    DXcreate_wait(&job->wait, "Job");

    DXlock(&job->lock, DXProcessorId());
    job->done = 0;

    _dxf_ExRQEnqueue (ExRunOnWorker, (Pointer) job, 1, 0, JID, TRUE);

    while (job->done == 0)
	DXwait(&job->wait, &job->lock);

    DXunlock(&job->lock, DXProcessorId());

    DXdestroy_lock(&job->lock);
    DXdestroy_wait(&job->wait);

    ecode = job->code;
    if (ecode != ERROR_NONE)
	DXSetError (ecode, job->emsg);
    
    if (job->size > 0)
	DXFree ((Pointer) job->arg);
    DXFree ((Pointer) job->emsg);

    DXFree ((Pointer) job);

    return (ecode == ERROR_NONE ? OK : ERROR);

error:
    if (job && job->size > 0)
	DXFree ((Pointer) job->arg);
    DXFree ((Pointer) job);
    DXErrorReturn (ERROR_INTERNAL, "_dxf_ExRunOn:  can't DXAllocate");
}


Error
_dxf_ExRunOnAll (PFE func, Pointer arg, int size)
{
    int		i;
    Error	ret=OK;

    for (i = 0; i < taskNprocs; i++)
    {
	ret = _dxf_ExRunOn (i + 1, func, arg, size);
	if (ret != OK)
	    break;
    }

    return (ret);
}
