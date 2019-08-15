#include <stdio.h>



#ifndef _FILE_MONITY_h
#define _FILE_MONITY_h

typedef  int (*do_file_monity_callback)(char *filename);

int do_file_monity(const char * path,do_file_monity_callback cb);


#endif 

