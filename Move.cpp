#include "Move.h"

bool moveLeft(Tile board[4][4], Mix_Chunk* mergeSound) {
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        Tile temp[4];
        bool merged[4] = {false};
        int k = 0;
        for (int j = 0; j < 4; j++) {
            if (board[i][j].value == 0) continue;
            if (k > 0 && temp[k - 1].value == board[i][j].value && !merged[k - 1]) {
                temp[k - 1].value *= 2;
                temp[k - 1].scale = 0.8f;
                temp[k - 1].justMerged = true;
                merged[k - 1] = true;
                changed = true;
                Mix_PlayChannel(-1, mergeSound, 0);
            } else {
                if (temp[k].value != board[i][j].value) changed = true;
                temp[k++] = board[i][j];
            }
        }
        for (int j = 0; j < 4; j++) board[i][j] = temp[j];
    }
    return changed;
}

bool moveRight(Tile board[4][4], Mix_Chunk* mergeSound) {
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        Tile temp[4];
        bool merged[4] = {false};
        int k = 3;
        for (int j = 3; j >= 0; j--) {
            if (board[i][j].value == 0) continue;
            if (k < 3 && temp[k + 1].value == board[i][j].value && !merged[k + 1]) {
                temp[k + 1].value *= 2;
                temp[k + 1].scale = 0.8f;
                temp[k + 1].justMerged = true;
                merged[k + 1] = true;
                changed = true;
                Mix_PlayChannel(-1, mergeSound, 0);
            } else {
                if (temp[k].value != board[i][j].value) changed = true;
                temp[k--] = board[i][j];
            }
        }
        for (int j = 0; j < 4; j++) board[i][j] = temp[j];
    }
    return changed;
}

bool moveUp(Tile board[4][4], Mix_Chunk* mergeSound) {
    bool changed = false;
    for (int j = 0; j < 4; j++) {
        Tile temp[4];
        bool merged[4] = {false};
        int k = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j].value == 0) continue;
            if (k > 0 && temp[k - 1].value == board[i][j].value && !merged[k - 1]) {
                temp[k - 1].value *= 2;
                temp[k - 1].scale = 0.8f;
                temp[k - 1].justMerged = true;
                merged[k - 1] = true;
                changed = true;
                Mix_PlayChannel(-1, mergeSound, 0);
            } else {
                if (temp[k].value != board[i][j].value) changed = true;
                temp[k++] = board[i][j];
            }
        }
        for (int i = 0; i < 4; i++) board[i][j] = temp[i];
    }
    return changed;
}

bool moveDown(Tile board[4][4], Mix_Chunk* mergeSound) {
    bool changed = false;
    for (int j = 0; j < 4; j++) {
        Tile temp[4];
        bool merged[4] = {false};
        int k = 3;
        for (int i = 3; i >= 0; i--) {
            if (board[i][j].value == 0) continue;
            if (k < 3 && temp[k + 1].value == board[i][j].value && !merged[k + 1]) {
                temp[k + 1].value *= 2;
                temp[k + 1].scale = 0.8f;
                temp[k + 1].justMerged = true;
                merged[k + 1] = true;
                changed = true;
                Mix_PlayChannel(-1, mergeSound, 0);
            } else {
                if (temp[k].value != board[i][j].value) changed = true;
                temp[k--] = board[i][j];
            }
        }
        for (int i = 0; i < 4; i++) board[i][j] = temp[i];
    }
    return changed;
}

