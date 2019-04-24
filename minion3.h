#pragma once

#include "enemy.h"

class minion3 : public enemy
{
private:

public:
	minion3();
	~minion3();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void enemySet();
	bool enemyFire();
	void setType(int type);
};

