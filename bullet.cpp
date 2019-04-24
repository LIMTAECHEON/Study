#include "stdafx.h"
#include "bullet.h"

// ========================================================================================================= [애너미]

bullet::bullet()
{
}

bullet::~bullet()
{
}

HRESULT bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update(float cameraX, float cameraY)
{
	_cameraX = cameraX;
	_cameraY = cameraY;

	bulletMove();
}

void bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left - _cameraX, _viBullet->rc.top - _cameraY);
	}
}

void bullet::bulletFire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.img->GetWidth() / 2;
	bullet.pos.x = bullet.firePos.x = x;
	bullet.pos.y = bullet.firePos.y = y;
	bullet.angle = angle;

	bullet.rc = RectMakeCenter(bullet.pos.x, bullet.pos.y,
		bullet.img->GetWidth(),
		bullet.img->GetHeight());

	_vBullet.push_back(bullet);
}

void bullet::bulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->pos.x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->pos.y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (_range < getDistance(_viBullet->pos.x, _viBullet->pos.y, _viBullet->firePos.x, _viBullet->firePos.y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bullet::deleteBullet(int bulletNum)
{
	_vBullet.erase(_vBullet.begin() + bulletNum);
}

// ========================================================================================================= [팽도리]

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
		bullet.img = new image;
		bullet.img->init("image/pengdori/bossShot.bmp", 0, 0, 216, 22, 2, 1, true, RGB(255, 0, 255));
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
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}
}

void bossBullet::update(float cameraX, float cameraY)
{
	_cameraX = cameraX;
	_cameraY = cameraY;

	bossBulletMove();
}

void bossBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->frameRender(getMemDC(),
			_viBullet->rc.left -_cameraX, _viBullet->rc.top -_cameraY,
			_viBullet->img->getFrameX(), 0);

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);

		_viBullet->count++;

		if (_viBullet->count % 10 == 0)
		{
			_viBullet->img->SetFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX());
			{
				_viBullet->img->SetFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void bossBullet::bossBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		break;
	}
}

void bossBullet::bossBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void bossBullet::deleteBossBullet(int bossBulletMax)
{
	SAFE_RELEASE(_vBullet[bossBulletMax].img);
	_vBullet.erase(_vBullet.begin() + bossBulletMax);
}

bossBullet2::bossBullet2()
{
}

bossBullet2::~bossBullet2()
{
}

HRESULT bossBullet2::init(int bossBullet2Max, float range)
{
	_range = range;

	for (int i = 0; i < bossBullet2Max; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/pengdori/bossShot2.bmp", 102, 99, true, RGB(255, 0, 255));
		bullet.speed = 12.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void bossBullet2::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}
}

void bossBullet2::update(float cameraX, float cameraY)
{
	_cameraX = cameraX;
	_cameraY = cameraY;

	bossBullet2Move();
}

void bossBullet2::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->render(getMemDC(),
			_viBullet->rc.left - _cameraX, _viBullet->rc.top - _cameraY,
			0, 0, _viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void bossBullet2::bossBullet2Fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());
		break;
	}
}

void bossBullet2::bossBullet2Move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void bossBullet2::deleteBossBullet2(int bossBullet2Max)
{
	SAFE_RELEASE(_vBullet[bossBullet2Max].img);
	_vBullet.erase(_vBullet.begin() + bossBullet2Max);
}

bossBullet3::bossBullet3()
{
}

bossBullet3::~bossBullet3()
{
}

HRESULT bossBullet3::init(int bossBullet3Max, float range)
{
	_range = range;

	for (int i = 0; i < bossBullet3Max; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/pengdori/bossShot3.bmp", 54, 52, true, RGB(255, 0, 255));
		bullet.speed = 3.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void bossBullet3::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}
}

void bossBullet3::update(float cameraX, float cameraY)
{
	_cameraX = cameraX;
	_cameraY = cameraY;

	bossBullet3Move();
}

void bossBullet3::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->render(getMemDC(),
			_viBullet->rc.left - _cameraX, _viBullet->rc.top - _cameraY,
			0, 0, _viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void bossBullet3::bossBullet3Fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());
	}
}

void bossBullet3::bossBullet3Move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.y += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void bossBullet3::deleteBossBullet3(int bossBullet3Max)
{
	SAFE_RELEASE(_vBullet[bossBullet3Max].img);
	_vBullet.erase(_vBullet.begin() + bossBullet3Max);
}

bossBullet4::bossBullet4()
{
}

bossBullet4::~bossBullet4()
{
}

HRESULT bossBullet4::init(int bossBullet4Max, float range)
{
	_range = range;

	for (int i = 0; i < bossBullet4Max; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/pengdori/bossShot3.bmp", 54, 52, true, RGB(255, 0, 255));
		bullet.speed = 3.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void bossBullet4::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}
}

void bossBullet4::update(float cameraX, float cameraY)
{
	_cameraX = cameraX;
	_cameraY = cameraY;

	bossBullet4Move();
}

void bossBullet4::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->render(getMemDC(),
			_viBullet->rc.left - _cameraX, _viBullet->rc.top - _cameraY,
			0, 0, _viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void bossBullet4::bossBullet4Fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());
	}
}

void bossBullet4::bossBullet4Move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.y += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void bossBullet4::deleteBossBullet4(int bossBullet4Max)
{
	SAFE_RELEASE(_vBullet[bossBullet4Max].img);
	_vBullet.erase(_vBullet.begin() + bossBullet4Max);
}

// ========================================================================================================= [엑스 일반 오른쪽]

normalRightBullet::normalRightBullet()
{
}

normalRightBullet::~normalRightBullet()
{
}

HRESULT normalRightBullet::init(int normalBulletMax, float range)
{
	_range = range;

	for (int i = 0; i < normalBulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/rockman/enemy_bu02.bmp", 24, 24, true, RGB(255, 0, 255));
		bullet.speed = 15.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void normalRightBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void normalRightBullet::update()
{
	normalRightBulletMove();
}

void normalRightBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->render(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			0, 0, _viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void normalRightBullet::normalRightBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());
		break;
	}
}

void normalRightBullet::normalRightBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}
void normalRightBullet::deleteNormalRightBullet(int normalBulletMax)
{
	SAFE_RELEASE(_vBullet[normalBulletMax].img);
	_vBullet.erase(_vBullet.begin() + normalBulletMax);
}

// ========================================================================================================= [엑스 일반 왼쪽]

normalLeftBullet::normalLeftBullet()
{
}

normalLeftBullet::~normalLeftBullet()
{
}

HRESULT normalLeftBullet::init(int normalBulletMax, float range)
{
	_range = range;

	for (int i = 0; i < normalBulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/rockman/enemy_bu02.bmp", 24, 24, true, RGB(255, 0, 255));
		bullet.speed = 15.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void normalLeftBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void normalLeftBullet::update()
{
	normalLeftBulletMove();
}

void normalLeftBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->render(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			0, 0, _viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);
	}
}

void normalLeftBullet::normalLeftBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());
		break;
	}
}

void normalLeftBullet::normalLeftBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->GetWidth(), _viBullet->img->GetHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}
void normalLeftBullet::deleteNormalLeftBullet(int normalBulletMax)
{
	SAFE_RELEASE(_vBullet[normalBulletMax].img);
	_vBullet.erase(_vBullet.begin() + normalBulletMax);
}

// ========================================================================================================= [엑스 차지 레벨1 오른쪽]

chargeRightBullet::chargeRightBullet()
{
}

chargeRightBullet::~chargeRightBullet()
{
}

HRESULT chargeRightBullet::init(int chargeBulletMax, float range)
{
	_range = range;

	for (int i = 0; i < chargeBulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/rockman/shot_s1.bmp", 0, 0, 96, 48, 2, 1, true, RGB(255, 0, 255));
		bullet.speed = 15.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void chargeRightBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void chargeRightBullet::update()
{
	chargeRightBulletMove();
}

void chargeRightBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), 0);

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);

		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->SetFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= 5)
			{
				_viBullet->img->SetFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void chargeRightBullet::chargeRightBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		break;
	}
}

void chargeRightBullet::chargeRightBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void chargeRightBullet::deleteChargeRightBullet(int chargeBulletMax)
{
	SAFE_RELEASE(_vBullet[chargeBulletMax].img);
	_vBullet.erase(_vBullet.begin() + chargeBulletMax);
}

// ========================================================================================================= [엑스 차지 레벨1 왼쪽]

chargeLeftBullet::chargeLeftBullet()
{
}

chargeLeftBullet::~chargeLeftBullet()
{
}

HRESULT chargeLeftBullet::init(int chargeBulletMax, float range)
{
	_range = range;

	for (int i = 0; i < chargeBulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/rockman/shot_s1.bmp", 0, 0, 96, 48, 2, 1, true, RGB(255, 0, 255));
		bullet.speed = 15.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void chargeLeftBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void chargeLeftBullet::update()
{
	chargeLeftBulletMove();
}

void chargeLeftBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), 0);

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);

		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->SetFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= 5)
			{
				_viBullet->img->SetFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void chargeLeftBullet::chargeLeftBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void chargeLeftBullet::chargeLeftBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void chargeLeftBullet::deleteChargeLeftBullet(int chargeBulletMax)
{
	SAFE_RELEASE(_vBullet[chargeBulletMax].img);
	_vBullet.erase(_vBullet.begin() + chargeBulletMax);
}

// ========================================================================================================= [엑스 차지 레벨2 오른쪽]

chargeLv2RightBullet::chargeLv2RightBullet()
{
}

chargeLv2RightBullet::~chargeLv2RightBullet()
{
}

HRESULT chargeLv2RightBullet::init(int chargeLv2BulletMax, float range)
{
	_range = range;

	for (int i = 0; i < chargeLv2BulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/rockman/shot_s1.bmp", 0, 0, 144, 72, 2, 1, true, RGB(255, 0, 255));
		bullet.speed = 15.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void chargeLv2RightBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void chargeLv2RightBullet::update()
{
	chargeLv2RightBulletMove();
}

void chargeLv2RightBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), 0);

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);

		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->SetFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= 5)
			{
				_viBullet->img->SetFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void chargeLv2RightBullet::chargeLv2RightBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void chargeLv2RightBullet::chargeLv2RightBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x += _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void chargeLv2RightBullet::deleteChargeLv2RightBullet(int chargeLv2BulletMax)
{
	SAFE_RELEASE(_vBullet[chargeLv2BulletMax].img);
	_vBullet.erase(_vBullet.begin() + chargeLv2BulletMax);
}

// ========================================================================================================= [엑스 차지 레벨2 왼쪽]

chargeLv2LeftBullet::chargeLv2LeftBullet()
{
}

chargeLv2LeftBullet::~chargeLv2LeftBullet()
{
}

HRESULT chargeLv2LeftBullet::init(int chargeLv2BulletMax, float range)
{
	_range = range;

	for (int i = 0; i < chargeLv2BulletMax; ++i)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(bullet));
		bullet.img = new image;
		bullet.img->init("image/rockman/shot_s1.bmp", 0, 0, 144, 72, 2, 1, true, RGB(255, 0, 255));
		bullet.speed = 15.0f;
		bullet.isFire = false;

		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void chargeLv2LeftBullet::release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_RELEASE(_viBullet->img);
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void chargeLv2LeftBullet::update()
{
	chargeLv2LeftBulletMove();
}

void chargeLv2LeftBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->img->frameRender(getMemDC(),
			_viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), 0);

		if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _viBullet->rc);

		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->SetFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= 5)
			{
				_viBullet->img->SetFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}

void chargeLv2LeftBullet::chargeLv2LeftBulletFire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire) continue;

		_viBullet->isFire = true;
		_viBullet->pos.x = _viBullet->firePos.x = x;
		_viBullet->pos.y = _viBullet->firePos.y = y;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		break;
	}
}

void chargeLv2LeftBullet::chargeLv2LeftBulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;

		_viBullet->pos.x -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->pos.x, _viBullet->pos.y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->firePos.x, _viBullet->firePos.y, _viBullet->pos.x, _viBullet->pos.y))
		{
			_viBullet->isFire = false;
		}
	}
}

void chargeLv2LeftBullet::deleteChargeLv2LeftBullet(int chargeLv2BulletMax)
{
	SAFE_RELEASE(_vBullet[chargeLv2BulletMax].img);
	_vBullet.erase(_vBullet.begin() + chargeLv2BulletMax);
}
