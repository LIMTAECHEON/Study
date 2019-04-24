#pragma once

#include "gameNode.h"
#include "enemy.h"
#include "minion.h"
#include "minion2.h"
#include "minion3.h"

class bullet;
class rockman;
class stageMap;

class enemyManager: public gameNode
{
private:

	typedef vector<enemy*>			 vEnemy;		// 에너미 vector
	typedef vector<enemy*>::iterator viEnemy;

private:

	vEnemy _vMinion;								// 기본 미니언 변수
	viEnemy _viMinion;
	
	bullet* _bullet;								// 공격 (공용 총알)

	rockman* _rm;									// rockman 클래스
	enemy* _enemy;									// enemy 클래스

	image* _boomImg;								// 폭파 이미지
	RECT _boomRc;									// 폭파 RECT
	POINTFLOAT _boomPos;							// 폭파 이미지 좌표

	image* _itemImg;								// 아이템 이미지
	RECT _itemRc;									// 아이템 RECT
	POINTFLOAT _itemPos;							// 아이템 이미지 좌표
	float _itemProbeY = 0;							// 아이템 픽셀 충돌 판정 Y축 변수

	int _count = 0;									// 폭파 연출 프레임 변수(속도조절)	
	int _index = 0;									// 폭파 연출 프레임 변수(프레임출력)

	int _count2 = 0;								// 아이템 프레임 변수(속도조절)	
	int _index2 = 0;								// 아이템 프레임 변수(프레임출력)

	int _motion = 0;								// 충돌 처리 확인 변수

	int _enemyShowCount = 0;						// 에너미 등장 카운트

	bool _check01 = false;							// 프레임 저하 방지 에너미 등장 시간 조절 bool 변수
	bool _check02 = false;
	bool _check03 = false;
	bool _check04 = false;
	bool _check05 = false;
	bool _check06 = false;
	bool _check07 = false;

	float _checkX;									// 폭파, 아이템 좌표 저장용 X축 좌표 변수
	float _checkY;									// 폭파, 아이템 좌표 저장용 Y축 좌표 변수

	float _cameraX;									// stageMap _cameraX set 변수
	float _cameraY;									// stageMap _cameraY set 변수

public:

	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageInit();								// 이미지 좌표 셋팅 함수
	void enemyManagerDynamic();						// 동적 할당 함수
	void setMinion(int type);						// enemy 클래스 좌표, 타입 동적 할당 함수
	void deleteMinion(int enemyNum);				// minion 삭제 함수
	void imageSetFrame();							// 이미지 프레임 함수
	void minionBulletFire();						// 에너미 공격 함수
	void collision();								// 에너미 공격 엑스 충돌 함수
	void itmePixelCheck();							// 아이템 픽셀 충돌 함수
	void posCheck(float x, float y);				// 폭파 연출, 아이템 좌표 함수
	void deleteSpinMinion();						// 에너미 삭제 함수

	// enemyManager 변수&함수를 다른 클래스에서 사용하기 위한 get 함수
	 
	int getMotion() { return _motion; }
	enemy* getEnemy() { return _enemy; }
	RECT getItemRc() { return _itemRc; }
	
	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getVIMinion() { return _viMinion; }

	// 상위 클래스(stageMap) Set 함수 

	void setCameraX(float cameraX) { _cameraX = cameraX; }
	void setCameraY(float cameraY) { _cameraY = cameraY; }

	// rockman 클래스를 이어주는 어드레스 링크 함수

	void setRockmanMemoryAddressLink(rockman* player) { _rm = player; }
};

