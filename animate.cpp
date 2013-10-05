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


