#include <time.h>
#include <naiveConsole.h>

static unsigned long ticks = 0;
static int flag = 1;
void timer_handler() {
	ticks++;
	if(seconds_elapsed()%5 == 0 ){
		if(flag){
		ncPrint("hello timer",BLACK,WHITE);
		flag = 0;
		}
	} else flag = 1;
	
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}