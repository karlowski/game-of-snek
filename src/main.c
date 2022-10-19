#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "./headers/snek.h"
#include "./headers/windows.h"
#include "./headers/utils.h"
#include "./headers/properties.h"
#include "./headers/controls.h"

Point *snek[100];
Point *fud;

int gameWidth;
int gameHeight;
int consoleWidth;
int consoleHeight;
int gameBorderRight;
int gameBorderLeft = 1;
int gameBorderUp = 1;
int gameBorderDown;
int gameSlowerness;
int score;
bool isGameOver = true;
bool isFirstRun = true;

int snekLength;
int snekDirection;

WINDOW *window;
WINDOW *console;

void giveMemory()
{
    for (int i = 0; i < 100; i++)
    {
        snek[i] = (Point *)malloc(sizeof(Point));
    }
    fud = (Point *)malloc(sizeof(Point));
}

void freeMemory()
{
    freeSnekPointers(snek);
    free(fud);
}

void handleFirstRun()
{
    wclear(console);
    box(console, 0, 0);
    mvwprintw(console, 1, 1, "WELCOME TO GAME OF SNEK");
    mvwprintw(console, 2, 1, "PRESS ENTER TO PLAY");
    handleConsoleControls(&isGameOver, console);
    isFirstRun = false;
    wclear(console);
    box(console, 0, 0);
}

void resolveGameOver()
{
    wclear(console);
    box(console, 0, 0);
    mvwprintw(console, 1, 1, "GAME OVER");
    mvwprintw(console, 1, 25, "SNEK IS DED");
    mvwprintw(console, 2, 1, "FINAL SCORE: %d", score);
    mvwprintw(console, 2, 25, "PRESS ENTER TO PLAY AGAIN");
    handleConsoleControls(&isGameOver, console);
}

void drawFud()
{
    mvwprintw(window, fud->y, fud->x, fudCharacter);
}

void eatFud()
{
    fud->y = calculateRandom(gameBorderUp, gameBorderDown);
    fud->x = calculateRandom(gameBorderLeft, gameBorderRight);

    drawFud();

    snek[snekLength]->y = snek[snekLength - 1]->y;
    snek[snekLength]->x = snek[snekLength - 1]->x;
    snekLength++;
    score++;
    gameSlowerness -= gameSlowernessDecrement;
}

void resetFud()
{
    fud->y = calculateRandom(gameBorderUp, gameBorderDown);
    fud->x = calculateRandom(gameBorderLeft, gameBorderRight);
    drawFud();
}

void checkSnekCollision()
{
    if (snek[0]->x == fud->x && snek[0]->y == fud->y) 
    {
        eatFud();
    }
    if (snek[0]->x < gameBorderLeft || snek[0]->x > gameBorderRight)
    {
        isGameOver = true;
    }
    if (snek[0]->y < gameBorderUp || snek[0]->y > gameBorderDown)
    {
        isGameOver = true;
    }
}

int update()
{
    drawFud();
    moveSnek(snek, window, snekLength, snekSpeed, snekDirection);
    checkSnekCollision();
    mvwprintw(console, 1, 1, "SCORE: %d", score);
    return 1;
}

void initialize()
{
    gameSlowerness = defaultGameSlowerness;
    snekDirection = 1;
    snekLength = 2;
    score = 0;
    isGameOver = false;

    for (int i = 0; i < snekLength; i++) 
    {
        snek[i]->y = gameHeight / 2;
        snek[i]->x = gameWidth / 2;
    }

    resetFud();
    initscr();
    window = createWindow(gameHeight, gameWidth, 1, 1);
    console = createWindow(consoleHeight, consoleWidth, gameHeight + 1, 1);
}

int main() 
{
    giveMemory();
    setWindowsSize(
        &gameWidth,
        &gameHeight,
        &gameBorderRight,
        &gameBorderDown,
        &consoleWidth,
        &consoleHeight
    );

    while(1)
    {
        initialize();
        keypad(window, TRUE);
        nodelay(window, TRUE);
        srand(time(NULL) - getpid());

        if (isFirstRun)
        {
            handleFirstRun();
        }

        while(!isGameOver)
        {
            handleGameControls(&snekDirection, window);
            update();
            wrefresh(window);
            wrefresh(console);
            msleep(gameSlowerness);
        }
        
        if (isGameOver && !isFirstRun)
        {
            resolveGameOver();
        }
    }

    werase(window);
    werase(console);
    freeMemory();
    return 0;
}
