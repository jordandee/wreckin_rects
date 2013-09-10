#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
  private:
    SDL_Surface *paddlesurf;

    SDL_Rect rect;
    float x,y;
    float xVel;

  public:
    Paddle();
    ~Paddle();

    void update_vel(float newVel);
    void move(Uint32 deltaTime);
    void render();
    SDL_Rect get_rect();
};

#endif
