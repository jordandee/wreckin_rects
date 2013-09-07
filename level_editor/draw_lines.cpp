// Drawing Lines and Setting Pixels

#include "SDL/SDL.h"
#include "globals.h"
#include <cmath>
#include <algorithm>
#include "draw_lines.h"

// RGB 4 bytes to one int, alpha doesn't seem to work
Uint32 RGBA_to_Uint32(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
  return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// Set Pixel at x,y with ARGB color
void SetPixel( int x, int y, Uint32 color ) 
{
  //Convert the pixels to 32 bit
  Uint32 *pixels = (Uint32 *)screen->pixels; //Set the pixel
  pixels[ ( y * screen->w ) + x ] = color;
}

// Draw line between x1,y1 and x2,y2 with ARGB color
// Bresenham's line algorithm, requires cmath, algorithm
void Line( float x1, float y1, float x2, float y2, Uint32 color )
{
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=(int)x1; x<maxX; x++)
    {
        if(steep)
        {
            SetPixel(y,x, color);
        }
        else
        {
            SetPixel(x,y, color);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
