#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600

#define START_SIDE_LENGTH 550
#define MAX_DEPTH 6

typedef struct Triangle {
    Vector2 a;
    Vector2 b;
    Vector2 c;
} Triangle;

// Draw filled triangle
void draw_triangle(Vector2 a, Vector2 b, Vector2 c, Color color)
{
    DrawTriangle(a, b, c, color);
}

// Midpoint helper
Vector2 mid(Vector2 a, Vector2 b)
{
    return (Vector2){
        (a.x + b.x) / 2.0f,
        (a.y + b.y) / 2.0f
    };
}

void sierpinski(Vector2 a, Vector2 b, Vector2 c, int depth)
{
    if (depth == 0)
    {
        draw_triangle(a, b, c, WHITE);
        return;
    }

    // Midpoints of triangle sides
    Vector2 ab = mid(a, b);
    Vector2 bc = mid(b, c);
    Vector2 ca = mid(c, a);

    // Recursive calls (3 corner triangles)
    sierpinski(a, ab, ca, depth - 1);
    sierpinski(ab, b, bc, depth - 1);
    sierpinski(ca, bc, c, depth - 1);
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Sierpinski Triangle");
    SetTargetFPS(60);

    int depth = 0;
    float timer = 0.0f;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            depth = 0;
            timer = 0.0f;
        }

        timer += GetFrameTime();
        if (timer >= 1.0f)
        {
            timer = 0.0f;
            if (depth < MAX_DEPTH)
                depth++;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Define main triangle (proper equilateral geometry)
        Vector2 a = { WIDTH / 2.0f, 50.0f };
        Vector2 b = { WIDTH / 2.0f - START_SIDE_LENGTH / 2.0f,
                      50.0f + START_SIDE_LENGTH * sinf(60 * DEG2RAD) };

        Vector2 c = { WIDTH / 2.0f + START_SIDE_LENGTH / 2.0f,
                      50.0f + START_SIDE_LENGTH * sinf(60 * DEG2RAD) };

        sierpinski(a, b, c, depth);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}