#pragma once
#include "gameNode.h"

class playMap:public gameNode
{
public:
	playMap();
	~playMap();

	HRESULT init();
	void release();
	void update();
	void render();
};

