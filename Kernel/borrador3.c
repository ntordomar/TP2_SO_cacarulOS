#include <borrador.h>
#include <video.h>
#include <pipe.h>
#include <process.h>

int proc3(char **args)
{
	int pipe = getPipeIdByName(10);
	// setFileDescriptor(getCurrentPid(), FD_WRITE, pipe
	pipeWrite(pipe, "Chau", 5);
	return 0;
}