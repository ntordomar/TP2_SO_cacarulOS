// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <user_syscalls.h>
#include <tron.h>
#include <userStdF.h>
#include <drawings.h>
#define SQUARE_UNIT 8
#define OUT_OF_BOUNDS(x, y) ((x) > SCREEN_WIDTH || (x) < 0 || (y) > SCREEN_HEIGHT || (y) < 0)

void exit()
{
    setCursorPosition(390, SCREEN_HEIGHT / 2);
    printf(PINK, "THANK YOU FOR PLAYING :)");
    hold(50);
    char c;
    while ((c = getChar()) != -1)
    {
        ;
    } // clears buffer
    return;
}

void youWin(int color, char *player)
{

    sys_beep(300, 18);
    setCursorPosition(440, SCREEN_HEIGHT / 2 + 80);
    printf(color, "%s!!\n", player);
    cup(250, SCREEN_HEIGHT / 2);
    cup(600, SCREEN_HEIGHT / 2);
    hold(50);
    exit();
    return;
}

void tronGame()
{

    setCursorPosition(375, 100);
    printf(GREEN, "WELCOME TO TRON LIGHT CYCLES\n");
    setCursorPosition(350, 400);
    print("Player 1: use the arrows to move", GREEN);
    setCursorPosition(345, 450);
    print("Player 2: use the WASD keys to move", GREEN);
    setCursorPosition(175, 600);
    print("Press 1 to start", GREEN);
    setCursorPosition(700, 600);
    print("Press ESC to exit", GREEN);
    char info;
    while ((info = getChar()) != '1')
    {
        if (info == 27)
        {
            return;
        }
    }
    sys_clear_screen();

    char matrix[SCREEN_WIDTH / SQUARE_UNIT][SCREEN_HEIGHT / SQUARE_UNIT];
    for (int i = 0; i < SCREEN_WIDTH / SQUARE_UNIT; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT / SQUARE_UNIT; j++)
        {
            matrix[i][j] = 0;
        }
    }

    int j1X = 900;
    int j1Y = 384;
    int j1Xincrement = -1;
    int j1Yincrement = 0;

    int j2X = 100;
    int j2Y = 384;
    int j2Xincrement = 1;
    int j2Yincrement = 0;
    char c;
    while (1)
    {
        hold(1);
        c = getChar();
        switch (c)
        {
        case 'W':
            if (j2Yincrement != 1)
            {
                j2Yincrement = -1;
                j2Xincrement = 0;
            }
            break;
        case 'A':
            if (j2Xincrement != 1)
            {
                j2Yincrement = 0;
                j2Xincrement = -1;
            }
            break;
        case 'S':
            if (j2Yincrement != -1)
            {
                j2Yincrement = 1;
                j2Xincrement = 0;
            }
            break;
        case 'D':
            if (j2Xincrement != -1)
            {
                j2Yincrement = 0;
                j2Xincrement = 1;
            }
            break;
        case 2: // left
            if (j1Xincrement != 1)
            {
                j1Xincrement = -1;
                j1Yincrement = 0;
            }
            break;
        case 3: // right
            if (j1Xincrement != -1)
            {
                j1Xincrement = 1;
                j1Yincrement = 0;
            }
            break;
        case 4: // up
            if (j1Yincrement != 1)
            {
                j1Xincrement = 0;
                j1Yincrement = -1;
            }
            break;
        case 5: // down
            if (j1Yincrement != -1)
            {
                j1Xincrement = 0;
                j1Yincrement = 1;
            }
            break;
        case 27:
            exit();
            return;
        default:
            break;
        }

        if (matrix[j1X / SQUARE_UNIT][j1Y / SQUARE_UNIT] == 1 || OUT_OF_BOUNDS(j1X, j1Y))
        {
            youWin(GREEN, "PLAYER 2 WINS");
            return;
        }
        else if (matrix[j2X / SQUARE_UNIT][j2Y / SQUARE_UNIT] == 1 || OUT_OF_BOUNDS(j2X, j2Y))
        {
            youWin(RED, "PLAYER 1 WINS");
            return;
        }
        //  else {
        //     matrix[j1X/SQUARE_UNIT][j1Y/SQUARE_UNIT] = 1;
        //     matrix[j2X/SQUARE_UNIT][j2Y/SQUARE_UNIT] = 1;
        // }
        if (j1X == j2X && j1Y == j2Y)
        {
            youWin(WHITE, "its a tie!");
            return;
        }
        j1X += SQUARE_UNIT * j1Xincrement;
        j2X += SQUARE_UNIT * j2Xincrement;
        j1Y += SQUARE_UNIT * j1Yincrement;
        j2Y += SQUARE_UNIT * j2Yincrement;

        sys_draw_rectangle(j1X, j1Y, SQUARE_UNIT, SQUARE_UNIT, RED);
        sys_draw_rectangle(j2X, j2Y, SQUARE_UNIT, SQUARE_UNIT, GREEN);
    }
    sys_clear_screen();
}