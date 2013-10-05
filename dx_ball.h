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


