#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "enemyManager.h"
#include "rockman.h"		// PlayGround/rockman
#include "pengdori.h"

class stageMap: public gameNode
{
private:

	image* _map;			// 게임 전체 맵 이미지
	image* _pixMap;			// 게임 전체 맵 픽셀충돌 체크 이미지

	image* _mapZ;
	RECT _mapZRc;
	POINTFLOAT _mapZPos;
	
	image* _doorImg;		// 팽도리 첫번째 방문 이미지
	RECT _doorRc;			// 팽도리 첫번째 방문 RECT
	POINTFLOAT _doorPos;	// 팽도리 첫번째 방문 POINT 좌표

	image* _door2Img;
	RECT _door2Rc;			// 팽도리 두번째 방문 RECT
	POINTFLOAT _door2Pos;	// 팽도리 두번째 방문 POINT 좌표

	bool _isOpen = false;	// 첫번째 방문 BOOL 변수
	bool _isOpen2 = false;	// 두번째 방문 BOOL 변수

	rockman* _rockman;		// rockman 클래스
	pengdori* _boss;		// pengdori 클래스
	enemyManager* _enemy;	// enemyManager 클래스
	
	RECT _readyRc;			// READY 글자 RECT
	POINT _readyPos;		// READY 글자 POINT 좌표
	image* _readyImg;		// READY 글자 이미지

	int _count = 0;			// READY 글자 프레임 변수(속도조절)
	int _index = 0;			// READY 글자 프레임 변수(프레임출력)
	bool _readyHUDCount;	// READY 글자 출력 제한 BOOL 변수

	int _count2 = 0;		// DOOR1 프레임 변수(속도조절)
	int _index2 = 0;		// DOOR1 글자 프레임 변수(프레임출력)

	int _count3 = 0;		// DOOR2 글자 프레임 변수(속도조절)
	int _index3 = 0;		// DOOR2 글자 프레임 변수(프레임출력)

	float _playerX;			// rockman 클래스 X축 좌표 저장을 위한 변수
	float _playerY;			// rockman 클래스 Y축 좌표 저장을 위한 변수

	float _cameraX;			// 카메라 시점 X축 좌표
	float _cameraY;			// 카메라 시점 Y축 좌표
	bool _cameraStop;		// 팽도리 카메라 제한 BOOL 변수

public:

	stageMap();
	~stageMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();	// 이미지 좌표 셋팅 함수
	void stageMapDynamic();	// 동적 할당 함수
	void bossRoomLimit();	// 팽도리 방 카메라 제한 함수
	void cameraSet();		// 카메라 셋팅(get/set) 함수
	void imageSetFrame();	// READY 이미지 프레임

	// rockman 클래스 카메라 좌표를 받기 위한 좌표 값 함수 선언
	// rockman 클래스 등장 이미지 출력을 제어하기 위한 index 값 함수 선언
	float getCameraX() { return _cameraX;}
	float getCameraY() { return _cameraY;}
	int getIndex() { return _index; }
};

