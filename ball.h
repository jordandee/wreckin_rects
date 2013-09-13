#ifndef BALL_H
#define BALL_H

class Ball
{
  private:
    SDL_Surface *ballsurf;
    SDL_Surface *ballsurf2;

    SDL_Rect rect;
    float x,y;
    float xVel,yVel;

  public:
    Ball();
    ~Ball();

    void moveX(Uint32 deltaTime);
    void moveY(Uint32 deltaTime);
    void render(int surface);
    void reset();
    void serve();
    void set_x(int X);
    void set_y(int Y);
    SDL_Rect get_rect();
    void change_xdirection();
    void change_ydirection();
    float get_xVel();
    float get_yVel();
};

#endif
