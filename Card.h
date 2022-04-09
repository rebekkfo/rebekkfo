#pragma once
#include "std_lib_facilities.h"

enum class Suit{clubs, diamonds, hearts, spades};
enum class Rank{two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
//enum class setter automatisk første element til 0, så 1, 2... overstyrer dette med "="

string suitToString(Suit suit);
string rankToString(Rank rank);

const map<Suit, string> suitToStringMap {
    {Suit::clubs, "clubs"},
    {Suit::diamonds, "diamonds"},
    {Suit::hearts, "hearts"},
    {Suit::spades, "spades"}
};

const map<Rank, string> rankToStringMap {
    {Rank::two, "two"},
    {Rank::three, "three"},
    {Rank::four, "four"},
    {Rank::five, "five"},
    {Rank::six, "six"},
    {Rank::seven, "seven"},
    {Rank::eight, "eight"},
    {Rank::nine, "nine"},
    {Rank::ten, "ten"},
    {Rank::jack, "jack"},
    {Rank::queen, "queen"},
    {Rank::king, "king"},
    {Rank::ace, "ace"}
};

string rankToString(Rank r);
string suitToString(Suit s);

class Card {
public:
    Card(Suit suit, Rank rank) : s{suit}, r{rank} {};
    Suit getSuit() const;
    Rank getRank() const;
    string toString() const;
private:
    Suit s;
    Rank r;
};

