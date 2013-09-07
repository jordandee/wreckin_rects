#ifndef INTRO_H
#define INTRO_H

class Intro : public GameState
{
  private:
    SDL_Surface *background;
    SDL_Surface *message;

  public:
    Intro();
    ~Intro();

    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
