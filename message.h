
#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>

#define DATA_SIZE 16
#define CONTINUE 0
#define ACK 1
#define END 2
#define PORT 12343


struct Message {
	double time;
	int loseflag;
};


#endif /* _MESSAGE_H_ */
