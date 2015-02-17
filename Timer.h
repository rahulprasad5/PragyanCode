#ifndef _TIMER_H
#define _TIMER_H

#include "SDL.h"

class Timer
{
	private:
	static const long Frames =  30;
	long PastFrames;
	long PerFrames;
	long beginTime;

	public:
	Timer();
	void start();
};

#endif
