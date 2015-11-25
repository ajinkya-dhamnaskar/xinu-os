#include <future.h> 

/* if future has value return */
syscall future_get(future *f, int *value){
	
	intmask	mask;
	mask=disable();
	pid32 pr;	
	
	if (f->state == FUTURE_VALID){
		f->state=FUTURE_EMPTY;
   	 	*value = *f->value;
		restore(mask);
    		return OK;
 	}
	
	if(f->state == FUTURE_EMPTY){
		
		f->state=FUTURE_WAITING;
		
		if(f->flag == FUTURE_EXCLUSIVE){
			f->pid=currpid;
			suspend(f->pid);
			*value = *f->value;
			f->state=FUTURE_EMPTY;
			restore(mask);
			return OK;
		
		}else if(f->flag == FUTURE_SHARED){	
			pr = feq(currpid, f->get_queue);
			if(pr == (pid32) SYSERR){
				restore(mask);
				return SYSERR;
			}				
			suspend(currpid);
			*value = *f->value;
			restore(mask);
			return OK;	
		
		}else if(f->flag == FUTURE_QUEUE){
			
			if(!fisempty(f->set_queue)){
				*value = *f->value;
				resume(fdq(f->set_queue));
			}else{	
				f->state=FUTURE_WAITING;
				pr = feq(currpid, f->get_queue);
				if(pr == (pid32) SYSERR){
					restore(mask);
					return SYSERR;
				}				
				suspend(currpid);
				*value = *f->value;				
			}
			restore(mask);
			return OK;	
		}
	}

	if(f->flag == FUTURE_SHARED && f->state==FUTURE_WAITING){
		pr = feq(currpid, f->get_queue);
		if(pr == (pid32) SYSERR){
			restore(mask);
			return SYSERR;
		}	
		suspend(currpid);
		*value = *f->value;
		restore(mask);
		return OK;	
	}

	if(f->flag == FUTURE_QUEUE && f->state==FUTURE_WAITING){
		if(!fisempty(f->set_queue)){
			resume(fdq(f->set_queue));
		}else{
			pr = feq(currpid, f->get_queue);
			if(pr == (pid32) SYSERR){
				restore(mask);
				return SYSERR;
			}	
			suspend(currpid);
			*value = *f->value;
		}
		
		restore(mask);
		return OK;	
	}


 	restore(mask);
  	return SYSERR;
}
