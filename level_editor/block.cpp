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
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,16,127,201));
  }
  else if (status == 2)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,14,78,173));
  }
  else if (status == 3)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,11,16,140));
  }
  else if (status == 4)
  {
    SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,12,15,102));
  }
}

void Block::increase_status()
{
  status++;
  if (status > 4)
  {
    status = 4;
  }
}

void Block::decrease_status()
{
  status--;
  if (status < 0)
  {
    status = 0;
  }
}

void Block::set_status(int S)
{
  status = S;
}

int Block::get_status()
{
  return status;
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
