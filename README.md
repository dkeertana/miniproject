# miniproject
2D Graphics Editor Using C

Project Description

This project implements a simple 2D Graphics Editor using C. The editor uses a 2D character array to represent a drawing canvas. Shapes are drawn using '*' characters, while empty spaces are represented using '_'.

Features

- Draw Line
- Draw Rectangle
- Draw Circle
- Draw Triangle
- Add objects to the canvas
- Delete objects from the canvas
- Modify existing objects
- Display the complete picture

Data Structures Used

- 2D Character Array ("canvas[ROWS][COLS]") for storing the picture.
- Structure ("Object") for storing shape information.
- Array of Objects for managing multiple graphical objects.

Functions Implemented

- "drawLine()"
- "drawRectangle()"
- "drawCircle()"
- "drawTriangle()"
- "addLine()"
- "addRectangle()"
- "addCircle()"
- "addTriangle()"
- "deleteObject()"
- "modifyObject()"
- "displayCanvas()"
- "redraw()"

Compilation

gcc miniproject.c -o miniproject -lm

Execution

./miniproject

(Windows PowerShell)

.\miniproject.exe

Menu Options

1. Add Line
2. Add Rectangle
3. Add Circle
4. Add Triangle
5. Delete Object
6. Modify Object
7. Display Picture
8. Exit

Outcome

The project successfully demonstrates basic computer graphics concepts using a character-based canvas and supports creation, modification, deletion, and display of graphical objects.