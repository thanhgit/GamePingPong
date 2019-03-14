#ifndef _UNTILS_H_
#define _UNTILS_H_
#define SPEED_BAR 10

#define SPEED_BALL_X 0.5
#define SPEED_BALL_Y 0.5
enum ChooseMenu {
	ONE_PLAYER,
	TWO_PLAYER,
	EXITGAME,
	NOTHING
};

enum ChooseTye {
	KEYBOARD,
	MOUSE
};

enum ChooseGameScene {
	PLAY_AGAIN,
	EXIT_GAME,
	NO_CHOOSE
};

enum SceneType {
	MENU_SCENE,
	CHOOSE_TYPE_SCENE,
	GAME_SCENE
};


enum InTurn {
	PLAYER1,
	PLAYER2,
	NOPLAYER
};

enum WINER {
	WIN1,
	WIN2,
	NOWIN
};
#endif