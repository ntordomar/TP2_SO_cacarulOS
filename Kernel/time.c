#include <time.h>
#include <lib.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

long ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void hold(int delta){
	int currentTicks = ticks;
	while(ticks - currentTicks < delta){
		hlt();
	}
}