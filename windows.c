#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "./headers/windows.h"

WINDOW * createWindow(int height, int width, int y, int x)
{
    WINDOW *window = newwin(height, width, y, x);
    wrefresh(window);
    box(window, 0, 0);
    return window;
}

void setWindowsSize
(
    int* gameWidth, 
    int* gameHeight, 
    int* gameBorderRight, 
    int* gameBorderDown, 
    int* consoleWidth, 
    int* consoleHeight
) 
{
    struct winsize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

    *gameWidth = window.ws_col - 5;
    *gameHeight = window.ws_row - 10;
    *gameBorderRight = *gameWidth - 2;
    *gameBorderDown = *gameHeight - 2;

    *consoleWidth = window.ws_col - 5;
    *consoleHeight = 5;
}