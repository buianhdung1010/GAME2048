#include<iostream>
#include<SDL.h>
#include<ctime>
#include<SDL_ttf.h>
#include<cstring>
#include<cmath>
#include<SDL_image.h>
#include<SDL_mixer.h>

#include "Move.h"
#include "UI.h"
#include "Board.h"
#include"Animation.h"
#include"Algorithm.h"
#include"bestcore.h"







int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;
        return -1;
    }
    if (!(IMG_Init(IMG_INIT_PNG))){
            std::cerr<< "IMG_Init failed: " << IMG_GetError() << std::endl;
    }

    TTF_Font* font = TTF_OpenFont("C:/GAME2048/bin/Debug/font.ttf", 32);
    if (!font) {
        std::cout << "Font failed: " << TTF_GetError() << std::endl;
        return -1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        std::cout<< "SDL_Mixer failed: " << Mix_GetError();
    }

    Mix_Chunk* mergeSound = loadSound("C:/GAME2048/bin/Debug/merge.wav");
    Mix_Chunk* gameOverSound = loadSound("C:/GAME2048/bin/Debug/lose.wav");
    Mix_Music* bgm = Mix_LoadMUS("C:/GAME2048/bin/Debug/bgm.mp3");


    SDL_Window* window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 500, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    GameState state = MENU;
    renderMenu(renderer, state, "C:/GAME2048/bin/Debug/Menu.png");




     if (state == HOW_TO_PLAY) {
       showHowToPlay(renderer, "C:/GAME2048/bin/Debug/HowToPlay.png");
       state = MENU;
       renderMenu(renderer, state, "C:/GAME2048/bin/Debug/Menu.png");
     }

    Tile board[4][4];
    initializerBoard(board);
    addRandomTile(board);
    addRandomTile(board);

    bool quit = false;
    bool gameOver = false;
    SDL_Event event;
    SDL_Rect ReplayButton = {118, 330, 150, 50};
    int score = 0;
    int bestScore = loadBestScore();


    Mix_PlayMusic(bgm, -1);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;

            if (!gameOver && event.type == SDL_KEYDOWN) {
                Tile prevBoard[4][4];
                std::memcpy(prevBoard, board, sizeof(board));

                switch (event.key.keysym.sym) {
                     case SDLK_UP:    moveUp(board, mergeSound);    break;
                     case SDLK_DOWN:  moveDown(board, mergeSound);  break;
                     case SDLK_LEFT:  moveLeft(board, mergeSound);  break;
                     case SDLK_RIGHT: moveRight(board, mergeSound); break;
                }
                bool moved = false;
                for (int i = 0; i < 4 && !moved; ++i)
                    for (int j = 0; j < 4 && !moved; ++j)
                        if (prevBoard[i][j].value != board[i][j].value)
                            moved = true;

                if (moved) {

                    score += updateScore(prevBoard, board);
                    if(score > bestScore){
                         bestScore = score;
                         saveBestScore(bestScore);
                    }
                    addRandomTile(board);
                    if (IsGameOver(board)) {
                        gameOver = true;
                        playSound(gameOverSound);
                    }
                }
            }
           if (gameOver && event.type == SDL_MOUSEBUTTONDOWN) {
              int x = event.button.x;
              int y = event.button.y;
                 if (x >= ReplayButton.x && x <= ReplayButton.x + ReplayButton.w &&
                    y >= ReplayButton.y && y <= ReplayButton.y + ReplayButton.h) {
                    initializerBoard(board);
                    addRandomTile(board);
                    addRandomTile(board);
                    gameOver = false;
                 }
              }


        }

        updateTileAnimations(board);

        DrawBoard(renderer, board);
        renderScore(renderer, font, score, bestScore);
        renderBoard(renderer, font, board, 0, 100, 100);

        if (gameOver) {
            score = 0;
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 160);
            SDL_Rect boardRect = {0, 100, 400, 500};
            SDL_RenderFillRect(renderer, &boardRect);
            renderGameOver(renderer);
            renderReplayButton(renderer,"C:/GAME2048/bin/Debug/TryAgain.png", ReplayButton);

        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_FreeChunk(mergeSound);
    Mix_FreeChunk(gameOverSound);
    Mix_FreeMusic(bgm);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
