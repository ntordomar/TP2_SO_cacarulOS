#include <user_syscalls.h>
#include <tron.h>
#include <userStdF.h>
#define SQUARE_UNIT 8
#define OUT_OF_BOUNDS(x, y) ((x) > 1024 || (x) < 0 || (y) > 768 || (y) < 0) 

void exit() {
    sys_clear_screen();
    print(500, 384, "Thank you for playing :)", PINK);
    int tick =0; 
   
    hold(10);
    return;
}

void youLoose(char * player){
    sys_clear_screen();
    print(300, 250, "Perdiste loco", RED);
    print(100,500,player,WHITE);
    hold(10);
    exit();
    return;
}

void tronGame(){
    sys_clear_screen();
    print(350,50,"Welcome to tron!!!     :) <3",GREEN);
    print(310, 200, "Player 1: use the arrows to move", GREEN);
    print(300, 250, "Player 2: use the WASD keys to move", GREEN);
    print(200, 500, "Press 1 to start", GREEN);
    print(550, 500, "Press ESC to exit", GREEN);
    char info;
    while((info=getc()) != '1') {
        if(info == 27) {
            return;
        }
    }
    sys_clear_screen();
    
  
    char matrix[1024/SQUARE_UNIT][768/SQUARE_UNIT];
    for(int i = 0; i< 128; i++){
        for(int j = 0; j<96; j++){
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
        //hold(1);
        for(int i = 0; i< 9000000; i++){for(int j = 0; i< 10; i++){}}
        c = getc();
        switch (c)
        {
        case 'W':
            j2Yincrement = -1;
            j2Xincrement = 0;
            break;
        case 'A':
            j2Yincrement = 0;
            j2Xincrement = -1;
            break;
        case 'S':
            j2Yincrement = 1;
            j2Xincrement = 0;
            break;        
        case 'D':
            j2Yincrement = 0;
            j2Xincrement = 1;
            break;
        case 2: // izquierda
            j1Xincrement = -1;
            j1Yincrement = 0;
            break;
        case 3: // derecha
            j1Xincrement = 1;
            j1Yincrement = 0;
            break;
        case 4: // arriba
            j1Xincrement = 0;
            j1Yincrement = -1;
            break;        
        case 5: // abajo
            j1Xincrement = 0;
            j1Yincrement = 1;
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