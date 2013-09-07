#ifndef LEVEL1_H
#define LEVEL1_H

class Level1 : public GameState
{
  private:
    SDL_Surface *background;

  public:
    Level1();
    ~Level1();

    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
