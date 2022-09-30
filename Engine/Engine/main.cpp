#include<iostream>
#include "Game.h"
#include "Character.h"
#include "BackgroundObj.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	Game* game = new  Game();
	game->Initialize();
	game->AddGameObject(new Character(game));
	game->AddGameObject(new BackgroundObj(game));
	game->GameLoop();
	return 0;
}