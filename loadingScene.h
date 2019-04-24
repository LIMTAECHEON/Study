#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "loadingBar.h"			// 2DFramework/progressBar
#include "title.h"
#include "stageSelect.h"	
#include "bossSelect.h"		
#include "stageMap.h"		

class loadingScene: public gameNode
{
private:

	loadingBar* _loading;			

	image* _setingImg;

	image* _loadManImg;
	RECT _loadManRc;
	POINTFLOAT _loadManPos;

	int _count = 0; 
	int _index = 0;

public:

	loadingScene();
	~loadingScene();

	int _currentCount;

	HRESULT init();
	void release();
	void update();
	void render();

	int getCurrentCount() { return _currentCount; }
};

static DWORD CALLBACK ThreadFuncition(LPVOID lpParameter);

