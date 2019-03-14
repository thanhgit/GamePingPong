#include"MenuScene.h"
#include"GameScene.h"

MenuScene::MenuScene(HINSTANCE hInstance,HWND hWnd,LPDIRECT3DDEVICE9 d3ddv,LPDIRECT3DSURFACE9 backbuffer) :Scene(hInstance,hWnd,d3ddv,backbuffer){
	this->surface = NULL;
	this->ball = NULL;
	this->sceneType = MENU_SCENE;
}

void MenuScene::init() {
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(TEXT("menuScene.png"), &info);
	if (result != D3D_OK)
		return;
	result = d3ddv->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (result != D3D_OK)
		return;
	result = D3DXLoadSurfaceFromFile(surface, NULL, NULL, TEXT("menuScene.png"),NULL,D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 0), &info);
	if (result != D3D_OK)
		return;
	ball = new Sprite(d3ddv, L"ball.bmp", 25, 25, 1, 1);
}
void MenuScene::run(DWORD _dt) {
	d3ddv->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);
	if (this->chooseMenu==ONE_PLAYER) {
		ball->Draw(310, 240);
	}
	else if(this->chooseMenu==TWO_PLAYER){
		ball->Draw(310, 332);
	}
	else if (this->chooseMenu == EXITGAME) {
		ball->Draw(310, 430);
	}
}
void MenuScene::exit() {
	if (surface != NULL)
		surface->Release();
}

void MenuScene::processInput() {
	if (IsKeyDown(DIK_ESCAPE)) {
		PostMessage(this->hWnd, WM_DESTROY, 0, 0);
	}

	if (IsKeyDown(DIK_1)) {
		this->chooseMenu = ONE_PLAYER;
	}

	if (IsKeyDown(DIK_2)) {
		this->chooseMenu = TWO_PLAYER;
	}

	if (IsKeyDown(DIK_3)) {
		this->chooseMenu = EXITGAME;
	}

	if (IsKeyDown(DIK_RETURN)) {
		this->exitScene();
		this->changeScene = true;
		if (this->chooseMenu == EXITGAME)
			PostMessage(hWnd, WM_QUIT, 0, 0);
	}
}
