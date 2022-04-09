#pragma once
#include "CardDeck.h"

const map<Rank, int> blackjackValues {
	{Rank::two, 2},
	{Rank::three, 3},
	{Rank::four, 4},
	{Rank::five, 5},
	{Rank::six, 6},
	{Rank::seven, 7},
	{Rank::eight, 8},
	{Rank::nine, 9},
	{Rank::ten, 10},
	{Rank::jack, 10},
	{Rank::queen, 10},
	{Rank::king, 10},
	{Rank::ace, 11}
};

class Blackjack {
private:
    CardDeck deck;
    vector<Card> playerHand;
    vector<Card> dealerHand;
    int playerHandSum;
    int dealerHandSum;

    bool isAce(Card c) const;
    int getCardValue(Card c) const;
    int getHandScore(vector<Card> hand) const;
    bool askPlayerQuestion();
    void drawPlayerCard();
    void drawDealerCard();
    void roundInit();
    bool askPlayAgain();
public:
    void playGame();
};
