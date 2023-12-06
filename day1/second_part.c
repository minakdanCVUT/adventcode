#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool checkIf(const char * str, const int index, const char symb, int len){
    if(symb == 't'){
        if(len == 2){
            return (str[index + 1] == 'w' && str[index + 2] == 'o');
        }else if(len == 4){
            return (str[index + 1] == 'h' && str[index + 2] == 'r' && str[index + 3] == 'e' && str[index + 4] == 'e');
        }
    }
    else if(symb == 'o'){
        return (str[index + 1] == 'n' && str[index + 2] == 'e');
    }else if(symb == 'f'){
        return ((str[index + 1] == 'i' && str[index + 2] == 'v' && str[index + 3] == 'e') || (str[index + 1] == 'o' && str[index + 2] == 'u' && str[index + 3] == 'r'));
    }else if(symb == 's'){
        if(len == 2){
            return (str[index + 1] == 'i' && str[index + 2] == 'x');
        }else if(len == 4){
            return (str[index + 1] == 'e' && str[index + 2] == 'v' && str[index + 3] == 'e' && str[index + 4] == 'n');
        }
    }else if(symb == 'e'){
        return (str[index + 1] == 'i' && str[index + 2] == 'g' && str[index + 3] == 'h' && str[index + 4] == 't');
    }else if(symb == 'n'){
        return (str[index + 1] == 'i' && str[index + 2] == 'n' && str[index + 3] == 'e');
    }
    return false;
}

void parse(const char * str, const int len, int * sum){
    bool firstDigit = false;
    int lastIndex = 0, firstIndex = 0;
    for(int i = 0; i < len;){
        if(firstDigit == false) {
            if (str[i] >= '1' && str[i] <= '9') {
                *sum += ((str[i] - '0') * 10);
                firstIndex = str[i] - '0';
                firstDigit = true;
                ++i;
                continue;
            }

            if (str[i] == 'o' && i + 2 < len) {
                if (checkIf(str, i, str[i], 0)) {
                    *sum += 1 * 10;
                    firstIndex = 1;
                    firstDigit = true;
                    i += 2;
                    continue;
                }
            }

            if (str[i] == 't') {
                if (i + 2 < len) {
                    if (checkIf(str, i, str[i], 2)) {
                        *sum += 2 * 10;
                        firstIndex = 2;
                        i += 2;
                        firstDigit = true;
                        continue;
                    }
                }
                if (i + 4 < len) {
                    if (checkIf(str, i, str[i], 4)) {
                        *sum += 3 * 10;
                        firstIndex = 3;
                        i += 4;
                        firstDigit = true;
                        continue;
                    }
                }
            }

            if (str[i] == 'f' && i + 3 < len) {
                if (str[i + 1] == 'o') {
                    if (checkIf(str, i, str[i], 0)) {
                        *sum += 4 * 10;
                        firstIndex = 4;
                        firstDigit = true;
                        i += 3;
                        continue;
                    }
                }
                if (str[i + 1] == 'i') {
                    if (checkIf(str, i, str[i], 0)) {
                        *sum += 5 * 10;
                        firstIndex = 5;
                        firstDigit = true;
                        i += 3;
                        continue;
                    }
                }
            }

            if (str[i] == 's') {
                if (i + 2 < len) {
                    if (checkIf(str, i, str[i], 2)) {
                        *sum += 6 * 10;
                        firstIndex = 6;
                        i += 2;
                        firstDigit = true;
                        continue;
                    }
                }
                if (i + 4 < len) {
                    if (checkIf(str, i, str[i], 4)) {
                        *sum += 7 * 10;
                        firstIndex = 7;
                        i += 4;
                        firstDigit = true;
                        continue;
                    }
                }
            }

            if (str[i] == 'e' && i + 4 < len) {
                if (checkIf(str, i, str[i], 0)) {
                    *sum += 8 * 10;
                    firstIndex = 8;
                    firstDigit = true;
                    i += 4;
                    continue;
                }
            }
            if (str[i] == 'n' && i + 3 < len) {
                if (checkIf(str, i, str[i], 0)) {
                    *sum += 9 * 10;
                    firstIndex = 9;
                    firstDigit = true;
                    i += 3;
                    continue;
                }
            }
        }else{
            if (str[i] >= '1' && str[i] <= '9') {
                lastIndex = str[i] - '0';
                ++i;
                continue;
            }

            if (str[i] == 'o' && i + 2 < len) {
                if (checkIf(str, i, str[i], 0)) {
                    lastIndex = 1;
                    i += 2;
                    continue;
                }
            }

            if (str[i] == 't') {
                if (i + 2 < len) {
                    if (checkIf(str, i, str[i], 2)) {
                        lastIndex = 2;
                        i += 2;
                        continue;
                    }
                }
                if (i + 4 < len) {
                    if (checkIf(str, i, str[i], 4)) {
                        lastIndex = 3;
                        i += 4;
                        continue;
                    }
                }
            }

            if (str[i] == 'f' && i + 3 < len) {
                if (str[i + 1] == 'o') {
                    if (checkIf(str, i, str[i], 0)) {
                        lastIndex = 4;
                        i += 3;
                        continue;
                    }
                }
                if (str[i + 1] == 'i') {
                    if (checkIf(str, i, str[i], 0)) {
                        lastIndex = 5;
                        i += 3;
                        continue;
                    }
                }
            }

            if (str[i] == 's') {
                if (i + 2 < len) {
                    if (checkIf(str, i, str[i], 2)) {
                        lastIndex = 6;
                        i += 2;
                        continue;
                    }
                }
                if (i + 4 < len) {
                    if (checkIf(str, i, str[i], 4)) {
                        lastIndex = 7;
                        i += 4;
                        continue;
                    }
                }
            }

            if (str[i] == 'e' && i + 4 < len) {
                if (checkIf(str, i, str[i], 0)) {
                    lastIndex = 8;
                    i += 4;
                    continue;
                }
            }
            if (str[i] == 'n' && i + 3 < len) {
                if (checkIf(str, i, str[i], 0)) {
                    lastIndex = 9;
                    i += 3;
                    continue;
                }
            }
        }
        ++i;
    }
    if(lastIndex == 0){
        *sum += firstIndex;
    }else {
        *sum += lastIndex;
    }
}
int main(void){
    bool found = false;
    int sum = 0;
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
        parse(buffer, len, &sum);
        free(buffer);
        if(found == true){
            break;
        }
    }
    printf("%d\n", sum);
    return 0;
}
