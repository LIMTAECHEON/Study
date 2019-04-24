#include "stdafx.h"
#include "iceman.h"

iceman::iceman()
{
}

iceman::~iceman()
{
}

HRESULT iceman::init()
{
	_bossState = 0;

	_icemanDirection = ICEMANDIRECTION_LEFT_STOP;

	_bossImg = IMAGEMANAGER->addFrameImage("iceman", "iceman.bmp", 0, 0, 2310, 840, 11, 4, true, RGB(255, 0, 255));

	int leftStop[] = { 21 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanLeftStop", "iceman", leftStop, 1, 6, true);
	int leftMove[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanLeftMove", "iceman", leftMove, 10, 5, true);
	int arrLeftJump[] = { 39, 38, 37, 36 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanLeftJump", "iceman", arrLeftJump, 4, 2, false, leftJump, this);
	int arrLeftAttack[] = { 35, 34, 33 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanLeftAttack", "iceman", arrLeftAttack, 3, 3, false, leftFire, this);
	int arrLeftJumpAttack[] = { 35, 34, 33 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanLeftJumpAttack", "iceman", arrLeftJumpAttack, 3, 3, false, leftJumpFire, this);
	int leftDead[] = { 40 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanLeftDead", "iceman", leftDead, 1, 6, true);

	int autoLeftAttack[] = { 35, 34, 33 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanAutoLeftAttack", "iceman", autoLeftAttack, 3, 3, false, leftAutoFire, this);
	
	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanRightStop", "iceman", rightStop, 1, 6, true);
	int rightMove[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("icemanRightMove", "iceman", rightMove, 10, 5, true);

	_pos.x = 570;
	_pos.y = 450;
	_rc = RectMakeCenter(_pos.x, _pos.y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());

	_jump = new jump;
	_jump->init();

	_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftStop");

	_bullet = new bossBullet;
	_bullet->init(100, WINSIZEY);

	_isShot = false;

	_hpBar = new progressBar;
	_hpBar->init(330, 550, 162, 39);
	_currentHP = _maxHP = 100;

	_count = 0;
	_count1 = 0;
	_count2 = 0;
	_motion = 0;
	_motion2 = 0;

	return S_OK;
}

void iceman::release()
{
	SAFE_DELETE(_bullet);
}

void iceman::update()
{
	_count++;
	_count1++;
	_count2++;

	if (_play->getMotion() == 0 &&
		_currentHP >= 0)
	{
		if (_count1 <= 300)
		{
			_state = MOVE01;

			if (_state == MOVE01)
			{
				if (_isShot == true)
				{
					_bullet->bossBulletFire(_pos.x - 50, _pos.y);
				}

				if (_count >= 90)
				{
					_isShot = true;

					_icemanDirection = ICEMANDIRECTION_LEFT_ATTACK;
					_icemanMotion = KEYANIMANAGER->findAnimation("icemanAutoLeftAttack");
					_icemanMotion->start();
				}

				if (_count == 100)
				{
					_count = 0;
					_isShot = false;
				}
			}
		}

		else if (_count1 <= 690)
		{
			_state = MOVE02;

			if (_state == MOVE02)
			{
				if (_isShot == true)
				{
					_bullet->bossBulletFire(_pos.x - 50, _pos.y);
				}

				if (_count >= 80)
				{
					_jump->jumping(&_pos.x, &_pos.y, 5.0f, 0.05f);

					_icemanDirection = ICEMANDIRECTION_LEFT_JUMP;
					_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftJump");
					_icemanMotion->start();
				}

				if (_count == 85)
				{
					_count = 0;
					_isShot = true;

					_icemanDirection = ICEMANDIRECTION_LEFT_ATTACK;
					_icemanMotion = KEYANIMANAGER->findAnimation("icemanAutoLeftAttack");
					_icemanMotion->start();
				}
			}
		}

		if (_count1 == 700)
		{
			_count1 = 0;
			_count = 0;
		}

		if (_motion2 == 1)
		{
			_motion2 = 0;
		}
	}

	if (_play->getMotion() == 1)
	{
		_icemanDirection = ICEMANDIRECTION_LEFT_DEAD;
		_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftDead");
		_icemanMotion->start();
	}

	if (_currentHP <= 0)
	{
		_icemanDirection = ICEMANDIRECTION_LEFT_DEAD;
		_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftDead");
		_icemanMotion->start();
	}

	//if (KEYMANAGER->isOnceKeyDown('A')) 
	//{
	//	_icemanDirection = ICEMANDIRECTION_LEFT_MOVE;
	//	_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftMove");
	//	_icemanMotion->start();
	//}
	//else if (KEYMANAGER->isOnceKeyUp('A'))
	//{
	//	_icemanDirection = ICEMANDIRECTION_LEFT_STOP;
	//	_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftStop");
	//	_icemanMotion->start();
	//}

	//if (KEYMANAGER->isOnceKeyDown('D'))
	//{
	//	_icemanDirection = ICEMANDIRECTION_RIGHT_MOVE;
	//	_icemanMotion = KEYANIMANAGER->findAnimation("icemanRightMove");
	//	_icemanMotion->start();
	//}
	//else if (KEYMANAGER->isOnceKeyUp('D'))
	//{
	//	_icemanDirection = ICEMANDIRECTION_RIGHT_STOP;
	//	_icemanMotion = KEYANIMANAGER->findAnimation("icemanRightStop");
	//	_icemanMotion->start();
	//}

	//if (KEYMANAGER->isOnceKeyDown('W'))
	//{
	//	_jump->jumping(&_pos.x, &_pos.y, 6.0f, 0.1f);
	//	if (_icemanDirection == ICEMANDIRECTION_LEFT_STOP)
	//	{
	//		_icemanDirection = ICEMANDIRECTION_LEFT_JUMP;
	//		_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftJump");
	//		_icemanMotion->start();
	//	}
	//}

	//if (KEYMANAGER->isOnceKeyDown('L'))
	//{
	//	_isShot = true;
	//
	//	if (_icemanDirection == ICEMANDIRECTION_LEFT_JUMP)
	//	{
	//		_icemanDirection = ICEMANDIRECTION_LEFT_JUMP_ATTACK;
	//		_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftJumpAttack");
	//		_icemanMotion->start();
	//	}
	//
	//	if (_icemanDirection == ICEMANDIRECTION_LEFT_STOP)
	//	{
	//		_icemanDirection = ICEMANDIRECTION_LEFT_ATTACK;
	//		_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftAttack");
	//		_icemanMotion->start();
	//	}
	//}

	//for (int i = 0; i < 10; ++i)
	//{
	//	if (_pos.y <= 300)
	//	{
	//		if (_icemanDirection == ICEMANDIRECTION_LEFT_JUMP)
	//		{
	//			_icemanDirection = ICEMANDIRECTION_LEFT_JUMP_ATTACK;
	//			_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftJumpAttack");
	//			_icemanMotion->start();
	//		}
	//	}

	//	if (_pos.y <= 450)
	//	{
	//		if (_icemanDirection == ICEMANDIRECTION_LEFT_JUMP)
	//		{
	//			_icemanDirection = ICEMANDIRECTION_LEFT_JUMP_ATTACK;
	//			_icemanMotion = KEYANIMANAGER->findAnimation("icemanLeftJumpAttack");
	//			_icemanMotion->start();
	//		}
	//	}
	//}
		
	switch (_icemanDirection)
	{
	case ICEMANDIRECTION_RIGHT_MOVE:
		_pos.x += ICEMANSPEED;
		break;

	case ICEMANDIRECTION_LEFT_MOVE: 
		_pos.x -= ICEMANSPEED;
		break;
	}

	_rc = RectMakeCenter(_pos.x, _pos.y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());

	KEYANIMANAGER->update();
	_jump->update();
	_bullet->update();
	collision();

	_hpBar->setX(330);
	_hpBar->setY(510);

	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
}

void iceman::render()
{
	_bossImg->aniRender(getMemDC(), _rc.left, _rc.top, _icemanMotion);
	_bullet->render();
	_hpBar->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		//Rectangle(getMemDC(), _rc);
		Rectangle(getMemDC(), rc);
	}
}

void iceman::collision()
{
	RECT temp;
	rc = RectMake(_play->getRockmanRc().left,
		_play->getRockmanRc().top,
		_play->getPlayImage()->getFrameWidth(),
		_play->getPlayImage()->getFrameHeight());

	for (int i = 0; i < _bullet->getVBossBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &rc, &_bullet->getVBossBullet()[i].rc))
		{
			//_bullet->deleteBossBullet(i);
			//_motion2 = 1;
			break;
		}
	}
}

void iceman::hitDamage(float damage)
{
	_currentHP -= damage;
}

void iceman::leftFire(void * obj)
{
	iceman* i = (iceman*)obj;

	i->setIceManDirection(ICEMANDIRECTION_LEFT_STOP);
	i->setIceManMotion(KEYANIMANAGER->findAnimation("icemanLeftStop"));
	i->getIceManMotion()->start();
}

void iceman::leftJump(void * obj)
{
	iceman* i = (iceman*)obj;

	i->setIceManDirection(ICEMANDIRECTION_LEFT_STOP);
	i->setIceManMotion(KEYANIMANAGER->findAnimation("icemanLeftStop"));
	i->getIceManMotion()->start();
}

void iceman::leftJumpFire(void * obj)
{
	iceman* i = (iceman*)obj;

	i->setIceManDirection(ICEMANDIRECTION_LEFT_STOP);
	i->setIceManMotion(KEYANIMANAGER->findAnimation("icemanLeftStop"));
	i->getIceManMotion()->start();
}

void iceman::leftAutoFire(void * obj)
{
	iceman* i = (iceman*)obj;

	i->setIceManDirection(ICEMANDIRECTION_LEFT_STOP);
	i->setIceManMotion(KEYANIMANAGER->findAnimation("icemanLeftStop"));
	i->getIceManMotion()->start();
}
