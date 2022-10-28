#include <user_syscalls.h>
#include <tron.h>
#include <userStdF.h>

#define SQUARE_UNIT 8
#define OUT_OF_BOUNDS(x, y) ((x) > 1024 || (x) < 0 || (y) > 768 || (y) < 0) 

void exit() {
    sys_clear_screen();
    print("Thank you for playing :)", PINK);
    int tick =0; 
   
    hold(50);
    return;
}

void youLoose(char * player){
    sys_clear_screen();
    print("Perdiste loco", RED);
    print(player,WHITE);
    hold(20);
    exit();
    return;
}

void tronGame(){
    sys_clear_screen();
    setCursorPosition(400, 768/2);
    printf(GREEN, "Welcome to tron!!!     :) <3 \n");
    print("Player 1: use the arrows to move", GREEN);
    print("Player 2: use the WASD keys to move", GREEN);
    print("Press 1 to start", GREEN);
    print("Press ESC to exit", GREEN);
    char info;
    while((info=getc()) != '1') {
        if(info == 27) {
            return;
        }
    }
    sys_clear_screen();
    
  
    char matrix[1024/SQUARE_UNIT][768/SQUARE_UNIT];
    for(int i = 0; i< 1024/SQUARE_UNIT; i++){
        for(int j = 0; j<768/SQUARE_UNIT; j++){
            matrix[i][j] = 0;
        }
    }
    
    int j1X = 900;
    int j1Y = 384;
    int j1Xincrement = -1;
    int j1Yincrement = 0;

    int j2X= 100;
    int j2Y = 384;
    int j2Xincrement = 1;
    int j2Yincrement = 0;
    
    int xP = SQUARE_UNIT;
    char c;
    while(1){
        hold(1);
        // for(int i = 0; i< 9000000; i++){for(int j = 0; i< 10; i++){}}
        c = getc();
        switch (c)
        {
        case 'W':
            if (j2Yincrement != 1){
                j2Yincrement = -1;
                j2Xincrement = 0;
            }
            break;
        case 'A':
            if (j2Xincrement != 1){
                j2Yincrement = 0;
                j2Xincrement = -1;
            }
            break;
        case 'S':
            if (j2Yincrement != -1){
                j2Yincrement = 1;
                j2Xincrement = 0;
            }
            break;        
        case 'D':
            if (j2Xincrement != -1){
                j2Yincrement = 0;
                j2Xincrement = 1;
            }
            break;
        case 2: // izquierda
            if (j1Xincrement != 1){
                j1Xincrement = -1;
                j1Yincrement = 0;
            }
            break;
        case 3: // derecha
            if (j1Xincrement != -1){
                j1Xincrement = 1;
                j1Yincrement = 0;
            }
            break;
        case 4: // arriba
            if (j1Yincrement != 1){
                j1Xincrement = 0;
                j1Yincrement = -1;
            }
            break;        
        case 5: // abajo
            if (j1Yincrement != -1){
                j1Xincrement = 0;
                j1Yincrement = 1;
            }
            break;    
        case 27:
            exit();
            return;
        default:
            break;
        } 

        if (matrix[j1X/SQUARE_UNIT][j1Y/SQUARE_UNIT] == 1 || OUT_OF_BOUNDS(j1X,j1Y)){
            youLoose("Jugador 1");
            return; 
        } else if (matrix[j2X/SQUARE_UNIT][j2Y/SQUARE_UNIT] == 1 || OUT_OF_BOUNDS(j2X,j2Y)){
            youLoose("Jugador 2");
            return;
        }
         else {
            matrix[j1X/SQUARE_UNIT][j1Y/SQUARE_UNIT] = 1;
            matrix[j2X/SQUARE_UNIT][j2Y/SQUARE_UNIT] = 1;
        }
        j1X += SQUARE_UNIT*j1Xincrement;
        j2X += SQUARE_UNIT*j2Xincrement;
        j1Y += SQUARE_UNIT*j1Yincrement;
        j2Y += SQUARE_UNIT*j2Yincrement;
        
        sys_draw_rectangle(j1X,j1Y,SQUARE_UNIT,SQUARE_UNIT,RED);
        sys_draw_rectangle(j2X, j2Y, SQUARE_UNIT, SQUARE_UNIT, GREEN);
    }
    sys_clear_screen();
}