/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include <dx/dx.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

static int _dxf_locks_enabled = 1;      /*  Enabled, by default  */
static pthread_key_t   tls_key = 0;

void 
DXInitThreadData()
{
    pthread_key_create(&tls_key, NULL);
}

struct dxthread_data *
DXGetThreadData()
{
    if (tls_key)
        return (void *)pthread_getspecific(tls_key);
    else
        return NULL;
}

int
DXGetThreadPid()
{
    struct dxthread_data *tdat = (struct dxthread_data *)DXGetThreadData();
    if (tdat) return tdat->pid;
    else return 0;
}

void
DXSetThreadData(struct dxthread_data *d)
{
    pthread_setspecific(tls_key, (void *)d);
}

void DXenable_locks(int enable)
{
    char *force_locks;

    if ( (force_locks = getenv( "DX_FORCE_LOCKS" )) != NULL ) {
	if ( !force_locks[0] )
	    _dxf_locks_enabled = 1;
	else
	    _dxf_locks_enabled = atoi(force_locks);
    }
    else if ( enable >= 0 )               /*  -1 only checks env var  */
        _dxf_locks_enabled = enable;
}

int _dxf_initlocks(void)
{
    DXenable_locks(-1);
    return OK;
}

int DXcreate_wait(wait_type *w, char *name)
{
    if ( !_dxf_locks_enabled ) 
	return OK;

    pthread_cond_init((pthread_cond_t *)w, NULL);
    return OK;
}

int DXdestroy_wait(wait_type *w)
{
    if ( !_dxf_locks_enabled ) 
	return OK;

    pthread_cond_destroy((pthread_cond_t *)w);
    return OK;
}

void DXbroadcast(wait_type *w)
{
    if ( !_dxf_locks_enabled ) 
	return OK;

    pthread_cond_broadcast((pthread_cond_t *)w);
}

void DXsignal(wait_type *w)
{
    if ( !_dxf_locks_enabled ) 
	return OK;

    pthread_cond_signal((pthread_cond_t *)w);
}

extern int DXGetThreadPid();

void DXwait(wait_type *w, lock_type *l)
{
    if ( !_dxf_locks_enabled ) 
	return OK;

    // pthread_cond_wait((pthread_cond_t *)w, (pthread_mutex_t *)l);
    if (l->pid != DXGetThreadPid())
    {
        fprintf(stderr, "waiting on a lock I don't own?\n");
	abort();
    }
    if (l->locked != 1)
    {
        if (l->locked > 1) fprintf(stderr, "DXwait - locked > 1\n");
        else fprintf (stderr, "DXwait - locked < 1\n");
	abort();
    }
    l->tag = 98;
    l->locked--;
    pthread_cond_wait((pthread_cond_t *)w, &l->lock);
    l->pid = DXGetThreadPid();
    l->tid = pthread_self();
    l->tag = 99;
    l->locked++;
    l->knt++;

}

static int lock_seq = 0;

int DXcreate_lock(lock_type *l, char *name)
{
    if ( !_dxf_locks_enabled ) 
	return OK;

    pthread_mutex_init(&l->lock, NULL);
    l->pid = -1;
    l->tid = -1;
    l->tag = -1;
    l->seq = lock_seq++;
    l->knt = 0;
    l->locked = 0;
    return OK;
}

int DXdestroy_lock(lock_type *l)
{
    if ( !_dxf_locks_enabled ) 
	return OK;

    pthread_mutex_destroy(&l->lock);
    return OK;
}

extern int DXGetThreadPid();

void found_lock() {}

int DXlock(lock_type *l, int who)
{
    int last_who;

    if (l->seq == 512 && l->knt > 2003475)
        found_lock();

    if ( !_dxf_locks_enabled ) 
	return OK;

    last_who = l->tag;

    pthread_mutex_lock(&l->lock);
    l->pid = DXGetThreadPid();
    l->tid = pthread_self();
    l->tag = who;
    l->locked++;
    l->knt++;

    return OK;
}

int DXtry_lock(lock_type *l, int who)
{
    int last_who = l->tag;

    if (l->seq == 512 && l->knt > 2003475)
        found_lock();

    if ( !_dxf_locks_enabled ) 
	return OK;

    if (pthread_mutex_trylock(&l->lock))
	return ERROR;
    else
    {
	if (l->locked != 0)
	{
	    fprintf(stderr, "try_lock gave be a lock in use!\n");
	    abort();
	}
	l->tag = who;
        l->pid = DXGetThreadPid();
        l->tid = pthread_self();
        l->knt++;
	l->locked++;
	return OK;
    }
}

int DXunlock(lock_type *l, int who)
{
    if (l->seq == 512 && l->knt > 2003475)
        found_lock();

    if ( !_dxf_locks_enabled ) 
	return OK;

    if (l->pid != DXGetThreadPid())
    {
        fprintf(stderr, "DXunlock a lock I don't own?\n");
	abort();
    }
    if (l->locked != 1)
    {
        if (l->locked > 1) fprintf(stderr, "DXunlock - locked > 1\n");
        else fprintf (stderr, "DXunlock - locked < 1\n");
	abort();
    }

    int last_who = l->tag;

    if ( !_dxf_locks_enabled ) 
	return OK;


    l->tag = who;
    l->locked--;

    pthread_mutex_unlock(&l->lock);

    return OK;
}

int DXfetch_and_add(int *p, int value, lock_type *l, int who)
{
    int old_value;

    DXlock(l, who);
    old_value = *p;
    *p += value;
    DXunlock(l, who);

    return old_value;
}
