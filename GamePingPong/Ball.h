#ifndef _BALL_H_
#define _BALL_H_
#include"IObject.h"
#include"Untils.h"

class Ball:public IObject {
public:
	Ball(LPDIRECT3DDEVICE9 d3ddv,LPCWSTR fileName,int width,int height,int count,int spritePerRow);
	void Draw(int x, int y);
	void Draw();
	void Move(InTurn turn, DWORD _dt);
	float SweptAABB(Box b2, float& normalx, float& normaly);
};
#endif