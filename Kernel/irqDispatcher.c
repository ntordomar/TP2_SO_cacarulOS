#include <time.h>
#include <stdint.h>
#include <keyBoardHandler.h>
#include <syscalls.h>
#include <video.h>
static void int_20();
static void int_21();
static void (*interrFunctions[20])(void) = {int_20,int_21};



void irqDispatcher(uint64_t irq) {
	draw_char(300, 350, 'o', WHITE, BLACK, 3);
	(*interrFunctions[irq])();
	return;
}

void int_20() {
	timer_handler();
}
void int_21(){
	keyHandler();
}

