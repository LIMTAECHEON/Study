#include "stdafx.h"
#include "loadingScene.h"

loadingScene::loadingScene()
	: _setingImg(nullptr), _loading(nullptr),
	_currentCount(0)
{
}

loadingScene::~loadingScene() {}

HRESULT loadingScene::init()
{
	_setingImg = LOADING_BACKGROUND_IMAGE;

	_loading = new loadingBar;
	_loading->init(LOADING_BAR_INIT);
	_loading->setGauge(0, 0);

	_loadManImg = LOADINGMAN_IMAGE;

	_loadManPos.x = LOADING_MAN_X;
	_loadManPos.y = LOADING_MAN_Y;
	_loadManRc = RectMakeCenter(_loadManPos.x, _loadManPos.y, _loadManImg->getFrameWidth(), _loadManImg->getFrameHeight());

	_loadManImg->SetFrameY(0);

	CreateThread
	(
		NULL,
		NULL,
		ThreadFuncition,
		this,
		NULL,
		0
	);

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();
	_loading->setGauge(_currentCount, LOADING_MAX);

	_count++;
	if (_count % LOADING_MAN_ICON_IMAGE_SPEED == 0)
	{
		_index++;
		_loadManImg->SetFrameX(_index);
		if (_index >= _loadManImg->getMaxFrameX()) _index = -1;
		_count = 0;
	}

	if (_currentCount == LOADING_MAX)
	{
		SOUNDMANAGER->play("01", VOLUME);
		SCENEMANAGER->changeScene("main");
	}
}

void loadingScene::render()
{
	_setingImg->render(getMemDC(), 0, 0);
	_loadManImg->frameRender(getMemDC(), _loadManRc.left, _loadManRc.top);
	_loading->render();
}

DWORD CALLBACK ThreadFuncition(LPVOID lpParameter)
{
	loadingScene* loadHelper = (loadingScene*)lpParameter;

	while (loadHelper->_currentCount != LOADING_MAX)
	{
		SCENEMANAGER->addScene("main", new title);
		SCENEMANAGER->addScene("loading", new loadingScene);	
		SCENEMANAGER->addScene("select", new stageSelect);		
		SCENEMANAGER->addScene("bossSel", new bossSelect);		
		SCENEMANAGER->addScene("map", new stageMap);			

		SOUNDMANAGER->addSound("01", "sound/01.mp3", true, false);
		SOUNDMANAGER->addSound("02", "sound/02.mp3", true, false);
		SOUNDMANAGER->addSound("03", "sound/03.mp3", true, false);
		SOUNDMANAGER->addSound("04", "sound/04.mp3", true, true);

		Sleep(1);

		loadHelper->_currentCount++;
	}

	return 0;
}
