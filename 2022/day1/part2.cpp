#include "../../utils.hpp"

int main() {
    std::ifstream file;
    file.open("input.txt");

    std::array<ll,  3> max3Calories{};
    ll currentCalories = 0;

    std::string line;

    while(!file.eof()) {
        if(file.eof()) break;
        std::getline(file, line);

        if(!line.length()) {
            int i = -1;
            while(i < 2 && max3Calories[i + 1] < currentCalories) {
                i++;
                std::cout << "current = " << currentCalories << " | i = " << i << " | " << max3Calories << std::endl;
                if(i != 0)
                    max3Calories[i - 1] = max3Calories[i];
                max3Calories[i] = currentCalories;
            }
            currentCalories = 0;
        } else {
            currentCalories += std::stoll(line);
        }
    }

    std::cout << max3Calories[0] << ' ' << max3Calories[1] << ' ' << max3Calories[2] << std::endl;
    std::cout << max3Calories[0] + max3Calories[1] + max3Calories[2];
}