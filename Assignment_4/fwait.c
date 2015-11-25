/* wait.c - wait */

#include <future.h>
/*------------------------------------------------------------------------
 *  wait  -  Cause current process to wait on a semaphore
 *------------------------------------------------------------------------
 */
syscall	fwait(
	  future *f		/* future in which to wait  */
	)
{
	intmask mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/

	mask = disable();

	if(f->state != FUTURE_EMPTY){
		restore(mask);
		return SYSERR;	
	}

	prptr = &proctab[currpid];
	prptr->prstate = PR_WAIT;
	
	f->tid = currpid;
	f->state=FUTURE_WAITING;		

	resched();			/*   and reschedule	*/

	restore(mask);
	return OK;
}
