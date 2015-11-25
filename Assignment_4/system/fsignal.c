/* fsignal.c - fsignal */

#include <future.h> 	
/*------------------------------------------------------------------------
 *  fsignal  -  Signal a semaphore, releasing a process if one is waiting
 *------------------------------------------------------------------------
 */
syscall	fsignal(
	  future *f			/* future to be signaled	*/
	)
{
	intmask mask;			/* Saved interrupt mask		*/
	struct procent *prptr;

	mask = disable();

	if (f->state == FUTURE_EMPTY){
		restore(mask);
		return SYSERR;
	}

	if(f->tid > 0){
		prptr = &proctab[f->tid];
		prptr->prstate = PR_READY;
		insert(f->tid, readylist, prptr->prprio);
		//ready(f->tid);		/* add process waiting in future to ready queue */
		resched();
	}

	restore(mask);
	return OK;
}
