#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "rockman.h"
#include "jump.h"
#include "progressBar.h"

#define ICEMANSPEED 2.5f

enum ICEMANDIRECTION
{
	ICEMANDIRECTION_RIGHT_STOP,
	ICEMANDIRECTION_LEFT_STOP,
	ICEMANDIRECTION_RIGHT_MOVE,
	ICEMANDIRECTION_LEFT_MOVE,
	ICEMANDIRECTION_RIGHT_JUMP,
	ICEMANDIRECTION_LEFT_JUMP,
	ICEMANDIRECTION_RIGHT_MOVE_JUMP,
	ICEMANDIRECTION_LEFT_MOVE_JUMP,
	ICEMANDIRECTION_RIGHT_ATTACK,
	ICEMANDIRECTION_LEFT_ATTACK,
	ICEMANDIRECTION_RIGHT_MOVE_ATTACK,
	ICEMANDIRECTION_LEFT_MOVE_ATTACK,
	ICEMANDIRECTION_RIGHT_JUMP_ATTACK,
	ICEMANDIRECTION_LEFT_JUMP_ATTACK,
	ICEMANDIRECTION_RIGHT_MOVE_JUMP_ATTACK,
	ICEMANDIRECTION_LEFT_MOVE_JUMP_ATTACK,
	ICEMANDIRECTION_LEFT_DEAD,
};

enum STATE_ICEMAN
{
	MOVE01,
	MOVE02
};

class rockman;

class iceman: public gameNode
{
private:
	ICEMANDIRECTION _icemanDirection;
	bossBullet* _bullet;
	animation* _icemanMotion;
	jump* _jump;

	int _count;
	int _count1;
	int _count2;

	STATE_ICEMAN _state;
	int _bossState;

	bool _isShot;

	image* _bossImg;
	RECT _rc;
	POINTFLOAT _pos;

	rockman* _play;

	RECT rc;
	int _motion;
	int _motion2;

	progressBar* _hpBar;
	float _currentHP, _maxHP;

public:
	iceman();
	~iceman();

	HRESULT init();
	void release();
	void update();
	void render();

	void hitDamage(float damage);
	void collision();

	static void leftFire(void* obj);
	static void leftJump(void* obj);
	static void leftJumpFire(void* obj);
	static void leftAutoFire(void* obj);
	
	RECT getIceManRc() { return _rc; }
	image* getBossImage() { return _bossImg; }
	int getMotion() { return _motion2; }
	
	// 아이스맨 상태 접근자 설정자
	ICEMANDIRECTION getIcesManDirection() { return _icemanDirection; }
	void setIceManDirection(ICEMANDIRECTION direction) { _icemanDirection = direction; }

	// 아이스맨 애니메이션 접근자 설정자
	animation* getIceManMotion() { return _icemanMotion; }
	void setIceManMotion(animation* ani) { _icemanMotion = ani; }

	// 록맨 어드레스 링크(포인트 연결)
	void setRockManMemoryAddressLink(rockman* rockman) { _play = rockman; }
};

