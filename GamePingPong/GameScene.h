#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include"Scene.h"
#include"Bar.h"
#include"Ball.h"
class GameScene :public Scene {
private:
	Bar* player1;
	Bar* player2;
	Ball* ball;
	InTurn turnPlay;
	WINER winner;
	ChooseGameScene choose;
	Sprite* chose;
	float normalx1;
	float normaly1;
	float normalx2;
	float normaly2;
protected:
	virtual void init();
	virtual void run(DWORD _dt);
	virtual void exit();
	virtual void processInput();
	//virtual void KeyDown(int vk_Code);
	//virtual void KeyUp(int ky_Code);
public:
	GameScene(HINSTANCE hInstance, HWND hWnd,LPDIRECT3DDEVICE9, LPDIRECT3DSURFACE9);
	void initBackground(LPCWSTR fileName);
	void logicGame(DWORD _dt);
	void controllGame();
};
#endif