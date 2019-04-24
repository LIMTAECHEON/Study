#include "stdafx.h"
#include "stageMap.h"

stageMap::stageMap() { }
stageMap::~stageMap() { }

HRESULT stageMap::init()
{
	_map		= GAME_MAP_IMAGE;										// ���� ���� ��� ����
	_mapZ		= MAP_Z_ORDER_IMAGE;									// ���� Z-ORDER �κ�
	_pixMap		= GAME_PIX_MAP_IMAGE;									// ���� �ȼ� �浹 �ĸ� ����
	_doorImg	= BOSS_ROOM_DOOR_IMAGE;									// ���� �湮 �̹���
	_door2Img	= BOSS_ROOM_DOOR2_IMAGE;								// ���� �湮 �̹���
	_readyImg	= READY_IMAGE;											// READY ���� �̹���

	imageSetInit();														// �̹��� ��ǥ ���� �Լ�
	stageMapDynamic();													// ���� �Ҵ� �Լ�

	return S_OK;
}

void stageMap::release()
{
	SAFE_DELETE(_rockman);						
	SAFE_DELETE(_boss);
	SAFE_DELETE(_enemy);
}

void stageMap::update()
{
	KEYANIMANAGER->update();

	_rockman->update();													// rockman Ŭ���� ������Ʈ
	_boss->update(_cameraX, _cameraY);									// pengdori Ŭ���� ������Ʈ (ī�޶� ��ǥ)
	_enemy->update();													// enemyManager Ŭ���� ������Ʈ
		
	_cameraX = CAMERA_X;												// ī�޶� ���� �÷��̾��� ��ġ ���� WINSIZE ������ /2(����) ũ��� ����
	_cameraY = CAMERA_Y;

	bossRoomLimit();													// �ص��� �ȹ� ī�޶� ����
	cameraSet();														// ī�޶� Ŭ���� ���� �Լ�
	imageSetFrame();													// READY �̹��� ������
}

void stageMap::render()
{
	// ������ ������ �÷��̾ �����̸� ī�޶� ������ 
	// �÷��̾ ���󰡰� �ϴ� ������ ���� ������ X��� Y�� ������ ī�޶� ��ǥ�� ���ش�
	 
	_map->render(getMemDC(), -_cameraX, -_cameraY);	
	if (KEYMANAGER->isToggleKey(VK_TAB)) _pixMap->render(getMemDC(), -_cameraX, -_cameraY);
	if (!_readyHUDCount) _readyImg->frameRender(getMemDC(), _readyRc.left, _readyRc.top);

	if (_readyHUDCount)
	{
		_enemy->render();
		_rockman->render();
		_mapZ->render(getMemDC(), _mapZRc.left - _cameraX, _mapZRc.top - _cameraY);

		_doorImg->frameRender(getMemDC(), _doorRc.left - _cameraX, _doorRc.top - _cameraY);
		_door2Img->frameRender(getMemDC(), _door2Rc.left - _cameraX, _door2Rc.top - _cameraY);

		// �ص��� ���� ī�޶�
		// ī�޶� ���ѵ� ������ �̵��ϸ� ī�޶� ��ǥ�� ���߰� pengdori Ŭ������ render

		if (_cameraX == BOSS_ROOM_CAMERA_X && _cameraY == BOSS_ROOM_CAMERA_Y) _boss->render();
	}
}

void stageMap::imageSetInit()
{
	_mapZPos.x = MAP_Z_ORDER_X;											// Z-ORDER ��ǥ
	_mapZPos.y = MAP_Z_ORDER_Y;
	_mapZRc = RectMakeCenter(_mapZPos.x, _mapZPos.y, _mapZ->GetWidth(), _mapZ->GetHeight());

	_readyPos.x = READY_HUD_X;											// REDAY ���� ��ǥ
	_readyPos.y = READY_HUD_Y;
	_readyRc = RectMakeCenter(_readyPos.x, _readyPos.y, _readyImg->GetCenterX(), _readyImg->GetCenterY());

	_doorPos.x = BOSS_DOOR_ONE_X;										// �ص��� ù��° �湮 ��ǥ
	_doorPos.y = BOSS_DOOR_Y;
	_doorRc = RectMakeCenter(_doorPos.x, _doorPos.y, _doorImg->GetWidth(), _doorImg->GetHeight());

	_door2Pos.x = BOSS_DOOR_TWO_X;										// �ص��� �ι�° �湮 ��ǥ
	_door2Pos.y = BOSS_DOOR_Y;
	_door2Rc = RectMakeCenter(_door2Pos.x, _door2Pos.y, _door2Img->GetWidth(), _door2Img->GetHeight());

	_readyImg->SetFrameY(0);											// REDAY ���� ������ ���� ��ȣ
	_doorImg->SetFrameX(0);												// door1 ������ ���� ��ȣ
	_door2Img->SetFrameX(0);											// door2 ������ ���� ��ȣ
}

void stageMap::stageMapDynamic()
{
	_rockman = new rockman;												// rockman Ŭ���� �����Ҵ�
	_rockman->init();

	_boss = new pengdori;												// pengdori Ŭ���� �����Ҵ�
	_boss->init();

	_enemy = new enemyManager;											// enemyManager Ŭ���� �����Ҵ�
	_enemy->init();
	_enemy->setMinion(0);												// enemy ���� Ÿ�� ���۰�

	_enemy->setRockmanMemoryAddressLink(_rockman);						// enemy, pengdori, rockman 
	_rockman->setEnemyMemoryAddressLink(_enemy);						

	_boss->setRockmanMemoryAddressLink(_rockman);						// Ŭ�������� ���� �������ִ� ��巹�� ��ũ
	_rockman->setPengdoriMemoryAddressLink(_boss);						// �̰� �����ָ� ���� ���� ����� �ְ� ���� ���ؿ�!
}

void stageMap::bossRoomLimit()
{
	// ȭ���� ���̻� �������� �ʰ� �ϱ� ���� ī�޶� ����
	// ī�޶� ��ǥ�� �����Ǳ� ������ ���� ī�޶� ���� render���� �������� �ʾƵ� �ȴ�

	if (_cameraX > BOSS_ROOM_CAMERA_X)
	{
		_cameraX = BOSS_ROOM_CAMERA_X;
		_cameraY = BOSS_ROOM_CAMERA_Y;
		_cameraStop = true;
	}

	if (_cameraStop == true)
	{
		if (_cameraX < BOSS_ROOM_CAMERA_X_STOP)
		{
			_cameraX = BOSS_ROOM_CAMERA_X;
			_cameraY = BOSS_ROOM_CAMERA_Y;
		}
	}

	if (_rockman->getMegaRc().right >= _doorRc.left) _isOpen = true;	// rockman RECT�� right�� door RECT�� left���� ũ�� true�� �� ����
	if (_rockman->getMegaRc().right >= _door2Rc.left) _isOpen2 = true;
}

void stageMap::cameraSet()
{
	_playerX = _rockman->getMegaRc().left;								// �÷��̾��� ��ǥ�� rockman RECT�� left, top���� ����
	_playerY = _rockman->getMegaRc().top;								// �̴� �̹��� ������ RECT�� �ϴ� ���� �����Ͽ� ���

	_rockman->setIndex(_index);											// �θ�/�ڽ� ������ Ŭ������ ���� ���� �ְ� �ޱ� ���� get/set �Լ� ����
	_rockman->setCameraX(_cameraX);
	_rockman->setCameraY(_cameraY);

	_enemy->setCameraX(_cameraX);										// enemy Ŭ������ �����ϰ� get/set �Լ� ����
	_enemy->setCameraY(_cameraY);
}

void stageMap::imageSetFrame()
{
	_count++;
	if (_count % READY_HUD_IMAGE_SPEED == 0)
	{
		_readyImg->SetFrameX(_index);
		if (_index <= INDEX_LIMIT) _index++;							// ���� ���� �� READY ���� ������ ���
		if (_index == READY_IMAGE_LIMIT) _readyHUDCount = true;			// ����� �Ϸ�Ǹ� rockman Ŭ���� ����
		_count = 0;
	}

	if (_isOpen)
	{
		_count2++;
		if (_count2 % DOOR_IMAGE_SPEED == 0)
		{
			_index2++;
			_doorImg->SetFrameX(_index2);
			if (_index2 >= _doorImg->getMaxFrameX()) _index2 = 4;
			_count2 = 0;
		}
	}

	if (_isOpen2)
	{
		_count3++;
		if (_count3 % DOOR_IMAGE_SPEED == 0)
		{
			_index3++;
			_door2Img->SetFrameX(_index3);
			if (_index3 >= _door2Img->getMaxFrameX()) _index3 = 4;
			_count3 = 0;
		}

		if (_cameraStop) _index3 = -1;
	}
}