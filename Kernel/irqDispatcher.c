#include <time.h>
#include <stdint.h>
#include <syscalls.h>
#include <video.h>

static void int_20();

static void (*interrFunctions[20])(void) = {int_20};


void irqDispatcher(uint64_t irq) {
	(*interrFunctions[irq])();
	return;
}

void int_20() {
	timer_handler();
}


