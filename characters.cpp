#include "characters.h"

Character::Character(SDL_Surface *screen, const char* image_file)
{
	screen_surface = screen;
	character_surface = IMG_Load(image_file);
	screen_rect = screen_surface->clip_rect;
	character_rect = character_surface -> clip_rect;
	character_rect.x = 300;
	character_rect.y = 300;
}
Character::~Character()
{
	SDL_FreeSurface(character_surface);
}

void Character::move_up()
{
	character_rect.y -= 10;
}
void Character::move_down()
{
	character_rect.y += 10;
}
void Character::move_right()
{
	character_rect.x += 10;
}
void Character::move_left()
{
	character_rect.x -= 10;
}
void Character::move_to(int x, int y)
{
	character_rect.x = x;
	character_rect.y = y;
}
void Character::draw(){}

Player::Player(SDL_Surface *screen,const char* image_file): 
Character(screen,image_file)
{
	number_of_weapons = 2;
	weapons.push_back(new Pistol(screen));
	weapons.push_back(new Beam(screen));
	weapon = weapons[0]; // assign weapons[0] as main weapon
	weapon->equiped = true; // equip first weapon
}
Player::~Player()
{
	for(int i=0;i<number_of_weapons;i++)
	{
		delete weapons[i];
	}
}
void Player::shoot()
{
	weapon->shoot(character_rect.x,character_rect.y);
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
	if(character_rect.y < 0)
	{
		character_rect.y = 0;
	}
	else if(character_rect.y+character_rect.h > screen_rect.h)
	{
		character_rect.y = screen_rect.h - character_rect.h;
	}
	//check if player is left of right of screen
	if(character_rect.x + character_rect.w > screen_rect.w)
	{
		character_rect.x = screen_rect.w - character_rect.w;
	}
	else if(character_rect.x < 0)
	{
		character_rect.x = 0;
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
	SDL_BlitSurface(character_surface,NULL,screen_surface,&character_rect);
}
Enemy::Enemy(SDL_Surface *screen, const char* image_file) : 
Character(screen,image_file)
{
	
}
Enemy::~Enemy(){}
void Enemy::draw(){}
	
