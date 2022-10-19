#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "./headers/snek.h"
#include "./headers/properties.h"

void freeSnekPointers(Point *snek[100])
{
    for (int i = 0; i < 100; i++) { 
    	free(snek[i]); 
    }
}

void drawSegment(int y, int x, WINDOW *window)
{
    mvwprintw(window, y, x, snekCharacter);
}

void drawHead(int y, int x, WINDOW *window)
{
    mvwprintw(window, y, x, snekHeadCharacter);
}

void eraseSegment(int y, int x, WINDOW *window)
{
    mvwprintw(window, y, x, " ");
}

void moveSnek(Point *snek[100], WINDOW *window, int length, int speed, int direction)
{
    for (int i = length - 1; i >= 1; i--) 
    {
        if (i == length - 1) eraseSegment(snek[i]->y, snek[i]->x, window);

        snek[i]->x = snek[i - 1]->x;
        snek[i]->y = snek[i - 1]->y;

        drawSegment(snek[i]->y, snek[i]->x, window);
    }

    if (direction == 0) 
    {
        snek[0]->y = snek[0]->y - speed;
    }
    else if (direction == 1)
    {
        snek[0]->x = snek[0]->x + speed;
    }        
    else if (direction == 2)
    {
        snek[0]->y = snek[0]->y + speed;
    }
    else if (direction == 3)
    {
        snek[0]->x = snek[0]->x - speed;
    }

    drawHead(snek[0]->y, snek[0]->x, window);
}