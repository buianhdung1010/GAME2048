#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>

#include"UI.h"
#include"Move.h"
#include"Animation.h"

void renderNumber(SDL_Renderer* renderer, TTF_Font* font, Tile tile, int x, int y, int size)
{
    if (tile.value == 0) return;

    SDL_Color color = {0 , 0, 0, 255};
    std::string text = std::to_string(tile.value);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) return;

    int textW = textSurface->w;
    int textH = textSurface->h;

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect;
    textRect.w = textW;
    textRect.h = textH;
    textRect.x = x + (size - textW) / 2;
    textRect.y = y + (size - textH) / 2;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void renderBoard(SDL_Renderer* renderer, TTF_Font* font, Tile board[4][4], int startX, int startY, int tileSize) {


    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_Rect background = {startX, startY, tileSize * 4, tileSize * 4};
    SDL_RenderFillRect(renderer, &background);


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = startX + j * tileSize;
            int y = startY + i * tileSize;

            Tile& tile = board[i][j];

            if (tile.value == 0) {
                SDL_SetRenderDrawColor(renderer, 205, 193, 180, 255);
            } else {

                switch (tile.value) {
                    case 2:    SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255); break;
                    case 4:    SDL_SetRenderDrawColor(renderer, 237, 224, 200, 255); break;
                    case 8:    SDL_SetRenderDrawColor(renderer, 242, 177, 121, 255); break;
                    case 16:   SDL_SetRenderDrawColor(renderer, 245, 149, 99, 255); break;
                    case 32:   SDL_SetRenderDrawColor(renderer, 246, 124, 95, 255); break;
                    case 64:   SDL_SetRenderDrawColor(renderer, 246, 94, 59, 255); break;
                    case 128:  SDL_SetRenderDrawColor(renderer, 237, 207, 114, 255); break;
                    case 256:  SDL_SetRenderDrawColor(renderer, 237, 204, 97, 255); break;
                    case 512:  SDL_SetRenderDrawColor(renderer, 237, 200, 80, 255); break;
                    case 1024: SDL_SetRenderDrawColor(renderer, 237, 197, 63, 255); break;
                    case 2048: SDL_SetRenderDrawColor(renderer, 237, 194, 46, 255); break;
                    default:    SDL_SetRenderDrawColor(renderer, 204, 192, 179, 255); break;
                }
            }


            int size = tileSize * tile.scale;
            int offset = (tileSize - size) / 2;
            SDL_Rect tileRect = { x + offset, y + offset, size, size };

            SDL_RenderFillRect(renderer, &tileRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &tileRect);


            renderNumber(renderer, font, tile, x + offset, y + offset, size);
        }
    }
}
void renderScore(SDL_Renderer* renderer, TTF_Font* font, int score, int bestScore)
{
    SDL_Color textColor = {0, 0, 0, 255};

    std:: string scoreText = "Score: " + std::to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {10, 20, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    std:: string bestText = "Best: " + std::to_string(bestScore);
    SDL_Surface* bestSurface = TTF_RenderText_Solid(font, bestText.c_str(), textColor);
    SDL_Texture* bestTexture = SDL_CreateTextureFromSurface(renderer, bestSurface);
    SDL_Rect bestRect = {200, 20, bestSurface->w, bestSurface->h};
    SDL_RenderCopy(renderer, bestTexture, NULL, &bestRect);
    SDL_FreeSurface(bestSurface);
    SDL_DestroyTexture(bestTexture);

}
void renderGameOver(SDL_Renderer* renderer) {
    TTF_Font* font = TTF_OpenFont("C:/GAME2048/bin/Debug/Arial.ttf", 48);
    SDL_Color textColor = { 255, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(font, "Game Over!", textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textW = surface->w;
    int textH = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect dstRect = {
        (400 - textW) / 2,
        (400 + 120 - textH) / 2,
        textW,
        textH
    };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
}
void renderReplayButton(SDL_Renderer* renderer, const char* imagePath, SDL_Rect buttonRect)
{
    SDL_Surface* surface = IMG_Load(imagePath);
    if(!surface){
        std::cout << "IMG failed" << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, &buttonRect);
    SDL_DestroyTexture(texture);
}
void renderMenu(SDL_Renderer* renderer, GameState& state, const char* menuImagePath) {
    SDL_Texture* menuTexture = nullptr;
    SDL_Surface* surface = IMG_Load(menuImagePath);
    if (!surface) {
        std::cerr << "Failed to load menu image: " << IMG_GetError() << std::endl;
        return;
    }
    menuTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    SDL_Rect resumeBtn     = {  90, 160, 236, 64 };
    SDL_Rect newGameBtn    = {  90, 239, 236, 64 };
    SDL_Rect howToPlayBtn  = {  90, 316, 220, 50 };
    SDL_Rect statisticsBtn = {  90, 392, 220, 50 };

    SDL_Event e;
    bool selected = false;

    while (!selected) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                state = EXIT;
                selected = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                if (x >= resumeBtn.x && x <= resumeBtn.x + resumeBtn.w &&
                    y >= resumeBtn.y && y <= resumeBtn.y + resumeBtn.h) {
                    state = PLAYING;
                    selected = true;
                }
                else if (x >= newGameBtn.x && x <= newGameBtn.x + newGameBtn.w &&
                         y >= newGameBtn.y && y <= newGameBtn.y + newGameBtn.h) {
                    state = PLAYING;
                    selected = true;
                }
                else if (x >= howToPlayBtn.x && x <= howToPlayBtn.x + howToPlayBtn.w &&
                         y >= howToPlayBtn.y && y <= howToPlayBtn.y + howToPlayBtn.h) {
                    state = HOW_TO_PLAY;
                    selected = true;
                }
                else if (x >= statisticsBtn.x && x <= statisticsBtn.x + statisticsBtn.w &&
                         y >= statisticsBtn.y && y <= statisticsBtn.y + statisticsBtn.h) {
                    state = STATISTICS;
                    selected = true;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(menuTexture);
}
void showHowToPlay(SDL_Renderer* renderer, const char* imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        std::cerr << "Failed to load HowToPlay image: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create HowToPlay texture: " << SDL_GetError() << std::endl;
        return;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return;
            if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
}
