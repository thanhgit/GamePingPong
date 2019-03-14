#ifndef _SPRITE_H_
#define _SPRITE_H_
#include<d3d9.h>
#include<d3dx9.h>
class Sprite {
private:
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite_hander;

	int index;
	int width, height;
	int x, y;
	int count, spritePerRow;
	LPCWSTR fileName;
	D3DCOLOR transcolor;
public:
	Sprite(LPDIRECT3DDEVICE9 d3ddv,LPCWSTR fileName,int width,int height,int count,int spritePerRow);
	Sprite(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR fileName,int x,int y, int width, int height, int count, int spritePerRow);
	Sprite(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR fileName, int width, int height, int count, int spritePerRow,D3DCOLOR transcolor);
	~Sprite();
	void Draw();
	void Draw(int x, int y);
	void next();
	void Reset();

	void setIndex(int _index) {
		this->index = _index;
	}
};
#endif