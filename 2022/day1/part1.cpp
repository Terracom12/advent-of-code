#include "../../utils.hpp"

int main() {
    std::ifstream file;
    file.open("input.txt");

    ll maxCalories = 0;
    ll currentCalories = 0;

    std::string line;

    while(!file.eof()) {
        if(file.eof()) break;
        std::getline(file, line);

        if(!line.length()) {
            maxCalories = std::max(currentCalories, maxCalories);
            currentCalories = 0;
        } else {
            currentCalories += std::stoll(line);
        }
    }
    file.close();

    std::cout << maxCalories;

}