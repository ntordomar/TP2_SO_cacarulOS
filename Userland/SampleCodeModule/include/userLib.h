#include <stdint.h>
void sys_int_80(uint64_t mode, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5);
void _hlt();