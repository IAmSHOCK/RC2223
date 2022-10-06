

#include "macros.h"
#include "write_noncanonical.h"
#include "stateMachine.h"
#include "utilities.h"

#define BAUDRATE B38400
#define _POSIX_SOURCE 1 // POSIX compliant source

#define FALSE 0
#define TRUE 1

#define BUF_SIZE 256

volatile int STOP = FALSE;

unsigned char SET[5];
unsigned char UA[5];

int alarm_flag = 0;
int attempts = 0;
int is_connected = 0;

int llopen_writer()
{
  // TODO: falta implementar o timer e o contador de tentativas

  (void)signal(SIGALRM, timeout);
  unsigned char buf[BUF_SIZE];


  SET[0] = FLAG;
	SET[1] = A_emiter;
	SET[2] = setF;
	SET[3] = SET[1] ^ SET[2];
	SET[4] = FLAG;

	UA[0] = FLAG;
	UA[1] = A_receiver;
	UA[2] = uaF;
	UA[3] = UA[1] ^ UA[2];
	UA[4] = FLAG;

  int bytes;
  if(!is_connected && attempts < MAXATTEMPTS){
    bytes = write(fd, SET, 5);
    alarm(3);
  }
  if (bytes > 0) printf("SET sent\n");

  int curr_state = 0;

  int i = 0;
  while(curr_state < 5){
    int bytes = read(fd, buf+i, 1);
    if (bytes > 0) {
      curr_state = stateMachine(buf[i], curr_state, UA);
    }
  }
  if(curr_state == 5){
    printf("UA received\n");
    is_connected = 1;
    return 0;
  }
  return -1;
}

void callAlarm()
{
  if (!alarm_flag)
    write(fd, SET, 5);
  else
    write(fd, message, message_size);
  alarm(3);
}

void timeout()
{
  //alarm handler
  attempts++;

  if(attempts > MAXATTEMPTS){
    exit(0);
  }
  printf("Attempt number = %d\n", attempts);
  callAlarm();
}


int trama_flag = 0;


int llwrite(int fd, unsigned char *buff, int length) {
  startCounter();
  attempts = 0;
  alarm_flag = 1;
  message = (unsigned char *)malloc((length + 6) * sizeof(unsigned char));
  message_size = length + 6;
  message[0] = FLAG;
  message[1] = A_emiter;
  message[2] = (trama_flag == 0) ? C0 : C1;
  message[3] = message[1] ^ message[2];

  // byte stuffing
  int j = 4;
  for (int i = 0; i < length; i++) {
    unsigned char c = buff[i];

    switch (c) {
    case FLAG:
      // byte stuff FLAG
      message = (unsigned char *)realloc(message, ++message_size);
      message[j] = ESC;
      message[j + 1] = FLAG_STUFF;
      j += 2;
      break;

    case ESC:
      // byte stuff ESC
      message = (unsigned char *)realloc(message, ++message_size);
      message[j] = ESC;
      message[j + 1] = ESC_STUFF;
      j += 2;
      break;
    default:
      message[j] = c;
      j++;
      break;
    }
  }

    int BCC2_size = 1;
    int rej = 0;
    do {
      unsigned char *BCC2Stuffed;
      unsigned char BCC2 = getBCC2(buff, length);
      BCC2Stuffed = stuffing(BCC2, &BCC2_size);
      if (BCC2_size == 1) {
        message[j] = BCC2;
        //printf("BCC2 normal\n");
      }
      else {
        message = (unsigned char *)realloc(message, ++message_size);
        message[j] = BCC2Stuffed[0];
        message[j + 1] = BCC2Stuffed[1];
        j++;
      }

      message[j+1] = FLAG; // end of frame
      write(fd, message, message_size);

      unsigned char CTRL[5];
      CTRL[0] = FLAG;
      CTRL[1] = A_emiter;
      CTRL[2] = RR0; // its not used
      CTRL[3] = CTRL[1] ^ CTRL[2];
      CTRL[4] = FLAG;

      alarm(3);

      unsigned char c = writer_readMessage(fd, CTRL);

      if ((c == RR0 && trama_flag == 1) || (c == RR1 && trama_flag == 0)) {
        rej = 0;
        attempts = 0;
        trama_flag = (trama_flag+1) % 2;
        if(c == RR0){
          printf("RR0 received\n");
        }
        else{
          printf("RR1 received\n");
        }

        break;
      }
      else if ((c == REJ0) || (c == REJ1)) { //rejected
        rej = 1;
        if(c == REJ0){
          printf("REJ0 received\n");
        }
        else if (c == REJ1){
          printf("REJ1 received\n");
        }
      }
      else {
        printf("Invalid data received!\n");
      }
    } while (((!is_connected) && (attempts < MAXATTEMPTS)) || rej);
  printf("Transfer Rate: %.1f Kb/s\n", getTransferRate(length));
}

unsigned char getBCC2(unsigned char *buf, int size)
{
  unsigned char BCC2 = buf[0];
  int i;
  for (i = 1; i < size; i++)
  {
    BCC2 ^= buf[i];
  }
  return BCC2;
}

unsigned char *stuffing(unsigned char c, int *size)
{
  //stuffing of BCC2
  unsigned char *returnValue;
  returnValue = (unsigned char *)malloc(2 * sizeof(unsigned char *));

  switch (c)
  {
  case FLAG:
    returnValue[0] = ESC;
    returnValue[1] = FLAG_STUFF;
    (*size)++;
    break;
  case ESC:
    returnValue[0] = ESC;
    returnValue[1] = ESC_STUFF;
    (*size)++;
    break;
  }

  return returnValue;
}


int main(int argc, char *argv[])
{
  // Program usage: Uses either COM1 or COM2
  const char *serialPortName = argv[1];

  if (argc < 2)
  {
    printf("Incorrect program usage\n"
           "Usage: %s <SerialPort>\n"
           "Example: %s /dev/ttyS1\n",
           argv[0],
           argv[0]);
    exit(1);
  }

  // Open serial port device for reading and writing, and not as controlling tty
  // because we don't want to get killed if linenoise sends CTRL-C.
  fd = open(serialPortName, O_RDWR | O_NOCTTY);

  if (fd < 0)
  {
    perror(serialPortName);
    exit(-1);
  }

  struct termios oldtio;
  struct termios newtio;

  // Save current port settings
  if (tcgetattr(fd, &oldtio) == -1)
  {
    perror("tcgetattr");
    exit(-1);
  }

  // Clear struct for new port settings
  memset(&newtio, 0, sizeof(newtio));

  newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;

  // Set input mode (non-canonical, no echo,...)
  newtio.c_lflag = 0;
  newtio.c_cc[VTIME] = 1; // Inter-character timer unused
  newtio.c_cc[VMIN] = 0;  // Blocking read until 5 chars received

  tcflush(fd, TCIOFLUSH);

  // Set new port settings
  if (tcsetattr(fd, TCSANOW, &newtio) == -1)
  {
    perror("tcsetattr");
    exit(-1);
  }

  printf("New termios structure set\n");
  // In non-canonical mode, '\n' does not end the writing.
  // Test this condition by placing a '\n' in the middle of the buffer.
  // The whole buffer must be sent even with the '\n'.

  int result = llopen_writer();

  close(fd);

  return 0;
}
