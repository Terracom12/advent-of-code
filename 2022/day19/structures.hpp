#pragma once

#include "../../utils.hpp"

class MiningState;

class Blueprint {
public:
    Blueprint(const std::string& input) {
        std::stringstream ss{};
        
        // Remove all characters that are non-numeric and non-whitespace
        for(const char& c : input) {
            if(c == ' ' || (c >= '0' && c <= '9'))
                ss << c;
        }

        ss >> id >> orebotCost >> claybotCost
           >> obibotOreCost >> obibotClayCost
           >> geodebotOreCost >> geodebotObiCost;
    }

    int getQuality() { return id * getMaxGeodesMined(24); }

    // friend std::ostream& operator<<(std::ostream& os, const Blueprint& bp);

    int getMaxGeodesMined(int minutes);

    short premutationAlgorithmHelper(int currentMinutes, MiningState state);

    short id;
    short orebotCost, claybotCost;
    short obibotOreCost, obibotClayCost;
    short geodebotOreCost, geodebotObiCost;
};

std::ostream& operator<<(std::ostream& os, const Blueprint& bp) {
    os << "Blueprint " << bp.id << ":\n"
        << "\tEach ore robot costs " << bp.orebotCost << " ore.\n"
        << "\tEach clay robot costs " << bp.claybotCost << " ore.\n"
        << "\tEach obsidian robot costs " << bp.obibotOreCost << " ore and " << bp.obibotClayCost << " clay.\n"
        << "\tEach geode robot costs " << bp.geodebotOreCost << " ore and " << bp.geodebotObiCost << " obsidian.";
    return os;
}

class MiningState {
public:
    MiningState(const Blueprint& bp) : blueprint(bp) {}
    MiningState(const MiningState&) = default;
    ~MiningState() = default;

    void runMinute() {
        ore += numOreBots;
        clay += numClayBots;
        obi += numObiBots;
        geodes += numGeodeBots;
    }

    int getGeodes() { return geodes; }

    std::vector<MiningState> getPossibleStates() const {
        std::vector<MiningState> p(4, *this);
        std::vector<MiningState> result;

        if(p[0].buildOreBot()) result.push_back(p[0]);
        if(p[1].buildClayBot()) result.push_back(p[1]);
        if(p[2].buildObiBot()) result.push_back(p[2]);
        if(p[3].buildGeodeBot()) result.push_back(p[3]);

        return result;
    }

private:
    bool buildOreBot() {
        if(ore >= blueprint.orebotCost) {
            ore -= blueprint.orebotCost;
            numOreBots++;
            return true;
        } else {
            return false;
        }
    }
    bool buildClayBot() {
        if(ore >= blueprint.claybotCost) {
            ore -= blueprint.claybotCost;
            numClayBots++;
            return true;
        } else {
            return false;
        }
    }
    bool buildObiBot() {
        if(ore >= blueprint.obibotOreCost && clay >= blueprint.obibotClayCost) {
            ore -= blueprint.obibotOreCost;
            clay -= blueprint.obibotClayCost;
            numObiBots++;
            return true;
        } else {
            return false;
        }
    }
    bool buildGeodeBot() {
        if(ore >= blueprint.geodebotOreCost && obi >= blueprint.geodebotObiCost) {
            ore -= blueprint.geodebotOreCost;
            obi -= blueprint.geodebotObiCost;
            numGeodeBots++;
            return true;
        } else {
            return false;
        }
    }

    const Blueprint& blueprint;
    short ore, clay, obi, geodes;
    short numOreBots, numClayBots, numObiBots, numGeodeBots;
};

int Blueprint::getMaxGeodesMined(int minutes) {
    auto s = MiningState(*this);
    return premutationAlgorithmHelper(minutes, s);
}

short Blueprint::premutationAlgorithmHelper(int currentMinutes, MiningState state) {
    const short& (*m)(const short&, const short&) = std::max<short>;
    static int numPerms = 0;
    std::cout << "permutation " << numPerms++ << '\n';
    state.runMinute();
    if(currentMinutes == 0) return state.getGeodes();

    short maxGeodes = 0;

    currentMinutes--;

    for(auto s : state.getPossibleStates()) {
        maxGeodes = m(maxGeodes, premutationAlgorithmHelper(currentMinutes, s));
    }

    return m(maxGeodes, premutationAlgorithmHelper(currentMinutes, state));
}