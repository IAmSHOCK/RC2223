#include "stateMachine.h"
#include "macros.h"


int stateMachine(unsigned char c, int curr_state, unsigned char control_tram[])
{
  // state machine for SET/UA
  switch (curr_state){
  case 0:
    if (c == control_tram[0]){
      curr_state = 1;
    }
    break;
  case 1:
    if (c == control_tram[0]){
      curr_state = 1;
    }
    else if (c == control_tram[1]){
      curr_state = 2;
    }
    else{
      curr_state = 0;
    }
    break;
  case 2:
    if (c == control_tram[0]){
      curr_state = 1;
    }
    else if (c == control_tram[2]){
      curr_state = 3;
    }
    else{
      curr_state = 0;
    }
    break;
  case 3:
    if (c == control_tram[0]){
      curr_state = 1;
    }
    else if (c == control_tram[3]){
      curr_state = 4;
    }
    else{
      curr_state = 0;
    }
    break;
  case 4:
    if (c == control_tram[0]){
      return curr_state = 5;
    }
    else{
      curr_state = 0;
    }
    break;
  }
  return curr_state;
}

unsigned char writer_readMessage(int fd,unsigned char * ctrl){
  int curr_state = 0;
  unsigned char c, returnValue;
  while (curr_state != 5) {
    read(fd, &c, 1);
    switch (curr_state) {
    case 0:
      if (c == ctrl[0]) {
        curr_state = 1;
      }
      break;
    case 1:
      if (c == ctrl[0]) {
        curr_state = 1;
      }
      else if (c == ctrl[1]) {
        curr_state = 2;
      }
      else {
        curr_state = 0;
      }
      break;
    case 2:
      if (c == ctrl[0]) {
        curr_state = 1;
      }
      else if (c == RR0 || c == RR1 || c == REJ0 || c == REJ1 || c == DISC) {
        curr_state = 3;
        returnValue = c;
      }
      else {
        curr_state = 0;
      }
      break;
    case 3:
      if (c == ctrl[0]) {
        curr_state = 1;
      }
      else if (c == (ctrl[1] ^ returnValue)) {
        curr_state = 4;
      }
      else {
        curr_state = 0;
      }
      break;
    case 4:
      if (c == ctrl[0]) {
        curr_state = 5;
        return returnValue;
      }
      else {
        curr_state = 0;
      }
      break;
    default:
      break;
    }
  }
  return returnValue;
}