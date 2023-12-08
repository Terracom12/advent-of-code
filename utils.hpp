#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <thread>
#include <utility>
#include <array>
#include <list>
#include <limits>
#include <algorithm>
#include <numeric>

using ll = long long;
using ull = unsigned long long;

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec) {
    os << "[";
    for(size_t i = 0; i < vec.size() - 1; i++)
        os << vec[i] << ", ";
    os << vec[vec.size() - 1] << "]";

    return os;
}

template<typename T>
T gcd(std::set<T> vals) {
    T ret = vals[0];
    
    for(int i = 1; i < vals.size(); i++) {
        ret = gcd({vals[i], ret % vals[i]});
    }

    return ret;
}

template<typename T>
T lcm(std::set<T> vals) {
    T ret = vals[0];

    for(int i = 1; i < vals.size(); i++) {
        ret = std::abs(ret * vals[i]) / gcd({vals[i], ret % vals[i]});
    }

    return ret;
}