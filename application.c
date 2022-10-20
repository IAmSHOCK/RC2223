
 
  #include <stdio.h>
  #include "link_layer.h"

  #define MAX_PAYLOAD_SIZE 1000

 long int findSize(char fileName[]) {
     FILE* fp =fopen(fileName, "r");
     if (fp == NULL) {
         printf("File not found!\n");
         return -1;
     }
     fseek(fp, 0L, SEEK_END);
     long int fileSize = ftell(fp);
     fclose(fp);
  
     return fileSize;
 }

int nBytes_to_represent(int n) {
  int i = 0;
  while (n > 0) {
    n = n >> 8;
    i++; 
  }
  return i;
}

 }
 int controlPackage(unsigned char* arr, unsigned char controlByte, int fileSize, char* fileName) {
     
     int size = findSize(fileName);
     
     char arr[MAX_PAYLOAD_SIZE];
     int aux = fileSize;
     arr[0] = controlByte;
     arr[1] = 0x00;
     arr[2] = size;
     for (int i = 0; i < size; ++i) {
        arr[3+i] = aux % 256;
        aux /= 256:
     }
     
     int nxt = 3 + n;
     arr[nxt] = 0x01;
     arr[nxt+1] = strlen(fileName) + 1); // 4
     int l = strlen(fileName +1);
     for (int j = 0; j < strlen(fileName) +1; j++) { // x = 2;
        arr[nxt + 2 + j] = fileName[j];
     }
     return 1;
  
   //llwrite();
 }

void dataPacket(char* buf, int* dataLength) {
 
    unsigned char *dataPacket = (unsigned char *)malloc((*sizeOfFragment) + 4);
    char *data = (char *)malloc(dataLength);
    memcpy(data, dataPacket, dataLength);
 
    unsigned char c = 0x01;
    int n = 0 % 255;
    int l1 = *dataLength % 256;
    int l2 = *dataLength / 256;
    
    dataPacket[0] = c;
    dataPacket[1] = n;
    dataPacket[2] = l1;
    dataPacket[3] = l2;
    
    for (int i = 0; i < dataLength; i++) {
       dataPacket[i+4] = data[i];
    }
 
    free(data);
 
    
 
}
void sendifle(char file_name[]) {
    startPackage();
    while (file_name != EOF) {

    }   

    endPackage();
}








/*
in the reciever:
-if an error in BCC1 is detected, print on the screen "error in the protocol"
-if an error in bcc2 is detected, print on the sceen "error in the data"
-if a duplicate frame is detected, print "duplicate frame"
 
in the transmitter:
-if a REJ frame is detected, print on the screen "REJ recieved"
-if a time-out occurs, print on the screen "time-out"
*/
