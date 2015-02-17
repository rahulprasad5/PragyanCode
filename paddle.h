#ifndef _PADDLE_H
#define _PADDLE_H

#include "functions.h"
#include "game.h"

class Paddle : public Functions
{
	private:
	float x1, y1, x2, y2;
	float velocity;
	int w, h;
	SDL_Surface *img, *img1;

	public:
	Paddle();
	~Paddle();
	virtual void DrawImage();
	virtual bool loadImage();
	void Move( SDL_Event event );
	void computerAI( float y, bool cEasy, bool cHard, bool cMighty);
	SDL_Rect* getPRect(); //Players rect
	SDL_Rect* getCRect(); //Computers rect
};

#endif 
	
