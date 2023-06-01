#include <video.h>
#include <borrador.h>
#include "./include/sync.h"




int proc1(char ** args){
	int semp1 = semOpen("tordox");
	semWait(semp1);
	for (size_t i = 0; i < 10000; i++)
	{
		draw_char(10, 10, 'A', RED, BLACK);
		draw_char(10, 10, 'B', RED, BLACK);
	}
	semPost(semp1);
	semClose(semp1);
	semDestroy(semp1);
	for(int i= 0; i < 10000; i++){
		draw_char(300, 200,'K',GREEN, BLACK);
		draw_char(300, 200, 'O',GREEN, BLACK);

	}
	return 0;
}


