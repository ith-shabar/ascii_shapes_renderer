#include "common.h"

int main(int argc, char *argv[])
{

    if (argc < 2) {
        render_donut();
        return 1;
    }

    if (strcmp(argv[1], "donut") == 0) {
        render_donut(); 
        
    } else if (strcmp(argv[1], "sphere") == 0) {
        render_sphere();

    } else if (strcmp(argv[1], "cube") == 0) {
        render_cube();

    } else {
        printf("Enter valid argument!\n\n");
        printf("donutplus <OPTION> \nOPTION = donut, sphere, cube \n");
    }


    return 0;
}
