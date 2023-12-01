#include "../../utils.hpp"

std::string toSNAFU(ll number) {
    int p = 25;
    ll f = pow(5, p);
    std::string result = "";
    ll nn = 0, maxDist;

    for(int i = 0; i < p; i++)
        maxDist += 2 / pow(5, i);

    while(p >= 0) {
        if(nn == number) {
            result += std::string(p, '0');
            break;
        }

        if(nn > number) {
            if(abs(nn - (f * 2) - number) <= maxDist) {
                result += '=';
                nn -= f * 2;
            } else if(abs(nn - f - number) <= maxDist) {
                result += '-';
                nn -= f;
            }
        } else {
            if(abs(nn + f * 2 - number) <= maxDist) {
                result += '2';
                nn += f * 2;
            } else if(abs(nn + f - number) <= maxDist) {
                result += '1';
                nn += f;
            }
        }
        maxDist -= 2 * (f - 1);
        f /= 5;
        --p;
    }
    return result;
}

int main() {
    using namespace std;
    std::ifstream file;
    file.open("input.txt");

    std ::string line;
    ll sum = 0;

    while(!file.eof()) {
        getline(file, line);
        
        ll f = 1;
        for(auto i = line.end() - 1; i >= line.begin(); --i) {
            switch(*i) {
                case '-':
                    sum += f * -1;
                    break;
                case '=':
                    sum += f * -2;
                    break;
                case '0':
                    break;
                case '1':
                    sum += f;
                    break;
                case '2':
                    sum += f * 2;
                    break;
            }
            f *= 5;
        }
        cout << "line: " << line << " | " << sum << endl;
    }

    cout << 1747 << " to " << toSNAFU(1747) << endl;

    cout << sum << endl;
}