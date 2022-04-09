#include "CardDeck.h"

CardDeck::CardDeck() {
    for (const auto& r : rankToStringMap) {
        for (const auto& s : suitToStringMap) {
            Card c(s.first, r.first);
            cards.push_back(c);
            //Alternativt:
            //cards.emplace_back(s.first, r.first)
        }
    }
}

void CardDeck::swap(int i, int j) {
    Card temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
}

void CardDeck::print() const {
    for (auto c : cards) {
        cout << c.toString() << '\n';
    }
}

void CardDeck::shuffle() {
    for (int i = 0; i < cards.size() - 1; i++) {
        swap(i, i + rand() % (cards.size() - i));
    }
}
//bytter kort nummer i med tilfeldig kort mellom i og cards.size() - 1
//har tall fra i = 0 til cards.size() - 1, velger random tall av de som er
//ikke har blitt iterert gjennom, bytter disse, gjøres til ikke flere kort 
//som kan bli iteret igjennom/byttet ut. 

Card CardDeck::drawCard() {
    if (cards.size() > 0) {
        Card c = cards.back();
        cards.pop_back();
        return c;
    }
    error("There are no more cards in the deck.\n");
}

int CardDeck::cardsLeft() const {
    return cards.size();
}