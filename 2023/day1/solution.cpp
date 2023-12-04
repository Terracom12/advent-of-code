#include "../../utils.hpp"

int part1(std::vector<std::string> input) {
    int firstDigit, lastDigit, number, sum = 0;

    for(const auto& line : input) {
        firstDigit = lastDigit = 0;
        for(int i = 0; i < line.size(); ++i) {
            char c = line[i];
            if(isdigit(c)) {
                lastDigit = c - '0';
            }

            if(!firstDigit) {
                firstDigit = lastDigit;
            }
        }

        number = firstDigit * 10 + lastDigit;
        sum += number;
    }

    return sum;
}

int part2(std::vector<std::string> input) {
    std::vector<std::string> numToWord = 
        { "one", "two", "three", "four", "five", "six", 
          "seven", "eight", "nine" };
    int firstDigit, lastDigit, number, sum = 0;

    for(const auto& line : input) {
        firstDigit = lastDigit = 0;
        for(int i = 0; i < line.size(); i++) {
            char c = line[i];
            if(isdigit(c)) {
                lastDigit = c - '0';
            } else {
                for(int j = 0; j < numToWord.size(); ++j) {
                    if(line.substr(i, numToWord[j].size()) == numToWord[j]) {
                        lastDigit = j + 1;
                    }
                }
            }

            if(!firstDigit) {
                firstDigit = lastDigit;
            }
        }

        number = firstDigit * 10 + lastDigit;
        sum += number;
    }

    return sum;
}

int main() {
    std::ifstream file;
    file.open("input.txt");

    if(!file) {
        std::cout << "ERROR: Could not open file 'input.txt'!\n";
        return -1;
    }

    std::vector<std::string> lines;
    std::string line;
    int firstDigit, lastDigit, n, sum = 0;

    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::cout << "Part 1: " << part1(lines) << std::endl;
    std::cout << "Part 2: " << part2(lines) << std::endl;
}