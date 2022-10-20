#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
int stateMachine(unsigned char c, int curr_state, unsigned char arg[]);

unsigned char readControlMessageW(int fd,unsigned char * ctrl);
unsigned char readControlMessageR(int fd,unsigned char * ctrl);
extern unsigned char SET[5];
extern unsigned char UA[5];
extern unsigned char DISCw[5];
extern unsigned char DISCr[5];
extern unsigned char RRv[5];


#endif
