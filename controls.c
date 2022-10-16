#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "./headers/controls.h"

void handleGameControls(int* direction, WINDOW* window)
{
    int c = wgetch(window);

    switch(c)
    {
        case KEY_UP:
            if (*direction != 2) 
                *direction = 0;
                break;
        case KEY_RIGHT:
            if (*direction != 3)
                *direction = 1;
                break;
        case KEY_DOWN:
            if (*direction != 0)
                *direction = 2;
                break;
        case KEY_LEFT:
            if (*direction != 1)
                *direction = 3;
                break;
        default:
            break;
    }
}

void handleConsoleControls(bool *isGameOver, WINDOW* console)
{
    int c = wgetch(console);

    switch(c)
    {
        case KEY_ENTER:
            *isGameOver = false;
            break;
        default:
            break;
    }
}