#include<Windows.h>
#include"Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	Game game(hInstance, L"Game Ping Pong", 800, 600, 60, nCmdShow);
	game.GameInit();
	game.GameRun();
	game.GameEnd();
}