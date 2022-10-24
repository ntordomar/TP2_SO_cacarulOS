 #include <video.h>
 #include <keyBoardHandler.h>
 #include <lib.h>
 
static char buff[256];

static int front = 0;
static int rear = 0;
static int prevConsSize = 0;
static int cantElems = 0;
static xPos = 0;




char nextElement(){
    if(cantElems <= 0 ) {return -1;} //PARCHE MEDIO PELO
    char toRet = buff[front];
    front++;
    cantElems--;
    return toRet;
}
 
void keyHandler(){
    int tecla = getKey();
    if(tecla <=0x79){
        
        if (cantElems == 256){
            return;
        }
        if(rear == 256) rear = 0;
        if(front == 256) front  = 0;
        buff[rear++] = keyBoardTable[tecla];
    
        // draw_char(200, 400, 'a', WHITE, BLACK, 3);
        cantElems++;
    }

	// 	if(tecla <= 0x79){
    //     if(tecla == 14){
    //         draw_char(xTerminal-DEFAULT_LETTER_SIZE*8,yTerminal,' ',BLACK,BLACK,DEFAULT_LETTER_SIZE);
    //         if(xTerminal <= 0) {
    //         if(yTerminal == 0) return;
        
    //             xTerminal = 1024;
    //             yTerminal -= 16 * DEFAULT_LETTER_SIZE;
    //         } else {
    //             xTerminal -= DEFAULT_LETTER_SIZE*8;
    //         }
    //     }    
	// 	else {
    //         draw_char(xTerminal, yTerminal, keyBoardTable[tecla], WHITE, BLACK, DEFAULT_LETTER_SIZE);
    //         xTerminal+= DEFAULT_LETTER_SIZE*8;
    //         if(xTerminal >= 1024) {
    //             yTerminal += 16 * DEFAULT_LETTER_SIZE;
    //             xTerminal = 0;
    //         }
    //     }
    // }
}