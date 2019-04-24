#include "stdafx.h"
#include "minion3.h"

minion3::minion3(){}
minion3::~minion3(){}

HRESULT minion3::init()
{
	enemy::init();

	return S_OK;
}

HRESULT minion3::init(const char * imageName, POINT position)
{
	enemy::init(imageName, position);

	return S_OK;
}

void minion3::release()
{
}

void minion3::update(float cameraX, float cameraY)
{
	enemy::update(cameraX, cameraY);
}

void minion3::render()
{
	enemy::render();
}

void minion3::enemySet()
{
	enemy::enemySet();
}

bool minion3::enemyFire()
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		_rndFireCount = 65;

		return true;
	}
	return false;
}

void minion3::setType(int type)
{
	enemy::setType(type);
}
