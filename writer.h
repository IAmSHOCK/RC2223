#ifndef WRITER_H_
#define WRITER_H_

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

#define CTRL_C_START 0x02
#define CTRL_C_END 0x03

void callAlarm();
void timeout();

// Data Link Layer Functions

int llopenW(int porta, int status);

int llwrite(int fd, char *buffer, int length);

// Global variables
extern int finalSize;
extern unsigned char *finalMessage;
extern int fd_w;
int llwriteW(int fd, unsigned char *startOfFile, int finalSize);

// Application Layer Functions

unsigned char getBCC2(unsigned char *mensagem, int size);
unsigned char *stuffBCC2(unsigned char BCC2, int *sizeOfBCC2);

void llcloseW(int fd);

#endif
