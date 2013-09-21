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
  std::cout << "made it to win, sheeit";
}

Win::~Win()
{
  SDL_FreeSurface(background);
  SDL_FreeSurface(message);
  SDL_FreeSurface(message2);
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

}

void Win::render()
{
  //Show the background
  apply_surface( 0, 0, background, screen );

  apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
  apply_surface( ( SCREEN_WIDTH - message2->w ) / 2, ( SCREEN_HEIGHT - message2->h ) - 200, message2, screen );
}
