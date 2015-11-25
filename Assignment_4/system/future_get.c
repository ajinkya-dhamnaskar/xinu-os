#include <future.h> 

/* if future has value return */
syscall future_get(future *f, int *value){
	
	intmask	mask;
	mask=disable();
	 if (f->state == FUTURE_VALID){
   	 	*value = f->value;
		f->tid=NULL;
		f->state=FUTURE_EMPTY;
		restore(mask);
    		return OK;
 	 }

	if(f->state == FUTURE_EMPTY){
		f->state=FUTURE_WAITING;
		f->tid=currpid;
		while(f->state != FUTURE_VALID){
			resched();
		}
		*value = f->value;
		restore(mask);
		return OK;
	}

 	restore(mask);
  	return SYSERR;
}
