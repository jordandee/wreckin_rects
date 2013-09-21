#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "constants.h"
#include "image.h"
#include "gamestate.h"
#include "win.h"
#include <iostream>

Win::Win()
{
  background = load_image("level4bg.png");

  message = TTF_RenderText_Solid(font, "You Beat Wreckin Rects", white);
  message2 = TTF_RenderText_Solid(font, "[R]estart or [ESC]ape", white);

  CmajChord = Mix_LoadWAV("Cmaj_chord.wav");

  timer.start();
  gibSelect = 0;
  init_explosion();

  Mix_PlayChannel(-1,CmajChord,0);
}

void Win::init_explosion()
{
  timer.start();

  int x = rand() % (SCREEN_WIDTH - 10);
  int y = rand() % (SCREEN_HEIGHT - 10);

  for (int i = 0; i < 200; i++)
  {
    gibs[gibSelect][i].set_color((rand() % 4) + 1);
    gibs[gibSelect][i].set_xy(x,y);
    gibs[gibSelect][i].set_randVel();
  }
  gibSelect++;
  if (gibSelect >= 4)
  {
    gibSelect = 0;
  }
}

Win::~Win()
{
  SDL_FreeSurface(background);
  SDL_FreeSurface(message);
  SDL_FreeSurface(message2);

  Mix_FreeChunk(CmajChord);
}

void Win::handle_events()
{
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      set_next_state(STATE_EXIT);
    }
    else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
    {
      set_next_state(STATE_EXIT);
      return;
    }
    else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_r))
    {
      set_next_state(STATE_LEVEL1);
      return;
    }
  }
}

void Win::logic(Uint32 deltaTime)
{
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 200; i++)
    {
      gibs[j][i].move(deltaTime);
    }
  }

  if (timer.get_ticks() > 500)
  {
    init_explosion();
  }
}

void Win::render()
{
  //Show the background
  apply_surface( 0, 0, background, screen );

  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 200; i++)
    {
      gibs[j][i].render();
    }
  }

  apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
  apply_surface( ( SCREEN_WIDTH - message2->w ) / 2, ( SCREEN_HEIGHT - message2->h ) - 200, message2, screen );
}
