#ifndef _MENU_H
#define _MENU_H

#include "functions.h"

class Menu : public Functions
{
	private:
	SDL_Rect start, high, exit, Easy, Hard, Mighty, Arrow, Oarrow, Back;
	SDL_Surface *Startbutton, *Highscore, *Exit, *BG, *easy, *hard, *mighty, *BG1, *arrow, *arrow1, *back;
	public:
	Menu();
	~Menu();
	virtual void DrawImage();
	void DrawNextImage();
	virtual bool loadImage();
	bool StartMouseClick(SDL_Event event);
	void DrawArrow(SDL_Event event);
	bool ExitMouseClick(SDL_Event event);
	bool DifficultyLevel(SDL_Event event);
	void DrawNextArrow(SDL_Event event);
	bool EasyMouseClick(SDL_Event event);
	bool HardMouseClick(SDL_Event event);
	bool MightyMouseClick(SDL_Event event);
	bool BackMouseClick(SDL_Event event);
	bool OptionsMouseclick(SDL_Event event);

};


#endif
