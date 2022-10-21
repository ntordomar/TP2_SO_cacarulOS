#include <user_syscalls.h>
static int xPos = 0;
static int yPos = 0;

void terminal() {
     sys_write(xPos, yPos, "p");
}