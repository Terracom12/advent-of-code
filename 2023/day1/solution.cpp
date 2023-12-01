#include "../../utils.hpp"

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");

    string line;
    int n1, n2, n, sum = 0;

    vector<string> numberWords = 
        { "one", "two", "three", "four", "five", "six", 
          "seven", "eight", "nine" };

    while(getline(file, line)) {
        n1 = n2 = 0;
        for(int i = 0; i < line.size(); ++i) {
            char c = line[i];
            if(!isalpha(c)) {
                n2 = atoi(&c);
            } else {
                for(int j = 0; j < numberWords.size(); ++j) {
                    if(line.substr(i, numberWords[j].size()) == numberWords[j])
                        n2 = j + 1;
                }
            }
            if(!n1)
                n1 = n2;
        }
        // cout << "1: " << n1 << " 2: "<< n2 << endl;
        n = n1 * 10 + n2;
        sum += n;

    }
    file.close();

    std::cout << sum;
}