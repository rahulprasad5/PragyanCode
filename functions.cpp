#include "functions.h"

Functions::Functions()
{
	Easy = false;
	Hard = false;
	Mighty = false;
}


void Functions::DrawImage( SDL_Surface* img, SDL_Surface* screen, int x, int y )
{
	SDL_Rect alue;
	alue.x = x;
	alue.y = y;
	SDL_BlitSurface(img, NULL, screen, &alue);
}

SDL_Surface* Functions::loadImage( const char* filename )
{
	SDL_Surface *temp1 = NULL;
	temp1 = SDL_LoadBMP(filename);
	return temp1;
}

bool Functions::intersects(int objectX, int objectY, int objectW, int objectH, int mouseX, int mouseY )
{
	if( mouseX < objectX || mouseY < objectY )
	{
		return false;
	}
	if( mouseX > objectX+objectW || mouseY > objectY+objectH )
	{
		return false;
	}

	return true;
}

void Functions::xDrawScore( SDL_Color color, TTF_Font* font, int Input, int x, int y )
{
	std::stringstream name;
	name << " " << Input;
	SDL_Surface* temp = TTF_RenderText_Solid(font, name.str().c_str(), color);
	DrawImage(temp, SDL_GetVideoSurface(), x, y);

}

void Functions::xDrawText( SDL_Color color, TTF_Font* font, const char text[30], int x, int y )
{
	SDL_Surface* temp = TTF_RenderText_Solid(font, text, color);
	DrawImage(temp, SDL_GetVideoSurface(), x, y);
}

void Functions::xPlaySound(int channel, Mix_Chunk* chunk, int loops)
{
	Mix_PlayChannel(channel, chunk, loops);
}
