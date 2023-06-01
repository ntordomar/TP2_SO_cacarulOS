#include <video.h>
#include <borrador.h>
#include "./include/sync.h"

int semp1;
int semp2;
int semp3;

int proc1(char ** args){
	draw_char(100, 200, 'p', RED, BLACK);
	semp1 = semOpen("mutex");

	semWait(semp1);
	for (size_t i = 0; i < 100000; i++)
	{
		draw_char(10, 10, 'A', RED, BLACK);
		draw_char(10, 10, 'B', RED, BLACK);
	}
	draw_char(200, 200, 'A', RED, BLACK);
	semPost(semp1);
	return 0;
}

int proc2(char ** args){
draw_char(100, 300, 'z', RED, BLACK);
	semp2 = semOpen("mutex");

	semWait(semp2);
	for(int i= 0; i < 100000; i++){
		draw_char(10, 60, 'A', RED, BLACK);
		draw_char(10, 60, 'B', RED, BLACK);
	}
	draw_char(400, 200, 'd', RED, BLACK);
	semPost(semp2);
	return 0;
}

int proc3(char ** args){
draw_char(100, 400, 'q', RED, BLACK);
	semp3 = semOpen("mutex");
	semWait(semp3);
	
	for (size_t i = 0; i < 100000; i++){
		
		draw_char(10, 80, 'A', RED, BLACK);
		draw_char(10, 80, 'B', RED, BLACK);
	}
	draw_char(600, 200, 'C', RED, BLACK);
	semPost(semp3);
	return 0;
}