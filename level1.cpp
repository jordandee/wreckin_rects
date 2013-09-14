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
#include <iostream>

Level1::Level1()
{
  background = load_image("level1bg.png");
  readyMessage = TTF_RenderText_Solid(font, "Get Ready ! ! ! !       Space to Serve", blue);

  timer.start();
  blockLastHitTime = timer.get_ticks() - 250; // -250 so ball doesn't flash at start
  blockHits = 0;
  wallLastHitTime = timer.get_ticks() - 250;

  Amin[0] = Mix_LoadWAV("1A.wav");
  Amin[1] = Mix_LoadWAV("2C.wav");
  Amin[2] = Mix_LoadWAV("3D.wav");
  Amin[3] = Mix_LoadWAV("4E.wav");
  Amin[4] = Mix_LoadWAV("5G.wav");
  Amin[5] = Mix_LoadWAV("6A.wav");

  AminChord = Mix_LoadWAV("Amin_chord.wav");
  Elow = Mix_LoadWAV("E_low.wav");

  gibSelect = 0;
  for (int i = 0; i < 4; i++)
  {
    gibs[i] = new Gib[24];
  }

  load_level();

  ready_screen();
}

Level1::~Level1()
{
  SDL_FreeSurface(background);
  SDL_FreeSurface(readyMessage);

  Mix_FreeChunk(AminChord);
  Mix_FreeChunk(Elow);
  Mix_FreeChunk(Amin[0]);
  Mix_FreeChunk(Amin[1]);
  Mix_FreeChunk(Amin[2]);
  Mix_FreeChunk(Amin[3]);
  Mix_FreeChunk(Amin[4]);
  Mix_FreeChunk(Amin[5]);

  for (int i = 0; i < 4; i++)
  {
    delete []gibs[i];
  }
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

void Level1::ready_screen()
{
  render();
  apply_surface((SCREEN_WIDTH - readyMessage->w)/2, SCREEN_HEIGHT-150, readyMessage, screen );
  SDL_Flip(screen);

  while(1)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        set_next_state(STATE_EXIT);
        return;
      }
      else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
      {
        set_next_state(STATE_EXIT);
        return;
      }
      else if((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE))
      {
        return;
      }
    }
  }

}

// gibs yay
void Level1::shatter_block(int B)
{
  int blockX = blocks[B].get_rect().x;
  int blockY = blocks[B].get_rect().y;
  int blockStatus = blocks[B].get_status();

  float ballxVel = ball.get_xVel();
  float ballyVel = ball.get_yVel();

  int j = 0;
  for (int x = blockX; x < blockX + 80; x += 10)
  {
    for (int y = blockY; y < blockY + 30; y += 10)
    {
      gibs[gibSelect][j].set_xy(x,y);
      gibs[gibSelect][j].set_xyVel(ballxVel,ballyVel);
      gibs[gibSelect][j].set_color(blockStatus);
      j++;
    }
  }
  gibSelect++;
  if (gibSelect >= 4)
  {
    gibSelect = 0;
  }
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

  // create left, right, and top hit boxes for paddle collision detection
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

  // check for sides of paddle collisions with ball
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
        shatter_block(i);
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
  // check for wall collisions
  if (ball.get_rect().x < 0)
  {
    ball.change_xdirection();
    ball.set_x(0);
    wallLastHitTime = timer.get_ticks();
  }
  else if (ball.get_rect().x + ball.get_rect().w > SCREEN_WIDTH)
  {
    ball.change_xdirection();
    ball.set_x(SCREEN_WIDTH - ball.get_rect().w);
    wallLastHitTime = timer.get_ticks();
  }


  ball.moveY(deltaTime);
  // check for block collisions
  for (int i = 0; i < 160; i++)
  {
    if (blocks[i].get_status())
    {
      if (check_collision(blocks[i].get_rect(), ball.get_rect()))
      {
        blockHit = true;
        shatter_block(i);
        blocks[i].set_status(0);
        ball.change_ydirection();
      }
    }
  }
  //std::cout << "x: " << gibs[1][0].get_rect().x << " ";
  //std::cout << "y: " << gibs[1][0].get_rect().y << " ";
  // check for paddle collision
  if (check_collision(padT, ball.get_rect()) && ball.get_yVel() > 0)
  {
    paddleHit = true;
    ball.change_ydirection();
    // change ball's x velocity if it hits the paddle when it's moving
    if (paddle.get_xVel() > .1)
    {
      ball.increase_xVel();
    }
    else if (paddle.get_xVel() < -.1)
    {
      ball.decrease_xVel();
    }
  }
  // check for top wall collision
  if (ball.get_rect().y < 0)
  {
    ball.change_ydirection();
    ball.set_y(0);
    wallLastHitTime = timer.get_ticks();
  }
  // check if went down off screen
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

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 24; j++)
    {
      gibs[i][j].move(deltaTime);
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

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 24; j++)
    {
      gibs[i][j].render();
    }
  }

  // flash ball if it just hit block or paddle
  if ((timer.get_ticks() - blockLastHitTime < 200) || (timer.get_ticks() - wallLastHitTime < 200))
  {
    ball.render(2);
  }
  else
  {
    ball.render(1);
  }
}
