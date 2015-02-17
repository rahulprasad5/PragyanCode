#ifndef _DJ_H
#define _DJ_H

#include "functions.h"
#include <ctime>

class DJ : public Functions
{
	private:
	Mix_Music* Sound[5];
	TTF_Font* font, *ofont;
	int current, temp;
	const char *text;

	public:
	DJ();
	~DJ();
	bool loadMusic();

	void xPlaySound();
	bool Reset();
	void PlayNext();
	void ShowCurrent();
};

#endif
