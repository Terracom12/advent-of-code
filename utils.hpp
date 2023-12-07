#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <thread>
#include <utility>
#include <array>
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