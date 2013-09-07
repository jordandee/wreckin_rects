
// RGB 4 bytes to one int, alpha doesn't seem to work
Uint32 RGBA_to_Uint32(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

// Set Pixel at x,y with ARGB color
void SetPixel(int x, int y, Uint32 color);

// Draw line between x1,y1 and x2,y2 with ARGB color
// Bresenham's line algorithm, requires cmath, algorithm
void Line(float x1, float y1, float x2, float y2, Uint32 color);
