#include <video.h>

struct vbe_mode_info_structure* screenInformation = (void *)0x5C00; // la datita que nos provee la catedra esta en esta direccion de memoria (fijarse la funcion sysvar en el Bootloader)

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
    
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            putpixel(x + i, y + j, color);
        }
        
    }
}