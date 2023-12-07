#pragma once
#include "../../utils.hpp"

class Card {
public:
    Card() : data(0) {};
    Card(char from, bool jacksAreJokers = false);
    Card(const Card& rhs) = default;

    bool operator==(const Card& rhs) const;
    bool operator!=(const Card& rhs) const;
    // For sorting
    bool operator<(const Card& rhs) const;

    operator bool() const;

    void toJoker() { data == 11 ? data = 1 : 0; }
    bool isJoker() const { return data == 1; }

    // For debugging
    friend std::ostream& operator<<(std::ostream& os, const Card& c);
private:
    int data;
    // A = 14, K = 13, Q = 12, J = 11, T = 10, 9..2
};

enum HandType {
    FiveKind,
    FourKind,
    FullHouse,
    ThreeKind,
    TwoPair,
    OnePair,
    HighCard
};

class Hand {
public:
    Hand(const std::string& from);
    Hand(const Hand& rhs) = default;

    // For sorting
    bool operator<(const Hand& rhs) const;

    void toJokers();

    // For debugging
    friend std::ostream& operator<<(std::ostream& os, const Hand& c);
private:
    HandType determineHandTypeHelper() const;
    HandType determineHandTypeJokerHelper() const;

    HandType type;
    std::array<Card, 5> cards;
};

/**IMPLEMENTATIONS**/

Card::Card(char from, bool jacksAreJokers) {
    switch(from) {
        case 'A':
            data = 14;
            break;
        case 'K':
            data = 13;
            break;
        case 'Q':
            data = 12;
            break;
        case 'J':
            if(jacksAreJokers)
                data = 1;
            else
                data = 11;
            break;
        case 'T':
            data = 10;
            break;
        default:
            data = from - '0';
            break;
    }
}
bool Card::operator==(const Card& rhs) const {
    return data == rhs.data;
}
bool Card::operator!=(const Card& rhs) const {
    return data != rhs.data;
}
bool Card::operator<(const Card& rhs) const {
    return data < rhs.data;
}
Card::operator bool() const {
    return (bool)data;
}

Hand::Hand(const std::string& from) {
    if(from.size() > 5) {
        std::cout << "Too many cards (" << from.size() << ")!\n";
        exit(-1);
    }

    for(int i = 0; i < 5; i++)
        cards[i] = Card(from[i]);
    
    type = determineHandTypeHelper();
}
bool Hand::operator<(const Hand& rhs) const {
    if(type != rhs.type) {
        // Enum HandTypes is in reverse order...
        return type > rhs.type;
    }

    for(int i = 0; i < 5; i++) {
        if(cards[i] != rhs.cards[i]) {
            return cards[i] < rhs.cards[i];
        }
    }

    // Hands are equivalent, therefore (this < rhs) is false 
    return false;
}
HandType Hand::determineHandTypeHelper() const {
    // Checks for each hand type individually

    // Only look for top two most repeating cards, since those
    // are all that matter for the given hand types
    std::map<Card, int> occurMap;
    int numOccur = 0, numOccur2 = 0;

    for(const auto& card : cards) {
        ++occurMap[card];
    }

    for(const auto& [_, val] : occurMap) {
        if(val > numOccur) {
            numOccur2 = numOccur;
            numOccur = val;
        } else if(val > numOccur2) {
            numOccur2 = val;
        }
    }

    // FiveKind
    if(numOccur == 5)
        return FiveKind;

    // FourKind
    if(numOccur == 4)
        return FourKind;

    // FullHouse
    if(numOccur == 3 && numOccur2 == 2)
        return FullHouse;

    // ThreeKind
    if(numOccur == 3) // Could reduce comparisons by 1, but compiler probably optimizes anyways
        return ThreeKind;

    // TwoPair
    if(numOccur == 2 && numOccur2 == 2)
        return TwoPair;

    // OnePair
    if(numOccur == 2)
        return OnePair;

    // HighCard
    return HighCard;
}
HandType Hand::determineHandTypeJokerHelper() const {
    HandType finalType;
    HandType typeWithoutJokers = determineHandTypeHelper();
    int numJokers = 0;

    for(const auto& c : cards)
        numJokers += c.isJoker();
    
    if(!numJokers)
        return typeWithoutJokers;
    
    // Manual conversions...
    // TODO: Optimize this, sorely needed
    if(numJokers == 1) {
        if(typeWithoutJokers == HighCard)
            finalType = OnePair;
        else if(typeWithoutJokers == OnePair)
            finalType = ThreeKind;
        else if(typeWithoutJokers == TwoPair)
            finalType = FullHouse;
        else if(typeWithoutJokers == ThreeKind)
            finalType = FourKind;
        // Cannot have FullHouse if there is only a single joker
        else if(typeWithoutJokers == FourKind)
            finalType = FiveKind;
        // Cannot have FiveKind if there is only a single joker
    } else if(numJokers == 2) {
        // Cannot have HighCard if there are two jokers
        if(typeWithoutJokers == OnePair)
            finalType = ThreeKind;
        else if(typeWithoutJokers == TwoPair)
            finalType = FourKind;
        else if(typeWithoutJokers == ThreeKind)
            finalType = FiveKind;
        else if(typeWithoutJokers == FullHouse)
            finalType = FiveKind;
        // Cannot have FourKind or FiveKind if there are two jokers
    } else if(numJokers == 3) {
        // Cannot have HighCard or OnePair or TwoPair if there are three jokers
        if(typeWithoutJokers == ThreeKind)
            finalType = FourKind;
        else if(typeWithoutJokers == FullHouse)
            finalType = FiveKind;
        // Cannot have FourKind or FiveKind if there are three jokers
    } else {
        finalType = FiveKind;
    }

    return finalType;
}
void Hand::toJokers() {
    for(auto& c : cards)
        c.toJoker();
    
    type = determineHandTypeJokerHelper();
}

// DEBUGGING Output

std::string handTypeToString(HandType ht) {
    const std::map<HandType, std::string> toStr = {
        { FiveKind, "Five of a Kind" },
        { FourKind, "Four of a Kind" },
        { FullHouse, "Full House" },
        { ThreeKind, "Three of a Kind" },
        { TwoPair, "Two Pair" },
        { OnePair, "One Pair" },
        { HighCard, "High Card" }
    };

    return toStr.at(ht);
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    const std::map<int, std::string> faceCardToStr = {
        { 14, "Ace" },
        { 13, "King" },
        { 12, "Queen" },
        { 11, "Jack" }
    };

    if(c.data > 10)
        os << faceCardToStr.at(c.data);
    else if(c.data == 1)
        os << "Joker";
    else
        os << c.data;
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const Hand& h) {
    os << "Hand: ";

    for(const auto& c : h.cards)
        os << c << ' ';

    os << "| " << handTypeToString(h.type);

    return os;
}