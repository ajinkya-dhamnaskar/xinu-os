#include <future.h> 

/* sets state of future to FREE */
syscall future_free(future *f){
	intmask mask;
	mask = disable();
	if(f->flag == FUTURE_EXCLUSIVE){		
		freemem((char*)f, sizeof(f));
		freemem((char*)f->value, sizeof(int));
	}else{
		if(f->flag != FUTURE_SHARED){
			freemem((char*)f->set_queue, sizeof(queue));
		}
		freemem((char*)f->get_queue, sizeof(queue));		
		freemem((char*)f->value, sizeof(int));
		freemem((char*)f, sizeof(f));		
	}	
	restore(mask);
  	return OK;

}
