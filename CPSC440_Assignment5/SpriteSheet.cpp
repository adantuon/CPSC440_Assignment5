//Aiden D'Antuono

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"
#include <stdio.h>

Sprite::Sprite() {
	image = NULL;
}

Sprite::~Sprite() {
	al_destroy_bitmap(image);
}

void Sprite::InitSprites(char file[16], int x, int y, bool player, Projectile *projectilesP, int numProjectilesP, Projectile *projectilesE, int numProjectilesE, Crystal *crystal) {
	//If player
	if (player) {
		sample = al_load_sample("playerhit.wav");
		lives = 5;
	}
	//If enemy
	else {
		sample = al_load_sample("skeletondeath.wav");
		lives = 1;
	}

	Sprite::x = x;
	Sprite::y = y;

	maxFrame = 49;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 10;
	direction = 1;
	speed = 2;
	firing = false;
	directionAI = rand() % 2;

	Sprite::projectilesP = projectilesP;
	Sprite::numProjectilesP = numProjectilesP;
	Sprite::projectilesE = projectilesE;
	Sprite::numProjectilesE = numProjectilesE;
	Sprite::crystal = crystal;

	image = al_load_bitmap(file);
}

void Sprite::UpdateSprites(Sprite *enemies, int numEnemies, int dir, int width, int height) {

	int oldx = x;
	int oldy = y;


	//Dead
	if (lives < 1) {
		if (curFrame < 40) {
			curFrame = 40;
		}

		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (curFrame < maxFrame) {
				curFrame++;
			}
		}
	}
	//Firing Projectile
	else if (dir == 4 || firing) {
		if (!firing) {
			curFrame = 30;
			frameCount = 0;
			firing = true;
		}
		
		if (curFrame == 36 && frameCount == 0) {
			for (int i = 0; i < numProjectilesP; i++) {
				if (!projectilesP[i].getLive()) {
					projectilesP[i].FireProjectile(x, y, direction);
					break;
				}
			}
		}

		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > 39) {
				curFrame = 0;
				firing = false;
			}	
		}
	}
	//Movement Up
	else if (dir == 0) {
		if (curFrame < 20) {
			curFrame = 20;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 29)
				curFrame = 20;
		}

		y -= speed;
	}
	//Movement Down
	else if (dir == 1) {
		if (curFrame < 20) {
			curFrame = 20;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 29)
				curFrame = 20;
		}

		y += speed;
	}
	//Movement Left
	else if (dir == 2) {
		if (direction != 0 || curFrame < 20) {
			direction = 0;
			curFrame = 20;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 29)
				curFrame = 20;
		}

		x -= speed;
	}
	//Movement Right
	else if (dir == 3) {
		if (direction != 1 || curFrame < 20) {
			direction = 1;
			curFrame = 20;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 29)
				curFrame = 20;
		}

		x += speed;
	}
	//If stopped
	else {
		if (curFrame > 19) {
			curFrame = 0;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 19)
				curFrame = 0;
		}
	}

	//Map Edge Collision
	//Top edge has no exits
	if (y <= 0 || x <= 0 || y >= height - frameHeight) {
		x = oldx;
		y = oldy;
	}
	//potential exit edges
	else if (x >= width - frameWidth) {
		x = oldx;
		y = oldy;
	}

	//Collision Detection
	if (collided(x + 6, y + 2) || collided(x + frameWidth - 6, y + frameHeight - 4) || collided(x + frameWidth - 6, y + 2) || collided (x + 6, y + frameHeight - 4)) {
		x = oldx;
		y = oldy;
	}

	//enemy collision
	for (int i = 0; i < numEnemies; i++) {
		if (enemies[i].getLives() > 0) {
			if (x + frameWidth >= enemies[i].getX() && x <= enemies[i].getX() + frameWidth && y + frameHeight >= enemies[i].getY() && y <= enemies[i].getY() + frameHeight) {
				x = oldx;
				y = oldy;
			}
		}
	}

	//Crystal collision
	if (crystal->returnInPlay()) {
		if (x + frameWidth >= crystal->getX() && x <= crystal->getX() + 64 && y + frameHeight >= crystal->getY() && y <= crystal->getY() + 128) {
			x = oldx;
			y = oldy;
		}
	}

	//Projectile collision
	if (lives > 0) {
		for (int i = 0; i < numProjectilesE; i++) {
			if (projectilesE[i].getLive()) {
				if (x + frameWidth >= projectilesE[i].getX() && x <= projectilesE[i].getX() + 8 && y + frameHeight >= projectilesE[i].getY() && y <= projectilesE[i].getY() + 8) {
					al_play_sample(sample, 0.66, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					projectilesE[i].setLive(false);
					lives--;
				}
			}
		}
	}
}

void Sprite::UpdateSpritesAI(Sprite &player, int width, int height) {

	int oldx = x;
	int oldy = y;

	if (player.getX() < x) {
		direction = 0;
	}
	else if (player.getX() > x + frameWidth) {
		direction = 1;
	}


	//Dead
	if (lives < 1) {
		if (curFrame < 40) {
			curFrame = 40;
		}

		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (curFrame < maxFrame) {
				curFrame++;
			}
		}
	}
	//Firing Projectile
	else if (rand() % 50 == 0 || firing) {
		if (!firing) {
			curFrame = 30;
			frameCount = 0;
			firing = true;
		}

		if (curFrame == 38 && frameCount == 0) {
			for (int i = 0; i < numProjectilesE; i++) {
				if (!projectilesE[i].getLive()) {
					projectilesE[i].FireProjectile(x, y, direction);
					break;
				}
			}
		}

		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > 39) {
				curFrame = 0;
				firing = false;
			}
		}
	}
	//Movement Up/Down
	else {
		if (curFrame < 20) {
			curFrame = 20;
		}

		if (++frameCount > frameDelay)
		{
			frameCount = 0;
			if (++curFrame > 29)
				curFrame = 20;
		}
		if (directionAI == 0) {
			y += speed;
		}
		else {
			y -= speed;
		}
		
	}

	//Map Edge Collision
	if (y <= 0 || x <= 0 || y >= height - frameHeight || x >= width - frameWidth) {
		x = oldx;
		y = oldy;
		if (directionAI == 0) {
			directionAI = 1;
		}
		else {
			directionAI = 0;
		}

	}

	//Collision Detection
	if (collided(x + 6, y) || collided(x + frameWidth - 6, y + frameHeight) || collided(x + frameWidth - 6, y) || collided(x + 6, y + frameHeight)) {
		x = oldx;
		y = oldy;
		if (directionAI == 0) {
			directionAI = 1;
		}
		else {
			directionAI = 0;
		}
	}

	//player collision
	if (player.getLives() > 0) {
		if (x + frameWidth >= player.getX() && x <= player.getX() + frameWidth && y + frameHeight >= player.getY() && y <= player.getY() + frameHeight) {
			x = oldx;
			y = oldy;
		}
	}
	

	//Projectile Collision
	if (lives > 0) {
		for (int i = 0; i < numProjectilesP; i++) {
			if (projectilesP[i].getLive()) {
				if (x + frameWidth >= projectilesP[i].getX() && x <= projectilesP[i].getX() + 8 && y + frameHeight >= projectilesP[i].getY() && y <= projectilesP[i].getY() + 8) {
					al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					projectilesP[i].setLive(false);
					lives--;
				}
			}
		}
	}
}

int Sprite::CollisionSpecial()
{
	return specialValue(x + 16, y + 16);
}

void Sprite::DrawSprites(int xoffset, int yoffset) {
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	if (direction == 0) {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}
	else {
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	}
}