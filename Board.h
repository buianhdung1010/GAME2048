#ifndef Board_H
#define Board_H


void DrawBoard(SDL_Renderer* renderer, Tile board[4][4]);

bool IsGameOver(Tile board[4][4]);

void addRandomTile(Tile board[4][4]);

void initializerBoard(Tile board[4][4]);

int updateScore(Tile prevBroad[4][4], Tile newBoard[4][4]);


#endif
