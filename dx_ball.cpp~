#include "dx_ball.h"
#include "models.cpp"
#include "collision.cpp"
#include "animate.cpp"

void user_input(unsigned char key, int x, int y)
{
     if(key == 13)
        launch_ball();
}

void ArrowKeys(int key, int x, int y)
{
     if(key==GLUT_KEY_LEFT)
        paddle_speed = -.5;

     if(key==GLUT_KEY_RIGHT)
        paddle_speed = +.5;
}

void set_xy()
{
    for(int a = 0; a < 5; a++)
    {
            for(int b = 0; b < 10; b++)
            {
                    show[a][b] = 1;
            }
    }
    int c = 0;
    for(float a = -0.94; c <= 9; a+=0.21)
    {         

              for(int b = 0; b <= 5; b++)
              {
                      x_brick[b][c] = a;

              }
              c++;
    }
    int d = 0;
    for(float s = 0.99; d <= 4; s-=0.11)
    {
              for(int  r = 0; r < 9; r++)
              {
                       y_brick[d][r] = s;
              }
              d++;
    }
}

void display()
{
    const int win_width  = glutGet(GLUT_WINDOW_WIDTH);
    const int win_height = glutGet(GLUT_WINDOW_HEIGHT);
    const float win_aspect = (float)win_width / (float)win_height;

    glViewport(0, 0, win_width, win_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(win_aspect > RATIO) {
        glOrtho(-win_aspect, win_aspect, -1., 1., -1., 1.);
    } else {
        glOrtho(-RATIO, RATIO, -RATIO/win_aspect, RATIO/win_aspect, -1., 1.);
    }

    glMatrixMode(GL_MODELVIEW);

    glClearColor(0., 0., 1., 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(-RATIO, -1);
        glVertex2f(RATIO, -1);
        glVertex2f(RATIO, 1);
        glVertex2f(-RATIO, 1);
        glEnd();

    draw_bricks();
    paddle_draw();
    ball_draw();

    glutSwapBuffers();

        // GLUT doesn't offer cross plattform timing
        // assume 60Hz refresh rate
        T_last_frame = 1./60.;
}

int main(int argc, char **argv)
{
    set_xy();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Brick Breaker");
    glutDisplayFunc(display);

    glutKeyboardFunc(user_input);
    glutSpecialFunc(ArrowKeys);

    glutIdleFunc(step_game);

    glutMainLoop(); 

    return 0;
}
