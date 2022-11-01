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