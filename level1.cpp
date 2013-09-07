#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "constants.h"
#include "image.h"
#include "gamestate.h"
#include "level1.h"

Level1::Level1()
{
  background = load_image("level1bg.png");
}

Level1::~Level1()
{
  SDL_FreeSurface(background);
}

void Level1::handle_events()
{
  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
      set_next_state(STATE_EXIT);
    }
    else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ) )
    {
      set_next_state(STATE_EXIT);
    }
    /*
    else if (event.type == SDL_KEYDOWN)
    {
      switch(event.key.keysym.sym)
      {
        case SDLK_a: blah(); break;
        case SDLK_d: break;
        case SDLK_SPACE: break;
      }
    }*/
  }
}

void Level1::logic(Uint32 deltaTime)
{
  //.move(deltaTime);
}

void Level1::render()
{
  apply_surface(0, 0, background, screen);
  //.render();
}
