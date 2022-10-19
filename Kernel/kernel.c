 #include <stdint.h>
 //#include <string.h>
 #include <video.h>
#include <lib.h>
 #include <moduleLoader.h>
 #include <naiveConsole.h>
 #include <idtLoader.h>
extern int getSeconds();
extern int getMinutes();
extern int getHours();
extern int getKey();
extern void sys_write(int fd, char * buff, int bytes);
extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main()
{	
	load_idt();
	putpixel(512,768/2, 0xFFFFFF);
	 putpixel(512,100, 0xFFFFFF);

	fillrect(300,0, 0xFF0080, 1024, 500);
	putpixel(1024,1024,0xFFFFFF);
	int tecla = 0;
	int i = 0;
	ncPrint("la tecla va aca",GREEN,GRAY);
	sys_write(1,"lavida",4);
	clearScreen();

	while(1){}
	return 0;
}