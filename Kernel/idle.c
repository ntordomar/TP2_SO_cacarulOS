#include <lib.h>
#include <idle.h>
#include <video.h>
#include <process.h>

void idle()
{

    while (1)
    {
        draw_char(900, 200, 'I', RED, BLACK);
		draw_char(900, 200, 'D', RED, BLACK);
        draw_char(900, 200, 'L', RED, BLACK);
        draw_char(900, 200, 'E', RED, BLACK);
    }
}
