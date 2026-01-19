#ifndef _COMMON_
#define _COMMON_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 35
#define SCREEN_RESOLUTION (SCREEN_HEIGHT * SCREEN_WIDTH)

// Main functions
void render_donut();
void render_sphere();
void render_cube();

#endif
