#ifndef COLLISION_H
#define COLLISION_H

#include "SDL/SDL.h"

// Returns true if there is a collision
bool check_collision(SDL_Rect A, SDL_Rect B);

// Returns true if there is a collision
bool check_collision(SDL_Rect A, int X, int Y);

#endif
