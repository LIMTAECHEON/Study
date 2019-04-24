#include "stdafx.h"
#include "bullets.h"

playBullet::playBullet()
{
}

playBullet::~playBullet()
{
}

HRESULT playBullet::init(int playBulletMax, float range)
{
	_range = range;

	for (int i = 0; i < playBulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.bulletImg = new image;
		bullet.bulletImg->init("shot.bmp", 63, 27, true, RGB(255, 0, 255));
		bullet.speed = 10.0f;
		bullet.isFire = false;
		 
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void playBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->bulletImg);
		SAFE_DELETE(_viBullet->bulletImg);
	}

	_vBullet.clear();
}

void playBullet::update()
{
	playBulletMove();
}

void playBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->bulletImg->render(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			0, 0, _viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());

		if (KEYMANAGER->isStayKeyDown(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void playBullet::playBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->fireX = x;
		_viBullet->pos.y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());
		break;
	}
}

void playBullet::playBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void playBullet::deletePlayBullet(int playBulletMax)
{
	SAFE_RELEASE(_vBullet[playBulletMax].bulletImg);
	_vBullet.erase(_vBullet.begin() + playBulletMax);
}

playBullet2::playBullet2()
{
}

playBullet2::~playBullet2()
{
}

HRESULT playBullet2::init(int playBullet2Max, float range)
{
	_range = range;

	for (int i = 0; i < playBullet2Max; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.bulletImg = new image;
		bullet.bulletImg->init("shot2_2.bmp", 201, 117, true, RGB(255, 0, 255));
		bullet.speed = 15.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void playBullet2::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->bulletImg);
		SAFE_DELETE(_viBullet->bulletImg);
	}

	_vBullet.clear();
}

void playBullet2::update()
{
	playBullet2Move();
}

void playBullet2::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->bulletImg->render(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			0, 0, _viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());

		if (KEYMANAGER->isStayKeyDown(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void playBullet2::playBullet2Fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->fireX = x;
		_viBullet->pos.y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());
		break;
	}
}

void playBullet2::playBullet2Move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void playBullet2::deletePlayBullet2(int playBullet2Max)
{
	SAFE_RELEASE(_vBullet[playBullet2Max].bulletImg);
	_vBullet.erase(_vBullet.begin() + playBullet2Max);
}

bossBullet::bossBullet()
{
}

bossBullet::~bossBullet()
{
}

HRESULT bossBullet::init(int bossBulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bossBulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.bulletImg = new image;
		bullet.bulletImg->init("bossShot.bmp", 102, 27, true, RGB(255, 0, 255));
		bullet.speed = 6.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}
	return S_OK;
}

void bossBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->bulletImg);
		SAFE_DELETE(_viBullet->bulletImg);
	}

	_vBullet.clear();
}

void bossBullet::update()
{
	bossBulletMove();
}

void bossBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->bulletImg->render(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			0, 0, _viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());

		if (KEYMANAGER->isStayKeyDown(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void bossBullet::bossBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->fireX = x;
		_viBullet->pos.y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());
	}
}

void bossBullet::bossBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->bulletImg->GetWidth(), _viBullet->bulletImg->GetHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void bossBullet::deleteBossBullet(int bossBulletMax)
{
	SAFE_RELEASE(_vBullet[bossBulletMax].bulletImg);
	_vBullet.erase(_vBullet.begin() + bossBulletMax);
}
