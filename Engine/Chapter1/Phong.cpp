#include "Phong.h"
#include <iostream>
using namespace std;

namespace phong {

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
			"Phong", // window title
			100,//top left x-coordinate of window
			100,//top let y-coordinate of window
			512,//width of window
			384,//height of window
			0// flag
		);

		mRenderer = SDL_CreateRenderer(
			mWindow, // renderer renders this window
			-1, // usually -1, means use which render driver
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  //it is SDL render flag
		);


		if (mWindow == nullptr) {
			SDL_Log("Unable to create window");
			cout << SDL_GetError() << endl;
			return false;
		}
		if (mRenderer == nullptr) {
			SDL_Log("Unable to create renderer");
			cout << SDL_GetError() << endl;
			return false;
		}
		mTicksCounts = SDL_GetTicks();
		SDL_GetWindowSize(mWindow, &mWindowSize.w, &mWindowSize.h);
		
		InitializeGameWorld();

		return true;
	}

	void Game::InitializeGameWorld() {
		mballPos = Vector2{ (float)mWindowSize.w / 2, (float)(mWindowSize.h / 2) };
		mboard1Pos = Vector2{ 5.0f, (float)(mWindowSize.h / 2) };
		mboard2Pos = Vector2{ (float)(mWindowSize.w - 5), (float)(mWindowSize.h / 2) };
		int fakeR = (mTicksCounts & 1) == 1 ? 1 : -1;
		mballSpeed = Vector2{ 100.0f * fakeR,167.5f };
		mGameStop = false;
	}

	void Game::Shutdown() {
		SDL_DestroyRenderer(mRenderer);
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

	void Game::ProcessInput() {
		SDL_Event event;// it is a general structure of event

		// SDL_PollEvent assign the event and return true if there is event
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				mIsRunning = false;
				break;
			} 
		
		}


		//Unit8 is a SDL defined 8 bits unsigned short 
		const Uint8* state = SDL_GetKeyboardState(NULL);
		//get input from keyboard
		minput[0] = state[SDL_SCANCODE_W];
		minput[1] = state[SDL_SCANCODE_S];
		minput[2] = state[SDL_SCANCODE_UP];
		minput[3] = state[SDL_SCANCODE_DOWN];
		minput[4] = state[SDL_SCANCODE_C];
		if (state[SDL_SCANCODE_ESCAPE]) {//when press escape, stop game
			mIsRunning = false;
		}

	}

	void Game::UpdateGame() {
		Uint32 expectCounts = mTicksCounts + 16;
		while (SDL_GetTicks() < expectCounts);// wait until 16 ms pass
		float deltaTime = (SDL_GetTicks() - mTicksCounts)/1000.0f; //it stores counts of ms
		mTicksCounts = SDL_GetTicks();
		deltaTime = min(deltaTime,0.5f);
		//TODO: Update objects in game world uas function as delta time
		//calculate direction of board movement
		if (!mGameStop) {
			BoardMovement(deltaTime);
			BallMovement(deltaTime);
		}
		else if (minput[4]>0) {
			InitializeGameWorld();
		}
	}

	void Game::GenerateOutput() {

		// ask renderer use this color to draw
		SDL_SetRenderDrawColor(mRenderer,
			100, // r
			100, // g 
			100, // b
			255); // alpha

		SDL_RenderClear(mRenderer); // use it to write whole buffer
		
		DrawWall();
		DrawBall();
		DrawBoards();

		/** Draw game scenes here, we will do it soon */
		SDL_RenderPresent(mRenderer); // swap background buffer with screen buffer 
	}

	void Game::DrawWall() {
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 200, 255);
		SDL_Rect wallu{
			0,
			0,
			512,
			10
		};

		SDL_Rect walld{
		0,
		mWindowSize.h - 10,
		512,
		10
		};

		SDL_RenderFillRect(mRenderer, &wallu);
		SDL_RenderFillRect(mRenderer, &walld);
	}

	void Game::DrawBall() {
		SDL_Rect ball{
		static_cast<int>(mballPos.x - 10.0f),
		static_cast<int>(mballPos.y - 10.0f),
		20,
		20
		};
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
		SDL_RenderFillRect(mRenderer, &ball);
	}

	void Game::DrawBoards() {
		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
		SDL_Rect board1{
			static_cast<int>(mboard1Pos.x - 5.f),
			static_cast<int>(mboard1Pos.y - 30.0f),
			10,
			60
		};

		SDL_Rect board2{
			static_cast<int>(mboard2Pos.x - 5.0f),
			static_cast<int>(mboard2Pos.y - 30.0f),
			10,
			60
		};

		SDL_RenderFillRect(mRenderer,&board1);
		SDL_RenderFillRect(mRenderer, &board2);
	}
	
	void Game::BallMovement(float deltaTime) {

		if (mballPos.x < -10 || mballPos.x > mWindowSize.w + 10) {
			mGameStop = true;
			return;
		}

		// deal with collision with wall
		if (mballPos.y < 20.f && mballSpeed.y < 0) mballSpeed.y *= -1;
		if (mballPos.y > mWindowSize.h-20 && mballSpeed.y > 0) mballSpeed.y *=-1;

		//deal with collision with board
		if (mballPos.x < 20 && abs(mballPos.y - mboard1Pos.y) < 40 && mballSpeed.x < 0) mballSpeed.x *= -1;
		if (mballPos.x > mboard2Pos.x-15 && abs(mballPos.y - mboard2Pos.y) < 40 && mballSpeed.x > 0) mballSpeed.x *= -1;

		mballPos.x += mballSpeed.x * deltaTime;
		mballPos.y += mballSpeed.y * deltaTime;
	}

	void Game::BoardMovement(float deltaTime) {
		int dir1 = minput[1] - minput[0];
		int dir2 = minput[3] - minput[2];
		
		if((dir1<0 && mboard1Pos.y>40 )|| (dir1>0 && mboard1Pos.y<mWindowSize.h-40))mboard1Pos.y += dir1 * deltaTime * 100.0f;
		if ((dir2 < 0 && mboard2Pos.y > 40) || (dir2 > 0 && mboard2Pos.y < mWindowSize.h - 40))mboard2Pos.y += dir2 * deltaTime * 100.0f;
	}
}


