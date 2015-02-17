#ifndef _LOADING_H
#define _LOADING_H

#include "functions.h"

class Loading : public Functions
{
	private:
	SDL_Surface* img[3];
	SDL_Surface* bg;
	SDL_Rect rect;
	int frame;

	public:
	Loading();
	~Loading();
	virtual void DrawImage();
	virtual bool loadImage();
	void Init();
	bool getFrame();
};

#endif
