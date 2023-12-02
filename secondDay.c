#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
  long sum = 0;
  while(true){
    size_t size = 10;
    char * buffer = (char*)calloc(size, sizeof(char));
    int len = 0, read;
    bool foundEof = false;
    while(true){
      read = getline(&buffer, &size, stdin);
      if(read == -1){
        foundEof = true;
        break;
      }
      len += read;
      if(buffer[len - 1] == '\n'){
        --len;
        break;
      }
      size *= 2;
      buffer = (char *)realloc(buffer, size);
    }
    addsum(&sum, buffer, &len);
    free(buffer);
  }
  printf("%ld\n", sum);
  return 0;
}
