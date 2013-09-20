#ifndef LEVEL4_H
#define LEVEL4_H

#include "SDL/SDL_mixer.h"
#include "block.h"
#include "paddle.h"
#include "ball.h"
#include "timer.h"
#include "gib.h"

class Level4 : public GameState
{
  private:
    SDL_Surface *background;
    SDL_Surface *readyMessage;
    SDL_Surface *winMessage;

    Block blocks[160];
    int blockCount;
    Paddle paddle;
    Ball ball;

    bool readyToServe;

    Timer timer;
    int blockLastHitTime;
    int blockHits;
    int wallLastHitTime;

    Gib *gibs[4];
    int gibSelect;

    Mix_Chunk *Amin[6];
    Mix_Chunk *AminChord;
    Mix_Chunk *CmajChord;
    Mix_Chunk *Elow;

  public:
    Level4();
    ~Level4();

    void load_level();
    void ready_screen();
    void win_screen();
    void shatter_block(int B);
    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
