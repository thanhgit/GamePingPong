#include"Bar.h"

Bar::Bar(LPDIRECT3DDEVICE9 d3ddv,LPCWSTR fileNameBar,LPCWSTR fileNameNum,int width,int height,int count,int spritePerRow,D3DCOLOR transcolor):IObject() {
	sprite = new Sprite(d3ddv, fileNameBar, width, height, count, spritePerRow,transcolor);
	pointSprite = new Sprite(d3ddv, fileNameNum, 50, 64, 12, 12,D3DCOLOR_XRGB(255,0,255));
	this->x = 0;
	this->y = 0;
	this->point = 0;
	this->box = new Box(this->x, this->y, width, height, this->vx, this->vy);
}

void Bar::Draw(int x, int y) {
	this->x = x;
	this->y = y;
	this->box->x = this->x;
	this->box->y = this->y;
	this->box->vx = this->vx;
	this->box->vy = this->vy;
	sprite->Draw(this->x,this->y);
}

void Bar::Draw() {
	sprite->Draw(this->x, this->y);
}

void Bar::displayPoint(int x, int y) {
	pointSprite->Draw(x,y);
}

void Bar::addPoint() {
	this->point += 1;
	if (this->point > 10) {
		this->point = 10;
	}
	pointSprite->setIndex(this->point);
}