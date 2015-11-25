#include <prodcons.h>
#include <stdlib.h>

int n;                 //Definition for global variable 'n'

int isNumeric(const char *str) 
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/

shellcmd xsh_prodcons(int nargs, char *args[])
{
	//local varible to hold count
	int count = 2000;

      	//Argument verifications and validations
	if(nargs > 2){
		printf("Too many arguments.\nType prodcons --help for details.\n");
		return 0;
	}
	
	if (nargs == 2) {
		if(strncmp(args[1], "--help", 7) == 0){
			printf("Use: %s [file...]\n", args[0]);
			printf("Description:\n");
			printf("\tProducer-Consumer problem demo\n");
			printf("\tdisplays garbage data\n");
			printf("\t--help\t display this help and exit\n");
			printf("Arguments:\n");
			printf("\tmax value of shared variable (integer){default value is 2000}\n");
			return 0;
		}

		//int arg= (atoi)(args[1]);
		//check, if command line arg is integer or not
		//if(arg == 0){
		if(!isNumeric(args[1])){
			printf("Invalid argument.\nType prodcons --help for details.\n");
			return 0; 
		}
		count = (atoi)(args[1]);
	}
		
	
	
	//reset shared variable 
	n=0;	  
             	
	//create and schedule producer thread
	resume( create(producer, 1024, 20, "producer", 1, count) );

	//create and schedule consumer thread	
	resume( create(consumer, 1024, 20, "consumer", 1, count) );
	
	return 0;
}
