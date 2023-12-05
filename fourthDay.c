#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUMS 100

typedef struct {
    int beforePipe[MAX_NUMS];
    int afterPipe[MAX_NUMS];
    int beforePipeSize;
    int afterPipeSize;
} Card;

void initCard(Card *card) {
    card->beforePipeSize = 0;
    card->afterPipeSize = 0;
}



void parse(const char *buffer, int * sum) {
    Card card;
    initCard(&card);
    const char *ptr = buffer;

    while(*ptr != ':') ++ptr;
    ++ptr;

     while(*ptr != '|'){
         if(*ptr == ' '){
             ++ptr;
             continue;
         }
         if(sscanf(ptr, "%d", &card.beforePipe[card.beforePipeSize])){
             while (*ptr && *ptr != ' ') {
                 ++ptr;
             }
             ++card.beforePipeSize;
             continue;
         }else{
             ++ptr;
             continue;
         }
     }
     ++ptr;
     while(*ptr != '\n'){
         if(*ptr == ' '){
             ++ptr;
             continue;
         }
         if(sscanf(ptr, "%d", &card.afterPipe[card.afterPipeSize])){
             while (*ptr && *ptr != ' ') {
                 if(*ptr == '\n'){
                     break;
                 }
                 ++ptr;
             }
             ++card.afterPipeSize;
             continue;
         }else{
             ++ptr;
             continue;
         }
     }

    int temp_sum = 0;
    for(int i = 0; i < card.beforePipeSize; ++i){
        for(int j = 0; j < card.afterPipeSize; ++j){
            if(card.beforePipe[i] == card.afterPipe[j]){
                if(temp_sum == 0){
                    temp_sum = 1;
                    break;
                }
                temp_sum *= 2;
                break;
            }
        }
    }
    *sum += temp_sum;
}

int main(){
    int sum = 0;
    bool found = false;
    while(true){
        size_t size = 20;
        char * buffer = (char*)calloc(size, sizeof(char));
        int len = 0, read;
        while(true){
            read = getline(&buffer, &size, stdin);
            if(read == 1){
                found = true;
                break;
            }
            len += read;
            if(buffer[len - 1] == '\n'){
                break;
            }
            size *= 2;
            buffer = (char*)realloc(buffer, size * sizeof(char));
        }
        if(found == true){
            free(buffer);
            break;
        }
        parse(buffer, &sum);
        free(buffer);
    }
    printf("%d\n", sum);
    return 0;
}
