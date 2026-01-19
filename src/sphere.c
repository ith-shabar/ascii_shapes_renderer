#include "common.h"


void render_sphere(){
    float theta, phi;
    float A = 0.0f, B = 0.0f;

    const float theta_spacing = 0.04f;
    const float phi_spacing = 0.01f;

    const float R1 = 1, R2 = 0;
    const float K2 = 5.0f;
    const float K1 = SCREEN_WIDTH*K2*3/(8*(R1+R2));

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

        for (theta = 0; theta < 6.28; theta += theta_spacing) {
            float sin_theta = sin(theta);
            float cos_theta = cos(theta);

            for (phi = 0; phi < 3.14; phi += phi_spacing) {
                float sin_phi = sin(phi);
                float cos_phi = cos(phi);

                float circleX = R2 + R1*cos_theta;
                float circleY = R1*sin_theta;

                float x = circleX*(cos_B*cos_phi + sin_A*sin_B*sin_phi) - circleY*cos_A*sin_B;
                float y = circleX*(sin_B*cos_phi - cos_B*sin_A*sin_phi) + circleY*cos_A*cos_B;
                float z = K2 + circleX*cos_A*sin_phi + circleY*sin_A;

                float depth = 1/(z);

                int screenX = ((SCREEN_WIDTH/2) + K1*depth*x);
                int screenY = ((SCREEN_HEIGHT/2) - 0.4f*K1*depth*y);

                int buffer_index = screenX + screenY*SCREEN_WIDTH;

                int luminous = 8*(cos_phi*cos_theta*sin_B - cos_A*cos_theta*sin_phi -sin_A*sin_theta + cos_B*(cos_A*sin_theta - cos_theta*sin_A*sin_phi));

                // depth test and screen bound test
                if (screenY >= 0 && screenY < SCREEN_HEIGHT && screenX >= 0 && screenX < SCREEN_WIDTH && depth > z_buffer[buffer_index]) {
                    z_buffer[buffer_index] = depth;
                    character_buffer[buffer_index] = brightness_level[luminous < 0 ? 0 : (luminous > 10 ? 10 : luminous)];
                }
            }
        }

        printf("\x1b[H");

        for (k = 0; k < SCREEN_RESOLUTION; k++) {
            putchar(k % SCREEN_WIDTH ? character_buffer[k] : 10);
        }

        usleep(30000);
        
    }
}

