/* queue.c - enqueue, dequeue */

#include <f_queue.h>


/*------------------------------------------------------------------------
 *  feq  -  Insert a process at the rear end of a queue
 *------------------------------------------------------------------------
 */
pid32	feq(
	  pid32		pid,	/* ID of process to insert	*/
	  queue* q		/* ID of queue to use		*/
	)
{
	
	if(q->count == QUEUE_SIZE){
		return (pid32)SYSERR;
	}

	q->rear = (q->rear + 1)%QUEUE_SIZE;
	q->parray[q->rear] = pid;
	q->count++;

	return pid;
}


/*------------------------------------------------------------------------
 *  fdq  -  Remove and return the front of a queue
 *------------------------------------------------------------------------
 */
pid32	fdq(
	  queue* q	/* ID of queue to use		*/
	  
	)
{
	if(q->count == 0){
		return (pid32)SYSERR;
	}
	pid32 pid;
	pid = q->parray[q->front];
	q->front = (q->front + 1)%QUEUE_SIZE;
	q->count--;
	return pid;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the front of a queue
 *------------------------------------------------------------------------
 */
int	fisempty(
	  queue* q	/* ID of queue to use		*/	  
	)
{
	if(q->count == 0){
		return 1;
	}
	return 0;
}
