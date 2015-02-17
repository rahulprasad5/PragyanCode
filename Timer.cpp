#include "Timer.h"

Timer::Timer()
{
	PastFrames = 0;
	PerFrames = 1000/ Frames;
	beginTime = SDL_GetTicks();
}

void Timer::start()
{
	PastFrames = SDL_GetTicks() - beginTime;
	beginTime = SDL_GetTicks();
	if( PastFrames < PerFrames )
	{
		SDL_Delay(PerFrames - PastFrames);
	}
}
