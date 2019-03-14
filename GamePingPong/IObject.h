#ifndef _IOBJECT_H_
#define _IOBJECT_H_
#include"Sprite.h"
#include"Box.h"
class IObject {
public:
	Box* box;
	int x, y;
	int point;
	float vx, vy;
	Sprite* sprite;
public:
	IObject() {};
#pragma region _get_set_
	int getX() {
		return x;
	}
	void setX(int x) {
		this->x = x;
	}

	int getY() {
		return y;
	}
	void setY(int y) {
		this->y = y;
	}

	int getPoint() {
		return this->point;
	}
	void setPoint(int point) {
		this->point = point;
	}
	void resetPoint() {
		this->point = 0;
	}
#pragma endregion
};
#endif