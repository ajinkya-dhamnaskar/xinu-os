#include <newmem.h>

int n;
pid32 pid;
sid32 consumed,produced;
struct memblk* memptr;
struct	procent	*prptr;
void getFreeBlocks();

shellcmd xsh_memmgmt(int nargs, char *args[])
{
	/* For argument '--help', emit help about the 'memmgmt' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("use: %s \n\n", args[0]);
		printf("Description:\n");
		printf("\tMemmory statistics\n");
		printf("\tShow free block list\n");
		printf("\tDemonstrate getmem without returning storage\n");
		printf("\tShow maximum stack usage for the process.\n");
		printf("\tDemonstrate getstk without returning storage\n");
		printf("Options:\n");
		printf("\t--help\t\tdisplay this help and exit\n");
		return 0;
	}

	/* Check for valid number of arguments */

	if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	getFreeBlocks();
	int i = (int) getmem(sizeof(int));
	printf("After allocating (int)heap space.\n");
	getFreeBlocks();
	pid = memcreate(test, STACK_SIZE, 20,"test", 0);
	getFreeBlocks();
	prptr = &proctab[pid];
	resume(pid);
	return 0;
}

void getFreeBlocks()
{
	/* Output a heading for the free list */

	printf("Free Blocks:\n");
	printf("Block address  Length (dec) \n");
	printf("-------------  ------------ \n");
	
	for (memptr = memlist.mnext; memptr != NULL; memptr = memptr->mnext) {
		printf("  0x%08x    %9d\n", memptr, memptr->mlength);
	}
	
	printf("\n");
}
