#include <video.h>
#include <time.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

extern void clearStackAndMain(); // from loader.asm

void zero_division();
void invalid_op_code();


void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	} else if (exception == INVALID_OP_CODE_ID){
		invalid_op_code();
	}
		
}

void printRegs() {
	
	int letterSize = get_default_fontSize();
	char r2[256] = {0};
    itoa(getRDI(), r2, 10);
    draw_string(0, 100, "RDI: ", 5, RED, BLACK);
    draw_string(6 * 8 * letterSize, 100 , r2, strlen(r2), RED, BLACK);
    int regs[16];
    getRegisters(regs);
    char * registersName[] = {"RAX: ","RBX: ","RCX: ","RDX: ","RSI: ","RBP: ","RSP: ","R8:  ","R9:  ","R10: "
								,"R11: " ,"R12: ","R13: ","R14: ","R15: ", "IP:  "};
    for (int i = 0; i<16; i++){
        char r[256] = {0};
        itoa(regs[i], r, 10);
		int yPos = 100 + (i+1)*16*letterSize;
		draw_string(0, yPos, registersName[i], 5,  RED, BLACK);
		draw_string(6 * 8 * letterSize, yPos, r, strlen(r), RED, BLACK);
    }
}

 void zero_division() {
	set_default_fontSize(INITIAL_FONT_SIZE);
	clearScreen();
	draw_string(400, 50, "TUVISTE UNA ZERO DIVISION", 25, RED, BLACK);
	printRegs();
	hold(100);
	clearScreen();
	draw_string(400, 50, "Reiniciando terminal...", 23, RED, BLACK);
	hold(40);
	clearScreen();
	clearStackAndMain();
}

 void invalid_op_code() {
	set_default_fontSize(INITIAL_FONT_SIZE);
	clearScreen();
	draw_string(400, 50, "TUVISTE UNA OP-CODE", 19, RED, BLACK);
	printRegs();
	hold(100);
	clearScreen();
	draw_string(400, 50, "Reiniciando terminal...", 23, RED, BLACK);
	hold(40);
	clearScreen();
	clearStackAndMain();
 }