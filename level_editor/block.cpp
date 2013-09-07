#include "globals.h"
#include "block.h"

Block::Block()
{
  rect.x = 0;
  rect.y = 0;
  rect.w = 80;
  rect.h = 30;

  status = 0;
}

Block::~Block()
{
}

void Block::render()
{
  if (status == 1)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,255,255,255));
  }
}

void Block::set_status(int S)
{
  status = S;
}

void Block::set_xy(int X, int Y)
{
  rect.x = X;
  rect.y = Y;
}

SDL_Rect Block::get_rect()
{
  return rect;
}
