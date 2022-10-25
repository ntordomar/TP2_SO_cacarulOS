#include <user_syscalls.h>
#include <userStdF.h>
#include <stdint.h>

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

void print(int xPos, int yPos, char * buffer){
int len = strlen(buffer);
sys_write(xPos,yPos,buffer,len,1);
}
