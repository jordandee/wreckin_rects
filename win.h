#ifndef WIN_H
#define WIN_H

#include "SDL/SDL_mixer.h"
#include "timer.h"
#include "gib.h"

class Win : public GameState
{
  private:
    SDL_Surface *background;
    SDL_Surface *message;
    SDL_Surface *message2;

    Timer timer;
    int gibSelect;
    Gib gibs[4][200];

    Mix_Chunk *CmajChord;

  public:
    Win();
    ~Win();

    void init_explosion();
    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
