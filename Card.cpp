#include "Card.h"

string suitToString(Suit suit) {
    return suitToStringMap.at(suit);

    // Alternativ med switch
	/* switch(s) {
		case Suit::clubs:
			return "clubs";
		case Suit::diamonds:
			return "diamonds";
		case Suit::hearts:
			return "hearts";
		case Suit::spades:
			return "spades";
	} */
}

string rankToString(Rank rank) {
    return rankToStringMap.at(rank);

    // Alternativ med switch
	/* switch(rank) {
		case Rank::two:
			return "two";
		case Rank::three:
			return "three";
		case Rank::four:
			return "four";
		case Rank::five:
			return "five";
		case Rank::six:
			return "six";
		case Rank::seven:
			return "seven";
		case Rank::eight:
			return "eight";
		case Rank::nine:
			return "nine";
		case Rank::ten:
			return "ten";
		case Rank::jack:
			return "jack";
		case Rank::queen:
			return "queen";
		case Rank::king:
			return "king";
		case Rank::ace:
			return "ace";
	} */
}


// 1. fanger opp skrivefeil, lett å rette opp istedenfor å måtte lese igjennom
// 2. Øker lesbarhet

Suit Card::getSuit() const {
	return s;
}

Rank Card::getRank() const {
	return r;
}

string Card::toString() const {
	return rankToString(r) + " of " + suitToString(s);
}

