#ifndef BLOCK_H
#define BLOCK_H

class Block
{
  private:
    SDL_Rect rect;
    Uint8 status;

  public:
    Block();
    ~Block();

    void render();
    void set_status(int S);
    void set_xy(int X, int Y);
    SDL_Rect get_rect();
};

#endif
