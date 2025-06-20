//Aiden D'Antuono

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Crystal.h"
#include <stdio.h>

Crystal::Crystal() {
	image = NULL;
	inPlay = false;
}

Crystal::~Crystal() {
	al_destroy_bitmap(image);
	al_destroy_sample(sample);
}

void Crystal::InitCrystal(char file[16], int x, int y, Projectile *projectiles, int numProjectiles) {
	sample = al_load_sample("crystal.wav");
	lives = 3;

	Crystal::x = x;
	Crystal::y = y;
	maxFrame = 3;
	curFrame = 0;
	frameWidth = 64;
	frameHeight = 128;
	animationColumns = 2;

	Crystal::projectiles = projectiles;
	Crystal::numProjectiles = numProjectiles; 

	inPlay = true;

	image = al_load_bitmap(file);
}

//Update sprite based on health and whether player hits it
void Crystal::UpdateCrystal() {

	if (curFrame > maxFrame) {
		curFrame = maxFrame;
	}

	//Projectile Collision
	if (lives > 0) {
		for (int i = 0; i < numProjectiles; i++) {
			if (projectiles[i].getLive()) {
				if (x + frameWidth >= projectiles[i].getX() && x <= projectiles[i].getX() + 8 && y + frameHeight >= projectiles[i].getY() && y <= projectiles[i].getY() + 8) {
					al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					projectiles[i].setLive(false);
					lives--;
					curFrame++;
				}
			}
		}
	}
}

//Draw crystal
void Crystal::DrawCrystal(int xoffset, int yoffset) {
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
}