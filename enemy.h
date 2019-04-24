#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "bullet.h"

enum typeEnemy									 // 에너미 종류 enum문, 편의상 이름은 ENEMY로 통일
{
	ENEMY01,
	ENEMY02,
	ENEMY03,
	ENEMY04,
	ENEMY05,
	ENEMY06,
	ENEMY07,
	ENEMY08,
	ENEMY09,
	ENEMY10,
	ENEMY11,
	ENEMY12,
	ENEMY13,	
	ENEMY14,
	ENEMY15,
};

struct tagEnemy									// 에너미 상태 구조체
{
	image* imageName;							// 이미지
	RECT rc;									// RECT
	POINTFLOAT pos;								// 좌표
	float angle;								// 각도
	float speed;								// 속도
	float speedFast;							// 좀 더 빠른 속도
};

// enemy -> minion, minion2, minion3 클래스를 public로 연결
// 서로 다른 형태의 움직임과 이미지, 공격 순서를 조절하기 위함

class enemy: public gameNode
{
protected:

	tagEnemy _enemy;							// 에너미 설정 enum문
	typeEnemy _state;							// 에너미 종류 enum문

	bullet* _bullet;							// bullet 클래스

	int _currentFrameX, _currentFrameY = 0;		// 이미지 프레임 순서
	int _count = 0;								// 에너미 프레임 변수(속도조절)
	int _fireCount = 0;							// 에너미 공격 변수
	int _rndFireCount = 0;						// 에너미 공격 횟수 변수

	float _cameraX;								// stageMap _cameraX set 변수
	float _cameraY;								// stageMap _cameraY set 변수

public:

	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update(float cameraX, float cameraY);
	virtual void render();
	
	virtual void enemyImageManager();			// 이미지 매니저 함수
	virtual void imageSetFrame();				// 에너미 움직임 이미지 프레임
	virtual void enemySet();					// 에너미 움직임 셋팅 함수
	virtual bool enemyFire();					// 에너미 공격 횟수 셋팅 함수
	virtual void setType(int type);				// 에너미 매니저 타입 get/set 함수

	// enemy 변수&함수를 다른 클래스에서 사용하기 위한 get 함수

	virtual float getEnemyX() { return _enemy.pos.x; }
	virtual float getEnemyY() { return _enemy.pos.y; }
	virtual tagEnemy getEnemy() { return _enemy; }
	virtual typeEnemy getState() { return _state; }
	virtual RECT getRect() { return _enemy.rc; }
	virtual image* getImage() { return _enemy.imageName; }
};

