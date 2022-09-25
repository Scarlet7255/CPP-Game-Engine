#pragma once
#include <SDL.h>
#include <vector>
#include <string>

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

	// create new GameObject
	void CreateGameObject(string name = "GameObject");
	// remove GameObject
	void RemoveGameObject(class GameObject*);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

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

	vector<class GameObject*> activeList;
	vector<class GameObject*> pendingList;
	vector<class GameObject*> deadList;

};

