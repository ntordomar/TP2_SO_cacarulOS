/* sampleCodeModule.c */

#include<user_syscalls.h>
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {

sys_clear_screen();
sys_write(12,122,'c');
sys_write(19,122,'h');	
}