// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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
