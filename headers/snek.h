struct SnekObject {
    int y;
    int x;
};
typedef struct SnekObject Point;

void freeSnekPointers(Point *snek[]);
void drawSegment(int y, int x, WINDOW *window);
void drawHead(int y, int x, WINDOW *window);
void eraseSegment(int y, int x, WINDOW *window);
void moveSnek(Point *snek[100], WINDOW *window, int snekLength, int snekSpeed, int direction);