#ifndef BALL_H
#define BALL_H

class Ball
{
  private:
    SDL_Surface *ballsurf;

    SDL_Rect rect;
    float x,y;
    float xVel,yVel;

  public:
    Ball();
    ~Ball();

    void moveX(Uint32 deltaTime);
    void moveY(Uint32 deltaTime);
    void reset();
    void serve();
    void render();
    SDL_Rect get_rect();
    void change_xdirection();
    void change_ydirection();
    float get_xVel();
    float get_yVel();
};

#endif
