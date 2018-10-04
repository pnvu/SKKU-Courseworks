#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <time.h> 
#include <errno.h>
#include <signal.h>

#include "common.h"

char *mylan;

/* clean up a lan */
void cleanup()
{
  char linkname[MAXSTRING];

  /* unlink the link */
  sprintf(linkname, ".%s.info", mylan);
  unlink(linkname);
    
  exit(0);
}

int main(int argc, char *argv[]){
	/* check usage */
	if (argc != 2) {
    	fprintf(stderr, "usage : %s <my lan name>\n", argv[0]);
    	exit(1);
  	}

  	mylan = strdup(argv[1]);
  	cleanup();
}