//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "Blackjack.h"

//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	//test Rank og Suit
	Rank r = Rank::king;
	Suit s = Suit::hearts;

	string rank = rankToString(r);
	string suit = suitToString(s);

	cout << "Rank: " << rank << " Suit: " << suit << '\n';

	cout << '\n';
	
	//test Card-klassen
	Card c{Suit::spades, Rank::ace};
	cout << c.toString() << '\n';

	cout << '\n';

	//test Carddeck-klassen
	CardDeck cd;
	cout << "Carddeck\n";
	cd.print();
	cd.shuffle();
	cout << "Carddeck after shuffle\n";
	cd.print();

	cout << '\n';

	//test Blackjack-klassen
	Blackjack bj;
	bj.playGame();

	cout << '\n';
}

//------------------------------------------------------------------------------
