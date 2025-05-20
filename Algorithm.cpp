#include<SDL.h>
#include<SDL_mixer.h>
#include<iostream>

#include"Algorithm.h"

Mix_Chunk* loadSound(const char* path) {
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if (!sound) {
        std::cout << "Không thể tải âm thanh: " << Mix_GetError() << std::endl;
    }
    return sound;
}

void playSound(Mix_Chunk* sound) {
    if (sound) {
        Mix_PlayChannel(-1, sound, 0);
    }
}

