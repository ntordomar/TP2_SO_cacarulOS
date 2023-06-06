#ifndef USERLANDAPPS_H
#define USERLANDAPPS_H

#include <userStdF.h>

int sh();
int clear(char **  args);
void backspace();
void newLine();
int ps(char **args);

int help(char **args);
int loop(char **args);
int kill(char **args);
int nice(char **args);
int test_processes(char **args);
int block(char **args);
int mem(char **args);
int findAndExecProcess(char * line, char piped, int *fds);
int cat(char ** args);
int filter(char ** args);
int wc(char **args);
int phylo(char ** arguments);
int test_sync(char ** args);
int test_prio(char ** args);
int test_mem(char ** args);
int linkingProcess(char ** args);

#endif