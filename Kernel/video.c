#include <video.h>
#include <lib.h>
#define SCREEN_W screenInformation->width
#define SCREEN_H screenInformation->height

struct vbe_mode_info_structure* screenInformation = (void *)0x5C00; // la datita que nos provee la catedra esta en esta direccion de memoria (fijarse la funcion sysvar en el Bootloader)
char bufferAux[1024*768];
unsigned char getRed(int color){
    return (color >> 16) & 255;
}

unsigned char getBlue(int color){
    return color & 255;
}

unsigned char getGreen(int color){
    return (color >> 8) & 255;
}

int getPosition(int x, int y) {
    return x*(screenInformation->bpp)/8 + y*(screenInformation->pitch);
}

int getXPos(int x){
    if (x<SCREEN_W){
        return x;
    }
    return SCREEN_W;
}

int getYPos(int y){
    if (y<SCREEN_H){
        return y;
    }
    return SCREEN_H;
}

 void putpixel(int x, int y, int color) {
    int where = getPosition(x, y);
    char * aux = screenInformation->framebuffer + where ;
    *aux = getBlue(color);  // BLUE
    *(aux+1) = getGreen(color); // GREEN
    *(aux+2) = getRed(color); // RED
    
 }

void fillrect(int x, int y, int color, int w, int h) {
    
     if(x > screenInformation->width || y > screenInformation->height) return;
    int i, j;
     if(w+x  > screenInformation->width) w = screenInformation->width -x;
     if(h+y > screenInformation->height) h = screenInformation->height - y;
    
    char * aux = screenInformation->framebuffer + getPosition(x, y) ;
    int blue = getBlue(color);
    int red = getRed(color);
    int green = getGreen(color);
    // *aux = getBlue(color);  // BLUE
    // *(aux+1) = getGreen(color); // GREEN
    // *(aux+2) = getRed(color); // RED
    
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            aux = screenInformation->framebuffer + getPosition(x+i,y+j);
            *(aux) = blue;  // BLUE
            *(aux+1) = green; // GREEN
            *(aux+2) = red; // RED
        }
        
    }

}
void clearScreen(){
        fillrect(0, 0, BLACK, SCREEN_W, SCREEN_H);

}


void draw_string( int x, int y, char* input, int color) {
    int where = x;
    while(*input) {
        draw_char(x,y,letterInPixel[*input], color);
        where += 13; // chat width
        input++; 
    }
}
void draw_char(int x, int y, char * letter, int color) {
    int l ,i;
    int j =x;
    for (l = 0; l <13 ; l++) {
        for (i = 16; i > 0; i--) {
            j++;
            if ((letter[l] & (1 << i))) {
                putpixel(j, y, color);
            }
        }
        y++;
        j = x;
    }
}