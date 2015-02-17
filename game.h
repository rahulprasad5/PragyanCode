#ifndef _GAME_H
#define _GAME_H

#include <Windows.h>
#include "Timer.h"
#include "paddle.h"
#include "Menu.h"
#include "ball.h"
#include "Loading.h"
#include "DJ.h"
#include "Options.h"

enum gamestate
{
	Intro,
	Load,
	Main,
	options,
	Difficulty,
	MainGame,
	Exit,
};


class Game : public Functions
{
	private:
	SDL_Surface* screen, *bg;
	SDL_Event event;
	bool running;
	int CurrentVolume;
	Mix_Chunk* click, *Introsound;
	public:
	Game();
	~Game();
	void Start();
	void Init();
	void HandleEvents();
	static bool Collide();
	static bool SideCollide();
};

#endif
