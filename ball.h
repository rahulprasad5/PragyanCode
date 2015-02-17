#ifndef _BALL_H
#define _BALL_H

#include "functions.h"
#include "game.h"
#include <string>
#include <ctime>

class Ball : public Functions
{
	private:
	float x,y;
	int w, h;
	float vx, vy;
	SDL_Surface* img;
	Mix_Chunk* bong;
	int computerscore, playerscore;

	public:
	Ball();
	~Ball();
	virtual void DrawImage();
	virtual bool loadImage();
	virtual void DrawScore();
	void Move();
	void InitSpeed( bool cEasy, bool cHard, bool cMighty );
	bool Reset();
	bool EndReset(SDL_Event event);
	void getEvent(SDL_Event event, bool cEasy, bool cHard, bool cMighty);
	SDL_Rect* getRect();
	void checkCollision();
	bool Initialize();
	TTF_Font* font1, *ofont1;
    SDL_Event event;
};

#endif
