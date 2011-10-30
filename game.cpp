#include "game.h"

Game::Game()
{
    //init game
    running = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(800,600,32,SDL_DOUBLEBUF);
    SDL_ShowCursor(0); // don't show cursor since the game will be controlled by it

    TTF_Init(); // initialize ttf
    font = TTF_OpenFont("font.ttf",28); // open the font
    // I need font color for font rendering onto the string
    font_color.r = 0xff;
    font_color.g = 0xff;
    font_color.b = 0xff;

    player = new Player(screen,0,0);
}
Game::~Game()
{
    // close ttf, free screen, quit sdl
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeSurface(screen);
    SDL_Quit();
}
void Game::handle_event()
{
    switch(event.type)
    {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEMOTION:
            player->move_to(event.motion.x,event.motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            player->shoot();
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    movement[0] = 1;
                    break;
                case SDLK_DOWN:
                    movement[1] = 1;
                    break;
                case SDLK_LEFT:
                    movement[2] = 1;
                    break;
                case SDLK_RIGHT:
                    movement[3] = 1;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    movement[0] = 0;
                    break;
                case SDLK_DOWN:
                    movement[1] = 0;
                    break;
                case SDLK_LEFT:
                    movement[2] = 0;
                    break;
                case SDLK_RIGHT:
                    movement[3] = 0;
                    break;
            }
            break;
    }
}
void Game::loop()
{
    while(running)
    {
        start = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            handle_event();
        }
        SDL_FillRect(screen,&screen->clip_rect,0x000000);
        if(movement[0])
        {
            player->move_up();
        }
        if(movement[1])
        {
            player->move_down();
        }
        if(movement[2])
        {
            player->move_left();
        }
        if(movement[3])
        {
            player->move_right();
        }
        //////////// this is just debugging stuff, since I didn't have a console on the sdl xcode project
        //first empty out the stringstream
        tmp.str(std::string());
        //grab the number of bullets on the screen and place them in the stringstream
        tmp<<player->ammo_count();
        // now place the stringstream in the log variable
        log = tmp.str();
        ////////////////////////////////////////////

        player->draw();

        text = TTF_RenderText_Solid(font,log.c_str(),font_color); // this returns a surface
        SDL_BlitSurface(text,NULL,screen,NULL); // blit the text onto the screen
        SDL_FreeSurface(text);
        SDL_Flip(screen);        // regulate the fps
        //if(1000/FPS > SDL_GetTicks() - start) // if frame to less than 1/60th of a second when fps = 60
        //{
        //    SDL_Delay(1000/FPS-(SDL_GetTicks()-start)); // delay it by the difference between 1/60th and how long it took
        //}
    }
}
