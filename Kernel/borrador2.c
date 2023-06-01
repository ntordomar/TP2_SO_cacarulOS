#include <borrador.h>
#include <video.h>
#include <pipe.h>
#include <scheduler.h>
#include <process.h>
#include <heap.h>

int proc2(char **args)
{
	int pipe = getPipeIdByName(10);
	setFileDescriptor(getCurrentPid(), FD_READ, pipe);
	char *buff = malloc(5);
	pipeRead(pipe, buff, 5);
	while (1)
	{
		draw_string(100, 100, buff, 5, RED, BLACK);
		draw_char(300, 100, 'O', GREEN, BLACK);
	}

	return 0;
}
