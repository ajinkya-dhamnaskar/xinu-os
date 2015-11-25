/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <stdio.h>
#define MAX_ARGS 2
/*------------------------------------------------------------------------
* xsh_hello - First XINU command 
*------------------------------------------------------------------------
*/

int displayHello(int noOfArgs, char *args[]);

shellcmd xsh_hello(int nargs, char *args[]){

  if (nargs == 2 && strncmp(args[1], "--help", 6) == 0) {
    printf("Use: %s [file...]\n\n", args[0]);
    printf("Description:\n");
    printf("\tFirst xinu command\n");
    printf("Options:\n");
    printf("\tAccepts one commandline arguement\n");
    return 0;
  }
  return displayHello(nargs, &args[0]);
}

/*
*function name:displayHello
*params: 1. noOfArgs - number of arguments passed with the command (with 0th element being the command itself)
*        2. *args[] - pointer to (argument)char array
*args[0]:hello
*args[1]....args[n] command line args
*n:max number of parameter
*/

int displayHello(int noOfArgs, char *args[]){
  
  if (noOfArgs == MAX_ARGS){
    int i;
    printf("Hello,");
    for(i = 1; i < MAX_ARGS; i++){
     printf(" %s", args[i]);
    } 	
    printf(" Welcome to the world of Xinu!!\n");

  }else if (noOfArgs > MAX_ARGS){	
    printf("Too many arguements\n");

  }else{
    printf("Not enough arguements\n");
  }

  return 0;

}
