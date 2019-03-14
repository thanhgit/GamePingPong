#ifndef _BAR_H_
#define _BAR_H_
#include"IObject.h"
#include"Untils.h"
class Bar :public IObject {
private:
	Sprite* pointSprite;
public:
	Bar(LPDIRECT3DDEVICE9,LPCWSTR fileNameBar,LPCWSTR fileNameNum,int width,int height,int count,int spritePerRow,D3DCOLOR transcolor);
	void displayPoint(int x,int y);
	void Draw();
	void Draw(int x, int y);
	void addPoint();

};
#endif