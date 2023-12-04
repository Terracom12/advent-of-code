#include "../../utils.hpp"

class Scratchcard {
public:
    Scratchcard(const std::string& input) {
        std::stringstream ss{};
        int temp;

        // Remove all non-essential characters
        for(auto c : input) {
            if(c == ' ' || (c >= '0' && c <= '9'))
                ss << c;
        }

        // Get card id
        ss >> id;
        // 10 winning numbers
        for(int i = 0; i < 10; i++) {
            ss >> temp;
            winningNums.push_back(temp);
        }  
        // Remaining chosen numbers
        while(ss >> temp) {
            nums.push_back(temp);
        }
    }

    int getScore() {
        return pow(2, getNumMatches() - 1);
    }

    void print() {
        std::cout << "Card " << id << ": ";
        for(auto n : winningNums) 
            std::cout << n << ' ';
        std::cout << "| ";
        for(auto n : nums) 
            std::cout << n << ' ';
        std::cout << '\n';
    }

    int getNumMatches() {
        int matches = 0;

        for(auto n1 : winningNums) {
            for(auto n2 : nums) {
                if(n1 == n2)
                    matches++;
            }
        }
        return matches;
    }

private:
    short id;
    std::vector<int> winningNums;
    std::vector<int> nums;
};

int part1(std::vector<Scratchcard> cards) {
    int totalScore = 0;
    for(auto card : cards) {
        totalScore += card.getScore();
    }

    return totalScore;
}

int part2(std::vector<Scratchcard> cards) {
    std::vector<int>  cardMatches;
    std::vector<ll> numCopies(cards.size(), 1);
    int matches, copies;

    for(auto card : cards) {
         cardMatches.push_back(card.getNumMatches());
    }

    for(int i = 0; i < cards.size(); i++) {
        matches =  cardMatches[i];
        copies = numCopies[i];
        for(int j = i + 1; j < std::min((ll)cards.size(), (ll)i + matches + 1); j++) {
            numCopies[j] += copies;
        }
    }

    return std::accumulate(numCopies.begin(), numCopies.end(), 0);
}

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");

    string line;
    vector<string> lines;
    vector<Scratchcard> cards;

    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    // Parse input
    for(auto line : lines) {
        cards.push_back(line);
    }

    std::cout << "Part 1: " << part1(cards) << endl;
    std::cout << "Part 2: " << part2(cards) << endl;
}