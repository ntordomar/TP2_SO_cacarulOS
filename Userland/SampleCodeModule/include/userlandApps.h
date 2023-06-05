#ifndef USERLANDAPPS_H
#define USERLANDAPPS_H

#include <userStdF.h>

int sh();
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
int findAndExecProcess(char * command, char * arg1, char * arg2, char fg, int * fds);
int cat(char ** args);
int filter(char ** args);
int wc(char **args);

#endif