#include"Sprite.h"

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR fileName, int width, int height, int count, int spritePerRow) {
	this->transcolor = D3DCOLOR_XRGB(0, 0, 0);
	this->d3ddv = d3ddv;
	this->count = count;
	this->spritePerRow = spritePerRow;
	HRESULT result = D3DXCreateSprite(d3ddv, &sprite_hander);
	if (result != D3D_OK)
		return;
	D3DXIMAGE_INFO info;
	result = D3DXGetImageInfoFromFile(fileName, &info);
	if (result != D3D_OK)
		return;
	result = D3DXCreateTextureFromFileEx(d3ddv, fileName, info.Width, info.Height, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, transcolor, &info,NULL,&texture);
	if (result != D3D_OK)
		return;

	this->width = width;
	this->height = height;
	this->index = 0;
	this->x = 0;
	this->y = 0;
}

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR fileName, int width, int height, int count, int spritePerRow,D3DCOLOR transcolor) {
	this->transcolor = transcolor;
	this->d3ddv = d3ddv;
	this->count = count;
	this->spritePerRow = spritePerRow;
	HRESULT result = D3DXCreateSprite(d3ddv, &sprite_hander);
	if (result != D3D_OK)
		return;
	D3DXIMAGE_INFO info;
	result = D3DXGetImageInfoFromFile(fileName, &info);
	if (result != D3D_OK)
		return;
	result = D3DXCreateTextureFromFileEx(d3ddv,fileName, info.Width, info.Height, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, transcolor, &info, NULL, &texture);
	if (result != D3D_OK)
		return;

	this->width = width;
	this->height = height;
	this->index = 0;
	this->x = 0;
	this->y = 0;
}

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR fileName, int x, int y, int width, int height, int count, int spritePerRow) {
	Sprite::Sprite(d3ddv, fileName, width, height, count, spritePerRow);
	this->x = x;
	this->y = y;
}

Sprite::~Sprite() {
	if (texture != NULL)
		texture->Release();
	if (sprite_hander != NULL)
		sprite_hander->Release();
}

void Sprite::next() {
	index = (index+count+1) % count;
}

void Sprite::Reset() {
	index = 0;
}

void Sprite::Draw() {
	RECT rec;
	rec.left = (index%spritePerRow)*width;
	rec.top = (index / spritePerRow)*height;
	rec.right = rec.left + width;
	rec.bottom = rec.top + height;
	if (index == 10) {
		rec.right += width;
	}
	sprite_hander->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 position((float)x, (float)y, 0);
	sprite_hander->Draw(texture,&rec, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
	sprite_hander->End();
}

void Sprite::Draw(int x, int y) {
	this->x = x;
	this->y = y;
	Sprite::Draw();
}