#include "Phong.h"

using namespace phong;
int main(int argc, char** argv) {

	Game game;
	bool success = game.Initialize();

	if (success)	game.GameLoop();
	game.Shutdown();
	return 0;
}