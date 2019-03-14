#ifndef _BOX_H_
#define _BOX_H_
class Box {
public:
	float x, y;
	int w, h;
	float vx, vy;
public:
	Box(float, float, int, int, float, float);

#pragma region get_set
	void setX(int x) {
		this->x = x;
	}
	float getX() {
		return this->x;
	}

	void setY(int y) {
		this->y = y;
	}
	float getY() {
		return this->y;
	}

	void setWidth(int width) {
		this->w = width;
	}
	int getWidth() {
		return this->w;
	}

	void setHeight(int height) {
		this->h = height;
	}
	int getHeight() {
		return this->h;
	}

	void setMoveX(float movex) {
		this->vx = movex;
	}
	float getMoveX() {
		return this->vx;
	}

	void setMoveY(float movey) {
		this->vy = movey;
	}
	float getMoveY() {
		return this->vy;
	}
#pragma endregion
};
#endif