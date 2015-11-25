#include <future.h> 

/* sets state of future to FREE */
syscall future_free(future *f){

  	return freemem((char*)f, sizeof(f));

}
