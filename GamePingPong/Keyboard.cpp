#include"Keyboard.h"

Keyboard::Keyboard(HINSTANCE hInstance, HWND hWnd) {
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dinput, NULL);
	dinput->CreateDevice(GUID_SysKeyboard, &dinputdv, NULL);
	dinputdv->SetDataFormat(&c_dfDIKeyboard);
	dinputdv->SetCooperativeLevel(this->hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	DIPROPDWORD dipdw;
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;
	dinputdv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	dinputdv->Acquire();
	for (int i = 0; i < 256; i++) {
		keyState[i] = 0x00;
	}
}

Keyboard::~Keyboard() {
	if (dinputdv != NULL) {
		dinputdv->Unacquire();
		dinputdv->Release();
	}

	if (dinput != NULL)
		dinput->Release();
}

void Keyboard::processKeyboard() {
	BYTE keys[256];
	dinputdv->GetDeviceState(256, keys);
	for (int i = 0; i < 256; i++) {
		keyState[i] = keys[i];
	}

	if (IsKeyDown(DIK_ESCAPE)) {
		PostMessage(this->hWnd, WM_QUIT, 0, 0);
	}
}

bool Keyboard::IsKeyDown(BYTE keyCode) {
	return (keyState[keyCode] & 0x80)>0;
}

bool Keyboard::IsKeyUp(BYTE keyCode) {
	return !((keyState[keyCode] & 0x80) > 0);
}