#include "../../utils.hpp"

enum class Dir {
    Right,
    Left
};

int part1(std::vector<Dir>& dirs, std::unordered_map<std::string, std::pair<std::string, std::string>>& paths, std::string& start) {
    ll steps = 0;
    int i = 0;
    std::string current = start;

    while(current != "ZZZ") {
        steps++;
        if(i >= dirs.size()) i = 0;
        switch(dirs[i++]) {
            case Dir::Left:
                current = paths.at(current).first;
                break;
            case Dir::Right:
                current = paths.at(current).second;
                break;
            default:
                std::cout << "BAD!\n";
                return -1;
        }
    }

    return steps;
}

int part2(std::vector<Dir>& dirs, std::unordered_map<std::string, std::pair<std::string, std::string>>& paths) {
    ll steps = 0;
    std::vector<std::string> startingLocs;
    std::vector<std::pair<int, int>> offsets;
    Dir dir;
    std::unordered_map<std::string, int> stack;

    // Populate starting locations
    for(const auto& p : paths) {
        if(p.first.find('A') != std::string::npos)
            startingLocs.push_back(p.first);
    }

    for(const auto& loc : startingLocs) {
        stack.clear();
        std::string current = loc;
        int i = 0;

        while(stack[current] != i) {
            steps++;
            if(i >= dirs.size()) i = 0;
            switch(dirs[i++]) {
                case Dir::Left:
                    current = paths.at(current).first;
                    break;
                case Dir::Right:
                    current = paths.at(current).second;
                    break;
                default:
                    std::cout << "BAD!\n";
                    return -1;
            }
        }
    }

    while(!allZs) {
        allZs = true;
        steps++;
        if(i >= dirs.size()) i = 0;

        dir = dirs[i++];

        for(int i = 0; i < locs.size(); i++) {
            if(dir == Dir::Left)
                locs[i] = paths.at(locs[i]).first;
            else
                locs[i] = paths.at(locs[i]).second;
            if(locs[i].find('Z') == std::string::npos) {
                allZs = false;
            }
        }

    }

    return steps;
}

int main() {
    using namespace std;
    ifstream file;
    file.open("input.txt");

    string line;
    vector<string> lines;
    vector<Dir> dirs;
    unordered_map<string, pair<string, string>> paths;
    stringstream ss{};
    ll temp;

    while(getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    for(char c : lines[0]) {
        switch (c) {
            case 'R':
                dirs.push_back(Dir::Right);
                break;
            case 'L':
                dirs.push_back(Dir::Left);
                break;
            default:
                std::cout << "ERROR! Could not parse directions! (" << c <<  ")\n";
                return -1;
        }
    }

    lines.erase(lines.begin(), lines.begin() + 2);

    for(auto& line : lines) {
        paths[line.substr(0, line.find(' '))] =
            make_pair(line.substr(line.find('(') + 1, 3),
                line.substr(line.find(',') + 2, 3));
    }


    std::cout << "Part 1: " << part1(dirs, paths, "AAA") << endl;
    std::cout << "Part 2: " << part2(dirs, paths) << endl;
}