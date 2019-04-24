#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "stageMap.h"
#include "progressBar.h"				// 2DFramework/progressBar
#include "bullet.h"						// PlayGround/bullet

enum ROCKMAN_ACTION						// 엑스 모션 관련 enum문
{
	ROCKMAN_START,						// 엑스 등장 모션 슈웅!
	ROCKMAN_RIGHT_STOP,					// 오른쪽 정지 모션
	ROCKMAN_LEFT_STOP,					// 왼쪽 정지 모션
	ROCKMAN_RIGHT_STAY,					// 오른쪽 정지 모션 (얼굴 움직임)
	ROCKMAN_LEFT_STAY,					// 왼쪽 정지 모션 (얼굴 움직임)
	ROCKMAN_RIGHT_MOVE,					// 오른쪽 이동
	ROCKMAN_LEFT_MOVE,					// 왼쪽 이동
	ROCKMAN_RIGHT_JUMP,					// 오른쪽 점프
	ROCKMAN_LEFT_JUMP,					// 왼쪽 점프
	ROCKMAN_RIGHT_MOVE_JUMP,			// 오른쪽 이동 점프
	ROCKMAN_LEFT_MOVE_JUMP,				// 왼쪽 이동 점프
	ROCKMAN_RIGHT_ATTACK,				// 오른쪽 제자리 공격
	ROCKMAN_LEFT_ATTACK,				// 왼쪽 제자리 공격
	ROCKMAN_RIGHT_MOVE_ATTACK,			// 오른쪽 이동 공격
	ROCKMAN_LEFT_MOVE_ATTACK,			// 왼쪽 이동 공격
	ROCKMAN_RIGHT_JUMP_ATTACK,			// 오른쪽 점프 공격
	ROCKMAN_LEFT_JUMP_ATTACK,			// 왼쪽 점프 공격
	ROCKMAN_RIGHT_MOVE_JUMP_ATTACK,		// 오른쪽 이동 점프 공격
	ROCKMAN_LEFT_MOVE_JUMP_ATTACK,		// 왼쪽 점프 이동 공격
	ROCKMAN_RIGHT_HIT,					// 오른쪽 피격
};

enum CHARGE_SHOT_IMAGE					// 차지샷 이펙트 관련 enum문
{
	CHARGELV1,
	CHARGELV2,
};

class enemyManager;						// enemyManager 빈 클래스 전방선언
class pengdori;							// pengdori 빈 클래스 전방선언

class rockman : public gameNode
{
private:

	enemyManager* _enemy;				// enemyManager 클래스
	pengdori* _p;						// pengdori 클래스

	RECT _megaRc;						// 엑스 RECT
	float _x, _y;						// 엑스 좌표
	float _rockProbeY;					// 엑스 픽셀 충돌 좌표
	
	image* _megaImg;					// 엑스 이미지
	ROCKMAN_ACTION _megaManDirection;	// 엑스 모션 enum문
	animation* _megaManMotion;			// animation 클래스

	float _jumpPower;					// 점프력
	float _gravity;						// 중력

	image* _hpHUDImg;					// HP HUD 이미지
	RECT _hpHUDRc;						// HP HUD RECT
	float _hpHUDX, _hpHUDY;				// HP HUD 좌표
	progressBar* _hpBar;				// progressBar 클래스
	float _currentHP, _maxHP;			// 현재 체력, 최대 체력

	CHARGE_SHOT_IMAGE _chargeLvImg;		// 차지샷 이펙트 enum문
	image* _chargeImg;					// 차지샷 레벨1 이미지
	image* _chargeLv2Img;				// 차지샷 레벨2 이미지

	normalRightBullet* _rightBullet;	// bullet 클래스, 오른쪽 일반 공격
	normalLeftBullet* _leftBullet;		// bullet 클래스, 왼쪽 일반 공격
	bool _isRightShot;					// 일반 공격 오른쪽 발사 유무 BOOL 
	bool _isLeftShot;					// 일반 공격 왼쪽 발사 유무 BOOL

	int _hitCheck = 0;					// 피격 모션 제어
	bool _isHitOn = false;				// 피격 상태 BOOL

	int _pMotion = 0;					// 팽도리 모션 체크

	int _countEnemy = 0;				// 에너미 사후 이펙트/아이템 관리 카운터
	bool _isEnemyDelete = false;		// 에너미 폭파 이펙트 체크
	bool _isEnemyDeleteHp = false;		// 에너미 아이템 드랍 체크

	int _chargeImgCount = 0;			// 차지샷 이펙트 프레임 변수(속도조절)
	int _chargeImgIndex = 0;			// 차지샷 이펙트 프레임 변수(프레임출력)

	image* _overImg;					// 게임 오버 이미지
	
	image* _rockmanIn;
	RECT _rockmanInRc;
	POINTFLOAT _rockmanInPos;
	bool _isCheckIn = false;

	int _index;							// stageMap _index set 변수
	float _cameraX;						// stageMap _cameraX set 변수
	float _cameraY;						// stageMap _cameraY set 변수

	// 차지샷 연출 관련 변수 
	// 순서대로 오른쪽 레벨1/오른쪽 레벨2/왼쪽 레벨1/왼쪽 레벨2
	// 변수는 순서대로 차지샷 누적 카운트, 이펙트 출력 카운트, 렌더 제한 카운트
	// 차지샷 발사 유무 BOOL, 차지샷 랜더 상황 유무 BOOL, 차지샷 레벨(종류) 체크 BOOL

	chargeRightBullet* _chargeRightShot;
	int _chargeShotRightCount = 0;
	int _chargeShotRightEffectCount = 0;
	int _chargeShotRightRenderCount = 0;
	bool _isChargeShotRight = false;
	bool _isStopChargeShotRight = false;
	bool _isChargeRightCheck = false;

	chargeLv2RightBullet* _chargeLv2RightShot;
	int _chargeLv2ShotRightCount = 0;
	int _chargeLv2ShotRightEffectCount = 0;
	int _chargeLv2ShotRightRenderCount = 0;
	bool _isChargeLv2ShotRight = false;
	bool _isStopChargeLv2ShotRight = false;
	bool _isChargeLv2RightCheck = false;

	chargeLeftBullet* _chargeLeftShot;
	int _chargeShotLeftCount = 0;
	int _chargeShotLeftEffectCount = 0;
	int _chargeShotLeftRenderCount = 0;
	bool _isChargeShotLeft = false;
	bool _isStopChargeShotLeft = false;
	bool _isChargeLeftCheck = false;

	chargeLv2LeftBullet* _chargeLv2LeftShot;
	int _chargeLv2ShotLeftCount = 0;
	int _chargeLv2ShotLeftEffectCount = 0;
	int _chargeLv2ShotLeftRenderCount = 0;
	bool _isChargeLv2ShotLeft = false;
	bool _isStopChargeLv2ShotLeft = false;
	bool _isChargeLv2LeftCheck = 0;

public:

	rockman();
	~rockman();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageInit();					// 이미지 좌표 셋팅 함수
	void rockmanDynamic();				// 동적 할당 함수
	void rockmanMotion();				// 엑스 키애니매니저 함수
	void chargeImageCount();			// 차지샷 이펙트 프레임 함수
	void chargeImageLocation();			// 차지샷 발사 좌표 함수
	void chargeImageRenderControl();	// 차지샷 이펙트 렌더 관리 함수
	void hpSet();						// 엑스 HP BAR 함수
	void enemyCountLimit();				// 에너미 폭파 이펙트 카운트 제어 함수
	void rockmanKeySet();				// 엑스 버튼 입력 함수
	void rockmanPixelCheck();			// 엑스 픽셀 충돌 함수
	void rockmanSpeedSwitch();			// 엑스 모션 속도 제어 switch문 함수
	void rockmanJump();					// 엑스 점프 관련 함수
	void itemCollision();				// 아이템 이펙트 카운트 제어 함수
	void rockmanInShow();
	void bulletRender();				// 공격 렌더 함수
	void normalBulletCollision();		// 엑스 공격 충돌 처리 함수 (에너미)
	void normalBulletBossCollision();	// 엑스 공격 충돌 처리 함수 (보스)
	void hitDamage(float damage);		// 엑스 피해량 체크 함수

	// 모션 함수 (특정 모션이 끝나면 해당 함수 내에 모션으로 변경)

	static void startMotion(void* obj);
	static void rightAttack(void* obj);
	static void rightMoveAttack(void* obj);
	static void rightJump(void* obj);
	static void rightMoveJump(void* obj);
	static void rightJumpAttack(void* obj);
	static void rightMoveJumpAttack(void* obj);
	static void leftJump(void* obj);
	static void leftMoveJump(void* obj);
	static void leftAttack(void* obj);
	static void leftMoveAttack(void* obj);
	static void leftJumpAttack(void* obj);
	static void leftMoveJumpAttack(void* obj);
	
	// 아래 클래스에서 올려주고! 위 클래스에서 당겨주는! 확실한 시스템으로!
	// rockman 변수&함수를 다른 클래스에서 사용하기 위한 get 함수

	float getPosX() { return _x; }
	float getPosY() { return _y; }
	float getCameraX() { return _cameraX; }
	float getCameraY() { return _cameraY; }
	float getCurrentHP() { return _currentHP; }
	int getMotion() { return _pMotion; }
	RECT getMegaRc() { return _megaRc; }
	image* getMegaImage() { return _megaImg; }
	bool getEnemyDelete() { return _isEnemyDelete; }
	bool getEnemyDeleteHp() { return _isEnemyDeleteHp; }

	// 엑스 상태 접근자 설정자

	ROCKMAN_ACTION getRockManDirection() { return _megaManDirection; }
	void setRockManDirection(ROCKMAN_ACTION direction) { _megaManDirection = direction; }

	// 엑스 애니메이션 접근자 설정자

	animation* getRockManMotion() { return _megaManMotion; }
	void setRockManMotion(animation* ani) { _megaManMotion = ani; }

	// 상위 클래스(stageMap) Set 함수 
	
	void setCameraX(float cameraX) { _cameraX = cameraX; }
	void setCameraY(float cameraY) { _cameraY = cameraY; }
	void setIndex(int index) { _index = index; }

	// enemyManager 클래스, pengdori 클래스를 이어주는 어드레스 링크 함수

	void setEnemyMemoryAddressLink(enemyManager* enemy) { _enemy = enemy; }
	void setPengdoriMemoryAddressLink(pengdori* boss) { _p = boss; }
};