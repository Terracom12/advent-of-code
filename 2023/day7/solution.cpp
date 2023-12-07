#include "../../utils.hpp"
#include "structures.hpp"

int part1(std::vector<std::pair<Hand, int>> hbps) {
    ll totalWinnings = 0;

    // Sort the vector so that the index becomes the "hand rank"
    // sorting based on hands (pair.first)
    std::sort(hbps.begin(), hbps.end(), 
        [](auto& p1, auto& p2) { return p1.first < p2.first; });

    for(int i = 0; i < hbps.size(); i++) {
        // std::cout << '\n' << hbps[i].first << " -- " << hbps[i].second << '\n';
        totalWinnings += hbps[i].second * (i + 1);
    }

    return totalWinnings;
}

int part2(std::vector<std::pair<Hand, int>> hbps) {
    ll totalWinnings = 0;

    for(auto& [hand, _] : hbps) {
        hand.toJokers();
    }
    // Sort the vector so that the index becomes the "hand rank"
    // sorting based on hands (pair.first)
    std::sort(hbps.begin(), hbps.end(), 
        [](auto& p1, auto& p2) { return p1.first < p2.first; });

    for(int i = 0; i < hbps.size(); i++) {
        // std::cout << '\n' << hbps[i].first << " -- " << hbps[i].second << '\n';
        totalWinnings += hbps[i].second * (i + 1);
    }

    return totalWinnings;
}

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");

    string line;
    stringstream ss{};
    vector<pair<Hand, int>> handBidPairs;
    ll temp;

    while(getline(file, line)) {
        handBidPairs.push_back(make_pair(
            line.substr(0, line.find(' ')),
            stoi(line.substr(line.find(' ')))));
    }
    file.close();

    

    cout << "Part 1: " << part1(handBidPairs) << endl;
    cout << "Part 2: " << part2(handBidPairs) << endl;
}