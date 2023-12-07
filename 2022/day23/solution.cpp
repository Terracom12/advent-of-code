#include "../../utils.hpp"

using vec2 = std::vector<int>;
using vec2d = std::vector<std::vector<int>>;

enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

bool checkIfDirectionFree(vec2 starting, const vec2d& positions, int direction) {
    for(const auto& pos : positions) {
        switch(direction) {
            case NORTH:
                if(pos[0] - 1 == starting[0] && abs(pos[1] - starting[1]) < 2) return false;
                break;
            case SOUTH:
                if(pos[0] + 1 == starting[0] && abs(pos[1] - starting[1]) < 2) return false;
                break;
            case EAST:
                if(pos[1] - 1 == starting[1] && abs(pos[0] - starting[0]) < 2) return false;
                break;
            case WEST:
                if(pos[1] + 1 == starting[1] && abs(pos[0] - starting[0]) < 2) return false;
                break;
        }
    }
    return true;
}

void playRound(vec2d& positions, int direction) {
    vec2d proposedPositions;
    // Fill proposed positions
    for(auto& pos : positions) {
        if(!(checkIfDirectionFree(pos, positions, NORTH) && checkIfDirectionFree(pos, positions, SOUTH)
            && checkIfDirectionFree(pos, positions, EAST) && checkIfDirectionFree(pos, positions, WEST))) {
            for(int i = 0; i < 4; i++) {
                if(checkIfDirectionFree(pos, positions, direction)) {
                    switch(direction) {
                        case NORTH:
                            proposedPositions.push_back({pos[0] + 1, pos[1]});
                            break;
                        case SOUTH:
                            proposedPositions.push_back({pos[0] - 1, pos[1]});
                            break;
                        case EAST:
                            proposedPositions.push_back({pos[0], pos[1] + 1});
                            break;
                        case WEST:
                            proposedPositions.push_back({pos[0], pos[1] - 1});
                            break;
                    }
                    break;
                }
                direction++;
                if(direction > WEST)
                    direction = NORTH;
            }
        }
    }

    bool doubleMove;

    // Modify positions based on proposed positions, checking to only add each position once
    for(int i = 0; i < proposedPositions.size(); i++) {
        doubleMove = false;
        for(int j = 0; j < proposedPositions.size(); j++) {
            if(i == j) continue;
            if(proposedPositions[i] == proposedPositions[j]) {
                doubleMove = true;
                break;
            }
        }
        if(!doubleMove) {
            positions[i] = proposedPositions[i];
        }
    }
}

int part1(vec2d positions) {
    int startingDir = NORTH;
    int xMin = 10000, xMax = 0, yMin = 10000, yMax = 0;

    for(int i = 0; i < 10; i++) {
        std::cout << "\nRound " << i << ": " << positions << std::endl;
        playRound(positions, startingDir);
        startingDir++;
        if(startingDir > WEST)
            startingDir = NORTH;
    }

    // Find smallest rectangle
    for(const auto& pos : positions) {
        xMin = std::min(pos[1], xMin);
        xMax = std::max(pos[1], xMax);
        yMin = std::min(pos[0], yMin);
        yMax = std::max(pos[0], yMax);
    }

    return (xMax - xMin) * (yMax - yMin);
}

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");
    string line;
    vector<string> input;

    vec2d elfPositions;

    while(getline(file, line)) {
        input.push_back(line);
    }
    file.close();

    // Parse and store elf positions
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {
            if(input[i][j] == '#')
                elfPositions.push_back({i + 200, j + 200});
        }
    }

    cout << "Part 1: " << part1(elfPositions);
    // cout << "Part 2: " << part2(elfPositions);
}