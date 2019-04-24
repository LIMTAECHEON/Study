#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "stageMap.h"
#include "progressBar.h"				// 2DFramework/progressBar
#include "bullet.h"						// PlayGround/bullet

enum ROCKMAN_ACTION						// ���� ��� ���� enum��
{
	ROCKMAN_START,						// ���� ���� ��� ����!
	ROCKMAN_RIGHT_STOP,					// ������ ���� ���
	ROCKMAN_LEFT_STOP,					// ���� ���� ���
	ROCKMAN_RIGHT_STAY,					// ������ ���� ��� (�� ������)
	ROCKMAN_LEFT_STAY,					// ���� ���� ��� (�� ������)
	ROCKMAN_RIGHT_MOVE,					// ������ �̵�
	ROCKMAN_LEFT_MOVE,					// ���� �̵�
	ROCKMAN_RIGHT_JUMP,					// ������ ����
	ROCKMAN_LEFT_JUMP,					// ���� ����
	ROCKMAN_RIGHT_MOVE_JUMP,			// ������ �̵� ����
	ROCKMAN_LEFT_MOVE_JUMP,				// ���� �̵� ����
	ROCKMAN_RIGHT_ATTACK,				// ������ ���ڸ� ����
	ROCKMAN_LEFT_ATTACK,				// ���� ���ڸ� ����
	ROCKMAN_RIGHT_MOVE_ATTACK,			// ������ �̵� ����
	ROCKMAN_LEFT_MOVE_ATTACK,			// ���� �̵� ����
	ROCKMAN_RIGHT_JUMP_ATTACK,			// ������ ���� ����
	ROCKMAN_LEFT_JUMP_ATTACK,			// ���� ���� ����
	ROCKMAN_RIGHT_MOVE_JUMP_ATTACK,		// ������ �̵� ���� ����
	ROCKMAN_LEFT_MOVE_JUMP_ATTACK,		// ���� ���� �̵� ����
	ROCKMAN_RIGHT_HIT,					// ������ �ǰ�
};

enum CHARGE_SHOT_IMAGE					// ������ ����Ʈ ���� enum��
{
	CHARGELV1,
	CHARGELV2,
};

class enemyManager;						// enemyManager �� Ŭ���� ���漱��
class pengdori;							// pengdori �� Ŭ���� ���漱��

class rockman : public gameNode
{
private:

	enemyManager* _enemy;				// enemyManager Ŭ����
	pengdori* _p;						// pengdori Ŭ����

	RECT _megaRc;						// ���� RECT
	float _x, _y;						// ���� ��ǥ
	float _rockProbeY;					// ���� �ȼ� �浹 ��ǥ
	
	image* _megaImg;					// ���� �̹���
	ROCKMAN_ACTION _megaManDirection;	// ���� ��� enum��
	animation* _megaManMotion;			// animation Ŭ����

	float _jumpPower;					// ������
	float _gravity;						// �߷�

	image* _hpHUDImg;					// HP HUD �̹���
	RECT _hpHUDRc;						// HP HUD RECT
	float _hpHUDX, _hpHUDY;				// HP HUD ��ǥ
	progressBar* _hpBar;				// progressBar Ŭ����
	float _currentHP, _maxHP;			// ���� ü��, �ִ� ü��

	CHARGE_SHOT_IMAGE _chargeLvImg;		// ������ ����Ʈ enum��
	image* _chargeImg;					// ������ ����1 �̹���
	image* _chargeLv2Img;				// ������ ����2 �̹���

	normalRightBullet* _rightBullet;	// bullet Ŭ����, ������ �Ϲ� ����
	normalLeftBullet* _leftBullet;		// bullet Ŭ����, ���� �Ϲ� ����
	bool _isRightShot;					// �Ϲ� ���� ������ �߻� ���� BOOL 
	bool _isLeftShot;					// �Ϲ� ���� ���� �߻� ���� BOOL

	int _hitCheck = 0;					// �ǰ� ��� ����
	bool _isHitOn = false;				// �ǰ� ���� BOOL

	int _pMotion = 0;					// �ص��� ��� üũ

	int _countEnemy = 0;				// ���ʹ� ���� ����Ʈ/������ ���� ī����
	bool _isEnemyDelete = false;		// ���ʹ� ���� ����Ʈ üũ
	bool _isEnemyDeleteHp = false;		// ���ʹ� ������ ��� üũ

	int _chargeImgCount = 0;			// ������ ����Ʈ ������ ����(�ӵ�����)
	int _chargeImgIndex = 0;			// ������ ����Ʈ ������ ����(���������)

	image* _overImg;					// ���� ���� �̹���
	
	image* _rockmanIn;
	RECT _rockmanInRc;
	POINTFLOAT _rockmanInPos;
	bool _isCheckIn = false;

	int _index;							// stageMap _index set ����
	float _cameraX;						// stageMap _cameraX set ����
	float _cameraY;						// stageMap _cameraY set ����

	// ������ ���� ���� ���� 
	// ������� ������ ����1/������ ����2/���� ����1/���� ����2
	// ������ ������� ������ ���� ī��Ʈ, ����Ʈ ��� ī��Ʈ, ���� ���� ī��Ʈ
	// ������ �߻� ���� BOOL, ������ ���� ��Ȳ ���� BOOL, ������ ����(����) üũ BOOL

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

	void imageInit();					// �̹��� ��ǥ ���� �Լ�
	void rockmanDynamic();				// ���� �Ҵ� �Լ�
	void rockmanMotion();				// ���� Ű�ִϸŴ��� �Լ�
	void chargeImageCount();			// ������ ����Ʈ ������ �Լ�
	void chargeImageLocation();			// ������ �߻� ��ǥ �Լ�
	void chargeImageRenderControl();	// ������ ����Ʈ ���� ���� �Լ�
	void hpSet();						// ���� HP BAR �Լ�
	void enemyCountLimit();				// ���ʹ� ���� ����Ʈ ī��Ʈ ���� �Լ�
	void rockmanKeySet();				// ���� ��ư �Է� �Լ�
	void rockmanPixelCheck();			// ���� �ȼ� �浹 �Լ�
	void rockmanSpeedSwitch();			// ���� ��� �ӵ� ���� switch�� �Լ�
	void rockmanJump();					// ���� ���� ���� �Լ�
	void itemCollision();				// ������ ����Ʈ ī��Ʈ ���� �Լ�
	void rockmanInShow();
	void bulletRender();				// ���� ���� �Լ�
	void normalBulletCollision();		// ���� ���� �浹 ó�� �Լ� (���ʹ�)
	void normalBulletBossCollision();	// ���� ���� �浹 ó�� �Լ� (����)
	void hitDamage(float damage);		// ���� ���ط� üũ �Լ�

	// ��� �Լ� (Ư�� ����� ������ �ش� �Լ� ���� ������� ����)

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
	
	// �Ʒ� Ŭ�������� �÷��ְ�! �� Ŭ�������� ����ִ�! Ȯ���� �ý�������!
	// rockman ����&�Լ��� �ٸ� Ŭ�������� ����ϱ� ���� get �Լ�

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

	// ���� ���� ������ ������

	ROCKMAN_ACTION getRockManDirection() { return _megaManDirection; }
	void setRockManDirection(ROCKMAN_ACTION direction) { _megaManDirection = direction; }

	// ���� �ִϸ��̼� ������ ������

	animation* getRockManMotion() { return _megaManMotion; }
	void setRockManMotion(animation* ani) { _megaManMotion = ani; }

	// ���� Ŭ����(stageMap) Set �Լ� 
	
	void setCameraX(float cameraX) { _cameraX = cameraX; }
	void setCameraY(float cameraY) { _cameraY = cameraY; }
	void setIndex(int index) { _index = index; }

	// enemyManager Ŭ����, pengdori Ŭ������ �̾��ִ� ��巹�� ��ũ �Լ�

	void setEnemyMemoryAddressLink(enemyManager* enemy) { _enemy = enemy; }
	void setPengdoriMemoryAddressLink(pengdori* boss) { _p = boss; }
};