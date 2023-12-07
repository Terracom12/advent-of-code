#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <array>
#include <algorithm>
#include <numeric>

using ll = long long;

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec) {
    os << "[";
    for(size_t i = 0; i < vec.size() - 1; i++)
        os << vec[i] << ", ";
    os << vec[vec.size() - 1] << "]";

    return os;
}