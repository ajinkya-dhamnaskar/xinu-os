
#include <future.h> 
/*
* using the future_flags as an index
*/



future* future_alloc(int future_flags){
	
	future *f;	
	intmask	mask;
	mask=disable();	
	
	f=(future *)getmem(sizeof(future));

	f->value = (int *)getmem(sizeof(int));
		
	f->state = FUTURE_EMPTY;
	f->flag = future_flags;

	if(future_flags != FUTURE_EXCLUSIVE){
		if(future_flags != FUTURE_SHARED){
			queue *setq;
			setq = (queue *)getmem(sizeof(queue));
			setq->front = 0;
			setq->rear = -1;
			setq->count=0;
			f->set_queue = setq;
		}
		queue *getq;
		getq = (queue *)getmem(sizeof(queue));
		getq->front = 0;
		getq->rear = -1;		
		getq->count=0;			
		f->get_queue = getq;
	}	
	restore(mask);
	return f;
}
