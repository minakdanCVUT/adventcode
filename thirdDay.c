#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int lastIndex;
    int y_position;
    int value;
    int cntValue;
}Number;


void initStruct(Number * number){
    number->value = 0;
    number->cntValue = 0;
}

void findNumber(char * buffer, const int * lenBuffer, Number ** numbers, int * capacityNumber, int * sizeNumber, int capacityInput){
    for(int i = 0; i < * lenBuffer; ++i){
        if(buffer[i] >= '0' && buffer[i] <= '9'){
            initStruct(&(*numbers)[*capacityNumber]);
            (*numbers)[*capacityNumber].y_position = capacityInput;
            while(buffer[i] >= '0' && buffer[i] <= '9'){
                if ((*numbers)[*capacityNumber].cntValue >= 1) {
                    (*numbers)[*capacityNumber].value *= 10;
                }
                (*numbers)[*capacityNumber].value += buffer[i] - '0';
                (*numbers)[*capacityNumber].lastIndex = i;
                ++(*numbers)[*capacityNumber].cntValue;
                ++i;
                if(buffer[i] < '0' || buffer[i] > '9'){
                    if(*capacityNumber + 1 == *sizeNumber){
                        *sizeNumber *= 2;
                        *numbers = (Number*)realloc(*numbers, *sizeNumber * sizeof(Number));
                        ++(*capacityNumber);
                    }else{
                        ++(*capacityNumber);
                    }
                }
            }
        }
    }
}

void addSum(int * sum, Number * numbers, int x, int y, int len, int cap) {
    for(int i = 0; i < cap; ++i){
        if((numbers[i].y_position == y - 1 && y - 1 >= 0) || (numbers[i].y_position == y + 1 && y + 1 <= len)){
            if(numbers[i].lastIndex + 1 - numbers[i].cntValue <= x && numbers[i].lastIndex >= x){ // вертикально
                *sum += numbers[i].value;
                continue;
            }
            if(numbers[i].lastIndex == x - 1){ // по диагонали слева
                *sum += numbers[i].value;
                continue;
            }
            if(numbers[i].lastIndex + 1 - numbers[i].cntValue == x + 1){ // по диагонали справа
                *sum += numbers[i].value;
                continue;
            }
        }
        if(numbers[i].y_position == y){ // горизонтально слева
            if(numbers[i].lastIndex + 1 == x){
                *sum += numbers[i].value;
                continue;
            }
            if((numbers[i].lastIndex + 1 - numbers[i].cntValue) - 1  == x){ // горизонтально справа
                *sum += numbers[i].value;
                continue;
            }
        }
    }
}

void printAnswer(char ** wholeInput, Number *numbers, const int capacityNumber, const int capacityInput, int len) {
    int sum = 0;
    for(int i = 0; i < capacityInput; ++i){
        int iterator = 0;
        while(wholeInput[i][iterator] != '\n'){
            if((wholeInput[i][iterator] < '0' || wholeInput[i][iterator] > '9') && wholeInput[i][iterator] != '.'){
                addSum(&sum, numbers, iterator, i, len, capacityNumber);
                ++iterator;
            }else{
                ++iterator;
            }
        }
    }
    printf("%d\n", sum);
}




int main(){
    int len = 0, read, sizeForWholeInput = 10, capacityWholeInput = 0, constLen = 0;
    char ** wholeInput = NULL;
    int capacityNumber = 0, sizeNumber = 10;
    Number * numbers = (Number*)malloc(sizeNumber * sizeof(Number));
    bool found = false, firstIteration = false;
    while(true){
        size_t size = 20;
        len = 0;
        char * buffer = (char*)calloc(size, sizeof(char));
        while(true){
            read = getline(&buffer, &size, stdin);
            if(read == 1){
                found = true;
                break;
            }
            len += read;
            if(buffer[len - 1] == '\n'){
                --len;
                break;
            }
            size *= 2;
            buffer = (char*)realloc(buffer, size * sizeof(char));
        }
        if(found == true){
            free(buffer);
            break;
        }
        if(firstIteration == false){
            wholeInput = (char**)calloc(sizeForWholeInput, sizeof(char*));
            constLen = len;
            firstIteration = true;
        }
        findNumber(buffer, &len, &numbers, &capacityNumber, &sizeNumber, capacityWholeInput);
        wholeInput[capacityWholeInput] = buffer;
        if(capacityWholeInput + 1 == sizeForWholeInput){
            sizeForWholeInput*=2;
            wholeInput = (char**)realloc(wholeInput, sizeof(char**) * sizeForWholeInput);
            ++capacityWholeInput;
        }else {
            ++capacityWholeInput;
        }
    }
    printAnswer(wholeInput, numbers, capacityNumber, capacityWholeInput, constLen);
    free(numbers);
    free(wholeInput);
    return 0;
}


