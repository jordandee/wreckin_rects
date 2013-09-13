#include "SDL/SDL.h"
#include "image.h"
#include "constants.h"
#include "globals.h"
#include "paddle.h"

Paddle::Paddle()
{
  paddlesurf = load_image("paddle.png");

  x = SCREEN_WIDTH/2 - paddlesurf->w/2;
  y = SCREEN_HEIGHT - 60;
  rect.x = x;
  rect.y = y;
  rect.w = paddlesurf->w;
  rect.h = paddlesurf->h;

  xVel = 0;
}

Paddle::~Paddle()
{
  SDL_FreeSurface(paddlesurf);
}

void Paddle::update_vel(float newVel)
{
  xVel = newVel;
}

void Paddle::move(Uint32 deltaTime)
{
  x += deltaTime * xVel;
  rect.x = x;

  // check for screen boundaries
  if (x < 0)
  {
    x = 0;
    rect.x = x;
  }
  if (x + rect.w > SCREEN_WIDTH)
  {
    x = SCREEN_WIDTH - rect.w;
    rect.x = SCREEN_WIDTH - rect.w;
  }
}

void Paddle::render()
{
  apply_surface(rect.x,rect.y,paddlesurf,screen);
}

SDL_Rect Paddle::get_rect()
{
  return rect;
}

float Paddle::get_xVel()
{
  return xVel;
}
