#include "../../utils.hpp"

int main() {
    std::ifstream file;
    file.open("input.txt");

    char inBoth;
    int totalPriorities = 0;
    std ::string line;

    std::cout << "STUFF\n";
    while(!file.eof()) {
        std::getline(file, line);

        for(int i = 0; i < line.size() / 2; i++) {
            for(int j = line.size() / 2 - 1; j < line.size(); j++) {
                if(line[j] == line[i]) {
                    inBoth = line[i];
                    break;
                }
            }
        }
        std::cout << inBoth;
        if(std::islower(inBoth))
            totalPriorities += inBoth - 70;
        else
            totalPriorities += inBoth - 64;
    }
    file.close();

    std::cout << totalPriorities;
}