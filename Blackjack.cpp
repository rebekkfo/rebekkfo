#include "Blackjack.h"

bool Blackjack::isAce(Card c) const {
    return c.getRank() == Rank::ace;
}

int Blackjack::getCardValue(Card c) const {
    return blackjackValues.at(c.getRank());
}

int Blackjack::getHandScore(vector<Card> hand) const {
    int score = 0;
    int numberOfAces = 0;
    for (const auto& c : hand) {
        score += getCardValue(c);
        if (isAce(c)) {
            numberOfAces++;
        }
    }
    for (int i = 0; i < numberOfAces && score > 21; i++) {
        score -= 10;
    }
    return score;
}

bool Blackjack::askPlayerQuestion() {
    char yn;
    cout << "Do you want another card?" << " (y/n) ";
    cin >> yn;
    cin.ignore(256, '\n');
    return yn == 'y';
}

void Blackjack::drawPlayerCard() {
    playerHand.push_back(deck.drawCard());
    cout << "You got: " << playerHand.back().toString() << '\n';
    playerHandSum = getHandScore(playerHand);
}

void Blackjack::drawDealerCard() {
    dealerHand.push_back(deck.drawCard());
    dealerHandSum = getHandScore(dealerHand);
}

void Blackjack::roundInit() {
    if (deck.cardsLeft() < 16) {
        deck = CardDeck{};
        deck.shuffle();
    }
    playerHandSum = 0;
    dealerHandSum = 0;
    dealerHand.clear();
    playerHand.clear();
    drawPlayerCard();
    drawPlayerCard();
    drawDealerCard();
    drawDealerCard();
}

bool Blackjack::askPlayAgain() {
    char yn;
    cout << "Do you want to play again?" << " (y/n) ";
    cin >> yn;
    cin.ignore(256, '\n');
    return yn == 'y';
}

void Blackjack::playGame() {
    cout << "******* LET'S PLAY BLACKJACK! *******\n";
    deck.shuffle();
    bool playerWins = false;
    do {
        roundInit();

        cout << "Player hand is currently: " << playerHandSum << '\n';
        cout << "The dealer's open card is: " << dealerHand.at(0).toString() << '\n';

        //spiller trekker kort
        while (playerHandSum < 21 && askPlayerQuestion()) {
            cout << "Player draws a card\n";
            drawPlayerCard();
            cout << "Player hand is currently: " << playerHandSum << '\n';
        }

        //dealer trekker kort
        while(dealerHandSum < 17) {
            cout << "Dealer draws a card.\n";
            drawDealerCard();
        }

        cout << "**************************************\n";
        cout << "Player's cards: ";
        for (const auto& c : playerHand) {
            cout << c.toString() << ", ";
        }
        cout << '\n';
        cout << "Player's hand: " << playerHandSum << '\n';

        cout << "Dealer's cards: ";
        for (const auto& c : dealerHand) {
            cout << c.toString() << ", ";
        }
        cout << '\n';
        cout << "Dealer's hand: " << dealerHandSum << '\n';

        //vinner bestemmes
        if (playerHandSum > 21) {
            cout << "Player burst.\n";
            playerWins = false;
        } else if (dealerHandSum > 21) {
            cout << "Dealer burst.\n";
            playerWins = true;
        } else if (dealerHandSum == 21 && dealerHand.size() == 2) {
            cout << "Dealer got blackjack!\n";
            playerWins = false;
        } else if (playerHandSum == 21 && playerHand.size() == 2) {
            cout << "Player got blackjack!\n";
            playerWins = true;
        } else if (dealerHandSum <= 21 && dealerHandSum > playerHandSum) {
            cout << "Dealer beat the player.\n";
            playerWins = false;
        } else if (playerHandSum <= 21 && playerHandSum > dealerHandSum) {
            cout << "Player beat the dealer.\n";
            playerWins = true;
        } else {
            cout << "Game was a draw.\n";
            playerWins = false;
        }

        if (playerWins) {
            cout << "You won! Congratulations!\n";
        } else {
            cout << "You lost!\n";
        }

    } while(askPlayAgain());
}