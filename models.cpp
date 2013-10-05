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


