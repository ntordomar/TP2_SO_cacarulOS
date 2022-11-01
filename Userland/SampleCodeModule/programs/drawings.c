#include <drawings.h>
#include <userStdF.h>
#include <user_syscalls.h>
void printAux(int xP, int yP){
 for(int i = 0; i<15; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP +=5;
    }
}

void cup(int xpos, int ypos){
    int xP = xpos;
    int yP = ypos;
    // first line
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
    // second line
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
    // third line
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
    // fourth line
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
    // line 5
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
    // line 6
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
    // line 7
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
    // line 8
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
    // line 9
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
    // line 10
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
    // line 11
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
    // line 12
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
    // line 13
    xP = xpos;
    yP+=5;
    xP+=30;
    for(int i = 0 ;i<15;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // line 14
    xP = xpos;
    yP+=5;
    xP+=35;
    for(int i = 0 ;i<13;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // line 15
     xP = xpos;
    yP+=5;
    xP+=40;
    for(int i = 0 ;i<11;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // line 16
     xP = xpos;
    yP+=5;
    xP+=50;
    for(int i = 0 ;i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // line 17 18 19
    for(int j =0; j<3;j++){
     xP = xpos;
    yP+=5;
    xP+=55;
    for(int i = 0 ;i<5;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    }
    // line 20
      xP = xpos;
    yP+=5;
    xP+=50;
    for(int i = 0 ;i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // line 21
    xP = xpos;
    yP+=5;
    xP+=45;
    for(int i = 0 ;i<9;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }

}

void cacarulo(int xPos, int yPos){
    int xP = xPos;
    int yP = yPos;
    // linea 1
    xP+=10;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=45;
    for(int i = 0; i<4;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    // 2da linea
    xP=xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=45;
    for(int i = 0; i<4;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,BLUE);
    // linea 3
    xP = xPos;
    yP+=5;
    xP+=10;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=10;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=40;
    for(int i = 0; i<4; i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    xP+=15;
    sys_draw_rectangle(xP,yP,5,5,BLUE);
    // linea 4
    xP=xPos;
    yP+=5;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=55;
    for(int i = 0; i<5;i++){
    sys_draw_rectangle(xP,yP,5,5,BLUE);
    xP+=5;
    }
    // linea 5
    xP=xPos;
    yP+=5;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=15;
    for(int i = 0; i<3; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=20;
    for(int i = 0;i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    // linea 6
    xP=xPos;
    yP+=5;
    xP+=10;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,RED);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=15;
    for(int i = 0; i<8;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    // linea 7
    xP= xPos;
    yP+=5;
    xP+=15;
    for(int i= 0; i<3;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    xP+=15;
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,BROWN);
        xP+=5;
    }
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i= 0; i<4;i++){
        sys_draw_rectangle(xP,yP,5,5,BROWN);
        xP+=5;
    }
    // linea 8
    xP=xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=15;
    for(int i = 0; i<12;i++)
    {
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    // linea 9
    xP=xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=25;
    for(int i = 0; i<8;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    //linea 10
    xP=xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=5;
    for(int i = 0; i<5;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,CREME);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    // linea 11 y 12
    for(int j = 0; j<2;j++){
    xP=xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    for(int i= 0; i<8;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    }
    // linea 13
    xP = xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    for(int i = 0; i<8;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,BLUE);
    // linea 14
    xP = xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,GRAY);
        xP+=5;
    }
    for(int i =0 ;i<3;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,GRAY);
        xP+=5;
    }
     for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    // linea 15
    xP= xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,CREME);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,CREME);
    xP+=5;
    for(int i =0 ; i<3;i++){
        sys_draw_rectangle(xP,yP,5,5,GRAY);
        xP+=5;
    }
    for(int i = 0; i<3;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    // linea 16
    xP=xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=20;
    for(int i = 0; i<9;i++){
        sys_draw_rectangle(xP,yP,5,5,GRAY);
        xP+=5;
    }
    for(int i = 0; i<4;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    // linea 17
    xP=xPos;
    yP+=5;
    xP+=15;
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    for(int i = 0; i<3;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    for(int i = 0; i<8;i++){
        sys_draw_rectangle(xP,yP,5,5,GRAY);
        xP+=5;
    }
    for(int i =0 ; i<5;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    //linea 18
    xP = xPos;
    yP+=5;
    xP+=15;
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    for(int i = 0; i<4;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,GRAY);
        xP+=5;
    }
    for(int i = 0; i<6;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    //linea 19
    xP = xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=30;
    for(int i = 0 ; i<4; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<7;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    //linea 20
    xP = xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=30;
    sys_draw_rectangle(xP,yP,5,5,GOLD);
    xP+=5;
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    for(int i = 0; i<8; i++){
        sys_draw_rectangle(xP,yP,5,5,GOLD);
        xP+=5;
    }
    //linea 21
    xP = xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=30;
    sys_draw_rectangle(xP,yP,5,5,BLUE);
    xP+=5;
    sys_draw_rectangle(xP,yP,5,5,GRAY);
    xP+=5;
    for(int i = 0; i<9;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    // linea 22 y 23
    for(int j = 0; j<2;j++){
    xP = xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=30;
    for(int i = 0; i<9;i++){
        sys_draw_rectangle(xP,yP,5,5,BLUE);
        xP+=5;
    }
    for(int i = 0; i<2;i++){
        sys_draw_rectangle(xP,yP,5,5,CREME);
        xP+=5;
    }
    }
    // linea 24 25 26
    for(int j = 0; j<3;j++){
        xP = xPos;
        yP+=5;
        xP+=20;
        sys_draw_rectangle(xP,yP,5,5,BROWN);
        xP+=30;
        for(int i = 0; i<10;i++){
            sys_draw_rectangle(xP,yP,5,5,BLUE);
            xP+=5;
        }
    }
    // linea 27 y ultima 
    xP = xPos;
    yP+=5;
    xP+=20;
    sys_draw_rectangle(xP,yP,5,5,BROWN);
    xP+=30;
    for(int i = 0; i<4;i++){
        sys_draw_rectangle(xP,yP,5,5,BROWN);
        xP+=5;
    }
    xP+=10;
     for(int i = 0; i<4;i++){
        sys_draw_rectangle(xP,yP,5,5,BROWN);
        xP+=5;
    }

    // las que tienen que ir desapareciendo estan en la posicion:
    int flag = 1;
    for(int i = 0; i<10;i++){
        hold(15);
        if(flag){
        sys_draw_rectangle(xPos+10,yPos,5,5,BLACK);
        sys_draw_rectangle(xPos+30,yPos,5,5,BLACK);
        sys_draw_rectangle(xPos+20,yPos+5,5,5,BLACK);
        sys_draw_rectangle(xPos+10,yPos+10,5,5,BLACK);
        sys_draw_rectangle(xPos+20,yPos+10,5,5,BLACK);
        sys_draw_rectangle(xPos,yPos+10,5,5,BLACK);
        sys_draw_rectangle(xPos,yPos+15,5,5,BLACK);
        sys_draw_rectangle(xPos,yPos+20,5,5,BLACK);

        flag = 0;
        }
        else{
        sys_draw_rectangle(xPos+10,yPos,5,5,RED);
        sys_draw_rectangle(xPos+30,yPos,5,5,RED);
        sys_draw_rectangle(xPos+20,yPos+5,5,5,RED);
        sys_draw_rectangle(xPos+10,yPos+10,5,5,RED);
        sys_draw_rectangle(xPos+20,yPos+10,5,5,RED);
        sys_draw_rectangle(xPos,yPos+15,5,5,RED);
        sys_draw_rectangle(xPos,yPos+20,5,5,RED);
        flag = 1;
        }
    }






}