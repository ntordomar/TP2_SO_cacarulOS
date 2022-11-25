#include <video.h>
#include <time.h>
#include <lib.h>
#include <speaker.h>
#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

extern const uint64_t excepRegs[17];


extern void clearStackAndMain(); // from loader.asm

void zero_division();
void invalid_op_code();


void exceptionDispatcher(int exception) {
	beep(1500,7);
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	} else if (exception == INVALID_OP_CODE_ID){
		invalid_op_code();
	}
		
}

void printRegs() {
	int letterSize = get_default_fontSize();

	char * registersName[] = {"RAX: ","RBX: ","RCX: ","RDX: ","RSI: ","RDI: ","RBP: ","RSP: ","R8:  ","R9:  ",
							"R10: ","R11: ","R12: ","R13: ","R14: ","R15: ", "RIP: "};
	
    for (int i = 0; i<17; i++){
        char r[256] = {0};
        itoa(excepRegs[i], r, 10);
		int yPos = 100 + (i+1)*CHAR_HEIGHT*letterSize;
		draw_string(0, yPos, registersName[i], 5,  RED, BLACK);
		draw_string(6 * CHAR_WIDTH * letterSize, yPos, r, strlen(r), RED, BLACK);
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