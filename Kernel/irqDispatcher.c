// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <time.h>
#include <stdint.h>
#include <syscalls.h>
#include <video.h>
#include <keyBoardHandler.h>

static void int_20();
static void int_21();

static void (*interrFunctions[20])(void) = {int_20, int_21};

void irqDispatcher(uint64_t irq)
{
	(*interrFunctions[irq])();
	return;
}

void int_20()
{
	timer_handler();
}

void int_21()
{
	keyHandler();
}
