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