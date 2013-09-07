// Wreckin Rects: An SDL Breakout clone

#include "SDL/SDL.h"
#include "init.h"
#include "globals.h"
#include "constants.h"
#include "timer.h"
#include "gamestate.h"
#include "intro.h"

int main(int argc, char* args[])
{
  Timer fps,delta;

  // Initialize SDL and load images, fonts, sounds
  if(!init())       { return 1; }
  if(!load_files()) { return 1; }

  // Initialize gamestate
  stateID = STATE_INTRO;
  currentState = new Intro();

  delta.start();

  while( stateID != STATE_EXIT )
  {
    fps.start();

    // Handle input, calculate game logic, draw to the screen
    currentState->handle_events();
    currentState->logic(delta.get_ticks());
    delta.start();
    change_state();
    currentState->render();

    // Update the screen
    if(SDL_Flip(screen) == -1 ) { return 1; }

    // Cap the frame rate
    if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
    {
      SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
    }
  }

  clean_up();
  return 0;
}
