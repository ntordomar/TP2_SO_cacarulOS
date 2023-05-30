#include <lib.h>
#include <idle.h>
#include <video.h>
#include <process.h>

void idle()
{
    for (int i = 0; i < 10000; i++)
    {
        draw_char(200, 400, 'X', RED, BLACK);
        draw_char(200, 400, 'Y', RED, BLACK);
    }

    toggleBlockProcess(2);
    draw_char(700, 400, 'K', RED, BLACK);

    while (1)
    {
        draw_char(200, 400, 'X', GREEN, BLACK);
        draw_char(200, 400, 'Y', GREEN, BLACK);
    }
}
