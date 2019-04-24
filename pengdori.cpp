#include "stdafx.h"
#include "pengdori.h"

pengdori::pengdori() {}
pengdori::~pengdori() {}

HRESULT pengdori::init() 
{
	_bossImg	= PENGDORI_IMAGE;			// 팽도리 이미지
	_hpHUDImg	= PENGDORI_HP_HUD_IMAGE;	// 팽도리 체력 HUD 이미지
	_cloudImg	= PENGDORI_CLOUD_IMAGE;		// 팽도리 구름 공격 이미지
	_clearImg	= GAMECLEAR_IMAGE;			// 게임 클리어 이미지

	imageInit();							// 이미지 좌표 셋팅 함수
	pengdoriDynamic();						// 동적 할당 함수
	pengdoriMotion();						// 팽도리 모션 함수

	return S_OK;
}

void pengdori::release()
{
	SAFE_DELETE(_bullet);
}

void pengdori::update(float cameraX, float cameraY)
{
	_rmMotion = 0;

	_cameraX = cameraX;
	_cameraY = cameraY;

	_bullet->update(_cameraX, _cameraY);
	_bullet2->update(_cameraX, _cameraY);
	_bullet3->update(_cameraX, _cameraY);
	_bullet4->update(_cameraX, _cameraY);

	pengdoriPattern();
	pengdoriSpeedSwitch();
	collision();
	hpSet();

	_bossRc = RectMakeCenter(_pos.x, _pos.y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	_cloudRc = RectMakeCenter(_cPos.x, _cPos.y, _cloudImg->getFrameWidth(), _cloudImg->getFrameHeight());
}

void pengdori::render()
{
	if (_currentHP >= 1)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left - _cameraX, _bossRc.top - _cameraY, _pengdoriMotion);
		_hpHUDImg->render(getMemDC(), _hpHUDRc.left, _hpHUDRc.top);
		_hpBar->render();

		if (_count >= CLOUD_RENDER_LIMIT)
		{
			_cloudImg->frameRender(getMemDC(), _cloudRc.left - _cameraX, _cloudRc.top - _cameraY, _currentFrameX, _currentFrameY);
			_cloudImg->frameRender(getMemDC(), _cloud3Rc.left - _cameraX, _cloud3Rc.top - _cameraY, _currentFrameX, _currentFrameY);
		}

		_bullet->render();
		_bullet2->render();
		_bullet3->render();
		_bullet4->render();
	}

	if (_currentHP <= 0)
	{
		_count = 0;
		_clearImg->render(getMemDC());
	}
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		char str[128]; // 출력 테스트용 
		sprintf_s(str, "[팽도리X축]: %f, [팽도리Y축]: %f, [보스모션]: %d", _pos.x, _pos.y, _count);
		TextOut(getMemDC(), 0, 120, str, strlen(str));
	}
}

void pengdori::pengdoriMotion()
{
	_pengdoriDirection = PENGDORI_LEFT_STOP;

	int leftStop[] = KEYANI_PENGDORI_LEFT_STOP;
	KEYANIMANAGER->addArrayFrameAnimation("pengdoriLeftStop", "pengdori", leftStop, 1, 5, true);
	int leftStay[] = KEYANI_PENGDORI_LEFT_STAY;
	KEYANIMANAGER->addArrayFrameAnimation("pengdoriLeftStay", "pengdori", leftStay, 4, 5, true);
	int leftHit[] = KEYANI_PENGDORI_LEFT_HIT;
	KEYANIMANAGER->addArrayFrameAnimation("pengdoriLeftHit", "pengdori", leftHit, 1, 5, true);
	int arrLeftAttack[] = KEYANI_PENGDORI_LEFT_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("pengdoriLeftAttack", "pengdori", arrLeftAttack, 2, 5, false, leftAttack, this);
	int leftGoodBoy[] = KEYANI_PENGDORI_LEFT_GOODBOY;
	KEYANIMANAGER->addArrayFrameAnimation("pengdoriLeftGoodBoy", "pengdori", leftGoodBoy, 1, 5, true);
	int rightGoodBoy[] = KEYANI_PENGDORI_RIGHT_GOODBOY;
	KEYANIMANAGER->addArrayFrameAnimation("pengdoriRightGoodBoy", "pengdori", rightGoodBoy, 1, 5, true);

	_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftStop");
}

void pengdori::imageInit()
{
	_pos.x = PENGDORI_X;
	_pos.y = PENGDORI_Y;
	_bossRc = RectMakeCenter(_pos.x, _pos.y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());

	_hpHUDX = PENGDORI_HP_HUD_X;
	_hpHUDY = PENGDORI_HP_HUD_Y;
	_hpHUDRc = RectMakeCenter(_hpHUDX, _hpHUDY, _hpHUDImg->GetWidth(), _hpHUDImg->GetHeight());

	_cPos.x = CLOUD_ONE_X;
	_cPos.y = CLOUD_Y;
	_cloudRc = RectMakeCenter(_cPos.x, _cPos.y, _cloudImg->getFrameWidth(), _cloudImg->getFrameHeight());

	_cPos3.x = CLOUD_TWO_X;
	_cPos3.y = CLOUD_Y;
	_cloud3Rc = RectMakeCenter(_cPos3.x, _cPos3.y, _cloudImg->getFrameWidth(), _cloudImg->getFrameHeight());
}

void pengdori::pengdoriDynamic()
{
	_hpBar = new progressBar;
	_hpBar->init(PENGDORI_HP_INIT);
	_currentHP = _maxHP = HP;

	_bullet = new bossBullet;
	_bullet->init(PENGDORI_BULLET_RANGE_INIT);

	_bullet2 = new bossBullet2;
	_bullet2->init(PENGDORI_BULLET_RANGE_INIT);

	_bullet3 = new bossBullet3;
	_bullet3->init(PENGDORI_CLOUD_BULLET_RANGE_INIT);

	_bullet4 = new bossBullet4;
	_bullet4->init(PENGDORI_CLOUD_BULLET_RANGE_INIT);
}

void pengdori::pengdoriSpeedSwitch()
{
	switch (_pengdoriDirection)
	{
	case PENGDORI_RIGHT_GOODBOY:
		_pos.x += PENGDORI_SPEED;

		if (_pos.x >= PENGDORI_LEFT_GOODBOY_STOP_LIMIT)
		{
			_pengdoriDirection = PENGDORI_LEFT_GOODBOY;
			_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftGoodBoy");
			_pengdoriMotion->start();
		}
		break;

	case PENGDORI_LEFT_GOODBOY:
		_pos.x -= PENGDORI_SPEED;

		if (_pos.x <= PENGDORI_RIGHT_GOODBOY_STOP_LIMIT)
		{
			_pengdoriDirection = PENGDORI_RIGHT_GOODBOY;
			_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriRightGoodBoy");
			_pengdoriMotion->start();
		}
		break;
	}
}

void pengdori::hpSet()
{
	_hpBar->setX(PENGDORI_HP_BAR_X);
	_hpBar->setY(PENGDORI_HP_BAR_Y);

	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
}

void pengdori::collision()
{
	RECT temp;
	RECT rc = RectMake(_rm->getMegaRc().left,
		_rm->getMegaRc().top,
		_rm->getMegaImage()->getFrameWidth(),
		_rm->getMegaImage()->getFrameHeight());

	for (int i = 0; i < _bullet->getVBossBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &_bullet->getVBossBullet()[i].rc, &rc))
		{
			_bullet->deleteBossBullet(i);
			_rm->hitDamage(ATTACK);
			_rmMotion = 1;
			break;
		}
	}

	for (int i = 0; i < _bullet3->getVBossBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &_bullet3->getVBossBullet()[i].rc, &rc))
		{
			_bullet3->deleteBossBullet3(i);
			_rm->hitDamage(ATTACK);
			_rmMotion = 1;
			break;
		}
	}

	for (int i = 0; i < _bullet4->getVBossBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &_bullet4->getVBossBullet()[i].rc, &rc))
		{
			_bullet4->deleteBossBullet4(i);
			_rm->hitDamage(ATTACK);
			_rmMotion = 1;
			break;
		}
	}

	for (int i = 0; i < _bullet2->getVBossBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &_bullet2->getVBossBullet()[i].rc, &rc))
		{
			_bullet2->deleteBossBullet2(i);
			_rm->hitDamage(ATTACK_SP);
			_rmMotion = 1;
			break;
		}
	}
}

void pengdori::hitDamage(float damage)
{
	_currentHP -= damage;
}

void pengdori::pengdoriPattern()
{
	if (_cameraX == BOSS_ROOM_CAMERA_X && _cameraY == BOSS_ROOM_CAMERA_Y) _count++;

	if (_rm->getMotion() == 1)
	{
		_pengdoriDirection = PENGDORI_LEFT_HIT;
		_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftHit");
		_pengdoriMotion->start();
		_isHitOn = true;
	}

	if (_isHitOn) _hitCheck++;

	if (_hitCheck >= HIT_MOSTION_LIMIT)
	{
		_pengdoriDirection = PENGDORI_LEFT_STOP;
		_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftStop");
		_pengdoriMotion->start();

		_hitCheck = 0;
		_isHitOn = false;
	}

	if (_count == PENGDORI_COUNT_MOTION01)
	{
		_bullet->bossBulletFire(_bossRc.left - 20, _bossRc.top + 50);

		_pengdoriDirection = PENGDORI_LEFT_ATTACK;
		_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftAttack");
		_pengdoriMotion->start();
	}

	if (_count == PENGDORI_COUNT_MOTION02)
	{
		_bullet->bossBulletFire(_bossRc.left - 20, _bossRc.top + 50);

		_pengdoriDirection = PENGDORI_LEFT_ATTACK;
		_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftAttack");
		_pengdoriMotion->start();
	}

	if (_count == PENGDORI_COUNT_MOTION03)
	{
		_bullet2->bossBullet2Fire(_bossRc.left - 20, _bossRc.top + 50);

		_pengdoriDirection = PENGDORI_LEFT_ATTACK;
		_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftAttack");
		_pengdoriMotion->start();
	}

	if (_count == PENGDORI_COUNT_MOTION04)
	{
		_pengdoriDirection = PENGDORI_LEFT_GOODBOY;
		_pengdoriMotion = KEYANIMANAGER->findAnimation("pengdoriLeftGoodBoy");
		_pengdoriMotion->start();

	}

	if (_count >= PENGDORI_COUNT_MOTION04)
	{
		_bullet3->bossBullet3Fire(_cloudRc.left + 85, _cloudRc.top + 50);
		_bullet4->bossBullet4Fire(_cloud3Rc.left + 85, _cloud3Rc.top + 50);

		if (_state == CLOUD)
		{
			_countFrame++;
			if (_countFrame % PENGDORI_CLOUD_IMAGE_SPEED == 0)
			{
				_currentFrameX++;
				_cloudImg->SetFrameX(_currentFrameX);
				if (_currentFrameX >= _cloudImg->getMaxFrameX()) _currentFrameX = 0;
				_countFrame = 0;
			}
		}
	}

	if (_count == PENGDORI_COUNT_MOTION05) _count = 0;
}

void pengdori::leftAttack(void * obj)
{
	pengdori* p = (pengdori*)obj;

	p->setPengdoriDirection(PENGDORI_LEFT_STOP);
	p->setPengdoriMotion(KEYANIMANAGER->findAnimation("pengdoriLeftStop"));
	p->getPengdoriMotion()->start();
}
