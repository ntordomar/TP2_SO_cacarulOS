 #include <video.h>
 #include <keyBoardHandler.h>
 #include <lib.h>
 
static char buff[256] = {0};
static unsigned char front = -1;
static unsigned char rear = -1;
static int prevConsSize = 0;
static int cantElems = 0;

void getBuff(char * buffDest){
    *buffDest = *buff;
}

// int getCantElems(){
//     if (rear >= front){
//         return rear - front + 1;
//     } else {
//         return (256 - (front - rear - 1));
//     }
// }


char nextElement(){
    if(cantElems == 0) {return -8;}
    if (front == -1){
        return;
    }
    char toRet = buff[front];
    front++;
    cantElems--;
    return toRet;
}
 
void keyHandler(){
    draw_char(400, 400, 'a', RED, WHITE, 5);
    int tecla = getKey();
    if(tecla < 0x79){
        
        if ((front == 0 && rear == 255) || (front == rear + 1)){
            return;
        }
        if (front == -1){
            front = 0;
            rear = 0;
        } else {
            if (rear == 255){
                rear = 0;
            } else rear = rear +1;
        }
        buff[rear] = keyBoardTable[tecla];
    

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