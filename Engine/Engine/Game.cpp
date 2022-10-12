#include "Game.h" 
#include "GameObject.h"
#include "SDL.h"
#include "SDL_Image.h"
#include "Sprite.h"
#include <iostream>

using namespace std;

#pragma region Game Initialize
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
		"Chapter2", // window title
		100,//top left x-coordinate of window
		100,//top let y-coordinate of window
		512,//width of window
		512,//height of window
		0// flag
	);

	mRenderer = SDL_CreateRenderer(
		mWindow, // renderer renders this window
		-1, // usually -1, means use which render driver
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  //it is SDL render flag
	);
	
	IMG_Init(IMG_INIT_PNG);

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
	LoadData();
	return true;
}

#pragma endregion

#pragma region GameLoop

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
	//...
	if (state[SDL_SCANCODE_ESCAPE]) {//when press escape, stop game
		mIsRunning = false;
	}

	for (auto it = activeList.begin(); it != activeList.end(); it++) {
		(*it)->ProcessInput(state);
	}
}

void Game::UpdateGame() {

	// Calculate delta time
	Uint32 expectCounts = mTicksCounts + 16;
	while (SDL_GetTicks() < expectCounts);// wait until 16 ms pass

	float deltaTime = (SDL_GetTicks() - mTicksCounts) / 1000.0f; //it stores counts of ms
	mTicksCounts = SDL_GetTicks();
	deltaTime = min(deltaTime, 0.5f);
	
	for (auto it = activeList.begin(); it != activeList.end(); ) {
		if ((*it)->IsActive()) {
			(*it)->Update(deltaTime);
			++it;
		}
		else if ((*it)->IsDead()) {
			deadList.push_back(*it);
			it = activeList.erase(it);
		}

	}
	for (auto it = pendingList.begin(); it != pendingList.end(); it++) {
		activeList.emplace_back(*it);
		(*it)->Awake();
	}
	pendingList.clear();

	for (auto it = deadList.begin(); it != deadList.end(); it++) {
		delete (*it);
	}
	deadList.clear();
}

void Game::GenerateOutput() {

	SDL_RenderClear(mRenderer); // use it to write whole buffer
	for (auto it = mSpriteList.begin(); it != mSpriteList.end();) {
		if ((*it) != nullptr) {
			(*it)->Draw(mRenderer);
			++it;
		}
		else {
			it = mSpriteList.erase(it);
		}
	}
	SDL_RenderPresent(mRenderer); // swap background buffer with screen buffer
}

#pragma endregion

#pragma region Add and Remove GameObject

GameObject* Game::CreateGameObject(string name) {
	GameObject* obj = new GameObject(this, name);
	pendingList.emplace_back(obj);
	return obj;
}

void Game::AddGameObject(GameObject *gameObject) {
	pendingList.emplace_back(gameObject);
}

#pragma endregion

#pragma region LoadResource

SDL_Texture* LoadTexture(const char url[],  SDL_Renderer  *mRenderer) {
	SDL_Surface*  surface= IMG_Load(url);
	if (surface == nullptr) {
		SDL_Log("Failed to load texture from file %s",url);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer,surface);
	if (texture == nullptr) {
		SDL_Log("Failed to convert texture from file %s", url);
		return nullptr;
	}
	return texture;
}

bool Game::LoadData() {
	return false;
}

SDL_Texture* Game::GetTexture(string texUrl) {
	if (mTextureAssets[texUrl] != nullptr) {
		return mTextureAssets[texUrl];
	}
	else {
		SDL_Texture* res = LoadTexture(texUrl.data(), mRenderer);
		mTextureAssets.insert({ texUrl, res });
		return res;
	}
}
#pragma endregion

#pragma region Component Relative Behaviour
void Game::AddSprite(Sprite* sprite) {
	int order =  sprite->GetDrawOrder();
	auto iter = mSpriteList.begin();
	for (; iter != mSpriteList.end(); ++iter) {
		if (order < (*iter)->GetDrawOrder()) break;
	}
	mSpriteList.insert(iter,sprite);
}

void Game::AddCollider(CircleCollider* collider) {
	mColliderList.push_back(collider);
}

void Game::RemoveSprite(Sprite* sprite) {
	for (auto it = mSpriteList.begin(); it != mSpriteList.end(); it++) {
		if ((*it) == sprite) {
			mSpriteList.erase(it);
			break;
		}
	}
}

void Game::RemoveCollider(CircleCollider* collider) {
	for (auto it = mColliderList.begin(); it != mColliderList.end(); it++) {
		if ((*it) == collider) {
			mColliderList.erase(it);
			break;
		}
	}
}
#pragma endregion

#pragma region Collide Detect

bool Intersect(const CircleCollider& a, const CircleCollider& b) {
	Eigen::Vector2f posa = a.Center, posb = b.Center;
	Eigen::Vector2f diff = posa - posb;
	return  diff.dot(diff) <= powf((a.Radius + b.Radius), 2);
}

bool Game::CollideDetect(const CircleCollider* collider) {
	for (auto it = mColliderList.begin(); it != mColliderList.end(); it++) {
		if ((*it) == nullptr) {
			mColliderList.erase(it);
			SDL_Log("Collider Removed");
		}
		else if ((*it) != collider) {
			if (Intersect(*collider, *(*it))) return true;
		}

	}
	return false;
}
#pragma endregion


void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	mIsRunning = false;
}