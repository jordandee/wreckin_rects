#include "SDL/SDL.h"
#include "image.h"
#include "constants.h"
#include "globals.h"
#include "ball.h"

Ball::Ball()
{
  ballsurf = load_image("ball.png");
  ballsurf2 = load_image("ball2.png");

  reset();
}

Ball::~Ball()
{
  SDL_FreeSurface(ballsurf);
  SDL_FreeSurface(ballsurf2);
}

void Ball::moveX(Uint32 deltaTime)
{
  x += deltaTime * xVel;
  rect.x = x;
}

void Ball::moveY(Uint32 deltaTime)
{
  y += deltaTime * yVel;
  rect.y = y;
}

void Ball::reset()
{
  // Place ball in the center
  rect.x = (SCREEN_WIDTH - ballsurf->w)/2;
  rect.y = SCREEN_HEIGHT - 100;
  rect.w = ballsurf->w;
  rect.h = ballsurf->h;
  x = rect.x;
  y = rect.y;

  xVel = 0;
  yVel = 0;
}

void Ball::serve()
{
  // Initialize xVel and yVel between .15 and .35
  xVel = .15 + rand()/(RAND_MAX/(.35 - .15));
  yVel = .15 + rand()/(RAND_MAX/(.35 - .15));
  yVel *= -1;

  // Randomize direction
  if (rand() % 2 == 0) { xVel *= -1; }
}

void Ball::render(int surface)
{
  if (surface == 1)
  {
    apply_surface(rect.x,rect.y,ballsurf,screen);
  }
  else if (surface == 2)
  {
    apply_surface(rect.x,rect.y,ballsurf2,screen);
  }

}

void Ball::set_x(int X)
{
  x = X;
  rect.x = X;
}

void Ball::set_y(int Y)
{
  y = Y;
  rect.y = Y;
}

SDL_Rect Ball::get_rect()
{
  return rect;
}

void Ball::change_xdirection()
{
  xVel *= -1;
}

void Ball::change_ydirection()
{
  yVel *= -1;
}

float Ball::get_xVel()
{
  return xVel;
}

float Ball::get_yVel()
{
  return yVel;
}
