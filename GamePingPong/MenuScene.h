#ifndef _MENUSCENE_H_
#define _MENUSCENE_H_
#include"Scene.h"
#include"Sprite.h"
#include"Untils.h"
class MenuScene:public Scene {
private:
	Sprite* ball;
	int x, y;
protected:
	virtual void init();
	virtual void run(DWORD _dt);
	virtual void exit();
	virtual void processInput();
	//virtual bool IsKeydown(int vk_Code);
	//virtual bool IsKeyup(int ky_Code);
public:
	MenuScene(HINSTANCE,HWND,LPDIRECT3DDEVICE9,LPDIRECT3DSURFACE9);
};
#endif