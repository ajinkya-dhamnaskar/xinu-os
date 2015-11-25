#include <future.h> 
/* if future does not have value set */
syscall future_set(future *f, int *i) {
	
	pid32 pid, enpr;
	
	intmask	mask;
	mask=disable();
	
	if (f->state == FUTURE_EMPTY){
		
		f->value = i;
		f->state = FUTURE_VALID; 
		
		if(f->flag == FUTURE_QUEUE){
			enpr = feq(currpid, f->set_queue);
			if(enpr == (pid32) SYSERR){
				restore(mask);
				return SYSERR;
			}	
			suspend(currpid);
			f->value = i;		
		}	
		restore(mask);
		return OK; 
	} 	

	if(f->state == FUTURE_WAITING){
		
		if(f->flag == FUTURE_EXCLUSIVE){
			f->value = i;			
			f->state=FUTURE_VALID;
			printf("Producer (PID : %d) signaling Consumer (PID : %d) \n", currpid, f->pid);
			resume(f->pid);
			restore(mask);
			return OK;
		
		}else if(f->flag == FUTURE_SHARED){
			f->value = i;			
			f->state=FUTURE_VALID;
			while (!fisempty(f->get_queue))
				resume(fdq(f->get_queue));
			restore(mask);
			return OK;
		}
		else if(f->flag == FUTURE_QUEUE){
			if(!fisempty(f->get_queue)){
				f->value = i;
				//f->state=FUTURE_VALID;
				resume(fdq(f->get_queue));
			}else{
				enpr = feq(currpid, f->set_queue);
				if(enpr == (pid32) SYSERR){
					restore(mask);
					return SYSERR;
				}	
				suspend(currpid);
				f->value = i;
			}
			
			restore(mask);
			return OK;
		}
	}

	restore(mask);
	return SYSERR;
}
