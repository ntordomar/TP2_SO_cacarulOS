/* sampleCodeModule.c */
// terminal
#include <user_syscalls.h>
#include <userStdF.h>
#include <stdint.h>
#include <userLib.h>

char * v = (char*)0xB8000 + 79 * 2;

int getFormat(int n);

static int var1 = 0;
static int var2 = 0;

static int yPos = 0;
static int xPos = 0;


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


int main() {
    char buff[1];
    int  seconds, minutes, hours;
    sys_get_seconds(&seconds);
    sys_get_minutes(&minutes);
    sys_get_hours(&hours); 
    
    char  secsChar[12] = {0};
    itoa(seconds, secsChar, 16) ;
    char  minChar[12] =  {0};
    itoa(minutes,minChar,16);
    char hourChar[12] = {0};  
    itoa(hours-3, hourChar, 16);
    
    sys_write(12, 122, secsChar, 20, 1);
    sys_write(12, 142, minChar, 20, 1);
    sys_write(12, 162, hourChar, 20, 1);
    sys_write(200, 200, "a", 1, 1);

    // char c = 0;
    // c = getc();

    // for (int i = 0; i<800000000; i++){
    //      _hlt();
    // }

    char a = getc();
    char b = getc();
    char c = getc();
    char d = getc();

    sys_write_char(200, 200, a, 1);
    sys_write_char(220, 200, b, 1);
    sys_write_char(240, 200, c, 1);
    sys_write_char(260, 200, d, 1);

    //c = getc();
    while(1){
        char c = getc();
        if (c!=-1){
            sys_write_char(xPos+=10, yPos, c, 1);
        }
        _hlt();
        //checkeo si hay algo ***nuevo***. Como se consume de a 1. Con que haya algo es nuevo 
        //Si hay algo lo imprimo
        //Si no hay nada --> repeat
    }
    
}

int getFormat(int n) {
	int dec = n & 240;
	dec = dec >> 4;
	int units = n & 15;
	return dec * 10 + units;
}

