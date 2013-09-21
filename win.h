#ifndef WIN_H
#define WIN_H

class Win : public GameState
{
  private:
    SDL_Surface *background;
    SDL_Surface *message;
    SDL_Surface *message2;

  public:
    Win();
    ~Win();

    void handle_events();
    void logic(Uint32 deltaTime);
    void render();
};

#endif
