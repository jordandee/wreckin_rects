#ifndef LEVEL1_H
#define LEVEL1_H

#include "block.h"
#include "paddle.h"
#include "ball.h"

class Level1 : public GameState
{
  private:
    SDL_Surface *background;

    Block blocks[160];
    Paddle paddle;
    Ball ball;

  public:
    Level1();
    ~Level1();

    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
