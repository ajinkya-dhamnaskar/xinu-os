
#include <future.h> 
/*
* using the future_flags as an index
*/

future* future_alloc(int future_flags){
	
	future *f;

	f=(future *)getmem(sizeof(future));
	
	if(f == SYSERR){
		return SYSERR;
	}

	f->state = FUTURE_EMPTY;
	f->flag = future_flags;

	return f;
}
