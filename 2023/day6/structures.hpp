#pragma once

#include "../../utils.hpp"

class Race {
public:
    Race(ll t, ll r) : time(t), recordDistance(r) {};

    ll marginOfError() const;

    bool checkForWin(ll heldTime) const;
private:
    ll time, recordDistance;
};

ll Race::marginOfError() const {
    ll numWays = 0;

    // Brute force, naive solution
    for(ll i = 1; i < time; i++) {
        if(checkForWin(i))
            numWays++;
    }

    return numWays;
}

bool Race::checkForWin(ll heldTime) const {
    return heldTime * (time - heldTime) > recordDistance;
}