#define BLACK 0x000000
#define GREEN 0x00FF00
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define CORAL 0xFF7F50
#define PINK 0xFF69B4
#define GOLD 0XAE8625
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#include <stdint.h>
char getChar();
void itoa(uint64_t value, char *buffer, uint32_t base);
int strcmp(char * s1, char * s2);
int strlen(char * s);
void print(char * buffer, int color);
void hold(int num);
void printChar(char c, int color);
void newLine();
void divideString(char * command, char * param, char delim);
void backspace();
void clear();
void setCharSize(int size);
void resetTerminal();
void setCursorPosition(int x, int y);
void printf(int color, char * str, ...);
int atoi(char* str);
int scanf(char * str, ...);
int isDigit(char c);


//https://www.techiedelight.com/implement-strcpy-function-c/
char * strcpy(char* destination, const char* source);