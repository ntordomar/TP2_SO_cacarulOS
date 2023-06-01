#include <video.h>
#include <borrador.h>
#include <pipe.h>
#include <scheduler.h>
#include <process.h>
#include <heap.h>

int proc1(char **args)
{
	int pip = pipeCreateWithName(10);
	setFileDescriptor(getCurrentPid(), FD_WRITE, pip);
	char *buff = malloc(5);
	buff[0] = 'H';
	buff[1] = 'O';
	buff[2] = 'L';
	buff[3] = 'A';
	buff[4] = 0;

	pipeWrite(pip, buff, 5);
	while (1)
		;
	return 0;
}
