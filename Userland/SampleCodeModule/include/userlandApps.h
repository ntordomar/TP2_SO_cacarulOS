#ifndef USERLANDAPPS_H
#define USERLANDAPPS_H
// #include <common.h>
#include <userStdF.h>

void sh();
void clear();
void backspace();
void newLine();
// void tron();
// void piano();
// void process();
int ps(char **args);

int help(char **args);
int loop(char **args);
int kill(char **args);
int nice(char **args);
int test_processes(char **args);
int block(char **args);
int mem(char **args);

#endif