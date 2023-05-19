
#include <stddef.h>

#define TOTALHEAPSIZE ( ( size_t ) ( 52 * 1024 ) ) // TODO preguntar que tamanio

void * malloc(size_t size);
void free(void * ptr);
