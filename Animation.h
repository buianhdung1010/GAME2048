#ifndef Animation_H
#define Animation_H

struct Tile {
    int value = 0;
    float scale = 1.0f;
    bool justMerged = false;
};


void updateTileAnimations(Tile board[4][4]);
#endif
