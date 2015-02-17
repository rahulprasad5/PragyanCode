#include "Options.h"

Options::Options()
{
	TTF_Init();
	font = TTF_OpenFont("GFX/pf_tempesta_five.ttf", 24);
	if(!font)
	{
		printf("Error loading Option font");
	}
	temp = NULL;
	BG = Functions::loadImage("GFX/bgfive.bmp");
	back = Functions::loadImage("GFX/back.bmp");
	Back.x = 100, Back.y = 400, Back.w = 120, Back.h = 40;
	text.x = 350, text.y = 170, text.w = 50, text.h = 40;
	vol.x = 370, vol.y = 220, vol.w = 30, vol.h = 30;
	clickedoff = false;
	clickplus = false;
	clickminus = false;
}

Options::~Options()
{
	TTF_CloseFont(font);
	SDL_FreeSurface(BG);
	SDL_FreeSurface(back);
}

void Options::xDrawText()
{
	Functions::DrawImage(BG, SDL_GetVideoSurface(), 0, 0);
	Functions::DrawImage(back, SDL_GetVideoSurface(), Back.x, Back.y);
	SDL_Color color = { 0xED, 0xCC, 0xFF };
	Functions::xDrawText(color, font, "Music: ", 230, 170);
	const char* TEXT = "OFF";
	if(clickedoff)
	{
		TEXT = "ON";
	}
	temp = TTF_RenderText_Solid(font, TEXT, color);
	Functions::DrawImage(temp, SDL_GetVideoSurface(), text.x, text.y);
	Functions::xDrawText(color, font, "Volume: ", 230, 220);
	Functions::xDrawText(color, font, "- ", vol.x, vol.y);
	Functions::xDrawText(color, font, "+ ", vol.x+40, vol.y);
	Functions::xDrawText(color, font, "Tip: Press 'n' to shift songs", 100, 350);
}

bool Options::BackMouseClick(SDL_Event event)
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

bool Options::OnMouseClick(SDL_Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		 if( ( event.button.button &Button ) == Button && intersects( text.x, text.y, text.w, text.h, event.button.x, event.button.y ) )
	      {
			  if( clickedoff == false )
			  {
				  clickedoff = true;
				  return clickedoff;
			  }
			  else clickedoff = false;
	      }
	}
	return clickedoff;
}


void Options::PlusMouseClick(SDL_Event event)
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		 if( ( event.button.button &Button ) == Button && intersects( vol.x+40, vol.y, vol.w, vol.h, event.button.x, event.button.y ) )
	      {
			  if(clickplus == false)
			  {
				  clickplus = true;
			  }
			  else clickplus = false;
	      }
		 else clickplus = false;
		 if( ( event.button.button &Button ) == Button && intersects( vol.x, vol.y, vol.w, vol.h, event.button.x, event.button.y ) )
	      {
			  if(clickminus == false)
			  {
				  clickminus = true;
			  }
			  else clickminus = false;
	      }
		 else clickminus = false;
	}
}
