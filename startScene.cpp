#include "stdafx.h"
#include "startScene.h"


startScene::startScene()
{
}


startScene::~startScene()
{
}

HRESULT startScene::init()
{
	IMAGEMANAGER->addImage("시작", "start.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
}

void startScene::render()
{
	IMAGEMANAGER->findImage("시작")->render(getMemDC());
}
