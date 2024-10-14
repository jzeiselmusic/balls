#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>

#define X_BALLS        200
#define MAX_VELOCITY   300
#define RADIUS         3

int get_random_sign() {
    return (rand() % 2 == 0) ? -1 : 1;
}

typedef struct {
    int location_x[X_BALLS];
    int location_y[X_BALLS];
    int velocity_x[X_BALLS];
    int velocity_y[X_BALLS];
    int radius[X_BALLS];
    int mass[X_BALLS];
} List_of_Balls_SoA;


int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    List_of_Balls_SoA balls;

    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    // init X amount of balls
    for (int i = 0; i < X_BALLS; i++) 
    {
        balls.location_x[i] = rand() % screenWidth;
        balls.location_y[i] = rand() % screenHeight;
        balls.velocity_x[i] = get_random_sign() * (rand() % MAX_VELOCITY);
        balls.velocity_y[i] = get_random_sign() * (rand() % MAX_VELOCITY);
        balls.radius[i] = RADIUS;
        balls.mass[i] = 5;
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        for (int i = 0; i < X_BALLS; i++) 
        {
            DrawCircle(balls.location_x[i], balls.location_y[i], balls.radius[i], DARKBLUE);
        }
        EndDrawing();

        for (int i = 0; i < X_BALLS; i++) 
        {
            // check for boundaries and bounces
            if (
                    (balls.location_x[i] + balls.radius[i] > screenWidth) || 
                    (balls.location_x[i] - balls.radius[i] < 0)
               ) 
            {
                balls.velocity_x[i] *= -1;
            }
            if (
                    (balls.location_y[i] + balls.radius[i] > screenHeight) || 
                    (balls.location_y[i] - balls.radius[i] < 0)
               )
            {
                balls.velocity_y[i] *= -1;
            }
            // update location
            balls.location_x[i] += (int)(balls.velocity_x[i] * (1.0/60.0));
            balls.location_y[i] += (int)(balls.velocity_y[i] * (1.0/60.0));
        }
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
