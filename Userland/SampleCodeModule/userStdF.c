#include <user_syscalls.h>
#include <userStdF.h>
#include <stdint.h>

static int Ypos = 0;
static int Xpos = 0;

static int charSize = 1;

static int buffPos = 0;
static int getCCount = 0;

char getc(){
    getCCount++;
    char localBuff[1];
    sys_read(&localBuff, 1);
    return localBuff[0];
}

void itoa(uint64_t value, char *buffer, uint32_t base) {
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    // Calculate characters for each digit
    do {
        uint32_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    } while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    // Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

}

int strcmp(char * s1, char * s2){ // returns 0 if there are the same string. ambos strings null terminated
int i = 0; 
while (s1[i] != 0 && s2[i] != 0){
    if(s1[i] != s2[i]) return 1;
    i++;
}
if(s1[i] != 0 || s2[i] != 0)return 1;
return 0;

}

int strlen(char * s){
    int counter  = 0;
    while(s[counter] != 0) counter ++;
    return counter;
}

void print(char * buffer, int color){
    int len = strlen(buffer);
    for (int i = 0; i<len; i++){
        if (Xpos >= 1024){
            Xpos = 0;
            Ypos += charSize * 16; // el 1 es el size falta getter
        }
        sys_write_char(Xpos, Ypos, buffer[i], color);
        Xpos += 8 * charSize;
        //Checkear si hay que saltar de linea
    }
}

void backspace(){
    if(Xpos <= 0) {
    if(Ypos == 0) return;

        Xpos = 1024;
        Ypos -= 16 * charSize; // el 1 es el size
    } else {
        Xpos -= charSize*8; // El 1 es el size
    }
    sys_write_char(Xpos,Ypos,' ',WHITE);
}

void clear(){
    sys_clear_screen();
    Xpos = 0;
    Ypos = 0;
}

void newLine(){
    Xpos = 0;
    Ypos += 16 * charSize;
}

void printChar(char c, int color){
    print(&c, color);
}

void printCurrentTime() {
    int  seconds, minutes, hours;
    sys_get_seconds(&seconds);
    sys_get_minutes(&minutes);
    sys_get_hours(&hours); 
    char  res[30] = {0};
    itoa(hours-3, res, 16) ;
    res[2] = ':';
    itoa(minutes,res+3,16);
    res[5] = ':'; 
    itoa(seconds, res+6, 16);

    // print(xPos, yPos, res, WHITE);
    print(res, WHITE);
}

void hold(int delta){
    long startTicks;
    sys_get_ticks(&startTicks);
    long ticks = startTicks;
    while(ticks <= startTicks + delta){
        sys_get_ticks(&ticks);
    }
    //print("me fui for good",WHITE);
}

void divideString(char * command, char * param, char delim){
    int i = 0;
    int dimParam=0;
    for ( ; command[i] != 0 && command[i] != delim; i++){
        ;
    }
    if(command[i] == 0) {
        param[0] = 0;
        return;
    }
    command[i++] = 0;
    
    for (; command[i] != 0; i++)
    {
        param[dimParam++] = command[i];
    }
    param[dimParam] = 0;
}

void setCharSize(int size) {
    charSize = size;
    sys_change_font_size(size);
}

void resetTerminal() {
    Xpos = 0;
    Ypos = 0;
}