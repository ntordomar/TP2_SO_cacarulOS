#include <time.h>
#include <naiveConsole.h>



static unsigned long ticks = 0;
static int flag = 1;
void timer_handler() {
	// ticks++;
	// //putpixel(200 + ticks, 200 + ticks,0xffffff);
	// if(seconds_elapsed()%5 == 0 ){
	// 	if(flag){
	// 		flag = 0;
	// 	}
	// } else flag = 1;
	
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}