
 
  #include <stdio.h>
 long int findSize(char file_name[]) {
     FILE* fp =fopen(file_name, "r");
     if (fp == NULL) {
         printf("File not found!\n");
         return -1;
     }
     fseek(fp, 0L, SEEK_END);
     long int res = ftell(fp);
     fclose(fp);
  
     return res;
 }

long int convertSize(file_name) {
    a =findSize(file_name);
    char c = a + '0';
    size = sizeof(c);
    return size;
 }

 long int convertHexa(int res) {
  binary_size = convertSize(file_name);
  char hexaDeciNum[];
  int i = 0;
  while(n !=0) {
    int temp = 0;
    temp = n % 16;
    
    if (temp < 10) {
      hexaDeciNum[i] = temp +48;
      i++;
    }
    else {
      hexaDeciNum[i] = temp +55;
      i++;
    }
    n = n / 16;
    
    int i = atoi(hexaDeciNum);
    return i;
  }

 }
 void startPackage() {
     size = convertSize(res);
     hexaSize = convertHexa(res);
     char arr[];
     arr[0] = 2;
     if(arr[1] = 0) {
        arr[4] = 1;
     }
     arr[2] = size;
     arr[3] =hexaSize;

     //missing arr[5] & arr[6];  

     else if(arr[1] = 1) {
        arr[4] = 4;
     }

    //missing arr[2] & arr[3];  

     arr[5] = size;
     arr[6] =hexaSize;

 }

 void endPackage() {
     size = convertSize(res);
     hexaSize = convertHexa(res);
     char arr[];
     arr[0] = 3;
     if(arr[1] = 0) {
        arr[4] = 1;
     }
     arr[2] = size;
     arr[3] =hexaSize;

     //missing arr[5] & arr[6];  

     else if(arr[1] = 1) {
        arr[4] = 4;
     }

    //missing arr[2] & arr[3];  

     arr[5] = size;
     arr[6] =hexaSize;

 }

void sendifle(char file_name[]) {
    startPackage();
    while (file_name != EOF) {

    }   

    endPackage();
}

