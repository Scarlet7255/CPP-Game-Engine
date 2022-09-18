#include <SDL.h>
#include "Vector.h"

namespace phong {

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

	private:
		void InitializeGameWorld();
		//we should process expected inputs from our computer
		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();

		void DrawWall();
		void DrawBall();
		void DrawBoards();
		void BallMovement(float);
		void BoardMovement(float);

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

		Vector2 mballPos;//center of the ball
		Vector2 mboard1Pos;
		Vector2 mboard2Pos;
		Vector2 mballSpeed;
		bool mGameStop;
		int minput[5]{0};
		int score[2]{ 0 };
	};

}