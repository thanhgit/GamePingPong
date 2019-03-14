#include"Game.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"ChooseTypeScene.h"
#include"Untils.h"

Game::Game(HINSTANCE hInstance, LPCWSTR name, int width,int height,int frameRate,int nCmdShow) {
	this->hInstance = hInstance;
	this->nameApp = name;
	this->frameRate = frameRate;
	this->d3d = NULL;
	this->d3ddv = NULL;
	this->backbuffer = NULL;
	this->widthScreen = width;
	this->heightScreen = height;
	this->isMeunuScene = true;
	this->isGameScene = false;
	this->scene = NULL;
	this->nCmdShow = nCmdShow;
}

LRESULT CALLBACK Game::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Game::InitWindow() {
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = this->hInstance;
	wc.lpfnWndProc = Game::WinProc;
	wc.lpszClassName = this->nameApp;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	this->hWnd = CreateWindow(nameApp, nameApp, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, widthScreen, heightScreen, NULL, NULL, this->hInstance, NULL);
	if (!hWnd)
		return;
	ShowWindow(this->hWnd, this->nCmdShow);
	UpdateWindow(this->hWnd);
}

void Game::InitDirectX() {
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddv);
	if (d3ddv==NULL)
		return;
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	d3ddv->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	d3ddv->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
}

void Game::GameInit() {
	Game::InitWindow();
	Game::InitDirectX();
	LoadResources();
	scene = new MenuScene(this->hInstance,this->hWnd,d3ddv, backbuffer);
	scene->initScene();
}

void Game::GameRun() {
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();

	DWORD count_per_frame = 1000 / this->frameRate;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// update game
		DWORD now = GetTickCount();
		DWORD dt = now - frame_start;
		if (dt >= count_per_frame)
		{
			frame_start = now;
			
			update(dt);
		}
		else {
			Sleep(count_per_frame - dt);
		}
	}
}

void Game::GameEnd() {
	if (d3d != NULL)
		d3d->Release();
	if (d3ddv != NULL)
		d3ddv->Release();
	if (backbuffer != NULL)
		backbuffer->Release();
}

void Game::update(DWORD _dt) {
	processInput();

	d3ddv->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	if (d3ddv->BeginScene()) {
		updateFrame(_dt);
		d3ddv->EndScene();
	}

	d3ddv->Present(0, 0, 0, 0);
}

void Game::LoadResources() {

}

void Game::processInput() {
	scene->processInputScene();
	if (scene->getChangeScene()) {
		scene->exitScene();
		if (scene->getSceneType() == MENU_SCENE) {
			scene = new ChooseTypeScene(hInstance, hWnd, d3ddv, backbuffer);
			scene->initScene();
		}else if (scene->getSceneType() == CHOOSE_TYPE_SCENE) {
			scene = new GameScene(hInstance, hWnd, d3ddv, backbuffer);
			scene->initScene();
		}
		else if (scene->getSceneType() == GAME_SCENE) {
			scene = new GameScene(hInstance, hWnd, d3ddv, backbuffer);
			scene->initScene();
		}
	}
}

void Game::updateFrame(DWORD _dt) {
	scene->runScene(_dt);
}