//Aiden D'Antuono

#include "SpriteSheet.h"
#include <stdio.h>

Sprite::Sprite() {
	image = NULL;
}

Sprite::~Sprite() {
	al_destroy_bitmap(image);
}

void Sprite::InitSprites() {
	x = 32;
	y = 360;

	maxFrame = 49;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 10;
	direction = 1;
	speed = 2;

	image = al_load_bitmap("SpriteSheet.png");
	al_convert_mask_to_alpha(image, al_map_rgb(255, 0, 255));
}

bool Sprite::UpdateSprites(int dir, int width, int height) {
	
	bool exited = false;
	int oldx = x;
	int oldy = y;

	//Movement Up
	if (dir == 0) {
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
	if (collided(x + 6, y) || collided(x + frameWidth - 6, y + frameHeight) || collided(x + frameWidth - 6, y) || collided (x + 6, y + frameHeight)) {
		x = oldx;
		y = oldy;
	}

	return exited;
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