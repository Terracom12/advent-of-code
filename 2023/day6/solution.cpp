#include "../../utils.hpp"
#include "structures.hpp"

int part1(std::vector<Race> races) {
    ll totalME = 1;

    for(const auto& race : races) {
        totalME *= race.marginOfError();
    }

    return totalME;
}

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");

    string line;
    vector<ll> data;
    vector<Race> races;
    stringstream ss{};
    ll temp;

    while(getline(file, line)) {
        ss.clear();
        ss << line.substr(line.find(':') + 1);
        while(ss >> temp) data.push_back(temp);
    }
    file.close();

    cout << "D: " << data << endl;

    for(int i = 0; i < data.size() / 2; i++) {
        races.push_back({data[i], data[i + data.size() / 2]});
    }


    cout << "Part 1: " << part1(races) << endl;
    // std::cout << "Part 2: " << part2(seeds, alm) << endl;
}