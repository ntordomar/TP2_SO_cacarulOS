#include <video.h>
#include <lib.h>
#include <font.h>
#define SCREEN_W screenInformation->width
#define SCREEN_H screenInformation->height


struct vbe_mode_info_structure* screenInformation = (void *)0x5C00; // la datita que nos provee la catedra esta en esta direccion de memoria (fijarse la funcion sysvar en el Bootloader)
static char bufferAux[1024*768];
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
    
    char * aux = screenInformation->framebuffer + getPosition(x, y);
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


void draw_string( int x, int y, char* input, int len,int color, int backgroundColor, int fontSize) {
     int xInter = x;
    int yInter = y;
    for(int i = 0; i<len; i++){
     if(input[i] == 8){
            draw_char(xInter-DEFAULT_LETTER_SIZE*8,yInter,' ',BLACK,BLACK,DEFAULT_LETTER_SIZE);
            if(xInter <= 0) {
            if(yInter == 0) return;
        
                xInter = 1024;
                yInter -= 16 * DEFAULT_LETTER_SIZE;
            } else {
                xInter -= DEFAULT_LETTER_SIZE*8;
            }
        }    
		else {
            draw_char(xInter, yInter, input[i], color, BLACK, DEFAULT_LETTER_SIZE);
            xInter+= DEFAULT_LETTER_SIZE*8;
            if(xInter >= 1024) {
                yInter += 16 * DEFAULT_LETTER_SIZE;
                xInter = 0;
            }
        }
    }
}

void draw_char(int x, int y, char letter, int color, int backgroundColor, int fontSize) {
    
    int aux_x = x;
	int aux_y = y;

    if (aux_x + 8*fontSize > SCREEN_W) {
        aux_x = 0;
        aux_y += 16*fontSize;
    }

	char bitIsPresent;

	unsigned char* toDraw = charBitmap(letter);

	for(int i = 0; i < 16; i++) { // 16 is the height of a letter
		for(int j = 0; j < 8; j++) { // 8 is the width 

        bitIsPresent = 0;
            switch (j)
            {
            case 0:
                bitIsPresent = 0x80 & *(toDraw + i); // 0x80h = 10000000b
                break;
                
            case 1: 
                bitIsPresent = 0x40 & *(toDraw + i); // 0x40h = 01000000b
                break;

            case 2: 
                bitIsPresent =0x20 & *(toDraw + i); // 0x20h = 00100000b
                break;
                
            case 3: 
                bitIsPresent =0x10 & *(toDraw + i); // 0x10h = 00010000b
                break;

            case 4: 
                bitIsPresent =0x08 & *(toDraw + i); // 0x08h = 00001000b
                break; 

            case 5: 
                bitIsPresent =0x04 & *(toDraw + i); // 0x04h = 00000100b
                break; 
                
            case 6: 
                bitIsPresent =0x02 & *(toDraw + i); // 0x02h = 000000010b
                break; 
                
            case 7: 
                bitIsPresent =0x01 & *(toDraw + i); // 0x01h = 000000001b
                break;             
            }

			if(bitIsPresent)
				fillrect(aux_x, aux_y,  color,fontSize,fontSize);
			else
				fillrect(aux_x, aux_y, backgroundColor, fontSize, fontSize);

			aux_x+=fontSize;
		}
        
        

		aux_x = x;
		aux_y+=fontSize;
	}
}

