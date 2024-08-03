#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#pragma once
#include <SDL.h>
class LTimer
{
public:
	LTimer();
	void start();
	void stop();
	void pause();
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();
private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;
	bool mPaused;
	bool mStarted;
};


#endif // TIMER_H_INCLUDED
