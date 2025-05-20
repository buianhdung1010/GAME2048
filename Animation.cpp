#include "Animation.h"


void updateTileAnimations(Tile board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j].justMerged) {
                board[i][j].scale += 0.1f;
                if (board[i][j].scale >= 1.0f) {
                    board[i][j].scale = 1.0f;
                    board[i][j].justMerged = false;
                }
            }
        }
    }
}

