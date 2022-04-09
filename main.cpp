//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "Animal.h"
#include "Emoji.h"
#include "AnimationWindow.h"

//------------------------------------------------------------------------------'

//definer str vindu og emoji
constexpr int xmax = 1000;
constexpr int ymax = 600;
constexpr int emojiRadius = 50;

void drawEmojis(vector<unique_ptr<Emoji>>& emojis, AnimationWindow& win) {
	/*for (int i = 0; emojis.size(); ++i) {
		emojis.at(i) -> draw(win);
	}*/

	for (auto it = emojis.begin(); it < emojis.end(); ++it)
	 {
	 	(*it)->draw(win);
	 }

}

int main()
{
	//testAnimal();

	const Point tl{100, 100};
	const string win_label{"Emoji factory"};
	AnimationWindow win{tl.x, tl.y, xmax, ymax, win_label};
	
	vector<unique_ptr<Emoji>> es;
	//new konstruerer nytt objekt på "denne" adressen
	es.emplace_back(new SmilingFace { Point {xmax / 2 - emojiRadius, ymax / 2 - emojiRadius}, emojiRadius});
	es.emplace_back(new SadFace { Point {xmax / 2 + emojiRadius, ymax / 2 - emojiRadius}, emojiRadius});
	es.emplace_back(new SurprisedFace { Point {xmax / 2 - emojiRadius, ymax / 2 + emojiRadius}, emojiRadius});
	es.emplace_back(new AngryFace { Point {xmax / 2 + emojiRadius, ymax / 2 + emojiRadius}, emojiRadius});
	es.emplace_back(new NeutralFace { Point {xmax / 2 + 3 * emojiRadius, ymax / 2 - emojiRadius}, emojiRadius});
	es.emplace_back(new WinkFace { Point { xmax / 2 + 3 * emojiRadius, ymax / 2 + emojiRadius}, emojiRadius});

	drawEmojis(es, win);

	win.wait_for_close();
}

//------------------------------------------------------------------------------
