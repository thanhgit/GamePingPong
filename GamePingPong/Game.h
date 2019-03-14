#ifndef _GAME_H_
#define _GAME_H_
#include"Scene.h"

class Game {
private:
	LPDIRECT3D9 d3d;
	HINSTANCE hInstance;

	LPCWSTR nameApp;
	int frameRate;
	int widthScreen;
	int heightScreen;
	int nCmdShow;
	Scene* scene;

protected:
	HWND hWnd;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backbuffer;
	bool isGameScene;
	bool isMeunuScene;
	virtual void LoadResources();
	virtual void processInput();
	virtual void updateFrame(DWORD _dt);
public:
	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
	Game(HINSTANCE, LPCWSTR, int,int,int, int);
	void GameInit();
	void InitWindow();
	void InitDirectX();
	void GameRun();
	void GameEnd();
	void update(DWORD _dt);
};
#endif