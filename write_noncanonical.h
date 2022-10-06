
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <signal.h>

unsigned char* message;
int message_size;
int fd;

int llopen_writer();
void callAlarm();
void timeout();
int llwrite(int fd, unsigned char * buff, int length);
