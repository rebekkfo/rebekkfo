#pragma once
#include "AnimationWindow.h"
#include "Tile.h"

enum class MouseButton { left = FL_LEFT_MOUSE, right = FL_RIGHT_MOUSE }; 

// Minesweeper GUI
class MinesweeperWindow : public AnimationWindow
{
public:
	// storrelsen til hver tile
	static constexpr int cellSize = 30;

	MinesweeperWindow(int x, int y, int width, int height, int mines, const string& title);
private:
	const int width;		// Bredde i antall tiles
	const int height;		// Hoyde i antall tiles
	const int mines;		// Antall miner
	int minesLeftUser;		// Antall miner spilleren har markeret at er igjen
	vector<shared_ptr<Tile>> tiles; // Vektor som inneholder alle tiles

	int remainingTiles; // Antall uaapnede tiles som gjenstaar for spillet er vunnet
	bool gameIsLost = false; 
	bool gameIsWon = false; 

	// hoyde og bredde i piksler
	int Height() const { return height * cellSize; } 
	int Width() const { return width * cellSize; }

	// Returnerer en vektor med nabotilene rundt en tile, der hver tile representeres som et punkt
	vector<Point> adjacentPoints(Point xy) const;
	// tell miner basert paa en liste tiles
	int countMines(vector<Point> coords) const;

	// Sjekker at et punkt er paa brettet
	bool inRange(Point xy) const { return xy.x >= 0 && xy.x< Width() && xy.y >= 0 && xy.y < Height(); }
	// Returnerer en tile gitt et punkt
	shared_ptr<Tile>& at(Point xy) { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }
	const shared_ptr<Tile>& at(Point xy) const { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }

	void openTile(Point xy);
	void flagTile(Point xy);

	// callback funksjoner for de tre knappene
	static void cb_quit(Fl_Widget*, void* pw) { static_cast<MinesweeperWindow*>(pw)->hide(); };
	static void cb_restart(Fl_Widget*, void* pw) { static_cast<MinesweeperWindow*>(pw)->restart(); }
	static void cb_click(Fl_Widget*, void* pw) { static_cast<MinesweeperWindow*>(pw)->click(); };
	void restart();
	void click();

	// Funksjoner som sjekker om spillet er vunnet eller tapt
	void gameLost();
	void gameWon();

	void addGameEndMenu(string s, Fl_Color c);

	// Medlemsvariabler knyttet til teksten nederst i vinduet
	Fl_Output minesLeftText;

	// Medlemsvariabler knyttet til spillslutt
	Fl_Button gameRestart;
	Fl_Button gameQuit;
	Fl_Output gameEndText;
};
