#include <future.h> 
/* if future does not have value set */
syscall future_set(future *f, int *i) {
	
	intmask	mask;
	mask=disable();
	if (f->state == FUTURE_EMPTY){
	
		f->value = *i;
		f->state = FUTURE_VALID; 
		restore(mask);
		return OK; 
	} 	

	if(f->state == FUTURE_WAITING){
		f->value = *i;
		printf("Producer (PID : %d) signaling Consumer (PID : %d) \n", currpid, f->tid);
		f->state=FUTURE_VALID;
		/*signal can be used to notify consumer 		
		//fsignal(f);*/
		restore(mask);
		return OK;
	}
	restore(mask);
	return SYSERR;
}
