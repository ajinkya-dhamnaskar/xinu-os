#include <prodcons.h>
#include <string.h>
#include <stdlib.h>

/*
* Assign new value to shared variable
*/
 void producer(int count)
 {  
	while(n<=count){

		//display shared varible	
		printf("Produced Value : %d\n", n);
		
		//increment value of shared variable if less than count 
		if(n==count){
			break;			
		}else{
			n++;
		}
	}

	printf("Producer stopped.\n"); 
	return;
 }
