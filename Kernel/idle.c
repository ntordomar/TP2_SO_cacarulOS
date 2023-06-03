#include <lib.h>
#include <idle.h>
#include <video.h>
#include <process.h>

void idle()
{

    while (1)
    {
        hlt();
    }
}
