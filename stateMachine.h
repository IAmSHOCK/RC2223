#ifndef STATEMACHINE_H
#define STATEMACHINE_H

int stateMachine(unsigned char c, int curr_state, unsigned char control_tram[]);
unsigned char writer_readMessage(int fd,unsigned char * ctrl);
unsigned char reader_readMessage(int fd,unsigned char * ctrl);
#endif