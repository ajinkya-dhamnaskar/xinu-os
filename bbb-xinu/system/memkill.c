/* memkill.c - memkill */

#include <newmem.h>

/*--------------------------------------------------------------------------------------
 *  memkill  -  memkill a process and remove it from the system without releasing stack
 *--------------------------------------------------------------------------------------
 */
syscall	memkill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	int32	i;			/* Index into descriptors	*/
	int stkLen;
	char *stkPtr;
	mask = disable();
	prptr = &proctab[pid];
	stkPtr = prptr->prstkbase;
	stkLen = prptr->prstklen;
	while(stkLen > 0){
		if(*stkPtr == 'A'){
			kprintf("Max Memory location : %d, Stack Base : %d, Total memory usage : %d\n", stkPtr, prptr->prstkbase, prptr->prstkbase-stkPtr);
			break;
		}
		stkPtr--;
		stkLen--;
	}

	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	/*
	do not free up the stack memory used by the process
	*/
	//freestk(prptr->prstkbase, prptr->prstklen);

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
