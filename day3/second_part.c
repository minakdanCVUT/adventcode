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


void findNumber(char * buffer, Number ** numbers, int * capacityNumber, int * sizeNumber, int capacityInput){
    const char *ptr = buffer;
    int iterator = 0;
    while(*ptr != '\n'){
        if(*ptr < '0' || *ptr > '9'){
            ++iterator;
            ++ptr;
            continue;
        }
        if(sscanf(ptr, "%d", &(*numbers)[*capacityNumber].value)){
            (*numbers)[*capacityNumber].y_position = capacityInput;
            while(*ptr && *ptr >= '0' && *ptr <= '9'){
                ++(*numbers)[*capacityNumber].cntValue;
                if(*ptr == '\n'){
                    break;
                }
                ++iterator;
                ++ptr;
            }
            (*numbers)[*capacityNumber].lastIndex = iterator - 1;
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

void addSumPartTwo(int * sum, Number * numbers, int x_symbol, int y_symbol, int len, int capacityNumbers){
    int count = 0, firstInteger = 0, secondInteger = 0;
    bool firstHave = false;
    for(int i = 0; i < capacityNumbers; ++i){
        if((numbers[i].y_position == y_symbol - 1 && y_symbol - 1 >= 0) || (numbers[i].y_position == y_symbol + 1 && y_symbol + 1 <= len)){
            if(numbers[i].lastIndex + 1 - numbers[i].cntValue <= x_symbol && numbers[i].lastIndex >= x_symbol){ // вертикально
                if(firstHave == false){
                    firstInteger = numbers[i].value;
                    firstHave = true;
                    ++count;
                    continue;
                }
                secondInteger = numbers[i].value;
                ++count;
                continue;
            }
            if(numbers[i].lastIndex == x_symbol - 1){ // по диагонали слева
                if(firstHave == false){
                    firstInteger = numbers[i].value;
                    firstHave = true;
                    ++count;
                    continue;
                }
                secondInteger = numbers[i].value;
                ++count;
                continue;
            }
            if(numbers[i].lastIndex + 1 - numbers[i].cntValue == x_symbol + 1){ // по диагонали справа
                if(firstHave == false){
                    firstInteger = numbers[i].value;
                    firstHave = true;
                    ++count;
                    continue;
                }
                secondInteger = numbers[i].value;
                ++count;
                continue;
            }
        }
        if(numbers[i].y_position == y_symbol){ // горизонтально слева
            if(numbers[i].lastIndex + 1 == x_symbol){
                if(firstHave == false){
                    firstInteger = numbers[i].value;
                    firstHave = true;
                    ++count;
                    continue;
                }
                secondInteger = numbers[i].value;
                ++count;
                continue;
            }
            if((numbers[i].lastIndex + 1 - numbers[i].cntValue) - 1  == x_symbol){ // горизонтально справа
                if(firstHave == false){
                    firstInteger = numbers[i].value;
                    firstHave = true;
                    ++count;
                    continue;
                }
                secondInteger = numbers[i].value;
                ++count;
                continue;
            }
        }
    }
    if(count == 2){
        *sum += firstInteger * secondInteger;
    }
}

void printAnswer(char ** wholeInput, Number *numbers, const int capacityNumber, const int capacityInput, int len) {
    int sum = 0;
    for(int i = 0; i < capacityInput; ++i){
        int iterator = 0;
        while(wholeInput[i][iterator] != '\n'){
            if((wholeInput[i][iterator] < '0' || wholeInput[i][iterator] > '9') && wholeInput[i][iterator] != '.'){
                addSumPartTwo(&sum, numbers, iterator, i, len, capacityNumber);
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
        findNumber(buffer, &numbers, &capacityNumber, &sizeNumber, capacityWholeInput);
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


