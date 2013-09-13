#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
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

  timer.start();
  blockLastHitTime = timer.get_ticks();
  blockHits = 0;

  Amin[0] = Mix_LoadWAV("1A.wav");
  Amin[1] = Mix_LoadWAV("2C.wav");
  Amin[2] = Mix_LoadWAV("3D.wav");
  Amin[3] = Mix_LoadWAV("4E.wav");
  Amin[4] = Mix_LoadWAV("5G.wav");
  Amin[5] = Mix_LoadWAV("6A.wav");

  AminChord = Mix_LoadWAV("Amin_chord.wav");
  Elow = Mix_LoadWAV("E_low.wav");

  load_level();
}

Level1::~Level1()
{
  SDL_FreeSurface(background);
  Mix_FreeChunk(AminChord);
  Mix_FreeChunk(Elow);
  Mix_FreeChunk(Amin[0]);
  Mix_FreeChunk(Amin[1]);
  Mix_FreeChunk(Amin[2]);
  Mix_FreeChunk(Amin[3]);
  Mix_FreeChunk(Amin[4]);
  Mix_FreeChunk(Amin[5]);
}

void Level1::load_level()
{
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
      Mix_PlayChannel(2,Elow,0);
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
  bool paddleHit = false; // used to play sound
  bool blockHit = false; // used to play sound

  paddle.move(deltaTime);
  //check for collision with sides of paddle
  SDL_Rect pad = paddle.get_rect();
  SDL_Rect padL, padR, padT;

  padL.x = pad.x;
  padL.y = pad.y+5;
  padL.w = 1;
  padL.h = pad.h-5;

  padR.x = pad.x + pad.w;
  padR.y = pad.y+5;
  padR.w = 1;
  padR.h = pad.h-5;

  padT.x = pad.x+5;
  padT.y = pad.y;
  padT.w = pad.w-10;
  padT.h = 1;

  if (check_collision(padL, ball.get_rect()) && ball.get_xVel() > 0)
  {
    paddleHit = true;
    ball.change_xdirection();
    ball.moveX(deltaTime);
  }
  else if (check_collision(padR, ball.get_rect()) && ball.get_xVel() < 0)
  {
    paddleHit = true;
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
        blockHit = true;
        blocks[i].set_status(0);
        ball.change_xdirection();
      }
    }
  }
  // check for paddle collisions
  if (check_collision(padL, ball.get_rect()) && ball.get_xVel() > 0)
  {
    paddleHit = true;
    ball.change_xdirection();
    ball.moveX(deltaTime);
  }
  else if (check_collision(padR, ball.get_rect()) && ball.get_xVel() < 0)
  {
    paddleHit = true;
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
        blockHit = true;
        blocks[i].set_status(0);
        ball.change_ydirection();
      }
    }
  }
  //check for paddle collision
  if (check_collision(padT, ball.get_rect()) && ball.get_yVel() > 0)
  {
    paddleHit = true;
    ball.change_ydirection();
  }
  //check if went down off screen
  if (ball.get_rect().y + ball.get_rect().h >= SCREEN_HEIGHT)
  {
    ball.reset();
    load_level();
  }

  if (paddleHit)
  {
    Mix_PlayChannel(2,Amin[0],0);
    blockLastHitTime = timer.get_ticks(); // for ball flashing only
  }
  if (blockHit)
  {
    if (timer.get_ticks() - blockLastHitTime > 100)
    {
      switch(blockHits)
      {
        case 0: Mix_PlayChannel(1,Amin[0],0); break;
        case 1: Mix_PlayChannel(1,Amin[1],0); break;
        case 2: Mix_PlayChannel(1,Amin[2],0); break;
        case 3: Mix_PlayChannel(1,Amin[3],0); break;
        case 4: Mix_PlayChannel(1,Amin[4],0); break;
        case 5: Mix_PlayChannel(1,Amin[5],0); break;
        case 6: Mix_PlayChannel(1,Amin[5],0); break;
        case 7: Mix_PlayChannel(1,Amin[4],0); break;
        case 8: Mix_PlayChannel(1,Amin[3],0); break;
        case 9: Mix_PlayChannel(1,Amin[2],0); break;
        case 10: Mix_PlayChannel(1,Amin[1],0); break;
        case 11: Mix_PlayChannel(1,Amin[0],0); break;
      }
      blockHits++;
      if (blockHits == 12)
      {
        blockHits = 0;
      }
      /*
         if (blockLastHitTime > 1000)
         {
         Mix_PlayChannel(-1,Amin[0],0);
         blockLastHitTime = timer.get_ticks();
         }
         else if (blockLastHitTime < 100)
         {
         Mix_PlayChannel(-1,Amin[1],0);
         }
         */
      blockLastHitTime = timer.get_ticks();
    }
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

  // flash ball if it just hit block or paddle
  if (timer.get_ticks() - blockLastHitTime < 200)
  {
    ball.render(2);
  }
  else
  {
    ball.render(1);
  }
}
