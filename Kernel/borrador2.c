#include<borrador.h>
#include <video.h>
#include "./include/sync.h"

int proc2(char ** args){

	int semp2 = semOpen("tordox");

	semWait(semp2);
	for(int i= 0; i < 10000; i++){
		draw_char(10, 60, 'A', RED, BLACK);
		draw_char(10, 60, 'B', RED, BLACK);
	}
	semPost(semp2);
    for(int i= 0; i < 20000; i++){
		draw_char(10, 60, 'A', GREEN, BLACK);
		draw_char(10, 60, 'B', GREEN, BLACK);
	}
	semClose(semp2);

	return 0;
}
