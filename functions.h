#ifndef _FUNCTION_H
#define _FUNCTION_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <sstream>

const Uint8 Button = SDL_BUTTON_LEFT;
class Functions
{
	public:
	Functions();
    void DrawImage( SDL_Surface* img, SDL_Surface* screen, int x, int y );
    SDL_Surface* loadImage( const char* filename );
	bool intersects( int objectX, int objectY, int objectW, int objectH, int mouseX, int mouseY );
	bool Easy, Hard, Mighty;
	void xDrawScore( SDL_Color color, TTF_Font* font, int Input, int x, int y );
	void xDrawText( SDL_Color color, TTF_Font* font, const char[30], int x, int y );
	void xPlaySound(int channel, Mix_Chunk* chunk, int loops);
};

#endif
