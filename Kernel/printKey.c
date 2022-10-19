 #include <naiveConsole.h>
 
 void printKey(){
   
int tecla = getKey();	
		if(tecla <= 0x79){
        if(tecla == 14){
            printBackSpace();
        }    
		//else ncPrintChar(keyBoardTable[tecla],WHITE,BLACK);
}
 }