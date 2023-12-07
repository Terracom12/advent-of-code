#include "../../utils.hpp"
#include "structures.hpp"

int part1(std::vector<Blueprint> bps) {
    int maxQual = 0;

    for(auto bp : bps) {
        maxQual = std::max(maxQual, bp.getQuality());
    }

    return maxQual;
}

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");
    string line;
    vector<string> lines;

    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    vector<Blueprint> blueprints;

    // Parse input into blueprints
    for(const auto& line : lines) {
        blueprints.push_back(line);
    }

    cout << "Part 1: " << part1(blueprints);
    // cout << "Part 2: " << part2(elfPositions);
}