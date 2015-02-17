#include "DJ.h"

DJ::DJ()
{
	Mix_OpenAudio(22040, MIX_DEFAULT_FORMAT, 2, 4096);
	TTF_Init();
	font = TTF_OpenFont("GFX/Robotica.ttf", 18);
	ofont = TTF_OpenFont("GFX/digital-7.ttf", 20);
	for( int i = 0; i < 5; i++ )
	{
		Sound[i] = NULL;
	}
	current = 0;

	loadMusic();
}

DJ::~DJ()
{
	for( int i = 0; i < 5; i++ )
	{
		Mix_FreeMusic(Sound[i]);
	}
	TTF_CloseFont(font);
	TTF_CloseFont(ofont);
	Mix_CloseAudio();
}

bool DJ::loadMusic()
{
	Sound[0] = Mix_LoadMUS("Audio/Song.ogg");
	Sound[1] = Mix_LoadMUS("Audio/Photon.ogg");
	Sound[2] = Mix_LoadMUS("Audio/Cygnus.ogg");
	Sound[3] = Mix_LoadMUS("Audio/Liquid Plasma.ogg");
	Sound[4] = Mix_LoadMUS("Audio/Def beat.ogg");
	for( int i = 0; i < 5; i++ )
	{
		if(!Sound[i])
		{
			printf("Error loading Music");
			return false;
		}
	}
	return true;
}

void DJ::xPlaySound()
{
	srand((unsigned int) time(NULL));
	current = rand()%5;
	Mix_PlayMusic(Sound[current], 0);
}

bool DJ::Reset()
{
	if(!Mix_PlayingMusic())
	{
		return true;
	}

	return false;
}

void DJ::PlayNext()
{
	temp = ++current;
	if( temp > 4 )
	{
		temp = 0;
		current = -1;
		temp = ++current;
	}
	Mix_PlayMusic(Sound[temp], 0);
}

void DJ::ShowCurrent()
{
	SDL_Color color = { 0xA2, 0x00, 0xFF };
	xDrawText( color, font, "Now Playing : ", 10, 400 );
	switch(temp)
	{
		case 0:
		text = "Quantum Singularity";
		break;
		case 1:
		text = "Photon Rez";
		break;
		case 2:
		text = "Cygnus Rift";
		break;
		case 3:
		text = "Liquid Plasma";
		break;
		case 4:
		text = "Def Beat";
		break;
		default:
			text = " ";
			break;

	}
	SDL_Color ocolor = { 0xDD, 0xFF, 0x00 };
	xDrawText( ocolor, ofont, text, 180, 400);

}
