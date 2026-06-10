#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 40
#define COLS 80
#define MAX_OBJECTS 100

char canvas[ROWS][COLS];

typedef enum {
    LINE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE
} ShapeType;

typedef struct {
    ShapeType type;
    int id;

    union {
        struct {
            int x1, y1, x2, y2;
        } line;

        struct {
            int x, y, width, height;
        } rect;

        struct {
            int xc, yc, radius;
        } circle;

        struct {
            int x1, y1, x2, y2, x3, y3;
        } triangle;
    };
} Shape;

Shape objects[MAX_OBJECTS];
int count = 0;
int nextID = 1;

/* ---------- Canvas Functions ---------- */

void clearCanvas()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

void setPixel(int x, int y)
{
    if(x >= 0 && x < COLS && y >= 0 && y < ROWS)
        canvas[y][x] = '*';
}

void displayCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

/* ---------- Drawing Functions ---------- */

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        setPixel(x1, y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width, y);
    drawLine(x, y, x, y + height);
    drawLine(x + width, y, x + width, y + height);
    drawLine(x, y + height, x + width, y + height);
}

void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    while(x <= y)
    {
        setPixel(xc + x, yc + y);
        setPixel(xc - x, yc + y);
        setPixel(xc + x, yc - y);
        setPixel(xc - x, yc - y);

        setPixel(xc + y, yc + x);
        setPixel(xc - y, yc + x);
        setPixel(xc + y, yc - x);
        setPixel(xc - y, yc - x);

        if(d < 0)
            d += 2 * x + 3;
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

/* ---------- Object Functions ---------- */

void addObject(Shape s)
{
    if(count < MAX_OBJECTS)
        objects[count++] = s;
}

void deleteObject(int id)
{
    int found = 0;

    for(int i = 0; i < count; i++)
    {
        if(objects[i].id == id)
        {
            found = 1;

            for(int j = i; j < count - 1; j++)
                objects[j] = objects[j + 1];

            count--;
            break;
        }
    }

    if(found)
        printf("Object deleted.\n");
    else
        printf("Object not found.\n");
}

void redraw()
{
    clearCanvas();

    for(int i = 0; i < count; i++)
    {
        Shape *s = &objects[i];

        switch(s->type)
        {
            case LINE:
                drawLine(
                    s->line.x1,
                    s->line.y1,
                    s->line.x2,
                    s->line.y2);
                break;

            case RECTANGLE:
                drawRectangle(
                    s->rect.x,
                    s->rect.y,
                    s->rect.width,
                    s->rect.height);
                break;

            case CIRCLE:
                drawCircle(
                    s->circle.xc,
                    s->circle.yc,
                    s->circle.radius);
                break;

            case TRIANGLE:
                drawTriangle(
                    s->triangle.x1,
                    s->triangle.y1,
                    s->triangle.x2,
                    s->triangle.y2,
                    s->triangle.x3,
                    s->triangle.y3);
                break;
        }
    }
}

/* ---------- Main ---------- */

int main()
{
    int choice;

    while(1)
    {
        printf("\n=== 2D ASCII GRAPHICS EDITOR ===\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Circle\n");
        printf("3. Add Line\n");
        printf("4. Add Triangle\n");
        printf("5. Delete Object\n");
        printf("6. Display Picture\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        Shape s;
        int id;

        switch(choice)
        {
            case 1:
                s.type = RECTANGLE;
                s.id = nextID++;

                printf("x y width height: ");
                scanf("%d%d%d%d",
                      &s.rect.x,
                      &s.rect.y,
                      &s.rect.width,
                      &s.rect.height);

                addObject(s);
                break;

            case 2:
                s.type = CIRCLE;
                s.id = nextID++;

                printf("centerX centerY radius: ");
                scanf("%d%d%d",
                      &s.circle.xc,
                      &s.circle.yc,
                      &s.circle.radius);

                addObject(s);
                break;

            case 3:
                s.type = LINE;
                s.id = nextID++;

                printf("x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &s.line.x1,
                      &s.line.y1,
                      &s.line.x2,
                      &s.line.y2);

                addObject(s);
                break;

            case 4:
                s.type = TRIANGLE;
                s.id = nextID++;

                printf("x1 y1 x2 y2 x3 y3: ");
                scanf("%d%d%d%d%d%d",
                      &s.triangle.x1,
                      &s.triangle.y1,
                      &s.triangle.x2,
                      &s.triangle.y2,
                      &s.triangle.x3,
                      &s.triangle.y3);

                addObject(s);
                break;

            case 5:
                printf("Enter object ID to delete: ");
                scanf("%d", &id);
                deleteObject(id);
                break;

            case 6:
                redraw();
                displayCanvas();
                printf("\nObjects currently present:\n");

                for(int i = 0; i < count; i++)
                    printf("ID = %d\n", objects[i].id);

                break;

            case 7:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}