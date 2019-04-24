#include "stdafx.h"
#include "enemyManager.h"
#include "stageMap.h"
#include "bullet.h"
#include "rockman.h"

enemyManager::enemyManager() {}
enemyManager::~enemyManager() {}

HRESULT enemyManager::init()
{
	_boomImg = ENEMY_EXPLOSION_IMAGE;	// 폭파 이펙트 이미지
	_itemImg = ITEM_IMAGE;

	imageInit();						// 이미지 좌표 셋팅 함수
	enemyManagerDynamic();				// 동적 할당 함수

	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_enemy);
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	_motion = 0;
	_enemyShowCount++;

	_bullet->update(_cameraX, _cameraY);
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion) (*_viMinion)->update(_cameraX, _cameraY);

	imageSetFrame();					// 이미지 프레임 함수
	minionBulletFire();					// 에너미 공격 함수
	collision();						// 에너미 공격 엑스 충돌 함수
	setMinion(0);						// enemy 클래스 좌표, 타입 동적 할당 함수
	itmePixelCheck();					// 아이템 픽셀 충돌 함수
	deleteSpinMinion();					// minion 삭제 함수
                                                                	
	_itemProbeY = _itemPos.y + _itemImg->GetHeight() / 2;
	if (_rm->getEnemyDeleteHp() == true) _itemRc = RectMakeCenter(_itemPos.x, _itemPos.y, _itemImg->GetWidth(), _itemImg->GetHeight());
	if (_rm->getEnemyDeleteHp() == false) _itemRc = RectMakeCenter(NULL, NULL, NULL, NULL);
}

void enemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion) (*_viMinion)->render();
	
	_bullet->render();
	if (_rm->getEnemyDelete() == true) _boomImg->frameRender(getMemDC(), (_boomPos.x - 50) - _cameraX, (_boomPos.y - 50) - _cameraY);
	if (_rm->getEnemyDeleteHp() == true) _itemImg->frameRender(getMemDC(), (_itemRc.left + 20) -_cameraX, _itemRc.top -_cameraY);

	// ========== 디버깅
	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	//	char str[128]; // 출력 테스트용 
	//	sprintf_s(str, "[에너미X축]: %f, [아이템X축]: %f, [카운트]: %d", _boomPos.x, _itemPos.x, _enemyShowCount);
	//	TextOut(getMemDC(), 0, 100, str, strlen(str));
	//} 
}

void enemyManager::imageInit()
{
	_itemProbeY = _itemPos.y + _itemImg->GetHeight() / 2;
	_itemRc = RectMakeCenter(_itemPos.x, _itemPos.y, _itemImg->GetWidth(), _itemImg->GetHeight());
	_boomImg->SetFrameY(0);
	_itemImg->SetFrameY(0);
}

void enemyManager::enemyManagerDynamic()
{
	_enemy = new enemy;
	_enemy->init();

	_rm = new rockman;
	_rm->init();

	_bullet = new bullet;
	_bullet->init(BULLET_INIT);
}

void enemyManager::setMinion(int type)
{
	switch (_enemyShowCount)
	{
		case ENEMY_COUNT_01:
		_check01 = true;
		break;

		case ENEMY_COUNT_02:
		_check02 = true;
		break;

		case ENEMY_COUNT_03:
		_check03 = true;
		break;

		case ENEMY_COUNT_04:
		_check04 = true;
		break;

		case ENEMY_COUNT_05:
		_check05 = true;
		break;

		case ENEMY_COUNT_06:
		_check06 = true;
		break;

		case ENEMY_COUNT_07:
		_check07 = true;
		break;
	}

	enemy* enemy;

	if (_check01)
	{
		enemy = new minion;
		enemy->init(ENEMY_INIT_CHECK01);
		enemy->setType(ENEMY01);
		_vMinion.push_back(enemy);

		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK02);
		enemy->setType(ENEMY02);
		_vMinion.push_back(enemy);

		_check01 = false;
	}

	if (_check02)
	{
		enemy = new minion;
		enemy->init(ENEMY_INIT_CHECK03);
		enemy->setType(ENEMY01);
		_vMinion.push_back(enemy);

		enemy = new minion;
		enemy->init(ENEMY_INIT_CHECK04);
		enemy->setType(ENEMY01);
		_vMinion.push_back(enemy);

		_check02 = false;
	}

	if (_check03)
	{
		enemy = new minion3;
		enemy->init(ENEMY_INIT_CHECK05);
		enemy->setType(ENEMY05);
		_vMinion.push_back(enemy);

		_check03 = false;
	}

	if (_check04)
	{
		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK06);
		enemy->setType(ENEMY06);
		_vMinion.push_back(enemy);

		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK07);
		enemy->setType(ENEMY07);
		_vMinion.push_back(enemy);

		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK08);
		enemy->setType(ENEMY08);
		_vMinion.push_back(enemy);

		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK09);
		enemy->setType(ENEMY09);
		_vMinion.push_back(enemy);

		_check04 = false;
	}

	if (_check05)
	{
		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK10);
		enemy->setType(ENEMY10);
		_vMinion.push_back(enemy);

		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK11);
		enemy->setType(ENEMY11);
		_vMinion.push_back(enemy);

		_check05 = false;
	}

	if (_check06)
	{
		enemy = new minion3;
		enemy->init(ENEMY_INIT_CHECK12);
		enemy->setType(ENEMY12);
		_vMinion.push_back(enemy);

		enemy = new minion3;
		enemy->init(ENEMY_INIT_CHECK13);
		enemy->setType(ENEMY14);
		_vMinion.push_back(enemy);

		_check06 = false;
	}

	if (_check07)
	{
		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK14);
		enemy->setType(ENEMY03);
		_vMinion.push_back(enemy);

		enemy = new minion2;
		enemy->init(ENEMY_INIT_CHECK15);
		enemy->setType(ENEMY04);
		_vMinion.push_back(enemy);

		enemy = new minion3;
		enemy->init(ENEMY_INIT_CHECK16);
		enemy->setType(ENEMY13);
		_vMinion.push_back(enemy);

		_check07 = false;
	}
}

void enemyManager::deleteMinion(int enemyNum)
{
	_vMinion.erase(_vMinion.begin() + enemyNum);
}

void enemyManager::imageSetFrame()
{
	_count++;
	if (_count % BOOM_IMAGE_SPEED == 0)
	{
		_index++;
		_boomImg->SetFrameX(_index);
		if (_index >= _boomImg->getMaxFrameX()) _index = 0;
		_count = 0;
	}

	_count2++;
	if (_count2 % ITEM_IMAGE_SPEED == 0)
	{
		_index2++;
		_itemImg->SetFrameX(_index2);
		if (_index2 >= _itemImg->getMaxFrameX()) _index2 = -1;
		_count2 = 0;
	}

	if (_rm->getEnemyDelete() == false) _index = 0;
}

void enemyManager::minionBulletFire()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->enemyFire())
		{
			_bullet->bulletFire((*_viMinion)->getEnemyX() - 10, (*_viMinion)->getEnemyY(),
				getAngle((*_viMinion)->getEnemyX() - 10, (*_viMinion)->getEnemyY(),
					_rm->getPosX(),
					_rm->getPosY()),
				5.0f);
		}
	}
}

void enemyManager::collision()
{
	RECT temp;
	RECT rc = RectMakeCenter(_rm->getPosX(), _rm->getPosY(),
		_rm->getMegaImage()->getFrameWidth(), _rm->getMegaImage()->getFrameHeight());

	for (int i = 0; i < _bullet->getVBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &rc, &_bullet->getVBullet()[i].rc))
		{
			_motion = 1;
			_rm->hitDamage(ATTACK);
			_bullet->deleteBullet(i);
			break;
		}
	}
}

void enemyManager::itmePixelCheck()
{
	if (_rm->getEnemyDeleteHp() == true)
	{
		_itemPos.y += ITME_DROP_SPEED;

		for (int i = _itemProbeY - ITEM_PROBE_Y_UP; i < _itemProbeY + ITEM_PROBE_Y_DOWN; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixmap")->getMemDC(), _itemPos.x, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			// 바닥
			if (PROBE_RGB_RED)
			{
				_itemProbeY = i - _itemImg->GetHeight() / 2;
				_itemPos.y -= ITME_DROP_SPEED;
				break;
			}
		}
	}
}

void enemyManager::posCheck(float x, float y)
{
	_checkX = _boomPos.x = _itemPos.x = x;
	_checkY = _boomPos.y = _itemPos.y = y;
}

void enemyManager::deleteSpinMinion()
{
	for (int i = 0; i < _vMinion.size(); i++)
	{
		if (_vMinion[i]->getEnemyX() <= _rm->getCameraX() - CAMERA_X_MINUS) deleteMinion(i);
		else if (_vMinion[i]->getEnemyX() <= -_vMinion[i]->getImage()->GetHeight()) deleteMinion(i);
	}
}
