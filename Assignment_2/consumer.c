#include <prodcons.h>
#include <stdlib.h>

/*
* Consume value generated by producer
* Display value of shared variable 'n'
* Does not perform any operations on 'n' 
n : shared variable
*/
 void consumer(int count)
 {
  
	while(n<=count){
				
		//display shared variable
		printf("Consumed Value : %d\n", n*100);
		
		//if n reaches limit break the loop and exit
		if(n == count) {
			break;			
		}

	}

	printf("Consumer stopped.\n");
	return;
	
 }