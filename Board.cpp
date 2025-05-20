#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<ctime>
#include<SDL_image.h>

#include"UI.h"
#include"Move.h"
#include"Animation.h"
#include"Board.h"

void DrawBoard(SDL_Renderer* renderer, Tile board[4][4]) {
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_RenderClear(renderer);

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            SDL_Rect rect = {j*100, i*100+100, 90, 90};
            if(board[i][j].value != 0) {

                SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
            else {

                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}


bool IsGameOver(Tile board[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(board[i][j].value == 0) return false;
            if(i < 3 && board[i][j].value == board[i+1][j].value) return false;
            if(j < 3 && board[i][j].value == board[i][j+1].value) return false;
        }
    }
    return true;
}



void addRandomTile(Tile board[4][4]) {
    int emptyTiles[16][2];
    int count = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if (board[i][j].value == 0) {
                emptyTiles[count][0] = i;
                emptyTiles[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int index = rand() % count;
        board[emptyTiles[index][0]][emptyTiles[index][1]].value = (rand() % 10 < 9) ? 2 : 4;
    }
}
void initializerBoard(Tile board[4][4]) {
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            board[i][j] = Tile();
    srand(time(0));
}

int updateScore(Tile prevBoard[4][4], Tile newBoard[4][4])
{
    int score = 0;
    for(int i = 0;i < 4; i++){
        for(int j = 0;j < 4; j++){
            if(newBoard[i][j].value != 0 &&
               newBoard[i][j].value != prevBoard[i][j].value &&
               newBoard[i][j].justMerged){
                   score += newBoard[i][j].value;
            }
        }
    }
    return score;
}

