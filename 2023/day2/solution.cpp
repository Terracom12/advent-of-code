#include "../../utils.hpp"

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");

    // map<string, int> maxCubes = { {"red", 12}, {"green", 13}, {"blue", 14} };
    // ll idSum = 0;
    ll powerSum = 0;

    string line;
    int id;
    int power, numCubes;
    bool possible;
    map<string, int> minCubes;

    while(getline(file, line)) {
        id = atoi(line.substr(5, 3).c_str());

        possible = true;
        minCubes["red"] = 0;
        minCubes["green"] = 0;
        minCubes["blue"] = 0;

        int i = (id > 9 ? (id > 99 ? 10 : 9) : 8);

        for(; i < line.size(); ++i) {
            if(!possible) break;
            numCubes = atoi(line.substr(i, 2).c_str());

            i += (numCubes > 9 ? 3 : 2);
            for(auto m : minCubes) {
                if(i + m.first.size() > line.size()) continue;
                string sub = line.substr(i, m.first.size());
                if(sub == m.first) {
                    if(numCubes > m.second)
                        minCubes[m.first] = numCubes;
                    i += sub.size() + 1;
                    break;
                }
            }
        }

        power = 1;
        for(auto n : minCubes)
            power *= n.second;
        
        powerSum += power;

        // if(possible)
        //     idSum += id;
    }

    file.close();

    std::cout << powerSum << endl;
}