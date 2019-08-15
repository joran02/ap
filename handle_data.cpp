#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/inotify.h>


int handle_file(char * filename)
{
	printf("handle_file = %s\n",filename);
	return 0;
}
