#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "constants.h"
#include "image.h"
#include "gamestate.h"
#include "level1.h"
#include "block.h"
#include <fstream>
#include "draw_lines.h"

Level1::Level1()
{
  background = load_image("level1bg.png");

  std::ifstream level("level.txt");
  int stat = 0;
  
  for (int i = 0; i < 10; i++)
  {
    blocks[i].set_xy(i*80,0);
    level >> stat;
    blocks[i].set_status(stat);
  }
  
  level.close();
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
  
  for (int i = 0; i < 10; i++)
  {
    blocks[i].render();
  }
  
  // draw grid
  for (int x = 0; x < SCREEN_WIDTH; x += 80)
  {
    Line(x,0,x,SCREEN_HEIGHT,RGBA_to_Uint32(255,0,0,0));
  }
  for (int y = 0; y < SCREEN_HEIGHT; y += 30)
  {
    Line(0,y,SCREEN_WIDTH,y,RGBA_to_Uint32(0,0,255,0));
  }
  
}
