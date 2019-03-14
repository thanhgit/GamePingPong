#include"Scene.h"

Scene::Scene(HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer) :Keyboard(hInstance, hWnd) {
	this->d3ddv = d3ddv; 
	this->backbuffer = backbuffer; 
	this->changeScene = false;
	this->chooseMenu = ONE_PLAYER;
	this->chooseType = KEYBOARD;
}

Scene::~Scene() {
	if (surface != NULL)
		surface->Release();
}

void Scene::initScene() {
	init();
}

void Scene::runScene(DWORD _dt) {
	run(_dt);
}

void Scene::exitScene() {
	exit();
}

void Scene::processInputScene() {
	processKeyboard();
	processInput();
}
