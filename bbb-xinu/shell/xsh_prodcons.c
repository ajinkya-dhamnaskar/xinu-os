#include <prodcons.h>

#define MAX_COUNT 2000

int n;                            //Definition for global variable 'n'
future *f_exclusive, *f_shared, *f_queue;     		//Defination for futures
sid32 consumed, produced;	//semaphores

int isNumeric(const char *str){
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

   /*Now global variables will be on Heap so they are accessible to all the processes i.e. consume and produce*/

   shellcmd xsh_prodcons(int nargs, char *args[])
   {
      //Argument verifications and validations
	if(nargs > 2){
		printf("Too many arguments.\nType prodcons --help for details.\n");
		return 0;
	}

	//initialize count to default value
	int count = MAX_COUNT;

	/*if there are command line args check if user has asked for help
	*if not check if user has provided valid input ((int) count and greater than 0)
	*else terminate execution 
	*/

	if (nargs == 2) {

		if(strncmp(args[1], "--help", 7) == 0){
			printf("Description:\n");
			printf("\t--help\t display this help and exit\n");
			printf("\t-f \t execute futures\n");
			printf("\t\t by default it will execute producer-consumer.\n");
			printf("Arguments in case of producer-consumer:\n");
			printf("\tmax value of shared variable (integer){default value is 2000}\n");
			return 0;
		}

			if(strncmp(args[1], "-f", 3) == 0){

			f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
			f_shared = future_alloc(FUTURE_SHARED);
			f_queue = future_alloc(FUTURE_QUEUE);
					 
			// Test FUTURE_EXCLUSIVE
			resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
			resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
			sleep(1);
			// Test FUTURE_SHARED
			resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
			resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
			resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
			resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
			resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );
			sleep(1);
			// Test FUTURE_QUEUE
			resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
			resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
			resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
			resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
			
			
			return 0;		

		}else{

			//check args[1](integer) if present assign value to count
			if(!isNumeric(args[1])){
				printf("Invalid argument.\nType prodcons --help for details.\n");
				return 0; 
			}
			count = (atoi)(args[1]);

			//if command line count is 0 terminate. 
			if(count == 0){
				printf("Nothing to produce.\n");
				return 0;	
			}			
		}
	}

	n=0;	
	
	/*Initialise semaphores*/
	produced = semcreate(0);
	consumed = semcreate(1);            

	//create the process produer and consumer and put them in ready queue.
	//Look at the definations of function create and resume in exinu/system folder for reference.      
	resume( create(producer, 1024, 20, "producer", 1, count) );
	resume( create(consumer, 1024, 20, "consumer", 1, count) );

	return 0;
   }
