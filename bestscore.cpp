#include<fstream>

#include"bestcore.h"
int loadBestScore() {
    std::ifstream file("best_score.txt");
    int best = 0;
    if (file >> best) {
        return best;
    }
    return 0;
}
void saveBestScore(int bestScore) {
    std::ofstream file("best_score.txt");
    file << bestScore;
}


