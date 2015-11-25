#include <future.h> 

/* if future has value return */
syscall future_get(future *f, int *value){
	
	intmask	mask;
	
	mask=disable();
	 if (f->state == FUTURE_VALID){
   	 	*value = f->value;
		restore(mask);
    		return OK;
 	 }

	if(f->state == FUTURE_EMPTY){
		
		f->state=FUTURE_WAITING;
		f->tid=currpid;
		/*can be used to wait while producer produces value in future
		//fwait(f);
		//*value = f->value;*/
		restore(mask);
		return SYSERR;
	}

 	restore(mask);
  	return SYSERR;
}
