#ifndef GLOBALS_H
#define GLOBALS_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "constants.h"
#include "gamestate.h"

extern SDL_Surface *screen;

extern SDL_Event event;

extern TTF_Font *font;
extern SDL_Color black;
extern SDL_Color white;
extern SDL_Color blue;

extern bool gotoNextLevel;
extern int stateID;
extern int nextState;
extern GameState *currentState;

#endif
