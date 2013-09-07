// Initialization, file loading, and cleanup functions

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "init.h"
#include "globals.h"
#include "constants.h"
#include "image.h"

// Initializes SDL, its components, and the window
bool init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }

  if(TTF_Init() == -1)
  {
    return false;
  }

  screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
  if(screen == NULL)
  {
    return false;
  }

  SDL_WM_SetCaption("Wreckin Rects", NULL);

  srand(SDL_GetTicks());

  return true;
}

// Load Images, Fonts, and Sounds
bool load_files()
{
  font = TTF_OpenFont("AeroviasBrasilNF.ttf",64);
  if (font == NULL)
  {
    return false;
  }

  return true;
}

// Clean up images, fonts, sounds and quit SDL
void clean_up()
{
  delete currentState;

  TTF_CloseFont(font);
  TTF_Quit();

  SDL_Quit();
}
