#include "characters.h"

Player::Player(SDL_Surface *screen,int x, int y)
{
	this->screen_surface = screen;
	SDL_GetClipRect(screen, &screen_rect);
	number_of_weapons = 2;
	weapons.push_back(new Pistol(screen));
	weapons.push_back(new Beam(screen));
	weapon = weapons[0]; // assign weapons[0] as main weapon
	weapon->equiped = true; // equip first weapon
	color = SDL_MapRGB(screen->format, 0x33, 0x66, 0x33);
	player_surface = IMG_Load("player.png");
	player_rect.x = x;
	player_rect.y = y;
	player_rect.w = 50;
	player_rect.h = 50;
}
Player::~Player()
{
	for(int i=0;i<number_of_weapons;i++)
	{
		delete weapons[i];
	}
	SDL_FreeSurface(player_surface);
}
void Player::move_up()
{
	player_rect.y -= 10;
}
void Player::move_down()
{
	player_rect.y += 10;
}
void Player::move_right()
{
	player_rect.x += 10;
}
void Player::move_left()
{
	player_rect.x -= 10;
}
void Player::move_to(int x, int y)
{
	player_rect.x = x;
	player_rect.y = y;
}
void Player::shoot()
{
	weapon->shoot(player_rect.x,player_rect.y);
	//weapons[0]->shoot(player_rect.x,player_rect.y);
}
void Player::equip_next()
{
	for(int i=0;i<number_of_weapons;i++)
	{
		if(weapons[i]->equiped) // switch out weapons
		{
			weapon->equiped = false;
			weapon = weapons[(i+1)%number_of_weapons];
			weapon->equiped = true;
			break;
		}
	}
}
int Player::ammo_count()
{
	return weapon->how_many_bullets();
}
void Player::check_bounds()
{
	// check if player if above or below screen
	if(player_rect.y < 0)
	{
		player_rect.y = 0;
	}
	else if(player_rect.y+player_rect.h > screen_rect.h)
	{
		player_rect.y = screen_rect.h - player_rect.h;
	}
	//check if player is left of right of screen
	if(player_rect.x + player_rect.w > screen_rect.w)
	{
		player_rect.x = screen_rect.w - player_rect.w;
	}
	else if(player_rect.x < 0)
	{
		player_rect.x = 0;
	}
}
void Player::draw()
{
	check_bounds();
	for(int i=0;i<number_of_weapons;i++)
	{
		weapons[i]->draw();
	}
	//SDL_FillRect(screen_surface, &player_rect, color);
	SDL_BlitSurface(player_surface,NULL,screen_surface,&player_rect);
}
Enemy::Enemy(SDL_Surface *screen, int x, int y) : Player(screen,x,y){}
	
