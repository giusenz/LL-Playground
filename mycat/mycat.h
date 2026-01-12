#ifndef MYCAT_H
#define MYCAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

/* Given a message, this function prints it on stderr */
void end(const char *msg);

/* Given a file name, this function reads 
 * the content of the corresponding file and prints it on stdout */
void myread(char *filename);

/* No arguments behaviour */
int toscreen(void);

#endif
