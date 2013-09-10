#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "constants.h"
#include "image.h"
#include "gamestate.h"
#include "collision.h"
#include <fstream>
#include "level1.h"

Level1::Level1()
{
  background = load_image("level1bg.png");

  std::ifstream level("level01.txt");
  int stat = 0, i = 0;

  for (int y = 0; y < SCREEN_HEIGHT-120; y += 30)
  {
    for (int x = 0; x < SCREEN_WIDTH; x += 80)
    {
      blocks[i].set_xy(x,y);

      if (level)
      {
        level >> stat;
      }

      blocks[i].set_status(stat);
      i++;
    }
    if (level)
    {
      // ignore eol
      level.ignore();
    }
  }

  level.close();
}

Level1::~Level1()
{
  SDL_FreeSurface(background);
}

void Level1::handle_events()
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
    }
    else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
    {
      ball.serve();
    }

    Uint8 *keystates = SDL_GetKeyState(NULL);

    if (keystates[SDLK_a])
    {
      paddle.update_vel(-.5);
    }
    if (keystates[SDLK_d])
    {
      paddle.update_vel(.5);
    }
    // stop paddle if both/neither a/d are pressed
    if (keystates[SDLK_a] && keystates[SDLK_d])
    {
      paddle.update_vel(0);
    }
    if (!(keystates[SDLK_a] || keystates[SDLK_d]))
    {
      paddle.update_vel(0);
    }
  }
}

void Level1::logic(Uint32 deltaTime)
{
  paddle.move(deltaTime);
  //check for collision with sides of paddle
  SDL_Rect pad = paddle.get_rect();
  SDL_Rect padL, padR;
  padL.x = pad.x;
  padL.y = pad.y+5;
  padL.w = 1;
  padL.h = pad.h-5;
  if (check_collision(padL, ball.get_rect()) && ball.get_xVel() > 0)
  {
    ball.change_xdirection();
    ball.moveX(deltaTime);
  }

  ball.moveX(deltaTime);
  // check for block collisions
  for (int i = 0; i < 160; i++)
  {
    if (blocks[i].get_status())
    {
      if (check_collision(blocks[i].get_rect(), ball.get_rect()))
      {
        blocks[i].set_status(0);
        ball.change_xdirection();
      }
    }
  }
  //check for collision with sides of paddle
  pad = paddle.get_rect();
  //SDL_Rect padL, padR;
  padL.x = pad.x;
  padL.y = pad.y+5;
  padL.w = 1;
  padL.h = pad.h-5;
  if (check_collision(padL, ball.get_rect()) && ball.get_xVel() > 0)
  {
    ball.change_xdirection();
    ball.moveX(deltaTime);
  }


  ball.moveY(deltaTime);
  for (int i = 0; i < 160; i++)
  {
    if (blocks[i].get_status())
    {
      if (check_collision(blocks[i].get_rect(), ball.get_rect()))
      {
        blocks[i].set_status(0);
        ball.change_ydirection();
      }
    }
  }
  //check for paddle collision
  if (check_collision(paddle.get_rect(), ball.get_rect()))
  {
    ball.change_ydirection();
  }
}

void Level1::render()
{
  apply_surface(0, 0, background, screen);

  for (int i = 0; i < 160; i++)
  {
    blocks[i].render();
  }
  paddle.render();
  ball.render();
}
