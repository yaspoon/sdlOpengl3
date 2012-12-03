#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <SDL/SDL.h>

/********************************
*Class Timer
*used to keep track of time
*Gets the amount of cpu ticks that have
*passed since the timer was started
*These are used for limiting FPS
*and keeping track of the animation
********************************/
class Timer
{
	private:
		Uint32 startTicks;
		Uint32 pauseTicks;

		bool paused;
		bool started;
	public:
		Timer();
		virtual ~Timer();

		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();
		bool isPaused();
		bool isStarted();
};

#endif
