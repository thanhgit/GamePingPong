#include"ChooseTypeScene.h"

ChooseTypeScene::ChooseTypeScene(HINSTANCE hInstance, HWND hWnd, LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer) :Scene(hInstance, hWnd, d3ddv, backbuffer) {
	this->surface = NULL;
	this->ball = NULL;
	this->sceneType = CHOOSE_TYPE_SCENE;
}

void ChooseTypeScene::init() {
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(TEXT("chooseTypeScene.png"), &info);
	if (result != D3D_OK)
		return;
	result = d3ddv->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (result != D3D_OK)
		return;
	result = D3DXLoadSurfaceFromFile(surface, NULL, NULL, TEXT("chooseTypeScene.png"), NULL, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 0), &info);
	if (result != D3D_OK)
		return;
	ball = new Sprite(d3ddv, L"ball.bmp", 25, 25, 1, 1);
}
void ChooseTypeScene::run(DWORD _dt) {
	d3ddv->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);
	if (this->chooseType == KEYBOARD) {
		ball->Draw(270,255);
	}
	else if (this->chooseType == MOUSE) {
		ball->Draw(465,330);
	}
}
void ChooseTypeScene::exit() {
	if (surface != NULL)
		surface->Release();
}

void ChooseTypeScene::processInput() {

	if (IsKeyDown(DIK_UP)) {
		this->chooseType = KEYBOARD;
	}

	if (IsKeyDown(DIK_DOWN)) {
		this->chooseType = MOUSE;
	}

	if (IsKeyDown(DIK_RETURN)) {
		this->exitScene();
		this->changeScene = true;
	}
}
