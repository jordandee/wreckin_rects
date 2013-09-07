#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "constants.h"
#include "image.h"
#include "gamestate.h"
#include "intro.h"

Intro::Intro()
{
    //Load the background
    background = load_image("introbg.png");

    //Render the intro message
    message = TTF_RenderText_Solid(font, "Jordanian Productions Presents...", black);
}

Intro::~Intro()
{
    //Free the surfaces
    SDL_FreeSurface(background);
    SDL_FreeSurface(message);
}

void Intro::handle_events()
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
            //Move to the title screen
            set_next_state( STATE_TITLE );
        }
    }
}

void Intro::logic(Uint32 deltaTime)
{

}

void Intro::render()
{
    //Show the background
    apply_surface( 0, 0, background, screen );

    //Show the message
    apply_surface( ( SCREEN_WIDTH - message->w ) / 2, ( SCREEN_HEIGHT - message->h ) / 2, message, screen );
}
