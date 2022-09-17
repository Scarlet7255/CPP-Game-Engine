#include "Game.h"
using namespace std;
int main(int argc, char** argv) {
	Game game;
	bool success = game.Initialize();

	if(success)		game.GameLoop();
	return 0;
}