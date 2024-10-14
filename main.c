#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <time.h>
#include <math.h>

#define X_BALLS        10
#define MAX_VELOCITY   300
#define RADIUS         20


typedef struct {
    int location_x[X_BALLS];
    int location_y[X_BALLS];
    int velocity_x[X_BALLS];
    int velocity_y[X_BALLS];
    int radius[X_BALLS];
    int mass[X_BALLS];
} List_of_Balls_SoA;

int get_random_sign() {
    return (rand() % 2 == 0) ? -1 : 1;
}

int distance(List_of_Balls_SoA* balls, int index_1, int index_2) {
    int x1 = balls->location_x[index_1];
    int y1 = balls->location_y[index_1];
    int x2 = balls->location_x[index_2];
    int y2 = balls->location_y[index_2];

    int dist = (int)sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    return dist;
}

void collision(List_of_Balls_SoA* balls, int index_1, int index_2) {
    int vx1 = balls->velocity_x[index_1];
    int vy1 = balls->velocity_y[index_1];
    int m1 = balls->mass[index_1];
    int vx2 = balls->velocity_x[index_2];
    int vy2 = balls->velocity_y[index_2];
    int m2 = balls->mass[index_2];

    balls->velocity_x[index_1] = (vx1 * (m1 - m2) + 2 * m2 * vx2) / (m1 + m2);
    balls->velocity_y[index_1] = (vy1 * (m1 - m2) + 2 * m2 * vy2) / (m1 + m2);
    balls->velocity_x[index_2] = (vx2 * (m2 - m1) + 2 * m1 * vx1) / (m1 + m2);
    balls->velocity_y[index_2] = (vy2 * (m2 - m1) + 2 * m1 * vy1) / (m1 + m2);
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    List_of_Balls_SoA balls;

    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "balls");
    SetTargetFPS(60);            
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
    while (!WindowShouldClose())  
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
            for (int j = 0; j < X_BALLS; j++) 
            {
                if (i == j) break;
                if (distance(&balls, i, j) < (balls.radius[i] + balls.radius[j])) 
                {
                    collision(&balls, i, j);
                }
            }
            // update location
            balls.location_x[i] += (int)(balls.velocity_x[i] * (1.0/60.0));
            balls.location_y[i] += (int)(balls.velocity_y[i] * (1.0/60.0));
        }
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
