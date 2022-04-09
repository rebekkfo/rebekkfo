#pragma once
#include "Card.h"

class CardDeck {
public:
    CardDeck();
    void print() const; //const - "read-only funksjon", endrer ikke objekt
    void shuffle();
    Card drawCard();
    int cardsLeft() const;
private:
    vector<Card> cards;
    void swap(int a, int b);
    //swap burde være private, kun funksjoner som krever objekter fra 
    //andre klasser når de skal brukes skal være public, generelt - private,
    //denne skal bare bytte om på to indekser i privat variabel
};