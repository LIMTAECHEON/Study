#pragma once

#include "enemy.h"

class minion: public enemy
{
private:
	float _cameraX, _cameraY;

public:
	minion();
	~minion();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void enemySet();
	bool enemyFire();
	void setType(int type);
};

