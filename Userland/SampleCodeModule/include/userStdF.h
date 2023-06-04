
#include <common.h>

#define BLACK 0x000000
#define GREEN 0x00FF00
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define CORAL 0xFF7F50
#define PINK 0xFF69B4
#define GOLD 0XAE8625
#define BLUE 0x1663BE
#define CREME 0xF1C27D
#define GRAY 0xDDDDDD
#define BROWN 0X92623A

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define LETTER_WIDTH 8
#define LETTER_HEIGHT 16

#include <stdint.h>
char getChar();
void itoa(int value, char *buffer, int base);
int strcmp(char *s1, char *s2);
int strlen(char *s);
void print(char *buffer, int color);
void hold(int num);
void printChar(char c, int color);
void newLine();
void divideString(char *command, char *param, char delim);
void backspace();
void clear();
void setCharSize(int size);
void resetTerminal();
void setCursorPosition(int x, int y);
void printf(int color, char *str, ...);
int atoi(char *str);
int isDigit(char c);
int killProcess(int pid);
int *getProcesses();
processInfo *getProcessInfo(int pid);
void *malloc(int size);
void free(void *ptr);
int setBlock(int pid);

int setNiceness(int pid, int prio);
memoryInfo * getMemoryInfo();

// https://www.techiedelight.com/implement-strcpy-function-c/
char *strcpy(char *destination, const char *source);