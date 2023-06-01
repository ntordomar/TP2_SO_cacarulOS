#include <stdint.h>
#include <video.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <syscalls.h>
#include <interrupts.h>
#include <speaker.h>
#include <process.h>
#include <time.h>
#include <idle.h>
#include "./include/sync.h"
#include <borrador.h>
#include <pipe.h>
// #include <scheduler.h>

// int testProcess(char **args);
// int tp2(char **args);
// int borrar(char **args);
// int borrar3(char **args);
// int borrar2(char **args);
extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;

typedef int (*EntryPoint)();

char *shellArgs[] = {"shell", NULL};
char *idleArgs[] = {"idle", NULL};

void clearBSS(void *bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void *getStackBase()
{
	return (void *)((uint64_t)&endOfKernel + PageSize * 8 // The size of the stack itself, 32KiB
					- sizeof(uint64_t)					  // Begin at the top of the stack
	);
}

void *initializeKernelBinary()
{

	void *moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}
int pid;
int pid2;
int shPid;

int idlePid;

int main()
{

	load_idt(); // Setup idt before terminal runs
	save_original_regs();
	restore_stack();
	initScheduler();
	semInit();
	pipeInit();

	// semCreate("tordox", 1);
	pid = createProcess("proc1", 0, 4096, 4096, shellArgs, &proc1);
	
	createProcess("proc2", 0, 4096, 4096, shellArgs, &proc2);
		createProcess("proc3", 0, 4096, 4096, shellArgs, &proc3);
		// shPid = createProcess("shell", 0, 4096, 4096, shellArgs, &borrar3);

		/* --- IDLE PROCESS --- */
	idlePid = createProcess("idle", 0, 4096, 4096, idleArgs, &idle);
	changePriority(idlePid, 0);

	includeTerminal(pid);

	// ((EntryPoint)sampleCodeModuleAddress)(); //Calling sampleCodeModule's main address
	while (1)
	{
		// draw_string(100,100,"1", 2, GREEN, BLACK);
		// draw_string(100,100,"0", 2, GREEN, BLACK);
	}
	return 0;
}
