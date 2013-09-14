#ifndef GIB_H
#define GIB_H

#include "SDL/SDL.h"

class Gib
{
  private:
    SDL_Rect rect;
    float x, y;
    float xVel, yVel;
    int color;

  public:
    Gib();
    ~Gib();

    void move(Uint32 deltaTime);
    void render();
    void set_xy(int X, int Y);
    void set_xyVel(float XV, float YV);
    void set_color(int C);
    SDL_Rect get_rect();
};

#endif
