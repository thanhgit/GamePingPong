#ifndef _SCENE_H_
#define _SCENE_H_
#include<d3d9.h>
#include<d3dx9.h>
#include"Keyboard.h"
#include"Untils.h"
class Scene : public Keyboard{
protected:
	ChooseMenu chooseMenu;
	ChooseTye chooseType;
	SceneType sceneType;
	LPDIRECT3DSURFACE9 surface;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backbuffer;
	HINSTANCE hInstance;
	HWND hWnd;
	bool changeScene;
	virtual void init()=0;
	virtual void run(DWORD _dt)=0;
	virtual void exit()=0;
	virtual void processInput() = 0;
public:
	Scene(HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer);
	~Scene();
	void initScene();
	void runScene(DWORD _dt);
	void exitScene();
	void processInputScene();

	bool getChangeScene() {
		return this->changeScene;
	}

	void setChangeScene(bool changeScene) {
		this->changeScene = changeScene;
	}

	SceneType getSceneType() {
		return sceneType;
	}

	void setSceneType(SceneType sceneType) {
		this->sceneType = sceneType;
	}
};
#endif