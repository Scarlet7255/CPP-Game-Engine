#include<iostream>
#include "Game.h"
#include "Character.h"
#include "BackgroundObj.h"
#include "Obstacle.h"
#include "Angle.h"
#include <string>
#include <Eigen/Core>
#include<Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
	

	Game* game = new  Game();
	game->Initialize();
	game->AddGameObject(new Character(game));
	game->AddGameObject(new BackgroundObj(game));
	game->AddGameObject(new Obstacle(game));
	game->AddGameObject(new Angle(game));
	game->GameLoop();
	return 0;
}