#include "ball.h"

Ball::Ball()
{
	srand((unsigned int)time(NULL));
	x = 320;
	y = 240;
	w = 20;
	h = 20;
	Initialize();
	loadImage();
}

Ball::~Ball()
{
	TTF_CloseFont(font1);
	TTF_CloseFont(ofont1);
	SDL_FreeSurface(img);
	Mix_CloseAudio();
	Mix_FreeChunk(bong);
}

bool Ball::Initialize()
{
	TTF_Init();
	Mix_OpenAudio(22040, MIX_DEFAULT_FORMAT, 2, 4096);
	font1 = TTF_OpenFont("GFX/Font.ttf", 50);
	ofont1 = TTF_OpenFont("GFX/pf_tempesta_five.ttf", 18);
	if(!font1 || !ofont1)
	{
		return false;
		printf("Error loading font");
	}
	bong = Mix_LoadWAV("Audio/sound.wav");
	if(!bong)
	{
		return false;
		printf("Error loading sounds");
	}
	playerscore = 0;
	computerscore = 0;

	return true;
}

void Ball::InitSpeed( bool cEasy, bool cHard, bool cMighty )
{
	if(cEasy)
	{
		vx = float(rand()%5? -4 : 4);
		vy = float(rand()%5? 4 : -4);
	}
	else if(cHard == true)
	{
		vx = float(rand()%5? -6 : 6);
		vy = float(rand()%5? 6 : -6);
	}
	else if(cMighty == true)
	{
		vx = float(rand()%5? -7 : 7);
		vy = float(rand()%5? -7 : 7);
	}
}
bool Ball::loadImage()
{
	img = Functions::loadImage("GFX/ball.bmp");
	if(!img)
	{
		printf("Error loading Ball image");
		return false;
	}
	return true;
}

void Ball::Move()
{
	x += vx;
	y += vy;
	if( y < 0 || y+h > SDL_GetVideoSurface()->h )
	{
		vy *= -1;
	}
	if(Reset())
	{
		x = 320;
		y = 240;
		vx = 0;
		vy = 0;
	}
}

void Ball::DrawImage()
{
	Functions::DrawImage(img, SDL_GetVideoSurface(), static_cast<int>(x), static_cast<int>(y));
}

bool Ball::Reset()
{
	if( x < 0 )
	{
		computerscore++;
		return true;
	}
	if( x + w > SDL_GetVideoSurface()->w )
	{
		playerscore++;
		return true;
	}

	return false;
}

void Ball::getEvent(SDL_Event event, bool cEasy, bool cHard, bool cMighty)
{
	srand((unsigned int)time(NULL));
	if( vx == 0 || vy == 0 )
	{
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	    {        
			if(cEasy)
			{
				vx = float(rand()%5? -4 : 4);
			    vy = float(rand()%5? -4 : 4);
			}
			if(cHard)
			{
				vx = float(rand()%5? -5.0f : 5.0f);
			    vy = float(rand()%5? 5.0f : -5.0f);
			}
			if(cMighty)
			{
				vx = float(rand()%5? -6 : 6);
			    vy = float(rand()%5? 6 : -6);
			}
		}
	}
	if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE )
	{
		exit(0);
	}

}

bool Ball::EndReset(SDL_Event event)
{
	if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN )
	{
		if( playerscore >= 5 || computerscore >= 5 )
		{
			SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	        SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
			playerscore = 0;
			computerscore = 0;
			return true;
		}
	}
	return false;
}

SDL_Rect* Ball::getRect()
{
	SDL_Rect rect = { (int)x, (int)y, 20, 20 };
	return &rect;
}

void Ball::checkCollision()
{
	if(Game::Collide())
	{
		Functions::xPlaySound(-1, bong, 0);
		vx *= -1;
	}
	if(Game::SideCollide())
	{
		vy *= -1;
		vx *= -1;
	}
}

void Ball::DrawScore()
{
	SDL_Color color = { 255, 255, 255 };
	Functions::xDrawScore(color, font1, playerscore, 80, 30);
	Functions::xDrawScore(color, font1, computerscore, 480, 30);
	if( playerscore >= 5 || computerscore >= 5 )
	{
		x = 320;
		y = 240;
		vx = 0;
		vy = 0;
		SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
		Functions::xDrawText(color, ofont1, "Press Enter To Play New Game", 140, 320);
		Functions::xDrawText(color, ofont1, "Press Esc To Quit Game", 185, 350);
	}
	if( vx == 0 && playerscore < 5 && computerscore < 5 )
			Functions::xDrawText(color, ofont1, "Press Enter to Launch Ball",180, 280);
}
