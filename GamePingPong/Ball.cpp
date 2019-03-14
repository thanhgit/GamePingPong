#include"Ball.h"
#include<cmath>
#include <algorithm>
#include <limits>

Ball::Ball(LPDIRECT3DDEVICE9 d3ddv,LPCWSTR fileName,int width,int height,int count,int spritePerRow):IObject() {
	sprite = new Sprite(d3ddv, fileName, width, height, count, spritePerRow, D3DCOLOR_XRGB(0, 0, 0));
	this->x = 0;
	this->y = 0;
	this->vx = 0;
	this->vy = 0;
	this->box = new Box(this->x, this->y, width, height, this->vx, this->vy);
}

void Ball::Draw(int x, int y) {
	this->x = x;
	this->y = y;
	this->box->x = this->x;
	this->box->y = this->y;
	this->box->vx = this->vx;
	this->box->vy = this->vy;
	Draw();
}

void Ball::Draw() {
	this->x = x;
	this->y = y;
	this->box->x = this->x;
	this->box->y = this->y;
	this->box->vx = this->vx;
	this->box->vy = this->vy;
	sprite->Draw(this->x, this->y);
}

void Ball::Move(InTurn turn, DWORD _dt) {
	if (turn == PLAYER1) {
		this->x += vx*_dt;
		this->y += vy*_dt;
	}
	else if (turn == PLAYER2) {
		this->x += vx*_dt;
		this->y += vy*_dt;
	}
	else {
		this->x += vx*_dt;
		this->y += vy*_dt;
	}

	
}

float Ball::SweptAABB(Box b2, float& normalx, float& normaly) {
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	if (box->vx > 0.0f) {
		xInvEntry = b2.x - (box->x + box->w);
		xInvExit = (b2.x + b2.w) - box->x;
	}
	else {
		xInvEntry = (b2.x + b2.w) - box->x;
		xInvExit = b2.x - (box->x + box->w);
	}

	if (box->vy > 0.0f) {
		yInvEntry = b2.y - (box->y + box->h);
		yInvExit = (b2.y + b2.h) - box->y;
	}
	else {
		yInvEntry = (b2.y + b2.h) - box->y;
		yInvExit = b2.y - (box->y + box->h);
	}

	float xEntry, yEntry;
	float xExit, yExit;

	if (box->vx == 0.0f) {
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / box->vx;
		xExit = xInvExit / box->vx;
	}

	if (box->vy == 0.0f) {
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / box->vy;
		yExit = yInvExit / box->vy;
	}

	float entryTime, exitTime;
	entryTime = max(xEntry, yEntry);
	exitTime = min(xExit, yExit);
	if (entryTime > exitTime || xEntry<0.0f && yEntry<0.0f || xEntry>1.0f || yEntry>1.0f) {
		normalx = 0.0f;
		normaly = 0.0f;

		return 1.0f;
	}
	else {
		if (xEntry > yEntry) {
			if (xInvEntry < 0.0f) {
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else {
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else {
			if (yInvEntry < 0.0f) {
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else {
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}
	}

	return entryTime;
}