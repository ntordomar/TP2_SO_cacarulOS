// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <video.h>
#include <lib.h>
#include <moduleLoader.h>
#include <idtLoader.h>
#include <syscalls.h>
#include <interrupts.h>
#include <speaker.h>
#include <time.h>
#include <idle.h>
#include <sync.h>
#include <pipe.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
int shPid;
static const uint64_t PageSize = 0x1000;

static void *const sampleCodeModuleAddress = (void *)0x400000;
static void *const sampleDataModuleAddress = (void *)0x500000;
int init(char **args);
typedef int (*EntryPoint)();
int prueba(char **args);
char *shellArgs[] = {"shell", NULL};
char *idleArgs[] = {"idle", NULL};

int fdDefault[] = {0, 0};

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

int idlePid;

int main()
{

	load_idt(); // Setup idt before terminal runs
	save_original_regs();
	restore_stack();
	initScheduler();
	semInit();
	pipeInit();

	shPid = createProcess("shell", 0, 4096, 4096, shellArgs, sampleCodeModuleAddress, 1, fdDefault);

	/* --- IDLE PROCESS --- */
	idlePid = createProcess("idle", 0, 4096, 4096, idleArgs, &idle, 1, fdDefault);
	changePriority(idlePid, 0);

	includeTerminal(shPid);
	return 0;
}
