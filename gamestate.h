#ifndef GAMESTATE_H
#define GAMESTATE_H

void set_next_state(int newState);
void change_state();

class GameState
{
  public:
    virtual void handle_events() = 0;
    virtual void logic(Uint32 deltaTime) = 0;
    virtual void render() = 0;
    virtual ~GameState(){};
};

#endif
