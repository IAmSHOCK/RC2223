
 
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
 }

long int convertSize(int res) {
    findSize(file_name);
    char c = a + '0';
    size = sizeof(c);
    return size;
 }
 void startPackage() {
     size = convertSize(res);
     char arr[2048];
     arr[0] = 1;
     arr[1] = 0;
     arr[2] = size;
     arr[3] = ;    
 }

void sendifle(char file_name[]) {

    while (file_name != EOF) {

    }   
}

