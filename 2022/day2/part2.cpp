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

        int score = 0;
        switch(play) {
            case 'X':
                switch(opp) {
                    case 'A':
                        score += 3;
                        break;
                    case 'B':
                        score += 1;
                        break;
                    case 'C':
                        score += 2;
                        break;
                }
                break;
            case 'Y':
                score += 3;
                score += opp - 64;
                break;
            case 'Z':
                score += 6;
                switch(opp) {
                    case 'A':
                        score += 2;
                        break;
                    case 'B':
                        score += 3;
                        break;
                    case 'C':
                        score += 1;
                        break;
                }
                break;
        }

        // std::cout << opp << " / " << play << " => " << score <<  std::endl;
        totalScore += score;
    }
    file.close();

    std::cout << totalScore;
}

int determineGameResult(char opp, char play) {
    opp += 23;


    if(opp == play) return 3;
    if(opp == play - 1 || opp == play + 2) return 6;

    return 0;
}