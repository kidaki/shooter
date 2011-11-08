#include "game.h"

Game::Game()
{
    //init game
    running = true;
	game_over = false;
	time_running = 0;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
    FPS = 60;
    SDL_ShowCursor(0); // don't show cursor since the game will be controlled by it
	movement[0] = 0;
	movement[1] = 0;
	movement[2] = 0;
	movement[3] = 0;
	shooting = 0;

    TTF_Init(); // initialize ttf
    font = TTF_OpenFont("font.ttf",28); // open the font
    // I need font color for font rendering onto the string
    font_color.r = 0xff;
    font_color.g = 0xff;
    font_color.b = 0xff;

    player = new Player(screen,"player.png");
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
            shooting = 1;
            break;
		case SDL_MOUSEBUTTONUP:
			shooting = 0;
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
				case SDLK_TAB:
					player->equip_next();
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
bool Game::check_collisions(SDL_Rect rect1, SDL_Rect rect2)
{
	if(rect1.x+rect1.w < rect2.x or rect2.x+rect2.w < rect1.x)
	{
		return false;
	}
	if(rect1.y+rect1.h < rect2.y or rect2.y + rect2.h < rect1.y)
	{
		return false;
	}
	return true;
}
void Game::loop()
{
	// I need to put this in a better place ***********
	Level *lvl = new Level1(screen); // **************
	//////////////////////////////////////// **********
    while(running)
    {
		start = SDL_GetTicks();
		if(game_over)
		{
			log = "Game Over";
		}
        while(SDL_PollEvent(&event))
        {
            handle_event();
        }
        SDL_FillRect(screen,&screen->clip_rect,0x000000); // clear out screen
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
		if(shooting)
		{
			player->shoot();
		}
		
		// collision detection -- for now, just bullets and enemies
		
		for(int i=0;i<player->weapon->bullets.size();i++) // player bullet to enemy
		{
			for(int j=0;j<lvl->level_enemies.size();j++)
			{
				if(check_collisions(player->weapon->bullets[i].bullet, lvl->level_enemies[j].enemy->character_rect))
				{
					delete lvl->level_enemies[j].enemy;
					lvl->level_enemies.erase(lvl->level_enemies.begin() + j);
					player->weapon->bullets.erase(player->weapon->bullets.begin()+i);
					i--;
					break;
				}
			}
		}
		for(int j = 0;j<lvl->level_enemies.size();j++)
		{
			for(int k=0;k<lvl->level_enemies[j].enemy->weapon->bullets.size();k++)
			{
				if(check_collisions(lvl->level_enemies[j].enemy->weapon->bullets[k].bullet, player->character_rect))
				{
					// game_over=true; // don't game over yet
				}
			}
		}
		
		// drawing code
		player->draw(game_over);
		for(int i=0;i<lvl->level_enemies.size();i++)
		{
			// simple enemy movement and screen detection for now
			if(lvl->level_enemies[i].enemy->character_rect.x <= 0)
			{
				delete lvl->level_enemies[i].enemy;
				lvl->level_enemies.erase(lvl->level_enemies.begin() + i);
				i--;
				continue;
			}
			if(lvl->time_passed >= lvl->level_enemies[i].time)
			{
				lvl->level_enemies[i].enemy->shoot();
				lvl->level_enemies[i].enemy->move_to(lvl->level_enemies[i].enemy->character_rect.x-2,lvl->level_enemies[i].enemy->character_rect.y);
				lvl->level_enemies[i].enemy->draw(game_over);
				lvl->enemy_number++;
			}
		}
		//if(lvl->enemy_number >= lvl->enemy_count and lvl->level_enemies.size() == 0)
		if(lvl->level_enemies.size() == 0)
		{
			lvl->init(); // restart cycle
			lvl->enemy_number = 0;
			lvl->time_passed = 0;
		}
		
        text = TTF_RenderText_Solid(font,log.c_str(),font_color); // this returns a surface
        SDL_BlitSurface(text,NULL,screen,NULL); // blit the text onto the screen
        SDL_FreeSurface(text);
        SDL_Flip(screen);
		
		
		
        //////////// this is just debugging stuff, since I didn't have a console on the sdl xcode project
        //first empty out the stringstream
        tmp.str(std::string());
        //grab the number of bullets on the screen and place them in the stringstream
        tmp<<lvl->level_enemies.size();
        // now place the stringstream in the log variable
        log = tmp.str();
        ////////////////////////////////////////////
		
		
		/*
		float end = (float)SDL_GetTicks();
        if(1000/FPS>(end - start)) // if frame to less than 1/60th of a second when fps = 60
        {
            SDL_Delay((Uint32)(1000/FPS-(end-start))); // delay it by the difference between 1/60th and how long it took
        }*/
		SDL_Delay(1);
		lvl->time_passed += (SDL_GetTicks() - start) / 1000;
    }
}
Level::Level(int num, SDL_Surface *screen)
{
	number = num;
	enemy_number = 0; // where I am in the sequence of enemies
	this->screen = screen;
	time_passed = 0;
	
}
Level::~Level()
{
	for(int i = 0;i<level_enemies.size();i++)
	{
		delete level_enemies[i].enemy;
	}
	level_enemies.clear();
}
Level1::Level1(SDL_Surface *screen):Level(1, screen)
{
	enemy_count = 7;
	init();
}
void Level1::init()
{
	float enemies[7][2] = {
		{20,1.5},
		{580,1.7},
		{300,2.3},
		{250,4.5},
		{450,5.7},
		{200,7.9},
		{300,8.5},
	};
	for(int i = 0; i < enemy_count; i++)
	{
		level_enemy tmp_e = {new Enemy(screen->clip_rect.w-20,enemies[i][0],screen,"enemy.png"),enemies[i][1]};
		level_enemies.push_back(tmp_e);
	}
}
