#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "constants.h"
#include "image.h"
#include "gamestate.h"
#include "title.h"

Title::Title()
{
    //Load the background
    background = load_image("titlebg.png");

    //Render the title message
    message = TTF_RenderText_Solid(font, "Wreckin Rects", black);
}

Title::~Title()
{
    //Free surfaces
    SDL_FreeSurface(background);
    SDL_FreeSurface(message);
}

void Title::handle_events()
{
    //While there's events to handle
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        else if(event.type == SDL_KEYDOWN)
        {
            set_next_state(STATE_LEVEL1);
        }
    }
}

void Title::logic(Uint32 deltaTime)
{

}

void Title::render()
{
    //Show the background
    apply_surface( 0, 0, background, screen );

    //Show the message
    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
}
