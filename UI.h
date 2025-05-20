#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Animation.h"


enum GameState {
    MENU,
    PLAYING,
    HOW_TO_PLAY,
    STATISTICS,
    EXIT,
};

void renderNumber(SDL_Renderer* renderer, TTF_Font* font, Tile tile, int x, int y, int size);

void renderBoard(SDL_Renderer* renderer, TTF_Font* font, Tile board[4][4], int startX, int startY, int tileSize);

void renderScore(SDL_Renderer* renderer, TTF_Font* font, int score, int bestScore);

void renderGameOver(SDL_Renderer* renderer);

void renderReplayButton(SDL_Renderer* renderer, const char* imagePath, SDL_Rect buttonRect);

void renderMenu(SDL_Renderer* renderer, GameState& state, const char* menuImagePath);

void showHowToPlay(SDL_Renderer* renderer, const char* imagePath);
#endif

