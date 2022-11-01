#include <user_syscalls.h>
#include <tron.h>
#include <userStdF.h>

#define SQUARE_UNIT 8
#define OUT_OF_BOUNDS(x, y) ((x) > SCREEN_WIDTH || (x) < 0 || (y) > SCREEN_HEIGHT || (y) < 0) 

void printAux(int xP, int yP){
 for(int i = 0; i<15; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP +=5;
    }
}
void cup(int xpos, int ypos){
    int xP = xpos;
    int yP = ypos;
    // primera linea
    for(int i = 0; i< 4; i++){
     sys_draw_rectangle(xP,yP,5,5,GOLD);
     xP +=5;
    }
    xP+=10;
   printAux(xP,yP);
   xP+=5*15;
    xP+=10;
    for(int i = 0; i< 4; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP +=5;
    }
    // segunda linea
    yP+=5;
    xP = xpos;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=15;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=15;
    printAux(xP,yP);
    xP+=5*15;
    xP+=10;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=15;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // tercera linea
    yP+=5;
    xP = xpos;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=15;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=10;
    for(int i = 0; i<8 ; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    sys_draw_rectangle(xP,yP,5,5,BLACK);
    xP+=5;
    for(int i = 0; i<6; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=15;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // cuarta linea
    yP+=5;
    xP = xpos;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=20;
    for(int i = 0; i<9; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    sys_draw_rectangle(xP,yP,5,5,BLACK);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,BLACK);
    xP+=5;
    for(int i = 0; i<8; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
xP+=15;
sys_draw_rectangle(xP,yP,5,5,GOLD);
// 5ta linea
    yP+=5;
    xP = xpos;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=30;
    for(int i = 0; i< 6 ; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i< 3; i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i = 0; i<6; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=25;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // 6ta linea
    yP+=5;
    xP = xpos;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=30;
    for(int i= 0; i< 5; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<4; i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i =0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=25;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // 7ta linea
    yP+=5;
    xP = xpos;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=30;
    for(int i = 0; i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<2; i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=25;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // linea 8
    xP= xpos;
    yP +=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=25;
    for(int i = 0; i<7; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // linea 9
    yP+=5;
    xP = xpos;
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=25;
    for(int i =0 ; i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<2; i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // linea 10
    yP+=5;
    xP = xpos;
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=20;
    for(int i = 0; i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=15;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    // linea 11
    xP=xpos;
    yP+=5;
    xP+=10;
    for(int i = 0; i<3;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=5;
    for(int i = 0; i<5;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i = 0; i<4; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=5;
    for(int i = 0; i<3;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // linea 12
    xP=xpos;
    yP+=5;
    xP+=20;
    for(int i = 0; i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,BLACK);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // linea 13
    xP = xpos;
    yP+=5;
    xP+=30;
    for(int i = 0 ;i<15;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // linea 14
    xP = xpos;
    yP+=5;
    xP+=35;
    for(int i = 0 ;i<13;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // linea 15
     xP = xpos;
    yP+=5;
    xP+=40;
    for(int i = 0 ;i<11;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // linea 16
     xP = xpos;
    yP+=5;
    xP+=50;
    for(int i = 0 ;i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // linea 17 18 19
    for(int j =0; j<3;j++){
     xP = xpos;
    yP+=5;
    xP+=55;
    for(int i = 0 ;i<5;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    }
    // 20 linea
      xP = xpos;
    yP+=5;
    xP+=50;
    for(int i = 0 ;i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // 21
      xP = xpos;
    yP+=5;
    xP+=45;
    for(int i = 0 ;i<9;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }

}









void exit() {
    clear();
    setCursorPosition(390,SCREEN_HEIGHT/2);
    printf(PINK,"THANK YOU FOR PLAYING :)");
     hold(50);
    char c; 
    while((c = getChar()) != -1){;} // clears buffer
    return;
}

void youWin(int color, char * player){
    clear();
    sys_beep(300, 18);
    setCursorPosition(440,SCREEN_HEIGHT/2 + 80);
    printf(color,"%s!!\n",player);
    cup(250,SCREEN_HEIGHT/2);
    cup(600,SCREEN_HEIGHT/2);
    hold(50);
    exit();
    return;
}

void tronGame(){
    
    clear();    
    setCursorPosition(375, 100);
    printf(GREEN, "WELCOME TO TRON LIGHT CYCLES\n");
    setCursorPosition(350, 400);
    print("Player 1: use the arrows to move", GREEN);
    setCursorPosition(345, 450);
    print("Player 2: use the WASD keys to move", GREEN);
    setCursorPosition(175, 600);
    print("Press 1 to start", GREEN);
    setCursorPosition(700, 600);
    print("Press ESC to exit", GREEN);
    char info;
    while((info=getChar()) != '1') {
        if(info == 27) {
            return;
        }
    }
    sys_clear_screen();
    
  
    char matrix[SCREEN_WIDTH/SQUARE_UNIT][SCREEN_HEIGHT/SQUARE_UNIT];
    for(int i = 0; i< SCREEN_WIDTH/SQUARE_UNIT; i++){
        for(int j = 0; j<SCREEN_HEIGHT/SQUARE_UNIT; j++){
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
    char c;
    while(1){
        hold(1);
        c = getChar();
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
            youWin(RED,"PLAYER 2 WINS");
            return; 
        } else if (matrix[j2X/SQUARE_UNIT][j2Y/SQUARE_UNIT] == 1 || OUT_OF_BOUNDS(j2X,j2Y)){
            youWin(GREEN,"PLAYER 1 WINS");
            return;
        }
         else {
            matrix[j1X/SQUARE_UNIT][j1Y/SQUARE_UNIT] = 1;
            matrix[j2X/SQUARE_UNIT][j2Y/SQUARE_UNIT] = 1;
        }
        if(j1X == j2X && j1Y == j2Y){
            youWin(BLACK,"its a tie!");
            return;
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