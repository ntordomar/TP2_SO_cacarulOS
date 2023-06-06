// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <time.h>
#include <lib.h>

static unsigned long ticks = 0;

void timer_handler()
{			 // Every time 55 ms passes this function gets triggerd by the timer tick interruption.
	ticks++; // by doing so we increment the tick static variable
}

long ticks_elapsed()
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}

void hold(int delta)
{ // This function gives us the possibility to wait delta ticks.
	int currentTicks = ticks;
	while (ticks - currentTicks < delta)
	{
		hlt();
	}
}