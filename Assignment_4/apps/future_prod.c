#include<prodcons.h>

uint future_prod(future *fut) {

	int i, j, result;
	j = (int)fut;
	
	for (i=0; i<1000; i++) {
		j += i;
	}
	result = future_set(fut, &j);
	if(result == OK){
		return OK;
	}
	return SYSERR;
}
