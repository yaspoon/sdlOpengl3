#include "timer.h"

/********************************
*Default Constructor Timer
*Initialises sane defaults for data
********************************/
Timer::Timer()
{

    paused = false;
    started = false;

    startTicks = 0;
    pauseTicks = 0;
}

Timer::~Timer()
{
}

/********************************
*Start
*sets the timer to started then
*gets the current amount of cpu ticks
*has passed since the program started
********************************/
void Timer::start()
{
    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
}

/********************************
*Stop
*Stops the timer and resets it to nothing
*Ready to be restarted
********************************/
void Timer::stop()
{
    started = false;
    paused = false;

    startTicks = 0;
    pauseTicks = 0;
}

/********************************
*pause
*If the timer has started then set the timer to paused
*then get the current cpu ticks used for restarting the timer
********************************/
void Timer::pause()
{
    if((started == true)&&(paused == false))
    {

        paused = true;

        pauseTicks = SDL_GetTicks() - startTicks;
    }
}

/********************************
*unpause
*resets the start ticks
as the current ticks take
the number of ticks before the timer
was paused
********************************/
void Timer::unpause()
{
    if(paused == true)
    {
        paused = false;

        startTicks = SDL_GetTicks() - pauseTicks;

        pauseTicks = 0;
    }
}

/********************************
*getTicks
*Returns the amount of cpu ticks
*that have occured since the timer
*started
********************************/
Uint32 Timer::getTicks()
{
    Uint32 currentTicks = 0;

    if(started == true)
    {
        if(paused == true)
        {
            currentTicks = pauseTicks;
        }
        else
        {
            currentTicks = SDL_GetTicks() - startTicks;
        }
    }

    return currentTicks;
}

/********************************
*isStarted
*Function to tell if the timer has started
********************************/
bool Timer::isStarted()
{
    return started;
}

/********************************
*isPaused
*returns if the timer is paused
********************************/
bool Timer::isPaused()
{
    return paused;
}
