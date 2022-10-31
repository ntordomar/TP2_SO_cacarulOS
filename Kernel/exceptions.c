#include <video.h>
#include <time.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

extern clearStackAndMain();

 void zero_division();
void invalid_op_code();


void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	} else if (exception == INVALID_OP_CODE_ID){
		invalid_op_code();
	}
		
}

 void zero_division() {
	clearScreen();
	draw_string(300, 300, "TUVISTE UNA ZERO DIVISION", 25, RED, BLACK);
	hold(40);
	clearScreen();
	draw_string(300, 300, "Reiniciando terminal...", 23, RED, BLACK);
	hold(40);
	clearScreen();
	clearStackAndMain();
}

 void invalid_op_code() {
	clearScreen();
	draw_string(300, 300, "TUVISTE UNA OP-CODE", 25, RED, BLACK);
	hold(40);
	clearScreen();
	draw_string(300, 300, "Reiniciando terminal...", 23, RED, BLACK);
	hold(40);
	clearScreen();
	clearStackAndMain();
 }