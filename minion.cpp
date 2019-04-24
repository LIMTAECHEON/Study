#include "stdafx.h"
#include "minion.h"
#include "enemyManager.h"

minion::minion(){}
minion::~minion(){}

HRESULT minion::init()
{
	enemy::init();

	return S_OK;
}

HRESULT minion::init(const char * imageName, POINT position)
{
	enemy::init(imageName, position);

	return S_OK;
}

void minion::release()
{
}

void minion::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);
}

void minion::render()
{
	enemy::render();
}

void minion::enemySet()
{
	enemy::enemySet();
}

bool minion::enemyFire()
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(50, 200);
		return true;
	}
	return false;
}

void minion::setType(int type)
{
	enemy::setType(type);
}