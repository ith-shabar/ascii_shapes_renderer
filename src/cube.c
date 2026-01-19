#include "common.h"

void render_cube(){
    float A = 0.0f, B = 0.0f;

    const float cube_size = 1.5f;
    const float resolution = 0.05f;

    const float K2 = 10.0f;
    const float K1 = SCREEN_WIDTH*K2*2/(8*(cube_size));

    int k;

    char character_buffer[SCREEN_RESOLUTION];
    float z_buffer[SCREEN_RESOLUTION];

    const char *brightness_level = ".,-~:;!*#$@";

    printf("\x1b[2J");

    while (1) {
        memset(character_buffer, 32, SCREEN_RESOLUTION);
        memset(z_buffer, 0, SCREEN_RESOLUTION*sizeof(float));

        float sin_A = sin(A);
        float sin_B = sin(B);
        float cos_A = cos(A);
        float cos_B = cos(B);

        for (float x = -cube_size; x <= cube_size; x+=resolution) {
            for (float y = -cube_size; y <= cube_size; y+=resolution) {
                float faces[6][6] = {
                    { x, y, -cube_size,  0,  0, -1},
                    { x, y, cube_size ,  0,  0,  1},
                    { x, -cube_size, y,  0, -1,  0},
                    { x,  cube_size, y,  0,  1,  0},
                    { -cube_size, x, y, -1,  0,  0},
                    {  cube_size, x, y,  1,  0,  0}
                };

               for (int f = 0; f < 6; f++) {
                    
                    float pointX  = faces[f][0];
                    float pointY  = faces[f][1];
                    float pointZ  = faces[f][2];

                    float normalX = faces[f][3];
                    float normalY = faces[f][4];
                    float normalZ = faces[f][5];

                    float x = pointX * cos_B + pointZ *sin_B;
                    float y = pointY * cos_A - sin_A * (pointZ * cos_B - pointX * sin_B);
                    float z = K2 + pointY * sin_A + cos_A * (pointZ * cos_B - pointX * sin_B);

                    float dept = 1.0f/z;

                    int screenX = (int)(SCREEN_WIDTH/2 + K1 * dept * x);
                    int screenY = (int)(SCREEN_HEIGHT/2 - 0.4f * K1 * dept * y);

                    int buffer_index = screenX + screenY * SCREEN_WIDTH;
                    
                    // Rotating normals
                    float rotated_normalX = normalX * cos_B + normalZ * sin_B;
                    float rotated_normalY = normalY * cos_A - sin_A * (normalZ * cos_B - normalX *sin_B);
                    float rotated_normalZ = normalY * sin_A + cos_A * (normalZ * cos_B - normalX *sin_B);

                    float lumin = rotated_normalX * 0 + rotated_normalY * 1 + rotated_normalZ * -1;
                    int lum_index = (int)(lumin * 8);
                    if (screenX >= 0 && screenX < SCREEN_WIDTH && screenY >= 0 && screenY < SCREEN_HEIGHT && dept > z_buffer[buffer_index]) {
                        z_buffer[buffer_index] = dept;
                        character_buffer[buffer_index] = brightness_level[lum_index < 0 ? 0 : (lum_index > 10 ? 10 : lum_index)];
                    }
               } 
            }
        }


        printf("\x1b[H");

        for (k = 0; k < SCREEN_RESOLUTION; k++) {
            putchar(k % SCREEN_WIDTH ? character_buffer[k] : 10);
        }

        A += 0.009f;
        B += 0.004f;

        usleep(30000);
        
    }
}

