#ifndef LEVEL1_H
#define LEVEL1_H

#include "SDL/SDL_mixer.h"
#include "block.h"
#include "paddle.h"
#include "ball.h"
#include "timer.h"

class Level1 : public GameState
{
  private:
    SDL_Surface *background;
    SDL_Surface *readyMessage;

    Block blocks[160];
    Paddle paddle;
    Ball ball;

    Timer timer;
    int blockLastHitTime;
    int blockHits;
    int wallLastHitTime;

    Mix_Chunk *Amin[6];
    Mix_Chunk *AminChord;
    Mix_Chunk *Elow;

  public:
    Level1();
    ~Level1();

    void load_level();
    void ready_screen();
    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
