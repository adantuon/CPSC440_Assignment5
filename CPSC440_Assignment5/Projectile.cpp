//Aiden D'Antuono

#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Projectile.h"
#include <stdio.h>

Projectile::Projectile() {
	speed = 4;
	live = false;
	frameWidth = 8;
	frameHeight = 8;
	angle = 0;

	image = al_create_bitmap(frameWidth, frameHeight);
	if (!image) {
		exit(1);
	}

	fire = al_load_sample("spell.wav");
}

Projectile::~Projectile() {
	al_destroy_bitmap(image);
	al_destroy_sample(fire);
}

//initialize projectile based on whether it is an enemy's or not
void Projectile::initProjectile(bool enemy) {
	Projectile::enemy = enemy;

	ALLEGRO_COLOR color, colorAlt;

	if (!enemy) {
		color = al_map_rgb(124, 142, 255);
		colorAlt = al_map_rgb(255, 255, 255);
	}
	else {
		color = al_map_rgb(164, 34, 187);
		colorAlt = al_map_rgb(0, 0, 0);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgba(0, 0, 0, 0));

	al_draw_filled_rectangle(0, 0, 8, 8, color);
	al_draw_filled_rectangle(2, 2, 6, 6, colorAlt);
}

//draw the projectile
void Projectile::DrawProjectile(int xoffset, int yoffset) {
	if (live) {
		al_draw_rotated_bitmap(image, 4, 4, x - xoffset, y - yoffset, (angle * 2 * ALLEGRO_PI) / 128, 0);
	}
}

//Fire projectile from sprite x, y, and direction
void Projectile::FireProjectile(int x, int y, int direction) {
	live = true;

	//Play sound at different volumes for player and enemy
	if (enemy) {
		al_play_sample(fire, .05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	else {
		al_play_sample(fire, 0.25, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	

	Projectile::direction = direction;
	if (direction == 0) {
		
		Projectile::x = x;
		Projectile::y = y + 12;
	}
	else {
		Projectile::x = x + 32;
		Projectile::y = y + 12;
	}
}

//Update projectile location and whether hit tile or map edge
void Projectile::UpdateProjectile(int width, int height) {
	
	if (live) {
		//Travel
		if (direction == 0) {
			x -= speed;
		}
		else {
			x += speed;
		}

		//Angle
		angle++;
		if (angle >= 128) {
			angle = 0;
		}

		//Map collision
		if (x <= 0 - frameWidth || x >= width) {
			live = false;
		}

		//Tile Collision
		if (collided(x, y) || collided(x + frameWidth, y + frameHeight) || collided(x + frameWidth, y) || collided(x, y + frameHeight)) {
			live = false;
		}
	}
}