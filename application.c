
 
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
     long int res = ftell(fp);
     fclose(fp);
  
     return res;
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
 int controlPackage(unsigned char * arr, unsigned char controlByte, int fileSize, char* fileName) {
     
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
 }

void dataPacket() {
}
void sendifle(char file_name[]) {
    startPackage();
    while (file_name != EOF) {

    }   

    endPackage();
}

