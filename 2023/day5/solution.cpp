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

void part2_helper(ll* m, ll s, ll e, const Almanac& alm, int num) {
    bool f = false;
    for(ll j = s; j < e; j++) {
        *m = std::min(*m, alm.computeMapping(j));
        if(*m == 0 && !f) {
            f = true;
            std::cout << "(" << num << ") {" << s << ',' << e << "} - " << j << '\n';
        }
    }
}

ll part2(const std::vector<ll>& seedRanges, const Almanac& alm) {
    const int NUM_THREADS = 200;
    // JANK, lololol
    // Optimization? More like, just get a better computer
    std::array<std::thread, NUM_THREADS> threads; 
    ll mins[NUM_THREADS], minimum = std::numeric_limits<ll>::max();
    std::fill(&mins[0], &mins[NUM_THREADS - 1], std::numeric_limits<ll>::max());
    ll start, length, d;
    for(int i = 0; i < seedRanges.size(); i += 2) {
        start = seedRanges[i];
        length = seedRanges[i + 1];
        d = length / NUM_THREADS;
        
        for(int j = 0; j < NUM_THREADS - 1; j++) {
            threads[j] = std::thread(part2_helper, &mins[j], start + d * j, start + d * (j + 1), alm, j);
        }
        threads[NUM_THREADS - 1] = std::thread(part2_helper, 
            &mins[NUM_THREADS - 1], start + d * (NUM_THREADS - 1), start + length, alm, NUM_THREADS - 1);

        for(auto& t : threads)
            t.join();

        for(auto m : mins) {
            if(m == 0)
                std::cout << m << ' ';
            minimum = std::min(m, minimum);
        }

        // std::cout << "-> " << minimum << '\n' << 100 * (i + 2) / seedRanges.size() << "% done";
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

    cout << "Part 1: " << part1(seeds, alm) << endl;
    std::cout << "Part 2: " << part2(seeds, alm) << endl;
}