#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct{
    int count_red;
    int count_green;
    int count_blue;
}Game;

void init(Game * game){
    game->count_red = 0;
    game->count_blue = 0;
    game->count_green = 0;
}


void parseLine(const char * buffer, const int * len, int * sum){
    Game game;
    init(&game);
    int index = 0, cntNumsIndex = 0, tempCounter = 0;
    for(int i = 5; i < *len; ++i){
        while(buffer[i] != ':'){
            ++cntNumsIndex;
            if(cntNumsIndex > 1){
                index *= 10;
            }
            index += buffer[i] - '0';
            ++i;
        }
        ++i;
        while(buffer[i] != '\n'){
            if(buffer[i] == ' ' || buffer[i] == ',' || buffer[i] == ';'){
                ++i;
                continue;
            }
            int cnt = 0;
            while(buffer[i] >= '0' && buffer[i] <= '9'){
                cnt++;
                if(cnt > 1){
                    tempCounter *= 10;
                }
                tempCounter += buffer[i] - '0';
                ++i;
            }
            if(buffer[i] >= 'a' && buffer[i] <= 'z'){
                if(buffer[i] == 'b'){
                    if(game.count_blue == 0){
                        game.count_blue = tempCounter;
                    }else{
                        if(game.count_blue < tempCounter){
                            game.count_blue = tempCounter;
                        }
                    }
                    tempCounter = 0;
                    i+=4;
                    continue;
                }else if(buffer[i] == 'r'){
                    if(game.count_red == 0){
                        game.count_red = tempCounter;
                    }else{
                        if(game.count_red < tempCounter){
                            game.count_red = tempCounter;
                        }
                    }
                    tempCounter = 0;
                    i+=3;
                    continue;
                }else if(buffer[i] == 'g'){
                    if(game.count_green == 0){
                        game.count_green = tempCounter;
                    }else{
                        if(game.count_green < tempCounter){
                            game.count_green = tempCounter;
                        }
                    }
                    tempCounter = 0;
                    i+=5;
                    continue;
                }
            }
        }
        *sum += (game.count_green * game.count_red * game.count_blue);
    }
}

int main(){
    bool found = false;
    int sum = 0;
    while(true){
        size_t size = 100;
        char * buffer = (char*)calloc(size, sizeof(char));
        int len = 0;
        int read;
        while(true){
            read = getline(&buffer, &size, stdin);
            if(read == -1){
                found = true;
                break;
            }
            len += read;
            if(buffer[len - 1] == '\n'){
                break;
            }
        }
        parseLine(buffer, &len, &sum);
        free(buffer);
        if(found == true){
            break;
        }
    }
    printf("%d\n", sum);
    return 0;
}
