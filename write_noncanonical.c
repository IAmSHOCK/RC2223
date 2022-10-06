

#include "macros.h"
#include "write_noncanonical.h"
#include "stateMachine.h"

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
    printf("Connection failed\n");
    exit(0);
  }
  printf("Attempt number = %d\n", attempts);
  callAlarm();
}


int trama_flag = 0;


int llwrite(int fd, unsigned char * buff, int length) {
  // TODO: falta implementar o timer e o contador de tentativas

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

    switch (c)
    {
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
