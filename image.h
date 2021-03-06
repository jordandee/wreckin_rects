#ifndef IMAGE_H
#define IMAGE_H

#include "SDL/SDL.h"
#include <string>

SDL_Surface *load_image(std::string filename);

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif
