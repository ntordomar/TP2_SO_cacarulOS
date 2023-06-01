#include <borrador.h>
#include <video.h>
#include "./include/sync.h"

int proc3(char ** args){
	int semp3 = semOpen("tordox");
		// draw_string(600, 200, m,6, RED, BLACK);

	semWait(semp3);
	
	for (size_t i = 0; i < 10000; i++){
		
		draw_char(10, 80, 'A', RED, BLACK);
		draw_char(10, 80, 'B', RED, BLACK);
	}
	semPost(semp3);
	semClose(semp3);
	return 0;
}