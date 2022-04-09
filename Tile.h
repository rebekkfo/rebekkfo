#pragma once
#include "GUI.h"

// De forskjellige tilstandene en Tile kan vaere i
enum class Cell { closed, open, flagged }; 

class Tile : public Fl_Button
{
	Cell state = Cell::closed;
	bool isMine = false;
	
	void set_label(string s) { this->copy_label(s.c_str());}
	void set_label_color(Color c) {this->labelcolor(c.as_int());}
public:
	Tile(Point pos, int size) 
		 :Fl_Button(pos.x, pos.y, s ize, size, "") {};

	// Vis hvor mange miner det er i naborutene
	void setAdjMines(int n);

	void open();
	void reset();
	void flag();

	bool getIsMine() const { return isMine; };
	void setIsMine(bool isMine) { this->isMine = isMine; };
	Cell getState() const { return state; };
};
