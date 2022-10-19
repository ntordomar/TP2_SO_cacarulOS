 #include <stdint.h>
 //#include <string.h>
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

	ncPrint("[x64BareBones]",WHITE,BLACK);
	ncNewline();

	ncPrint("CPU Vendor:",WHITE,BLACK );
	ncPrint(cpuVendor(buffer),WHITE,BLACK);
	ncNewline();

	ncPrint("[Loading modules]",WHITE,BLACK);
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]",WHITE,BLACK);
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]",WHITE,BLACK);
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x",WHITE,BLACK);
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x",WHITE,BLACK);
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x",WHITE,BLACK);
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x",WHITE,BLACK);
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]",WHITE,BLACK);
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{	
	load_idt();
	// ncPrint("[Kernel Main]",WHITE);
	// ncNewline();
	// ncPrint("  Sample code module at 0x",WHITE);
	// ncPrintHex((uint64_t)sampleCodeModuleAddress);
	// ncNewline();
	// ncPrint("  Calling the sample code module returned: ",WHITE);
	// ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	// ncNewline();
	// ncNewline();

	// ncPrint("  Sample data module at 0x",WHITE);
	// ncPrintHex((uint64_t)sampleDataModuleAddress);
	// ncNewline();
	// ncPrint("  Sample data module contents: ",WHITE);
	// ncPrint((char*)sampleDataModuleAddress,WHITE);
	// ncNewline();
	// ncPrint("Arquitectura de computadoras",LIGHT_GREEN);
	// ncNewline();
	// ncPrint("tiempo: ",LIGHT_GREEN);
	// ncPrintHex((getHours() -3 -6)); // restamos 3 pues el utc es de 3 yay. El 6 se lo restamos pues hay 6 caracteres (A B C D E F) le resto los 6 a los cuales no puedo acceder, 
	// ncPrint(" : ", LIGHT_GREEN);
	// ncPrintHex(getMinutes());
	// ncPrint(" : ",LIGHT_GREEN);
	// ncPrintHex(getSeconds());
	// ncNewline();
	
	// ejercicio de la teclita omg hi;
	int tecla = 0;
	int i = 0;
	ncPrint("la tecla va aca",GREEN,GRAY);
	// while(1){
	// 	tecla = getKey();
	// 	if(tecla <= 0x79)
	// 	ncPrintChar(keyBoardTable[tecla],WHITE,GRAY);
	// }
	sys_write(1,"lavida",4);
	while(1){
		
	}

	// ncPrint("[Finished]",WHITE);
	return 0;
}
