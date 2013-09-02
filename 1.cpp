#include "StdAfx.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <stdarg.h>
#include <stdio.h>
#include <cmath>

using namespace std;

#define RADIUS 0.025

#define RATIO (4./3.)

bool show[5][10];
//array of x,y positions of the brick object.
//read this from a file for creating map effects or you may initialize this directly.
const int x_max = 9;
const int y_max = 9;

float x_brick[x_max][y_max];
float y_brick[x_max][y_max];

float paddle_x = 0;
float paddle_y = -0.8;
float paddle_speed = 0;
const float PaddleSpeedFactor = 3.;

bool phit_center = false , phit_corner = false;
bool game_over = false;

float speed_x = 0.;
float speed_y = 0.;

float x_pos = 0,y_pos = -0.75; //position of the ball.
int lives  = 3; //display this. 

float T_last_frame = 0.;//????

//draws bricks on the screen.
//Uses GL_QUADS to draw the brick.
void draw_bricks()
{
      glColor3f(1.0,0.0,0.0);
      glBegin(GL_QUADS);

      for(int a = 0; a < 9; a++)
              for(int b = 0; b < 4; b++)
                      if(show[b][a] == 1)
                      {
                                    glVertex2f(x_brick[b][a],y_brick[b][a]);
                                    glVertex2f(x_brick[b][a],y_brick[b][a] - 0.10); 
                                    glVertex2f(x_brick[b][a]+0.2,y_brick[b][a] - 0.10);
                                    glVertex2f(x_brick[b][a]+0.2,y_brick[b][a]);  
                      }
      glEnd();
}

//Draw circle for ball.
void ball_draw()
{
     glColor3f(0.0,0.0,0.0);
     glBegin(GL_TRIANGLE_FAN); 
     glVertex2f(x_pos,y_pos); //position of the ball.
     for (float angle = 0; angle < (10); angle+=0.01)
     {
         glVertex2f((x_pos + sin(angle) * RADIUS), (y_pos + (cos(angle)) * RADIUS));
     }
	 /// if you increase number of fans then ball will appear more circular.
     glEnd();
}
//Check for collision with every brick. Better implementation is possible, but since there are only 36 bricks this approach is ok.

bool brick_hit()
{
     bool hit = false;
     int flag = 1;
     for(int a = 0; a < 10; a++)
     {
             for(int b =0; b < 4; b++)
             {
                     if(x_pos >= x_brick[b][a] && x_pos <= x_brick[b][a] + 0.2)
                     {
                              if(y_pos <= y_brick[b][a] && y_pos >= y_brick[b][a] - 0.1)
                              {
                                       if(show[b][a] == 1)
                                       {
                                                     show[b][a] = 0;
                                                     flag = 0;
                                                     hit = true;
                                                     break;
                                       }
                              }
                     }
             }
             if(flag == 0)
                   break;
     }
     return hit;
}

bool crashed()
{
     if(y_pos < paddle_y - 0.05)
		return true;
	 else
	    return false;
}
//collision with the paddle.
void paddle_hit()
{
     phit_corner = false;
     phit_center = false;
     if(x_pos <= paddle_x + 0.13 && x_pos >= paddle_x - 0.13)
     {
              if(y_pos <= paddle_y)
              {
                       phit_center = true;
              } // doubt
     }
     else if( (x_pos >= paddle_x + 0.13 && x_pos <= paddle_x + 0.2) || 
                  (x_pos <= paddle_x - 0.13 && x_pos >= paddle_x - 0.2))
     {
               if(y_pos <= paddle_y)
               {
                        phit_corner = true;
               }
     }
}

void paddle_move(float dT)
{

    if(paddle_x < RATIO && paddle_x > -RATIO)
        paddle_x += paddle_speed * PaddleSpeedFactor * dT;

        if( paddle_x > 0.95) {
        paddle_x = 0.95;
        paddle_speed = 0.;
    }

        if( paddle_x < -0.95) {
        paddle_x = -0.95;
        paddle_speed = 0.;
    }

    paddle_speed *= (1. - 0.05);
    if( fabs(paddle_speed) < 0.01 )
        paddle_speed = 0.;
}

void ball_move(float dT)
{
      x_pos += speed_x * dT;
      y_pos += speed_y * dT;

      if( brick_hit() ) {
        speed_y *= -1;
      }

      if( x_pos >= (RATIO-RADIUS) || x_pos <= (-RATIO+RADIUS ) )
      {
        speed_x *= -1;
      }

      if( y_pos >= (1.-RADIUS) )
      {
        speed_y *= -1;
      }

      paddle_hit();
      if(phit_center)
      {
        speed_y *= -1;
      }
      if(phit_corner)
      {
        speed_x *= -1;
        speed_y *= -1;
      }
}

void paddle_draw()
{
     glColor3f(0.0,0.0,0.0);
     glBegin(GL_QUADS);
                      glVertex2f(paddle_x - 0.2, paddle_y);
                      glVertex2f(paddle_x + 0.2, paddle_y);
                      glVertex2f(paddle_x + 0.2, paddle_y - 0.05);
                      glVertex2f(paddle_x - 0.2, paddle_y - 0.05);
     glEnd();
}

void step_game()
{
     paddle_move(T_last_frame);
     ball_move(T_last_frame);

     if(crashed())
     {
        speed_x = 0;
        speed_y = 0; 
        x_pos = 0;
        y_pos = -0.7;
        paddle_speed = 0;
        paddle_x = 0;
		lives--;
     }

     glutPostRedisplay();
}

void launch_ball()
{
    speed_y = .1;
    speed_x = .1;
}

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
