#define BLACK 0x000000
#define GREEN 0x00FF00
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define CORAL 0xFF7F50
#define PINK 0xFF69B4
#include <stdint.h>
char getc();
void itoa(uint64_t value, char *buffer, uint32_t base);
int strcmp(char * s1, char * s2);
int strlen(char * s);
void print(int xPos, int yPos,char * buffer, int color);
void printCurrentTime(int xPos, int yPos);
void hold(int num);