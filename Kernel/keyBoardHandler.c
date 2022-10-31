 #include <video.h>
 #include <keyBoardHandler.h>
 #include <lib.h>
 
static char buff[256] = {0};

static int front = 0;
static int rear = 0;
static int cantElems = 0;

char nextElement(){
    if(cantElems <= 0 ) {return -1;} 
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
    
        cantElems++;
    }
}