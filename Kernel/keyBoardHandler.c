 #include <video.h>
 #include <keyBoardHandler.h>
 
static char buff[256];
static char teclaCant = 0;

char nextElement(){
    if(teclaCant == 0) return -1;
    return buff[--teclaCant];
}
 
void keyHandler(){

    char tecla = getKey();	
    if(tecla <= 0x79 || teclaCant >= 256) return;
    buff[teclaCant++] = keyBoardTable[tecla];


	// 	if(tecla <= 0x79){
    //     if(tecla == 14){
    //         draw_char(xTerminal-DEFAULT_LETTER_SIZE*8,yTerminal,' ',BLACK,BLACK,DEFAULT_LETTER_SIZE);
    //         if(xTerminal <= 0) {
    //             if(yTerminal == 0) {
    //                 return;
    //             }
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