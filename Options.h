#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "functions.h"

class Options : public Functions
{
	private:
	TTF_Font* font;
	SDL_Surface* BG, *back, *temp;
	SDL_Rect Back, text, vol;

	public:
	Options();
	~Options();
	virtual void xDrawText();
	bool BackMouseClick(SDL_Event event);
	bool OnMouseClick(SDL_Event event);
	void PlusMouseClick(SDL_Event event);
	bool clickedoff, clickplus, clickminus;
};

#endif
