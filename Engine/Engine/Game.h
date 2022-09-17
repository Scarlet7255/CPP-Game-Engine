#include <SDL.h>
class Game
{
public:
	Game();
	// initialize a game
	bool Initialize();
	// runs game loop until game is over
	void GameLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// window created by SDL
	SDL_Window* mWindow;
	// game should continue running
	bool mIsRunning;
};

Game::Game() {
	mWindow = nullptr;
	mIsRunning = true;
}

bool Game::Initialize() {
	// We use it to initialize video system, it returns 0 if unable to initialize
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize the game");
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // window title
		100,//top left x-coordinate of window
		100,//top let y-coordinate of window
		1024,//width of window
		768,//height of window
		0// flag
	);

	if (mWindow == nullptr) {
		SDL_Log("Unable to create window");
		return false;
	}
	return true;
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	mIsRunning = false;
}

void Game::GameLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {}
void Game::UpdateGame() {}
void Game::GenerateOutput() {}