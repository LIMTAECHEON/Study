#include "stdafx.h"0
#include "enemy.h"

enemy::enemy(){}
enemy::~enemy(){}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	enemyImageManager();									// 이미지 매니저 함수

	_enemy.speed = ENEMY_SPEED;
	_enemy.speedFast = ENEMY_FAST_SPEED;

	_enemy.pos.x = position.x;								// 에너미 매니저에서 X축 좌표와 Y축 좌표를 설정
	_enemy.pos.y = position.y;

	_enemy.imageName = IMAGEMANAGER->findImage(imageName);	// 에너미 매니저에서 에너미의 이미지를 설정

	_rndFireCount = ENEMY_FIRE_RANDOM;						// 무작위 정수값 함수

	_enemy.rc = RectMakeCenter(position.x, position.y,
		_enemy.imageName->getFrameWidth(), _enemy.imageName->getFrameHeight());

	_bullet = new bullet;
	
	return S_OK;
}

void enemy::release()
{
	SAFE_DELETE(_bullet);
}

void enemy::update(float cameraX, float cameraY)
{
	_cameraX = cameraX;
	_cameraY = cameraY;

	imageSetFrame();											// 에너미 움직임 이미지 프레임
	enemySet();													// 에너미 움직임 셋팅 함수

	_enemy.rc = RectMakeCenter(_enemy.pos.x - _cameraX, _enemy.pos.y - _cameraY,
		_enemy.imageName->getFrameWidth(), _enemy.imageName->getFrameHeight());
}

void enemy::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _enemy.rc);
	_enemy.imageName->frameRender(getMemDC(), _enemy.rc.left, _enemy.rc.top, _currentFrameX, _currentFrameY);
}

void enemy::enemyImageManager()
{
	IMAGEMANAGER->addFrameImage("Bee", "image/enemy/enemy_bee.bmp", 0, 0, 405, 135, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Drop", "image/enemy/enemy_drop.bmp", 0, 0, 465, 96, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Snow", "image/enemy/enemy_snow.bmp", 0, 0, 945, 174, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Bat", "image/enemy/enemy_bat.bmp", 0, 0, 492, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Gong", "image/enemy/enemy_gong.bmp", 0, 0, 333, 111, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Turret", "image/enemy/enemy_turret.bmp", 0, 0, 384, 75, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Turret2", "image/enemy/enemy_turretL.bmp", 0, 0, 384, 75, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TurretM", "image/enemy/enemy_turretM.bmp", 0, 0, 69, 96, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TurretM2", "image/enemy/enemy_turretML.bmp", 0, 0, 69, 96, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("snow_Bullet", "image/enemy/enemy_bu02.bmp", 24, 24, true, RGB(255, 0, 255));
}

void enemy::imageSetFrame()
{
	// typeEnemy enum문에 맞춰 에너미의 프레임을 다르게 준다

	if (_state == ENEMY01 ||
		_state == ENEMY10 || _state == ENEMY11 ||
		_state == ENEMY12 || _state == ENEMY13)
	{
		_count++;
		if (_count % ENEMY_IMAGE_SPEED_01 == 0)
		{
			_currentFrameX++;
			_enemy.imageName->SetFrameX(_currentFrameX);
			if (_currentFrameX >= _enemy.imageName->getMaxFrameX()) _currentFrameX = 0;
			_count = 0;
		}
	}

	if (_state == ENEMY02 || _state == ENEMY03 || _state == ENEMY04 ||
		_state == ENEMY05 ||
		_state == ENEMY06 || _state == ENEMY07 || _state == ENEMY08 || _state == ENEMY09 ||
		_state == ENEMY14 || _state == ENEMY15)
	{
		_count++;
		if (_count % ENEMY_IMAGE_SPEED_02 == 0)
		{
			_currentFrameX++;
			_enemy.imageName->SetFrameX(_currentFrameX);
			if (_currentFrameX >= _enemy.imageName->getMaxFrameX()) _currentFrameX = 0;
			_count = 0;
		}
	}
}

void enemy::enemySet()
{
	// typeEnemy enum문에 맞춰 에너미의 움직임을 다르게 준다
	// 일정 이상 좌표까지 움직이면 반대로 값을 빼거나 더해서 반복적인 움직임을 준다
	// ENEMY06, 07, 08, 09는 angle 값을 개별로 받아 cosf, sinf 식에 맞춰 한 장소에서 회전하듯이 움직인다.

	if (_state == ENEMY01)
	{
		_enemy.pos.x -= _enemy.speed;
	} 

	if (_state == ENEMY02)
	{
		_enemy.pos.y += _enemy.speed;

		if (_enemy.pos.y <= ENEMY02_Y_UP_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
		if (_enemy.pos.y >= ENEMY02_Y_DOWN_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
	}

	if (_state == ENEMY03)
	{
		_enemy.pos.y += _enemy.speed;

		if (_enemy.pos.y <= ENEMY03_Y_UP_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
		if (_enemy.pos.y >= ENEMY03_Y_DOWN_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
	}

	if (_state == ENEMY04)
	{
		_enemy.pos.y -= _enemy.speed;

		if (_enemy.pos.y <= ENEMY03_Y_UP_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
		if (_enemy.pos.y >= ENEMY03_Y_DOWN_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
	}

	if (_state == ENEMY06)
	{
		_enemy.angle -= ENEMY_ANGLE;
		_enemy.pos.x = ENEMY06_X;
		_enemy.pos.y = ENEMY06_Y;
	}

	if (_state == ENEMY07)
	{
		_enemy.angle -= ENEMY_ANGLE;
		_enemy.pos.x = ENEMY07_X;
		_enemy.pos.y = ENEMY07_Y;
	}

	if (_state == ENEMY08)
	{
		_enemy.angle -= ENEMY_ANGLE;
		_enemy.pos.x = ENEMY08_X;
		_enemy.pos.y = ENEMY08_Y;
	}

	if (_state == ENEMY09)
	{
		_enemy.angle -= ENEMY_ANGLE;
		_enemy.pos.x = ENEMY09_X;
		_enemy.pos.y = ENEMY09_Y;
	}

	if (_state == ENEMY10)
	{
		_enemy.pos.x -= _enemy.speedFast;

		if (_enemy.pos.x <= ENEMY10_11_Y_UP_LIMIT)
		{
			_enemy.speedFast *= ENEMY_SPEED_MINUS;
		}
		if (_enemy.pos.x >= ENEMY10_11_Y_DOWN_LIMIT)
		{
			_enemy.speedFast *= ENEMY_SPEED_MINUS;
		}
	}

	if (_state == ENEMY11)
	{
		_enemy.pos.x -= _enemy.speedFast;

		if (_enemy.pos.x <= ENEMY10_11_Y_UP_LIMIT)
		{
			_enemy.speedFast *= ENEMY_SPEED_MINUS;
		}
		if (_enemy.pos.x >= ENEMY10_11_Y_DOWN_LIMIT)
		{
			_enemy.speedFast *= ENEMY_SPEED_MINUS;
		}
	}

	if (_state == ENEMY14)
	{
		_enemy.pos.y -= _enemy.speed;

		if (_enemy.pos.y <= ENEMY14_Y_UP_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
		if (_enemy.pos.y >= ENEMY14_Y_DOWN_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
	}

	if (_state == ENEMY15)
	{
		_enemy.pos.y -= _enemy.speed;

		if (_enemy.pos.y <= ENEMY15_Y_UP_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
		if (_enemy.pos.y >= ENEMY15_Y_DOWN_LIMIT)
		{
			_enemy.speed *= ENEMY_SPEED_MINUS;
		}
	}
}

bool enemy::enemyFire()
{
	return false;
}

void enemy::setType(int type)
{
	_state = (typeEnemy)type;
}