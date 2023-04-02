/*
MAIN
*/

# include "game.hpp"
# include "pictures.hpp"

int main() {
	std::unique_ptr<Game> game;
	game.reset(new Game());
	(*game).playGame();

	return 0;
}

