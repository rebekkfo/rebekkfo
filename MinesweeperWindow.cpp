#include "MinesweeperWindow.h"

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize, (height + 1) * cellSize, title},
	width{width}, height{height}, mines{mines}, minesLeftUser{mines},
	remainingTiles{height * width - mines},
	minesLeftText{0, height*cellSize, width*cellSize, cellSize},
	gameRestart{Width() / 2 - 60, Height() / 2, 60, 40, "Restart"},
	gameQuit{Width() / 2, Height() / 2, 60, 40, "Quit"},
	gameEndText{Width() / 2 - 60, Height() / 2 - 40, 120, 40, " "}
{
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->callback(cb_click, this);
			add(tiles.back().get()); 
		}
	}

	// Legger til miner paa tilfeldige posisjoner
	int i = 0;
	while (i < mines) {
		int pos = rand() % tiles.size();
		if (!tiles[pos]->getIsMine()) {
			tiles[pos]->setIsMine(true);
			++i;
		}
	}

	// Legger til felt overst i vinduet for aa markere antall miner som gjenstaar
	minesLeftText.textsize(20);
	minesLeftText.color(Color::black);
	minesLeftText.textcolor(Color::mid_gray);
	minesLeftText.value(("Mines left: " + to_string(minesLeftUser)).c_str());
	add(minesLeftText);

	// Legger til buttons i spillsluttmenyen
	gameRestart.callback(cb_restart, this);
	add(gameRestart);
	gameQuit.callback(cb_quit, this);
	add(gameQuit);
	gameRestart.hide();
	gameQuit.hide();

	// Fjern window reskalering
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());
}

int MinesweeperWindow::countMines(vector<Point> points) const {
	int adjacentMines = 0;
	for (Point p : points) {
		if (at(p)->getIsMine()) {
			++adjacentMines;
		}
	}
	return adjacentMines;

	// Alternativt <algorithm>
	//  return std::count_if(points.begin(), points.end(), [this](auto point){
	//  	return at(point)->getIsMine();
	//  });
};
vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}

	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	shared_ptr<Tile>& tile = at(xy);

	// Reagerer kun hvis Tile er lukket
	if (tile->getState() != Cell::closed) {
		return;
	}

	// Hvis tilen er en mine er spillet over
	if (tile->getIsMine()) {
		gameLost();
		return;
	}

	tile->open();
	remainingTiles--;

	vector<Point> adjPoints = adjacentPoints(xy);
	int adjMines = countMines(adjPoints);

	if (adjMines > 0) { 
		// Hvis det er miner i naerheten setter vi labelen
		tile->setAdjMines(adjMines);
	}
	else {
		// Hvis det ikke er noen miner i naerheten vil vi aapne tilene rundt rekursivt 
		for (Point p : adjPoints) {
			openTile(p);
		}
	}

	if (remainingTiles == 0 && !gameIsWon) {
		gameWon();
		return;
	}
}

void MinesweeperWindow::flagTile(Point xy) {

	shared_ptr<Tile>& tile = at(xy);

	tile->flag();
	if (tile->getState() == Cell::flagged) {
		// Hvis den ble flagget markerer vi at brukeren har en mindre mine igjen aa flagge
		minesLeftUser--;
	}
	else if(tile->getState() == Cell::closed) {
		// Hvis ikke markerer vi at brukeren har en mer mine igjen aa flagge
		minesLeftUser++;
	}

	// Oppdaterer teksten i toppen av vinduet
	minesLeftText.value(("Mines left: " + to_string(minesLeftUser)).c_str());
}

void MinesweeperWindow::click()
{
	Point xy{Fl::event_x(), Fl::event_y()};

	MouseButton mb = static_cast<MouseButton>(Fl::event_button());

	if (!inRange(xy) || gameIsLost || gameIsWon) {
		return;
	}

	switch (mb) {
	case MouseButton::left:
		openTile(xy);
		break;
	case MouseButton::right:
		flagTile(xy);
		break;
	}
}

void MinesweeperWindow::restart() {

	for (auto tile : tiles) {
		tile->reset();
	}

	// Fjerner spillsluttmenyen
	gameRestart.hide();
	gameQuit.hide();
	remove(gameEndText);

	// Plasser nye miner
	int mineCount = 0;
	while (mineCount < mines) {
		int pos = rand() % tiles.size();
		if (!tiles[pos]->getIsMine()) {
			tiles[pos]->setIsMine(true);
			++mineCount;
		}
	}

	// Nullstiller variabler
	remainingTiles = width * height - mines;
	gameIsLost = false;
	gameIsWon = false;
	minesLeftUser = mines;
	minesLeftText.value(("Mines left: " + to_string(minesLeftUser)).c_str());
};

void MinesweeperWindow::gameLost() {
	gameIsLost = true;
	for (auto tile : tiles) {
		if (tile->getIsMine()) {
			tile->open();
		}
	}

	// Legger til meny for at spillet er tapt
	addGameEndMenu("Game Over", Color::red);
};

void MinesweeperWindow::gameWon() { 
	gameIsWon = true;

	for (auto tile : tiles) {
		if (tile->getState() == Cell::closed) {
			tile->flag();
		}
	}

	// Legger til meny for at spillet er vunnet
	addGameEndMenu("Game Won", Color::green);
};

void MinesweeperWindow::addGameEndMenu(string s, Fl_Color c) {
	// setter riktig font og farger til vinn eller tap
	gameEndText.value(s.c_str());
	gameEndText.color(c);
	gameEndText.textcolor(Color::black);
	gameEndText.textsize(20);

	// Legger til menyen paa vinduet
	add(gameEndText);
	gameRestart.show();
	gameQuit.show();
}
