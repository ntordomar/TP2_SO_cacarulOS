#include <user_syscalls.h>
#include <userStdF.h>
#include <stdint.h>
#include <stdarg.h>

static int Ypos = 0;
static int Xpos = 0;

static int charSize = 1;


char getChar(){
    char localBuff[1];
    sys_read(localBuff, 1);
    return localBuff[0];
}





void itoa(int value, char *buffer, int base) {
    char *myBuff = buffer;
    int digits = 0;

    if (value == 0) {
        *myBuff++ = '0';
    }

    while (value) {
       
        int resto = value % base;
        if (resto < 10) {
            *myBuff++ = resto + '0';
        } else {
            *myBuff++ = resto + 'A' - 10;
        }
        digits++;
        value /= base;
    }
    
    *myBuff = 0;
    
    char *aux1, *aux2;
    aux1 = buffer;
    aux2 = myBuff - 1;
    while (aux1 < aux2) {
        char tmp = *aux1;
        *aux1 = *aux2;
        *aux2 = tmp;
        aux1++;
        aux2--;
    }
}

 
int atoi(char* str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    return res;
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
        if ((Xpos + (charSize * 8)) >= 1024){
            Xpos = 0;
            Ypos += charSize * 16; // el 1 es el size falta getter
        } if ((Ypos + (charSize * 16)) >= 768){
            clear();
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
    resetTerminal();
}

void newLine(){
    Xpos = 0;
    Ypos += 16 * charSize;
}

void printChar(char c, int color){
    print(&c, color);
}



//https://www.techiedelight.com/implement-strcpy-function-c/
char * strcpy(char* destination, const char* source){
    // return if no memory is allocated to the destination
    if (destination == 0) {
        return 0;
    }
 
    // take a pointer pointing to the beginning of the destination string
    char *ptr = destination;
 
    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // include the terminating null character
    *destination = '\0';
 
    // the destination is returned by standard `strcpy()`
    return ptr;
}

void hold(int delta){
    sys_get_ticks(delta);
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

void setCursorPosition(int x, int y){
    Xpos = x;
    Ypos = y;
}

// https://www.equestionanswers.com/c/c-printf-scanf-working-principle.php
void printf(int color, char * str, ...) {  
    va_list vl;
    int i = 0, j=0;
    char buff[100]={0}, tmp[20];
    char * str_arg;
    
    va_start( vl, str );
    while (str && str[i])
    {
        if(str[i] == '%'){
            i++;
            switch (str[i]) {
            /* Convert char */
                case 'c': {
                    buff[j] = (char)va_arg( vl, int );
                    j++;
                    break;
                }
                /* Convert decimal */
                case 'd': {
                    itoa(va_arg( vl, int ), tmp, 10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                /* Convert hex */
                case 'x': {
                    itoa(va_arg( vl, int ), tmp, 16);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                /* Convert octal */
                case 'o': {
                    itoa(va_arg( vl, int ), tmp, 8);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                /* copy string */
                case 's': {
                    str_arg = va_arg( vl, char* );
                    strcpy(&buff[j], str_arg);
                    j += strlen(str_arg);
                    break;
                }
            }
        }else if(str[i] == '\n'){
            j = 0;
            print(buff, color); 
            buff[j]=0; // arreglamos el caso de \n encadenados
            newLine();
        } 
        else {
            buff[j] =str[i];
            j++;
        }
        i++;
    } 
    buff[j] = 0;
    print(buff, color); 
    va_end(vl);
    
}


int isDigit(char c){
    return c >= '0' && c<= '9';
}