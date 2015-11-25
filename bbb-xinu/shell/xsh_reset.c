#include <xinu.h>
#include <stdlib.h>

shellcmd xsh_reset(int nargs, char *args[])
{
      //Argument verifications and validations

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s [file...]\n", args[0]);
		printf("Description:\n");
		printf("\tReset XINU\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	}
	
	volatile uint32 *prm_rstctrl = (volatile uint32 *) 0x44E00F00;
	*prm_rstctrl = 0x01;
      
      return 0;
}
