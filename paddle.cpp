#include "paddle.h"

Paddle::Paddle()
{
	x1 = 10;
	y1 = 320;
	x2 = 610;
	y2 = 240;
	velocity = 2;
	w = 20;
	h = 70;
	if(Easy) velocity = 2;
	if(Hard) velocity = 5;

	loadImage();
}

Paddle::~Paddle()
{
	SDL_FreeSurface(img);
}

void Paddle::Move( SDL_Event event )
{
	if( event.type == SDL_MOUSEMOTION)
	{
		y1 = event.motion.y;
		if( y1 < 0 )
		{
			y1 = 0;
		}
		if( y1 > SDL_GetVideoSurface()->h - h )
		{
			y1 = (float)SDL_GetVideoSurface()->h - h;
		}
	}
}

void Paddle::DrawImage()
{
	Functions::DrawImage(img, SDL_GetVideoSurface(), (int)x1, (int)y1);
	Functions::DrawImage(img1, SDL_GetVideoSurface(), (int)x2, (int)y2);
}

bool Paddle::loadImage()
{
	img = Functions::loadImage("GFX/paddle.bmp");
	img1 = Functions::loadImage("GFX/paddle.bmp");
	if(!img || !img1 )
	{
		printf("Error loading Paddle Image");
		return false;
	}

	return true;
}

void Paddle::computerAI( float y, bool cEasy, bool cHard, bool cMighty )
{
	if(cEasy)
	{
		if( y2 < y )
		{
			y2 += 3.0;
		}
		else if( y2 > y )
		{
			y2 -= 3.0;
		}

	}
	else if(cHard)
	{
		if( y2 < y )
		{
			y2 += 5.0;
		}
		else if( y2 > y )
		{
			y2 -= 5.0f;
		}
	}
	else if(cMighty)
	{
		y2 = y;
	}

	if( y2 < 0 )
		y2 = 0;
	if( y2 > SDL_GetVideoSurface()->h - h )
		y2 = (float)SDL_GetVideoSurface()->h - h;
}

SDL_Rect* Paddle::getPRect()
{
	SDL_Rect rect = { (int)x1, (int)y1, 20, 70 };
	return &rect;
}

SDL_Rect* Paddle::getCRect()
{
	SDL_Rect rect = { (int)x2, (int)y2, 20, 70 };
	return &rect;
}
