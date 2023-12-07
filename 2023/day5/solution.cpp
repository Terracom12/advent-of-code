#include "../../utils.hpp"
#include "structures.hpp"

std::vector<ll> getSeeds(const std::string& from) {
    int startSubstr = from.find(' ');
    ll temp;
    std::vector<ll> result{};

    std::stringstream ss(from.substr(startSubstr));

    while(ss >> temp)
        result.push_back(temp);

    return result;
}

ll part1(std::vector<ll> seeds, const Almanac& alm) {
    ll minimum = std::numeric_limits<ll>::max();
    for(auto seed : seeds) {
        minimum = std::min(minimum, alm.computeMapping(seed));
    }

    return minimum;
}

ll part2(std::vector<ll> seedRanges, const Almanac& alm) {
    ll minimum = std::numeric_limits<ll>::max();
    int start, length;
    for(int i = 0; i < seedRanges.size(); i += 2) {
        start = seedRanges[i];
        length = seedRanges[i + 1];
        std::cout << i << std::endl;
        for(int j = start; j < start + length; j++) {
            // double percent = (double)(j - start) / (length);
            // std::cout << 100 * percent << "% done" << std::endl;
            minimum = std::min(minimum, alm.computeMapping(j));
        }
    }

    return minimum;
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

    vector<ll> seeds = getSeeds(lines[0]);
    Almanac alm(vector<string>(lines.begin() + 1, lines.end()));

    // cout << seeds << endl;
    // alm.print();

    // cout << "Part 1: " << part1(seeds, alm) << endl;
    // std::cout << "Part 2: " << part2(seeds, alm) << endl;
}