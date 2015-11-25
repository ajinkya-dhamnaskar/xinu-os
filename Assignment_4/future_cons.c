#include<prodcons.h>

uint future_cons(future *fut) {

	int i, status;
	
	/*uncomment below line to run with fsignal anf fwait
	status = future_get(fut, &i);*/

	/*as suggested this code follows busy waiting 
	*same can be implemented with resched() which is implemented and commented for now*/
	/*if (status < 1) {
		printf("future_get failed\n");
		return -1;
	}*/
	while(1){
		status = future_get(fut, &i);
		if(status == OK){
			break;
		}
	}

	status = future_get(fut, &i);

	printf("it produced %d (Consumer PID : %d)\n", i, currpid);

	future_free(fut);

	return OK;
}
