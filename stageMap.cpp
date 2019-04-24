#include "stdafx.h"
#include "stageMap.h"

stageMap::stageMap() { }
stageMap::~stageMap() { }

HRESULT stageMap::init()
{
	_map		= GAME_MAP_IMAGE;										// 게임 실제 출력 지도
	_mapZ		= MAP_Z_ORDER_IMAGE;									// 지도 Z-ORDER 부분
	_pixMap		= GAME_PIX_MAP_IMAGE;									// 게임 픽셀 충돌 후면 지도
	_doorImg	= BOSS_ROOM_DOOR_IMAGE;									// 보스 방문 이미지
	_door2Img	= BOSS_ROOM_DOOR2_IMAGE;								// 보스 방문 이미지
	_readyImg	= READY_IMAGE;											// READY 글자 이미지

	imageSetInit();														// 이미지 좌표 셋팅 함수
	stageMapDynamic();													// 동적 할당 함수

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

	_rockman->update();													// rockman 클래스 업데이트
	_boss->update(_cameraX, _cameraY);									// pengdori 클래스 업데이트 (카메라 좌표)
	_enemy->update();													// enemyManager 클래스 업데이트
		
	_cameraX = CAMERA_X;												// 카메라 값은 플레이어의 위치 뺴기 WINSIZE 사이즈 /2(절반) 크기로 선언
	_cameraY = CAMERA_Y;

	bossRoomLimit();													// 팽도리 안방 카메라 제한
	cameraSet();														// 카메라 클래스 연결 함수
	imageSetFrame();													// READY 이미지 프레임
}

void stageMap::render()
{
	// 고정된 지도에 플레이어가 움직이면 카메라 시점이 
	// 플레이어를 따라가게 하는 연출을 위해 지도의 X축과 Y축 렌더를 카메라 좌표로 뺴준다
	 
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

		// 팽도리 등장 카메라
		// 카메라 제한된 값까지 이동하면 카메라 좌표가 멈추고 pengdori 클래스를 render

		if (_cameraX == BOSS_ROOM_CAMERA_X && _cameraY == BOSS_ROOM_CAMERA_Y) _boss->render();
	}
}

void stageMap::imageSetInit()
{
	_mapZPos.x = MAP_Z_ORDER_X;											// Z-ORDER 좌표
	_mapZPos.y = MAP_Z_ORDER_Y;
	_mapZRc = RectMakeCenter(_mapZPos.x, _mapZPos.y, _mapZ->GetWidth(), _mapZ->GetHeight());

	_readyPos.x = READY_HUD_X;											// REDAY 글자 좌표
	_readyPos.y = READY_HUD_Y;
	_readyRc = RectMakeCenter(_readyPos.x, _readyPos.y, _readyImg->GetCenterX(), _readyImg->GetCenterY());

	_doorPos.x = BOSS_DOOR_ONE_X;										// 팽도리 첫번째 방문 좌표
	_doorPos.y = BOSS_DOOR_Y;
	_doorRc = RectMakeCenter(_doorPos.x, _doorPos.y, _doorImg->GetWidth(), _doorImg->GetHeight());

	_door2Pos.x = BOSS_DOOR_TWO_X;										// 팽도리 두번째 방문 좌표
	_door2Pos.y = BOSS_DOOR_Y;
	_door2Rc = RectMakeCenter(_door2Pos.x, _door2Pos.y, _door2Img->GetWidth(), _door2Img->GetHeight());

	_readyImg->SetFrameY(0);											// REDAY 글자 프레임 시작 번호
	_doorImg->SetFrameX(0);												// door1 프레임 시작 번호
	_door2Img->SetFrameX(0);											// door2 프레임 시작 번호
}

void stageMap::stageMapDynamic()
{
	_rockman = new rockman;												// rockman 클래스 동적할당
	_rockman->init();

	_boss = new pengdori;												// pengdori 클래스 동적할당
	_boss->init();

	_enemy = new enemyManager;											// enemyManager 클래스 동적할당
	_enemy->init();
	_enemy->setMinion(0);												// enemy 종류 타입 시작값

	_enemy->setRockmanMemoryAddressLink(_rockman);						// enemy, pengdori, rockman 
	_rockman->setEnemyMemoryAddressLink(_enemy);						

	_boss->setRockmanMemoryAddressLink(_rockman);						// 클래스끼리 서로 연결해주는 어드레스 링크
	_rockman->setPengdoriMemoryAddressLink(_boss);						// 이걸 안해주면 서로 값을 제대로 주고 받지 못해염!
}

void stageMap::bossRoomLimit()
{
	// 화면이 더이상 움직이지 않게 하기 위한 카메라 제한
	// 카메라 좌표가 고정되기 때문에 따로 카메라 값을 render에서 관리하지 않아도 된다

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

	if (_rockman->getMegaRc().right >= _doorRc.left) _isOpen = true;	// rockman RECT의 right가 door RECT의 left보다 크면 true로 값 변경
	if (_rockman->getMegaRc().right >= _door2Rc.left) _isOpen2 = true;
}

void stageMap::cameraSet()
{
	_playerX = _rockman->getMegaRc().left;								// 플레이어의 좌표는 rockman RECT의 left, top으로 선언
	_playerY = _rockman->getMegaRc().top;								// 이는 이미지 렌더를 RECT로 하는 것을 감안하여 계산

	_rockman->setIndex(_index);											// 부모/자식 관계의 클래스가 서로 값을 주고 받기 위해 get/set 함수 선언
	_rockman->setCameraX(_cameraX);
	_rockman->setCameraY(_cameraY);

	_enemy->setCameraX(_cameraX);										// enemy 클래스도 동일하게 get/set 함수 선언
	_enemy->setCameraY(_cameraY);
}

void stageMap::imageSetFrame()
{
	_count++;
	if (_count % READY_HUD_IMAGE_SPEED == 0)
	{
		_readyImg->SetFrameX(_index);
		if (_index <= INDEX_LIMIT) _index++;							// 게임 시작 후 READY 글자 프레임 출력
		if (_index == READY_IMAGE_LIMIT) _readyHUDCount = true;			// 출력이 완료되면 rockman 클래스 렌더
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