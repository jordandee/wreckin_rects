#ifndef LEVEL1_H
#define LEVEL1_H

#include "block.h"

class Level1 : public GameState
{
  private:
    SDL_Surface *background;
    Block blocks[10];

  public:
    Level1();
    ~Level1();

    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
