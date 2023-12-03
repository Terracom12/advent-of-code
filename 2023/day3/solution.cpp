#include "../../utils.hpp"

bool isAdjacent(int digits, std::pair<int, int> numPos, std::pair<int, int> partPos) {
    for(int i = 0; i < digits; i++) {
        if(abs(numPos.first - partPos.first) < 2 && abs(numPos.second + i - partPos.second) < 2) {
            return true;
        }
    }
    return false;
}

int part1(std::multimap<char, std::pair<int, int>>& parts, std::multimap<int, std::pair<int, int>>& numbers) {
    int partNumSum = 0;
    
    // Sum valid numbers
    for(auto& [num, numPos] : numbers) {
        for(auto& [part, partPos] : parts) {
            if(isAdjacent(log10(num) + 1, numPos, partPos)) {
                partNumSum += num;
                break;
            }
        }
    }

    return partNumSum;
}

int part2(std::multimap<char, std::pair<int, int>>& parts, std::multimap<int, std::pair<int, int>>& numbers) {
    std::multimap<char, std::pair<int, int>> gearParts;
    std::vector<int> adjacentParts;
    int totalGearRatios = 0;

    // Store ONLY gear parts
    for(auto& [part, partPos] : parts) {
        if(part == '*') {
            gearParts.emplace(part, partPos);
        }
    }
    
    // Sum valid part numbers
    for(auto& [_, partPos] : parts) {
        for(auto& [num, numPos] : numbers) {
            if(isAdjacent(log10(num) + 1, numPos, partPos)) {
                adjacentParts.push_back(num);
            }
        }
        if(adjacentParts.size() == 2) {
            totalGearRatios += adjacentParts[0] * adjacentParts[1];
        }
        adjacentParts.clear();
    }

    return totalGearRatios;
}

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");

    string line;
    vector<string> input;
    multimap<char, pair<int, int>> parts;
    multimap<int, pair<int, int>> numbers;

    char partNumSymbol;
    int currentNum = 0;
    char c;

    while(getline(file, line)) {
        input.push_back(line);
    }
    file.close();

    // Store part symbols and positions
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {
            c = input[i][j];
            if(!(c >= '0' && c <= '9') && c != '.') {
                // cout << c << " : { " << i << ", " << j << " }\n";
                parts.emplace(c, make_pair(i, j));
            }
        }
    }
    // Store numbers
    for(int i = 0; i < input.size(); i++) {
        pair<int, int> pos;
        for(int j = 0; j < input[i].size(); j++) {
            c = input[i][j];
            if(c >= '0' && c <= '9') {
                if(!currentNum) pos = make_pair(i, j);
                currentNum *= 10;
                currentNum += c - '0';
                // if(currentNum > 1000) {
                //     cout << c << " : { " << i << ", " << j << " }\n";
                //     cout << currentNum << " [" << c - '0' << "?]" << endl;
                // }
            } else {
                if(currentNum) {
                    numbers.emplace(currentNum, pos);
                }
                currentNum = 0;
            }

            if(j == input[i].size() - 1) {
                if(currentNum) {
                    numbers.emplace(currentNum, pos);
                }
                currentNum = 0;
            }
        }
    }

    std::cout << "Part 1: " << part1(parts, numbers) << endl;
    std::cout << "Part 2: " << part2(parts, numbers) << endl;
}