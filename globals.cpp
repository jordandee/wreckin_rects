#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "constants.h"
#include "gamestate.h"

SDL_Surface *screen = NULL;

SDL_Event event;

TTF_Font *font = NULL;
SDL_Color black = {0,0,0};
SDL_Color red = {0xFF,0,0};
SDL_Color blue = {0,0,0xFF};

bool gotoNextLevel = false;
int stateID = STATE_NULL;
int nextState = STATE_NULL;
GameState *currentState = NULL;
