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


