#ifndef MOVE_H
#define MOVE_H

#include "Animation.h"
#include<SDL_mixer.h>


bool moveLeft(Tile board[4][4], Mix_Chunk* mergeSound);
bool moveRight(Tile board[4][4], Mix_Chunk* mergeSound);
bool moveUp(Tile board[4][4], Mix_Chunk* mergeSound);
bool moveDown(Tile board[4][4], Mix_Chunk* mergeSound);

#endif
