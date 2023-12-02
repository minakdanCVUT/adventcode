#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void addsum(long * sum, const char * buffer, const int * size){
    bool firstDigit = false;
    int lastDigit = 0;
    for(int i = 0; i < *size; ++i){
        if(firstDigit == false){
            if(buffer[i] >= '1' && buffer[i] <= '9'){
                *sum += ((buffer[i] - '0') * 10);
                firstDigit = true;
            }
        }
        if(buffer[i] >= '1' && buffer[i] <= '9'){
            lastDigit = buffer[i] - '0';
        }
    }
    *sum += lastDigit;
}

int main(void){
    bool found = false;
    long sum = 0;
    while (true) {
        size_t size = 10;
        char * buffer = (char*)calloc(size, sizeof(char));
        int read, len = 0;
        while (true) {
            read = getline(&buffer, &size, stdin);
            if (read == -1) {
                found = true;
                break;
            }
            len += read;
            if (buffer[len - 1] == '\n'){
                len--;
                break;
            }
            size *= 2;
            buffer = (char *)realloc(buffer, size);
        }
        addsum(&sum, buffer, &len);
        free(buffer);
        if(found == true){
            break;
        }
    }
    printf("%ld\n", sum);
    return 0;
}
