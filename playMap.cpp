#include "stdafx.h"
#include "playMap.h"


playMap::playMap()
{
}


playMap::~playMap()
{
}

HRESULT playMap::init()
{
	IMAGEMANAGER->addImage("배경1", "back.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경2", "back1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	return S_OK;
}

void playMap::release()
{
}

void playMap::update()
{
}

void playMap::render()
{
	IMAGEMANAGER->findImage("배경1")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("배경2")->render(getMemDC(), 0, 0);
}
