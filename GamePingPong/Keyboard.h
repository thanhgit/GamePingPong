#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#define KEYBOARD_BUFFER_SIZE 1024
#include<dinput.h>
class Keyboard {
private:
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 dinputdv;
	BYTE keyState[256];
	DIDEVICEOBJECTDATA keyEvent[KEYBOARD_BUFFER_SIZE];
	HINSTANCE hInstance;
	HWND hWnd;
protected:
public:
	Keyboard(HINSTANCE hInstance, HWND hWnd);
	~Keyboard();
	void processKeyboard();
	bool IsKeyDown(BYTE keyCode);
	bool IsKeyUp(BYTE keyCode);
};
#endif