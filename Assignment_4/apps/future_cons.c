#include<prodcons.h>

uint future_cons(future *fut) {

	int i, status;
	
	status = future_get(fut, &i);

	if (status < 1) {
		printf("future_get failed\n");
		return -1;
	}

	printf("it produced %d (Consumer PID : %d)\n", i, currpid);

	future_free(fut);

	return OK;
}
