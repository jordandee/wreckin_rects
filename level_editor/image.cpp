#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "image.h"

// Loads an image then converts it to same format as the screen
// Example 24 bpp -> 32 bpp
SDL_Surface *load_image(std::string filename)
{
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  // Can load BMP,PNG,JPEG,TGA,GIF,PNM,XPM,LBM,PCX
  loadedImage = IMG_Load(filename.c_str());

  if (loadedImage !=NULL)
  {
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);

    // color key for transparency
    if(optimizedImage != NULL)
    {
      // Set teal to color key in this case
      Uint32 colorkey = SDL_MapRGB(optimizedImage->format,0,0xFF,0xFF);
      SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,colorkey);
    }
  }

  return optimizedImage;
}


// Apply source surface to destination at x,y coordinates
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
  // Rect has x,y,w,h components
  SDL_Rect offset; //BlitSurface takes a Rect

  offset.x = x;
  offset.y = y;

  // Put source surface on destination surface at the offset position
  SDL_BlitSurface(source,clip,destination,&offset);
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
  apply_surface(x,y,source,destination,NULL);
}
