#include <lib.h>
#include <idle.h>
#include <video.h>
#include <process.h>

void idle()
{

    while (1)
    {
        draw_char(200, 200, 'A', RED, BLACK);
        draw_char(200, 200, 'B', RED, BLACK);
        // hlt();
    }
}
