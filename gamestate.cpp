#include "globals.h"
#include "constants.h"
#include "gamestate.h"
#include "title.h"
#include "level1.h"

void set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

void change_state()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        //Change the state
        switch( nextState )
        {
            case STATE_TITLE:
                currentState = new Title();
                break;

            case STATE_LEVEL1:
                currentState = new Level1();
                break;
        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
    }
}
