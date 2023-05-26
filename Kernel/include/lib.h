#ifndef LIB_H
#define LIB_H
#include <stdint.h>

//from lib.c
void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
void itoa(uint64_t value, char* buffer, uint16_t base);
int strlen(char * s);
char * strcpy(char* destination, const char* source);

char *cpuVendor(char *result);

//from libasm.asm
int getSeconds(); 
int getMinutes();
int getHours();
char getKey();
void _sti();
void hlt();
void outb(int memoryMap, int output); 
int inb(int memoryMap); // both inb and outb functions are used for beep, and to write/read in a memory position.
int getRDI();
void getRegisters(uint64_t * regs);
void getMemory(int memoryPos, unsigned char * res);
void getRegistersDebugger();
#endif


