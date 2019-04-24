#pragma once

#include "gameNode.h"		// 2DFramework
#include "loadingScene.h"	// 2DFramework/loading
#include "title.h"			// PlayGround/startMain
#include "stageSelect.h"	// PlayGround/stageSelect
#include "bossSelect.h"		// PlayGround/stageSelect
#include "stageMap.h"		// PlayGround/map
#include "Alldefine.h"		// PlayGround

class playGround : public gameNode
{
private:

	int _sceneCount;		// 화면 전환 카운터

public:

	playGround();
	~playGround();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

