#ifndef TITLE_H
#define TITLE_H

class Title : public GameState
{
  private:
    SDL_Surface *background;
    SDL_Surface *message;

  public:
    Title();
    ~Title();

    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
