#include "Menu.h"

Menu::Menu()
{
	loadImage();
	start.x = 230, start.y = 170, start.w = 200, start.h = 50;
	high.x = 230, high.y = 220, high.w = 200, high.h = 50;
	exit.x = 280, exit.y = 270, exit.w = 100, exit.h = 50;
	Easy.x = 260, Easy.y = 170, Easy.w = 120, Easy.h = 40;
	Hard.x = 260, Hard.y = 220, Hard.w = 120, Hard.h = 40;
	Mighty.x = 250, Mighty.y = 270, Mighty.w = 140, Mighty.h = 40;
	Arrow.x = 290, Arrow.y = -100, Arrow.w = 37, Arrow.h = 40;
	Oarrow.x = 290, Oarrow.y = -100, Oarrow.w = 37, Oarrow.h = 40;
	Back.x = 100, Back.y = 400, Back.w = 120, Back.h = 40;
}

Menu::~Menu()
{
	SDL_FreeSurface(Startbutton);
	SDL_FreeSurface(Highscore);
	SDL_FreeSurface(Exit);
	SDL_FreeSurface(BG);
	SDL_FreeSurface(BG1);
	SDL_FreeSurface(easy);
	SDL_FreeSurface(hard);
	SDL_FreeSurface(mighty);
	SDL_FreeSurface(arrow);
	SDL_FreeSurface(arrow1);
}

void Menu::DrawImage()
{
	Functions::DrawImage(BG, SDL_GetVideoSurface(), 0, 0);
	Functions::DrawImage(Startbutton, SDL_GetVideoSurface(), start.x, start.y);
	Functions::DrawImage(Highscore, SDL_GetVideoSurface(), high.x, high.y);
	Functions::DrawImage(Exit, SDL_GetVideoSurface(), exit.x, exit.y);
	Functions::DrawImage(arrow, SDL_GetVideoSurface(), Arrow.x, Arrow.y);
}

bool Menu::loadImage()
{
	Startbutton = Functions::loadImage("GFX/newgame.bmp");
	Highscore = Functions::loadImage("GFX/highscore.bmp");
	Exit = Functions::loadImage("GFX/exit.bmp");
	BG = Functions::loadImage("GFX/bgtwo.bmp");
	easy = Functions::loadImage("GFX/easy.bmp");
	hard = Functions::loadImage("GFX/hard.bmp");
	mighty = Functions::loadImage("GFX/mighty.bmp");
	BG1 = Functions::loadImage("GFX/bgthree.bmp");
	arrow = Functions::loadImage("GFX/arrow.bmp");
	arrow1 = Functions::loadImage("GFX/arrow1.bmp");
	back = Functions::loadImage("GFX/back.bmp");

	if(!Startbutton || !Highscore || !Exit || !BG || !easy || !hard || !mighty || !BG1 || !arrow || !arrow1 || !back )
	{
		printf("Error loading Menu images");
		return false;
	}

	return true;
}

bool Menu::StartMouseClick(SDL_Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN )
	{
	    if( (event.button.button &Button) == Button && intersects(start.x, start.y, start.w, start.h, event.button.x, event.button.y))
	    {
		    return true;
	    }
	}

	return false;
}

void Menu::DrawArrow(SDL_Event event)
{
	if( intersects(start.x, start.y, start.w, start.h, event.button.x, event.button.y ) )
	{
		Arrow.y = start.y+10;
		Arrow.x = start.x - 6;
	}
	else if( intersects(high.x, high.y, high.w, high.h, event.button.x, event.button.y ) )
	{
		Arrow.y = high.y+10;
		Arrow.x = high.x - 20;
	}
	else if( intersects(exit.x, exit.y, exit.w, exit.h, event.button.x, event.button.y ) )
	{
		Arrow.y = exit.y+10;
		Arrow.x = exit.x-15;
	}
	else
	{
		Arrow.x = -100;
		Arrow.y = -100;
	}
}


bool Menu::ExitMouseClick(SDL_Event event)
{
	if( ( event.button.button &Button ) == Button && intersects( exit.x, exit.y, exit.w, exit.h, event.button.x, event.button.y ) )
	{
		return true;
	}
	return false;
}

void Menu::DrawNextImage()
{
	Functions::DrawImage(BG1, SDL_GetVideoSurface(), 0, 0);
	Functions::DrawImage(easy, SDL_GetVideoSurface(), Easy.x, Easy.y);
	Functions::DrawImage(hard, SDL_GetVideoSurface(), Hard.x, Hard.y);
	Functions::DrawImage(mighty, SDL_GetVideoSurface(), Mighty.x, Mighty.y);
	Functions::DrawImage(back, SDL_GetVideoSurface(), Back.x, Back.y);
	Functions::DrawImage(arrow1, SDL_GetVideoSurface(), Oarrow.x, Oarrow.y);
}

void Menu::DrawNextArrow(SDL_Event event)
{
	if( intersects(Easy.x, Easy.y, Easy.w, Easy.h, event.button.x, event.button.y) )
	{
		Oarrow.x = Easy.x+5;
		Oarrow.y = Easy.y;
	}
	else if( intersects(Hard.x, Hard.y, Hard.w, Hard.h, event.button.x, event.button.y))
	{
		Oarrow.x = Hard.x;
		Oarrow.y = Hard.y;
	}
	else if( intersects(Mighty.x, Mighty.y, Mighty.w, Mighty.h, event.button.x, event.button.y))
	{
		Oarrow.x = Mighty.x-3;
		Oarrow.y = Mighty.y;
	}
	else if( intersects(Back.x, Back.y, Back.w, Back.h, event.button.x, event.button.y))
	{
		Oarrow.x = Back.x-6;
		Oarrow.y = Back.y;
	}
	else
	{
		Oarrow.x = -100;
		Oarrow.y = -100;
	}
}

bool Menu::BackMouseClick(SDL_Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		 if( ( event.button.button &Button ) == Button && intersects( Back.x, Back.y, Back.w, Back.h, event.button.x, event.button.y ) )
	      {
		      return true;
	      }
	}
	return false;
}
		
bool Menu::EasyMouseClick(SDL_Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
	    if( ( event.button.button &Button ) == Button && intersects( Easy.x, Easy.y, Easy.w, Easy.h, event.button.x, event.button.y ) )
	   {
		   return true;
	   }
	}

	return false;
}

bool Menu::HardMouseClick(SDL_Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
	    if( ( event.button.button &Button ) == Button && intersects( Hard.x, Hard.y, Hard.w, Hard.h, event.button.x, event.button.y ) )
	    {
		    return true;
	    }
	}
	return false;
}

bool Menu::MightyMouseClick(SDL_Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if( ( event.button.button &Button ) == Button && intersects( Mighty.x, Mighty.y, Mighty.w, Mighty.h, event.button.x, event.button.y ) )
		{
			return true;
		}
	}
	return false;
}

bool Menu::OptionsMouseclick(SDL_Event event)
{	
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if( ( event.button.button &Button ) == Button && intersects( high.x, high.y, high.w, high.h, event.button.x, event.button.y ) )
		{
			return true;
		}
	}
	return false;
}
	
