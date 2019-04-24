#pragma once
#include "gameNode.h"

class UI : public gameNode
{
private:

public:
	UI();
	~UI();

	HRESULT init();
	void release();
	void update();
	void render();
};

