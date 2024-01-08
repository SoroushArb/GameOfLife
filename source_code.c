#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

// Function to draw the current state of the world
void draw(void *u, int w, int h) {
    char (*world)[w] = u;
    
    // Loop through each cell in the world
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++)
            // Print '#' for live cell, empty space for dead cell
            printf(world[y][x] ? " # " : " ");
        
        // Move to the next line for the new row
        printf("\n");
    }
}

// Function to evolve the world to the next generation
void evolution(void *u, int w, int h) {
    char (*world)[w] = u;
    char new[h][w];

    // Loop through each cell in the world
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            int lives = 0;

            // Check the neighbors of the current cell
            for (int xd = x - 1; xd <= x + 1; xd++) {
                for (int yd = y - 1; yd <= y + 1; yd++) {
                    // Ensure valid indices and count live neighbors
                    if (world[(yd + 1) % h][(xd + w) % w]) {
                        lives++;
                    }
                }
            }

            // Subtract the current cell if it is alive
            if (world[y][x]) {
                lives--;
            }

            // Apply the rules of the Game of Life to update the new world
            new[y][x] = (lives == 3 || (lives == 2 && world[y][x]));
        }
    }

    // Update the original world with the new generation
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            world[y][x] = new[y][x];
        }
    }
}

int main() {
    int w = 100;
    int h = 100;
    char world[w][h];

    // Initialize the world randomly with approximately 1/6 cells alive
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++)
            world[y][x] = rand() < RAND_MAX / 6 ? 1 : 0;
    }

    // Main loop for the Game of Life
    while (1) {
        // Draw the current state of the world
        draw(world, w, h);
        
        // Evolve the world to the next generation
        evolution(world, w, h);
        
        // Pause for a short period to observe the animation
        usleep(1000000);
    }

    return 0;
}
