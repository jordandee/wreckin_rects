#include "SDL/SDL.h"
#include "gib.h"
#include "globals.h"

Gib::Gib()
{
  x = 0;
  y = 0;
  rect.x = x;
  rect.y = y;
  rect.w = 10;
  rect.h = 10;

  xVel = 0;
  yVel = 0;

  color = 0;
}

Gib::~Gib()
{
}

void Gib::move(Uint32 deltaTime)
{
  x += xVel * deltaTime;
  y += yVel * deltaTime;

  if (x < 0)
  {
    color = 0;
    x = 0;
    xVel = 0;
  }
  if (x + rect.w > SCREEN_WIDTH)
  {
    color = 0;
    x = 0;
    xVel = 0;
  }

  if (y < 0)
  {
    color = 0;
    y = 0;
    yVel = 0;
  }
  if (y + rect.h > SCREEN_HEIGHT)
  {
    color = 0;
    y = 0;
    yVel = 0;
  }
  
  rect.x = x;
  rect.y = y;
}

void Gib::render()
{
  //SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,rand()%256,rand()%256,rand()/256));
  if (color == 1)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,16,127,201));
  }
  else if (color == 2)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,14,78,173));
  }
  else if (color == 3)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,11,16,140));
  }
  else if (color == 4)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,12,15,102));
  }
}

void Gib::set_xy(int X, int Y)
{
  x = X;
  y = Y;
  rect.x = x;
  rect.y = y;
}

void Gib::set_xyVel(float XV, float YV)
{
  xVel = XV;
  yVel = YV;
  xVel += (float) rand()/RAND_MAX * .5 * XV;
  yVel += (float) rand()/RAND_MAX * .5 * YV;

  if (rand() % 5 == 0)
  {
    xVel *= -1;
  }
  if (rand() % 5 == 0)
  {
    yVel *= -1;
  }
/*  
  if (xVel > 0)
  {
    xVel += (float) rand()/RAND_MAX * .2;
  }
  else
  {
    xVel -= (float) rand()/RAND_MAX * .2;
  }
  
  if (yVel > 0)
  {
    yVel += (float) rand()/RAND_MAX * .2;
  }
  else
  {
    yVel -= (float) rand()/RAND_MAX * .2;
  }
  */
}

SDL_Rect Gib::get_rect()
{
  return rect;
}

void Gib::set_color(int C)
{
  color = C;
}
