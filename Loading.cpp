#include "Loading.h"

Loading::Loading()
{
	frame = 0;
	loadImage();
	Init();
}

Loading::~Loading()
{
	for( int i = 0; i < 3; i++ )
	{
		SDL_FreeSurface(img[i]);
	}
	SDL_FreeSurface(bg);
}

void Loading::Init()
{
	rect.w = 300;
	rect.h = 100;
	rect.x = (rect.w+rect.h)/2;
	rect.y = (rect.w+rect.h)/2;
}

bool Loading::loadImage()
{
	img[0] = Functions::loadImage("GFX/one.bmp");
	img[1] = Functions::loadImage("GFX/two.bmp");
	img[2] = Functions::loadImage("GFX/three.bmp");
	bg = Functions::loadImage("GFX/bgfour.bmp");
	for( int i = 0;i < 3; i++ )
	{
		if(!img[i])
		printf("Error loading Load menu imgs");
	}
	return true;
}

void Loading::DrawImage()
{
	SDL_Delay(500);
	frame++;
	if(frame > 2)
	{
		frame = 0;
	}
	Functions::DrawImage(bg, SDL_GetVideoSurface(), 0, 0);
	Functions::DrawImage(img[frame], SDL_GetVideoSurface(), rect.x, rect.y);

}

bool Loading::getFrame()
{
	int i = SDL_GetTicks();
	if( i > 16000 && frame == 2 )
	{
		return true;
	}
	return false;
}
