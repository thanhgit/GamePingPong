#include"GameScene.h"
#define KEY_DOWN(vk_Code) ((GetAsyncKeyState(vk_Code)&0x8000)?1:0)


GameScene::GameScene(HINSTANCE hInstance,HWND hWnd,LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer) :Scene(hInstance,hWnd,d3ddv, backbuffer) {
	this->surface = NULL;
	this->sceneType = GAME_SCENE;
	this->turnPlay = PLAYER1;
	this->winner = NOWIN;
	this->choose = PLAY_AGAIN;
	this->normalx1 = 0;
	this->normaly1 = 0;
	this->normalx2 = 0;
	this->normaly2 = 0;
}

void GameScene::initBackground(LPCWSTR fileName) {
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(fileName, &info);
	if (result != D3D_OK)
		return;
	result = d3ddv->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (result != D3D_OK)
		return;
	result = D3DXLoadSurfaceFromFile(surface, NULL, NULL, fileName, NULL, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), &info);
	if (result != D3D_OK)
		return;
}

void GameScene::init() {
	initBackground(L"gameScene.png");
	player1 = new Bar(d3ddv, L"bar.png",L"numbers.png",20, 80, 1, 1,D3DCOLOR_XRGB(255,255,255));
	player1->x = 16;
	player1->y = 400;
	player2 = new Bar(d3ddv, L"bar.png",L"numbers.png", 20, 80, 1, 1, D3DCOLOR_XRGB(255, 255, 255));
	player2->x = 750;
	player2->y = 400;
	ball = new Ball(d3ddv, L"ball.bmp", 25, 25, 1, 1);
	ball->x = 380;
	ball->y = 300;
	ball->vx = -SPEED_BALL_X;
	ball->vy = SPEED_BALL_Y;
	chose = new Sprite(d3ddv, L"ball.bmp",25,25,1,1,D3DCOLOR_XRGB(0,0,0));
}
void GameScene::run(DWORD _dt) {
	d3ddv->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);
	player1->Draw();
	player1->displayPoint(40, 60);
	player2->Draw();
	player2->displayPoint(690, 60);
	//ball->Move(turnPlay, _dt);

	logicGame(_dt);

	controllGame();
}

void GameScene::logicGame(DWORD _dt) {
	ball->x += ball->vx*_dt;
	ball->y += ball->vy*_dt;

	if (ball->y < 0) {
			ball->vy = SPEED_BALL_Y;
	}
	else if (ball->y>530) {
		ball->vy = -SPEED_BALL_Y;
	}

	this->ball->box->x = this->ball->x;
	this->ball->box->y = this->ball->y;
	this->ball->box->vx = ball->vx*_dt;
	this->ball->box->vy = ball->vy*_dt;
	this->player1->box->x = this->player1->x;
	this->player1->box->y = this->player1->y;
	this->player2->box->x = this->player2->x;
	this->player2->box->y = this->player2->y;

	ball->SweptAABB(*player1->box, normalx1, normaly1);
	if (normalx1 == -1.0f && normaly1 == 0.0f) {
		ball->vx= -SPEED_BALL_X;
	}
	else if (normalx1 == 1.0f && normaly1 == 0.0f) {
		ball->vx = SPEED_BALL_X;
	}
	else if (normaly1 == -1.0f && normalx1 == 0.0f) {
		ball->vy = SPEED_BALL_Y;
	}
	else if (normaly1 == 1.0f && normalx1 == 0.0f) {
		ball->y = -SPEED_BALL_Y;
	}

	normalx1 = 0;
	normaly1 = 0;

	ball->SweptAABB(*player2->box, normalx2, normaly2);
	if (normalx2 == -1.0f && normaly2 == 0.0f) {
		ball->vx = -SPEED_BALL_X;
	}
	else if (normalx2 == 1.0f && normaly2 == 0.0f) {
		ball->vx = SPEED_BALL_X;
	}
	else if (normaly2 == -1.0f && normalx2 == 0.0f) {
		ball->vy = -SPEED_BALL_Y;
	}
	else if (normaly2 == 1.0f && normalx2 == 0.0f) {
		ball->vy = SPEED_BALL_Y;
	}
}
void GameScene::controllGame()
{
	if (winner == NOWIN) {
		ball->Draw();
	}
	else {
		if (choose == PLAY_AGAIN) {
			chose->Draw(480, 350);
		}
		else if (choose == EXIT_GAME) {
			chose->Draw(480, 445);
		}

		ball->x = 380;
		ball->y = 300;
		ball->Draw();
	}

	if (ball->x < -30) {
		player2->addPoint();
		ball->x = 380;
		ball->y = 300;
	}

	if (ball->x > 800) {
		player1->addPoint();
		ball->x = 380;
		ball->y = 300;
	}

	if (player1->point == 3) {
		winner = WIN1;
	}

	if (player2->point == 3) {
		winner = WIN2;
	}

	if (winner == PLAYER1) {
		surface = NULL;
		initBackground(L"win1.png");
		ball->vx = 0;
		ball->vy = 0;
		turnPlay = NOPLAYER;
	}

	if (winner == PLAYER2) {
		surface = NULL;
		initBackground(L"win2.png");
		ball->vx = 0;
		ball->vy = 0;
		turnPlay = NOPLAYER;
	}
}
void GameScene::exit() {
	if (surface != NULL)
		surface->Release();
}

void GameScene::processInput() {
	if (winner == NOWIN) {
		if (IsKeyDown(DIK_W)) {
			player1->y -= SPEED_BAR;
			if (player1->y < 0) {
				player1->y = 0;
			}
		}
		if (IsKeyDown(DIK_S)) {
			player1->y += SPEED_BAR;
			if (player1->y > 480)
				player1->y = 480;
		}

		if (IsKeyDown(DIK_UP)) {
			player2->y -= SPEED_BAR;
			if (player2->y < 0) {
				player2->y = 0;
			}
		}
		if (IsKeyDown(DIK_DOWN)) {
			player2->y += SPEED_BAR;
			if (player2->y > 480)
				player2->y = 480;
		}
	}
	else {
		if (IsKeyDown(DIK_UP)) {
			choose = PLAY_AGAIN;
		}

		if (IsKeyDown(DIK_DOWN)) {
			choose = EXIT_GAME;
		}

		if (IsKeyDown(DIK_RETURN)) {
			if (choose == PLAY_AGAIN) {
				changeScene = true;
			}

			if (choose == EXIT_GAME) {
				PostMessage(this->hWnd, WM_QUIT, 0, 0);
			}
		}
	}

}

//void GameScene::KeyDown(int vk_Code) {
//	if (IsKeyDown(DIK_0)) {
//		MessageBox(NULL, L"0", L"MESSAGE", MB_OK);
//	}
//}
//
//void GameScene::KeyUp(int vk_Code) {
//
//}