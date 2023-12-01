#include "../../utils.hpp"

int determineGameResult(char opp, char play);

int main() {
    std::ifstream file;
    file.open("input.txt");

    ll score = 0;

    ll totalScore = 0;

    while(!file.eof()) {
        char opp, play;
        file >> opp;
        file >> play;
        if(file.eof()) break;

        int score = determineGameResult(opp, play);
        switch(play) {
            case 'X':
                score += 1;
                break;
            case 'Y':
                score += 2;
                break;
            case 'Z':
                score += 3;
                break;
        }

        std::cout << opp << " / " << play << " => " << score <<  std::endl;
        totalScore += score;
    }
    file.close();

    std::cout << totalScore;
}

int determineGameResult(char opp, char play) {
    std::cout << opp << "->" << char(opp + 23) << std::endl;
    opp += 23;


    if(opp == play) return 3;
    if(opp == play - 1 || opp == play + 2) return 6;

    return 0;
}