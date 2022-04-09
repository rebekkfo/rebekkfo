#include "Tile.h"

// For aa sette labelfarge i henhold til hvor mange miner som er rundt
const map<int, Color> minesToColor{{1, Color::blue},
								   {2, Color::red},
								   {3, Color::dark_green},
								   {4, Color::dark_magenta},
								   {5, Color::dark_blue},
								   {6, Color::dark_cyan},
								   {7, Color::dark_red},
								   {8, Color::dark_yellow}};

// For aa sette Tilelabel i henhold til state
const map<Cell, string> cellToSymbol{{Cell::closed, ""},
									 {Cell::open, ""},
									 {Cell::flagged, "@<"}};

void Tile::open()
{
	if (state != Cell::flagged) {
		this->set();// Setter en button som trykket paa, tilsvarer aapnet rute
		state = Cell::open;

		if (isMine) {
			set_label("X");
			set_label_color(Color::red);
		}
	}
}

void Tile::flag()
{
	switch (state) { // Sjekk om ruten er flagget fra for, enten flag eller unflag
	case Cell::closed:
		set_label(cellToSymbol.at(Cell::flagged));
		state = Cell::flagged;
		set_label_color(Color::blue);
		break;
	case Cell::flagged:
		set_label(cellToSymbol.at(Cell::closed));
		state = Cell::closed;
		break;
	case Cell::open:; // Kan ikke flagge åpen rute, gjør ingenting
	}
}

void Tile::reset()
{
	this->value(0);
	state = Cell::closed;
	set_label(cellToSymbol.at(Cell::closed));
	isMine = false;
}

void Tile::setAdjMines(int n)
{
	set_label(to_string(n));
	set_label_color(minesToColor.at(n));
}
