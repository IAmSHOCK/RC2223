#ifndef DATA_LINK_H_
#define DATA_LINK_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include "macros.h"
#define BAUDRATE B38400
#define TRANSMITTER 0
#define RECEIVER 1
#define BER 0.9

typedef struct{
    char * port; /*Dispositivo /dev/ttySx, x = 0, 1*/
    int baudRate; /*Velocidade de transmissão*/
    int status;
    struct termios oldPortSettings;
    int n_wrong_packets;
} LinkLayer;
extern LinkLayer link_layer;

int setTermios(int fd);

int sendControlField(int fd, unsigned char controlField);

void set_n_wrong_packets(int n);

#endif
