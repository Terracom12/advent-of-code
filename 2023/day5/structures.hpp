#pragma once

#include "../../utils.hpp"

class Map;
class Almanac;

class MapRange {
public:
    friend class Almanac; // Bad practice; lazy
    friend class Map; // Bad practice; lazy
    MapRange(const std::string& from);
    MapRange(ll sourceSt, ll destSt, ll len) 
        : sourceStart(sourceSt), destinationStart(destSt), length(len) { initHelper(); }

    bool canMap(ll value) const { return value >= sourceStart && value < sourceStart + length; };
    // Assume canMap(value) is true for mapFrom
    ll mapFrom(ll value) const { return value - sourceStart + destinationStart; }
    void print() const;
    operator bool() const { return length != 0; }
    // Assumes of non-overlapping ranges
    bool operator<(const MapRange& rhs) const { return sourceStart < rhs.sourceStart; }
private:
    void initHelper();

    ll sourceStart, destinationStart, length;
    ll start, end, change;
};

class Map {
public:
    friend class Almanac; // Bad practice; lazy
    Map() = default;
    Map(const std::vector<std::string>& from);
    Map(const Map&) = default;

    ll mapFrom(ll value) const;
    void print() const;

    Map operator|(const Map& lhs);
private:
    std::vector<MapRange> ranges;
    std::string name;
};

class Almanac {
public:
    Almanac(const std::vector<std::string>& from);

    ll computeMapping(ll value) const;
    ll minMappingFromRange(ll start, ll length) const;
    void print() const;
private:
    static Map compactMaps(std::vector<Map> maps);
    std::vector<Map> maps;
    Map compactedMap;
};

MapRange::MapRange(const std::string& from) {
    std::stringstream ss(from);

    ss >> destinationStart >> sourceStart >> length;
    initHelper();
}
void MapRange::print() const {
    using std::cout;

    cout << "(" << start << "-" << end  << " => "
         << start + change << "-" << end + change << ") "
         << std::showpos << change << std::noshowpos;
    // cout << "Starts {source: " << sourceStart 
    //      << ", dest: " << destinationStart 
    //      << "} - length = " << length;
}
void MapRange::initHelper() {
    start = sourceStart;
    end = sourceStart + length - 1;
    change = destinationStart - sourceStart;
}

Map::Map(const std::vector<std::string>& from) : ranges() {
    name = from[0].substr(0, from[0].find(' '));

    for(int i = 1; i < from.size(); i++)
        ranges.push_back(from[i]);
}
ll Map::mapFrom(ll value) const {
    // It is assumed that ranges do not overlap
    for(const auto& range : ranges) {
        if(range.canMap(value))
            return range.mapFrom(value);
    }

    return value;
}
void Map::print() const {
    using std::cout;

    cout << "Map " << name << ":\n";

    for(const auto& range : ranges) {
        cout << '\t';
        range.print();
        cout << '\n';
    }
}
Map Map::operator|(const Map& rhs) {
    /* COMPOSING MAPS Step-by-step 
    *   Test Case: {{50,98,2},{52,50,48}} -> {{0,15,37},{37,52,2},{39,0,15}}
    *   Composed:  {{0,15,37},{37,52,2},{52,9,4},{55,53,44}}
    *  disjoint (easy)-----^--------^
    * Steps:
    * 1) Split ranges
    *  1) Find which range begins earlier
    *  2) If the earlier range is disjoint from the other, continue to the next
    *  3) If the earlier range ends in the middle of the other, split each range.
    *     Earlier should be split into two parts, the middle only one for now
    */
    // Composing this map onto lhs, similar behavior to pipe operator
    std::vector<ll> splitLocations{};
    std::vector<MapRange> lhsSplit{}, rhsSplit{};
    Map result{};
    int i, j, c;
    // Two steps: ensure ranges are sorted correctly, split ranges, then merge them
    std::sort(ranges.begin(), ranges.end(), 
        [](const MapRange& l, const MapRange& r) { return l.destinationStart < r.destinationStart; });

    // Determine where to split
    i = j = 0;
    while(i < ranges.size() && j < rhs.ranges.size()) {
        MapRange from = ranges[i], to = rhs.ranges[j];

        if(from.start + from.change < to.start) {
            if(from.end + from.change <= to.start) {
                i++;
            } else {
                splitLocations.push_back(to.start);

                if(from.end + from.change > to.end) {
                    splitLocations.push_back(to.end);
                    j++;
                } else if(from.end + from.change < to.end) {
                    splitLocations.push_back(from.end + from.change);
                    i++;
                } else {
                    i++;
                    j++;
                }
            }
        } else if(from.start + from.change > to.start) {
            if(to.end <= from.start + from.change) {
                j++;
            } else {
                splitLocations.push_back(from.start + from.change);

                if(to.end > from.end + from.change) {
                    splitLocations.push_back(from.end + from.change);
                    i++;
                } else if(to.end < from.end + from.change) {
                    splitLocations.push_back(to.end);
                    j++;
                } else {
                    i++;
                    j++;
                }
            }
        } else {
            if(from.end + from.change < to.end) {
                splitLocations.push_back(from.end + from.change);
                i++;
            } else if(from.end + from.change > to.end) {
                splitLocations.push_back(to.end);
                j++;
            } else {
                i++;
                j++;
            }
        }
    }

    std::cout << "\nlocs = " << splitLocations << '\n';
    // Splitting
    for(auto& location : splitLocations) {
        for(auto& from : ranges) {
            // Use the **destinations* for splitting 
            if(location <= from.start + from.change ||
                    location >= from.end + from.change) {
                lhsSplit.push_back(from);
            } else {
                lhsSplit.push_back(
                    MapRange(from.sourceStart, from.destinationStart, 
                        from.length - (from.end + from.change - location)));
                lhsSplit.push_back(
                    MapRange(location - from.change, location, 
                        from.end + from.change - location));
            }
        }
        for(auto& to : rhs.ranges) {
            // Use the **sources* for splitting
            if(location <= to.start || location >= to.end) {
                rhsSplit.push_back(to);
            } else {
                rhsSplit.push_back(
                    MapRange(to.sourceStart, to.destinationStart, 
                        to.length - (to.end - location)));
                rhsSplit.push_back(
                    MapRange(location, location + to.change, 
                        to.end - location));
            }
        }
    }

    print(); rhs.print();
    std::cout << "\nSPLIT -- (" << lhsSplit.size() << ", " << rhsSplit.size() << ")";
    for(auto& l : lhsSplit) {
        std::cout << '\n';
        l.print();
    }
    std::cout << "\n___";
    for(auto& r : rhsSplit) {
        std::cout << '\n';
        r.print();
    }
    std::cout << '\n';

    return result;
}

Almanac::Almanac(const std::vector<std::string>& from) : maps(), compactedMap() {
    auto first = from.begin();
    int mapBegin = 0;

    for(auto i = 0; i < from.size(); i++) {
        if(from[i].size() == 0) {
            if(i - mapBegin > 1) {
                maps.push_back(std::vector<std::string>(first + mapBegin, first + i));
            }
            mapBegin = i + 1;
        }
    }
    // Ensure map ranges are all in correct order
    // for(Map& map : maps) {
    //     std::sort(map.ranges.begin(), map.ranges.end());
    // }

    // compactedMap = compactMaps(maps);
    // compactedMap.name = "compact";
}
ll Almanac::computeMapping(ll value) const {
    // return compactedMap.mapFrom(value);
    
    ll to = value;
    for(const auto& map : maps) {
        to = map.mapFrom(to);
    }
    return to;
}
ll Almanac::minMappingFromRange(ll start, ll length) const {
    ll minimum = compactedMap.mapFrom(start);

    for(const auto& r : compactedMap.ranges) {
        if(r.sourceStart >= start && r.sourceStart < start + length) {
            minimum = std::min(minimum, r.destinationStart);

            if(r.sourceStart + r.length <= start + length) {
                minimum = std::min(minimum, compactedMap.mapFrom(r.sourceStart + r.length));
            }
        }
    }

    return minimum;
}
void Almanac::print() const {
    using std::cout;

    cout << "Almanac:\n";

    for(const auto& map : maps) {
        cout << "\n ";
        map.print();
        cout << '\n';
    }

    cout << "\n ";
    compactedMap.print();
    cout << '\n';
}
Map Almanac::compactMaps(std::vector<Map> maps) {
    Map result{};

    for(int i = 0; i < maps.size() - 1; i++) {
        maps[i] | maps[i + 1];
        std::cout << "____________________\n";
    }

    // for(auto& map : maps) {
    //     result = result | map;
    // }

    return result;
}