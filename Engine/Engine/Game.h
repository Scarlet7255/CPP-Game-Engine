#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "GameObject.h"

using namespace std;
struct WindowSize {
	int w, h;
};

class Game
{
public:
	Game();
	// initialize a game
	bool Initialize();

	// runs game loop until game is over
	void GameLoop();
	void Shutdown();

	// create new GameObject, suppose to use it dynamicly 
	class GameObject* CreateGameObject(string name = "GameObject");
	// add GameObject
	void AddGameObject(class GameObject*);
	// remove GameObject
	void RemoveGameObject(class GameObject*);


	SDL_Texture* GetTexture(string);
	void AddSprite(class Sprite*);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// load data from file
	bool LoadData();

	// game should continue running
	bool mIsRunning;
	// we use this render draw the graphics
	SDL_Renderer* mRenderer;
	// window created by SDL
	SDL_Window* mWindow;
	// record our client window size
	WindowSize mWindowSize;
	// record time count since last frame
	Uint32 mTicksCounts;

	//record textures has been created
	unordered_map <string, SDL_Texture* > mTextureAssets;


	vector<class GameObject*> activeList;
	vector<class GameObject*> pendingList;
	vector<class GameObject*> deadList;

	vector<class Sprite*> mSpriteList;
};
#endif // !GAME_H



