typedef int pipe_t;
#define BUFFER_PIPE_SIZE 1024
#define MAX_PIPES 50

void pipeInit();
pipe_t pipeCreateWithName(int name);
pipe_t pipeCreateAnonymous();
int pipeWrite(pipe_t id, const char *src, unsigned int count);
int pipeRead(pipe_t id, char *dest, unsigned int count);
void pipeDestroy(pipe_t id);
void sendEOFSignal(pipe_t id);
pipe_t getPipeIdByName(int name);
void sendEOFToCurrent();
