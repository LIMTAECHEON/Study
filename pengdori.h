#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "stageMap.h"
#include "rockman.h"
#include "bullet.h"
#include "progressBar.h"

enum PENGDORIDIRECTION
{
	PENGDORI_LEFT_STOP,
	PENGDORI_LEFT_STAY,
	PENGDORI_LEFT_HIT,
	PENGDORI_LEFT_GOODBOY,
	PENGDORI_RIGHT_GOODBOY,
	PENGDORI_LEFT_ATTACK,
};

enum CLOUD_IMAGE
{
	CLOUD,
};

class pengdori: public gameNode
{
private:
	PENGDORIDIRECTION _pengdoriDirection;
	animation* _pengdoriMotion;

	CLOUD_IMAGE _state;

	image* _bossImg;
	RECT _bossRc;
	POINTFLOAT _pos;

	image* _cloudImg;
	RECT _cloudRc;
	POINTFLOAT _cPos;

	RECT _cloud3Rc;
	POINTFLOAT _cPos3;

	bool _test = false;

	rockman* _rm;
	bool _isHitOn = false;
	int _hitCheck = 0;
	int _rmMotion = 0;

	bossBullet* _bullet;
	bossBullet2* _bullet2;
	bossBullet3* _bullet3;
	bossBullet4* _bullet4;

	image* _hpHUDImg;
	RECT _hpHUDRc;
	float _hpHUDX, _hpHUDY;
	progressBar* _hpBar;
	float _currentHP, _maxHP;

	image* _clearImg;

	float _cameraX;
	float _cameraY;

	int _count = 0;

	float _currentFrameX, _currentFrameY = 0;
	int _countFrame = 0;

public:
	pengdori();
	~pengdori();

	HRESULT init();
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void pengdoriMotion();
	void imageInit();
	void pengdoriDynamic();				// 동적 할당 함수
	void pengdoriSpeedSwitch();			// 팽도리 모션 속도 제어 switch문 함수
	void hpSet();
	void collision();
	void hitDamage(float damage);
	void pengdoriPattern();

	static void leftAttack(void* obj);

	RECT getPengdoriRc() { return _bossRc; }
	image* getPengdoriImage() { return _bossImg; }
	int getMotion() { return _rmMotion; }

	// 팽도리 상태 접근자 설정자
	PENGDORIDIRECTION getPengdoriDirection() { return _pengdoriDirection; }
	void setPengdoriDirection(PENGDORIDIRECTION direction) { _pengdoriDirection = direction; }

	// 팽도리 애니메이션 접근자 설정자
	animation* getPengdoriMotion() { return _pengdoriMotion; }
	void setPengdoriMotion(animation* ani) { _pengdoriMotion = ani; }

	void setRockmanMemoryAddressLink(rockman* rm) { _rm = rm; }
};

