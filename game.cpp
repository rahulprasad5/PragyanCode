#include "game.h"

Ball* myBall = new Ball;
Paddle* myPaddle = new Paddle;
Menu* myMenu = new Menu;
Functions myFunc;
Loading* myLoading = new Loading;
DJ myDJ;
Options* myOptions = new Options;

gamestate current = Intro;

Game::Game()
{
	CurrentVolume = 100;
	Uint32 myFlags = NULL;
	if(MessageBox(NULL, L"Play in FullScreen Mode?", L"FullScreen", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		myFlags = SDL_SWSURFACE | SDL_FULLSCREEN;
	}
	else 
	{
		myFlags = SDL_SWSURFACE;
	}
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(640, 480, 32, myFlags);
	TTF_Init();
	Mix_OpenAudio(22040, MIX_DEFAULT_FORMAT, 2, 4096);
	Introsound = Mix_LoadWAV("Audio/osound.wav");
	SDL_WM_SetCaption("Pongster", NULL);
	running = true;
	bg = loadImage("GFX/bgone.bmp");

}

Game::~Game()
{
	delete myBall; //Free all the surfaces.
	delete myPaddle;
	delete myMenu;
	delete myLoading;
	Mix_FreeChunk(Introsound);
	Mix_CloseAudio();
	SDL_Quit();
}

void Game::HandleEvents()
{
	Mix_VolumeMusic(CurrentVolume);
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		{
			myDJ.PlayNext();
		}
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			current = Exit;
		}
		switch(current)
		{
			case Intro:
			if( event.type == SDL_QUIT )
			{
				current = Exit;
			}
			break;
			case Load:
			if(myLoading->getFrame())
			{
				current = Main;
			}
			if(event.type == SDL_QUIT)
			{
				current = Exit;
			}
			break;
			case Main:
			if(myMenu->StartMouseClick(event))
			{
				current = Difficulty, SDL_Delay(200);
			}
			else if( myMenu->ExitMouseClick(event) )
			{
				current = Exit;
			}
			else if( myMenu->OptionsMouseclick(event) )
			{
				current = options;
			}

			else if( event.type == SDL_QUIT )
			{
				current = Exit;
			}
			myMenu->DrawArrow(event);

			break;

			case options:
			if(event.type == SDL_QUIT)
			{
				current = Exit;
			}
			if( myOptions->BackMouseClick(event))
			{
				current = Main;
			}
			else if( myOptions->OnMouseClick(event))
			{
				Mix_PauseMusic();
			}
			if( myOptions->clickedoff == false )
			{
				Mix_ResumeMusic();
			}
			myOptions->PlusMouseClick(event);
			if(myOptions->clickplus)
			{
				CurrentVolume += 5;
				if(CurrentVolume > 128)
				{
					CurrentVolume = 128;
				}
			}
			else if(myOptions->clickminus)
			{
				CurrentVolume -= 5;
				if(CurrentVolume < 0)
				{
					CurrentVolume = 0;
				}
			}
			break;

			case Difficulty:
			if( event.type == SDL_QUIT )
			{
				current = Exit;
			}
			myMenu->DrawNextArrow(event);
			if(myMenu->EasyMouseClick(event))
			{
				Functions::Hard = false;
				Functions::Mighty = false;
				Functions::Easy = true;
				current = MainGame;
			}
			else if(myMenu->HardMouseClick(event))
			{
				Functions::Easy = false;
				Functions::Mighty = false;
				Functions::Hard = true;
				current = MainGame;
			}
			else if(myMenu->MightyMouseClick(event))
			{
				Functions::Easy = false;
				Functions::Hard = false;
				Functions::Mighty = true;
				current = MainGame;
			}
			myBall->InitSpeed(Functions::Easy, Functions::Hard, Functions::Mighty );
			if(myMenu->BackMouseClick(event))
			{
				current = Main;
			}

			break;

			case MainGame:
			myBall->getEvent(event, Functions::Easy, Functions::Hard, Functions::Mighty );
			myPaddle->Move(event);
			if(event.type == SDL_QUIT)
			{
				current = Exit;
			}
			if(myBall->EndReset(event))
			{
				current = Main, HandleEvents(), Init();
			}

			break;
		}
	}
}

void Game::Init()
{
	Timer myTimer;
	Mix_PlayChannel(-1, Introsound, 0 );
	while(current != Exit)
	{
		myTimer.start();
		HandleEvents();
		switch(current)
		{
			case Intro:
			if( Mix_PlayChannel(-1, Introsound, 0 ) == false )
			{
			    current = Load, Mix_Pause(-1), myDJ.xPlaySound();
			}
			DrawImage(bg, screen, 0, 0);
			break;

			case Load:
			if(myDJ.Reset())
			{
				myDJ.xPlaySound();
			}
			myLoading->DrawImage();
			break;

			case Main:
			if(myDJ.Reset())
			{
				myDJ.xPlaySound();
			}
			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
			myMenu->DrawImage();
			myDJ.ShowCurrent();
			break;

			case options:
			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
			myOptions->xDrawText();
			break;
			case Difficulty:
			if(myDJ.Reset())
			{
				myDJ.xPlaySound();
			}
			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
			myMenu->DrawNextImage();
			break;
			case MainGame:
			if(myDJ.Reset())
			{
				myDJ.xPlaySound();
			}
			myPaddle->computerAI(myBall->getRect()->y, Functions::Easy, Functions::Hard, Functions::Mighty );
			myBall->Move();
			myBall->checkCollision();
			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
			myBall->DrawImage();
			myPaddle->DrawImage();
			myBall->DrawScore();
			break;

		}
		SDL_Flip(screen);
	}
}

void Game::Start()
{
	Init();
}

bool Game::Collide()
{
	float bx = myBall->getRect()->x;
    float by = myBall->getRect()->y;
    float py1 = myPaddle->getPRect()->y;
    float py2 = myPaddle->getCRect()->y;
	if( ( bx + 20 >= 10 && bx <= 30 ) && ( by+20 >= py1 && by <= py1+70 ) )
	{
		return true;
	}
	if( ( bx + 20 >= 610 && bx <= 630 ) && ( by+20 >= py2 && by <= py2+70 ) )
	{
		return true;
	}
	return false;
}

bool Game::SideCollide()
{
	float bx = myBall->getRect()->x;
    float by = myBall->getRect()->y;
    float py1 = myPaddle->getPRect()->y;
    float py2 = myPaddle->getCRect()->y;
	if( ( bx + 20 >= 10 && bx <= 30 ) && ( by+20 >= py1 && by <= py1+70 ) )
	{
		if( bx+5 < 30 )
		{
			return true;
		}
	}

	return false;
}
