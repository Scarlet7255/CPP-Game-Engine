# 第一章 游戏编程概述

## 1.1 使用到的 C++ 以外的库

&emsp;&emsp;在第一章中，除了 C++的标准库以外，也需要用到 SDL 库，SDL 库是一个 C 语言编写的跨平台游戏开发库，支持包括创建窗口、2D 图像、输入输出、音频处理等常用游戏功能。同时这个库也是后期游戏会用到的主要的库。

## 1.2 关于游戏循环

&emsp;&emsp;游戏在运行过程中属于循环的过程，只要游戏在运行，那么每一秒都需要对游戏中的各种逻辑进行多次更新。只要玩家没有退出游戏，那么游戏的循环将不会退出。

&emsp;&emsp;每一次游戏循环都是一帧，大多数游戏每秒会运行 30 到 60 帧，这就说明了我们的游戏逻辑将会在一秒内循环 30 或 60 次。这种高频率的游戏更新，将会给玩家带来画面连续运动的感觉。我们通常用**帧率**来描述每秒中游戏的循环次数。

&emsp;&emsp;在每一次游戏循环中（每一帧），游戏循环需要处理以下内容：

1. 处理来自外部的输入
2. 更新游戏世界各种信息
3. 输出内容

&emsp;&emsp;第一个步骤，处理来自外部的输入。这个不一定只是键盘鼠标的输入，如果你的引擎还考虑别的平台设备，比如手柄等，你也必须能处理，即**你必须确保你能够能检测各种来自你引擎支持的设备的输入**。同时在网络游戏中，输入包括了**各种来自互联网的输入**，比如用于帧同步的 UDP 数据报。

&emsp;&emsp;第二个步骤，更新游戏世界。这个指的是在每一次游戏循环中都要仔细检查游戏中的各个对象，并且按照代码的逻辑将对象的各种属性进行更新，比如 transform(中文名变换,这是一种用于计算机描述一个对象在空间中的属性，包括缩放，位置，旋转等，因为变换这个词太过直译因此之后统一使用 transform)、颜色等。这些对象包括代码循环中的功能性对象，比如时钟，对象池等，这些往往是不可见的；以及具体游戏中的各个自定义对象，比如游戏中的人物，UI，场景等。

&emsp;&emsp;最后一个步骤，输出。作为一个游戏，最重要的就是输出图像，同时也可能伴随着音效震动等额外反馈。

&emsp;&emsp;综上，整个流程伪代码如下：

```C++
    void Game::GameLoop()
    {
        if(!mShouldQuit)//如果不需要退出
        {
            HandleInput();//接受与处理输入
            UpdateGame();//根据输入与代码逻辑更新游戏中的对象
            GenerateOutput();//产生输出，
        }
    }
```

&emsp;&emsp;对于以前的游戏来说，游戏能够刚刚好在一定的时间内完成它的所有更新并且输出，但是随着现在 CPU 等硬件的进步，不能再像以前直接通过写一定时间复杂度的代码控制循环，我们需要用到系统时间来帮我们更好地执行循环。利用系统时间还有个好处，允许我们通过获取两帧之间的时间差来调整 UpdateGame 的频率以尽可能消除游戏在不同设备上游戏循环的差异。而这些会在稍后讲到。

&emps;&emps;Unity 的 MonoBehaviour 生命周期就是一个比较著名是游戏循环。[Unity MonoBehaviour](!https://docs.unity3d.com/Manual/ExecutionOrder.html)

## 1.2 Game 类骨架

&emsp;&emsp;我们现在先制作一个 Game 类的骨架，这个骨架应该包括以下内容：

1. 前文提到的各种游戏循环应该处理的方法声明。
2. 允许开始与结束游戏。
3. 创建游戏窗口。

因为使用到了 SDL 提供创建窗口的功能，因此我们需要引用 [SDL 库](https://github.com/libsdl-org/SDL/releases)。#include<SDL.h>

```c++
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
	SDL_Window* mwindow;
	// game should continue running
	bool mIsRunning;
};

```

&emsp;&emsp;Game 对象的初始化不需要做什么事情，把 mIsRunning 设置为 true，mwindow 设置为 nullptr 就好。

```c++
Game::Game() {
	mwindow = nullptr;
	mIsRunning = true;
}
```

### Game::Initialize()方法

&emsp;&emsp;这个方法我们用来进行项目的初始化，它要做的工作即创建游戏窗口。

```c++
bool Game::Initialize() {
	// We use it to initialize video system, it returns 0 if unable to initialize
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize the game");
        return false;
	}
    ...
	return true;
}

```

&emsp;&emsp;SDL_Init()这个函数接受一个单一参数(标志位)来初始化对应子系统，而我们在这里初始化的就是视频子系统。这个方法的返回值为一个整数，如果返回值不为 0 的话，那么说明此次创建失败。

&emsp;&emsp;常用子系统包括。

1. SDL_INIT_AUDIO 初始化音频子系统
2. SDL_INIT_VIDEO 初始化视频子系统，其可以连接 OpenGL 库和 2D 图形库
3. SDL_INIT_HAPTIC 力反馈子系统
4. SDL_INIT_GAMECONTROLLER 输入设备子系统

我们可以通过或位运算标志一次创建多个子系统，即

```c++
int sdlResult = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_HAPTIC|SDL_INIT_GAMECONTROLLER);
```

&emsp;&emsp;接下来就是创建具体的窗口。

```c++
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
```

&emsp;&emsp;SDL_CreateWindow()函数接受的参数包括窗口的名称（通常就是游戏名），左上角坐标，窗口大小，以及窗口创建标志。
&emsp;&emsp;窗口标志用于配置一些窗口的属性，当我们把窗口标志设置为 0 的时候，窗口不会有任何特别。常用标志包括以下内容:

1. SDL_WINDOW_FULLSCREEN 全屏进行游戏
2. SDL_WINDOW_FULLSCREEN_DESKTOP 在当前桌面分辨率下使用全屏模式(忽视 CreateWindow 的其它参数)
3. SDL_WINDOW_OPENGL 添加对 OpenGL 库的支持
4. SDL_WINDOW_RESIZEABLE 允许用户调整窗口大小

&emsp;&emsp;同前面的创建子系统，也允许使用或位运算一次性开启多个标志。虽然很多游戏都是全屏，玩起来也爽，但是这样不利于开发者的调试。
&emsp;&emsp;整个 Initialize 的代码如下:

```c++
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
```

### Game::Shutdown 方法

&emsp;&emsp;Shutdown 方法和 Initialize 方法相反，Shutdown 方法只要你销毁掉 SDL_Window，关闭 SDL 库，结束游戏循环即可。

```c++
void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	mIsRunning = false;
}
```

### Game::GameLoop 方法

&emsp;&emsp;GameLoop 方法具体该干什么已经在游戏循环中讲了，我们暂时不实现它里面的三个方法，这样的话运行后什么也不会做，但是并不会报错。

