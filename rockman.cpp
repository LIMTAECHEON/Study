#include "stdafx.h"
#include "rockman.h"
#include "pengdori.h"									// ���漱�� Ŭ���� ���
#include "enemyManager.h"								// ���漱�� Ŭ���� ���

rockman::rockman() {}
rockman::~rockman() {}

HRESULT rockman::init()
{
	_megaImg = ROCKMAN_IMAGE;							// ���� �̹���
	_rockmanIn = ROCKMAN_IN;							// ���� ���� ����
	_hpHUDImg = ROCKMAN_HP_HUD_IMAGE;					// HP HUD �̹���
	_chargeImg = CHARGE_LV1_IMAGE;						// ������ ����Ʈ ����1 �̹���
	_chargeLv2Img = CHARGE_LV2_IMAGE;					// ������ ����Ʈ ����2 �̹���
	_overImg = GAMEOVER_IMAGE;							// ���� ����

	imageInit();										// �̹��� ��ǥ ���� �Լ�
	rockmanDynamic();									// ���� �Ҵ� �Լ�
	rockmanMotion();									// ���� Ű�ִϸ��̼� �Լ�
	
	return S_OK;
}

void rockman::release()
{
	SAFE_DELETE(_rightBullet);
	SAFE_DELETE(_leftBullet);
	SAFE_DELETE(_chargeRightShot);
	SAFE_DELETE(_chargeLeftShot);
	SAFE_DELETE(_chargeLv2RightShot);
	SAFE_DELETE(_chargeLv2LeftShot);
}

void rockman::update()
{
	_pMotion = 0;

	rockmanJump();										// ���� ���� ���� �Լ�
	rockmanPixelCheck();								// ���� �ȼ� �浹 �Լ�
	rockmanKeySet();									// ���� ��ư �Է� �Լ�
	rockmanSpeedSwitch();								// ���� ��� �ӵ� ���� Switch�� �Լ�
	hpSet();											// ���� HP BAR �Լ�

	chargeImageCount();									// ������ ����Ʈ ������ �Լ�
	chargeImageLocation();								// ������ �߻� ��ǥ �Լ�
	chargeImageRenderControl();							// ������ ����Ʈ ���� ���� �Լ�
	
	_rightBullet->update();
	_leftBullet->update();
	_chargeRightShot->update();
	_chargeLeftShot->update();
	_chargeLv2RightShot->update();
	_chargeLv2LeftShot->update();

	normalBulletCollision();							// ���� ���� �浹 ó�� �Լ� (���ʹ�)
	normalBulletBossCollision();						// ���� ���� �浹 ó�� �Լ� (����)
	
	enemyCountLimit();									// ���ʹ� ���� ����Ʈ ī��Ʈ ���� �Լ�
	itemCollision();									// ������ ����Ʈ ī��Ʈ ���� �Լ�

	rockmanInShow();									// ���� ���� ���� �Լ�

	_isRightShot = _isLeftShot = false;					// �߻� ���� false ������ ���� �ʱ�ȭ

	_rockProbeY = _y + _megaImg->getFrameHeight() / 2;
	_megaRc = RectMakeCenter(_x, _y, _megaImg->getFrameWidth(), _megaImg->getFrameHeight());
	
	// ===== �׽�Ʈ

	if (KEYMANAGER->isOnceKeyDown('Q')) _currentHP -= 20;
}

void rockman::render()
{
	// ����ü��(_currentHP)�� 1 �̻��̸� ĳ����, HP �̹����� ����ϰ�
	// ����ü��(_currentHP)�� 0 �̸��̸� ���ӿ��� �̹��� ����ϸ鼭 ĳ���Ϳ� HP �̹��� ����� �����Ѵ�

	if (_currentHP >= 1)
	{
		if (_isCheckIn) _rockmanIn->render(getMemDC(), _rockmanInRc.left - _cameraX, _rockmanInRc.top - _cameraY);
		_megaImg->aniRender(getMemDC(), _megaRc.left - _cameraX, _megaRc.top - _cameraY, _megaManMotion);
		_hpHUDImg->render(getMemDC(), _hpHUDRc.left, _hpHUDRc.top);
		_hpBar->render();
	}
		
	if (_currentHP <= 0)
	{
		_overImg->render(getMemDC());
	}
	
	bulletRender();

	// ========== �����

	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	//	char str[128]; // ��� �׽�Ʈ�� 
	//	sprintf_s(str, "[����X��]: %f, [����Y��]: %f", _x, _y);
	//	TextOut(getMemDC(), 0, 60, str, strlen(str));
	//	sprintf_s(str, "[ī�޶�X��]: %f, [ī�޶�Y��]: %f", _cameraX, _cameraY);
	//	TextOut(getMemDC(), 0, 80, str, strlen(str));
	//	sprintf_s(str, "[ī��Ʈ]: %d", _countEnemy);
	//	TextOut(getMemDC(), 0, 120, str, strlen(str));
	//}
}

void rockman::imageInit()
{
	_hpHUDX = ROCKMAN_HP_HUD_X;							// ���� HP HUD ��ǥ
	_hpHUDY = ROCKMAN_HP_HUD_Y;
	_hpHUDRc = RectMakeCenter(_hpHUDX, _hpHUDY, _hpHUDImg->GetWidth(), _hpHUDImg->GetHeight());

	_x = ROCKMAN_X;										// ���� ���� ���� ��ǥ
	_y = ROCKMAN_Y;
	_rockProbeY = _y + _megaImg->getFrameHeight() / 2;	// ���� �ȼ� �浹 üũ ����
	_megaRc = RectMakeCenter(_x, _y, _megaImg->getFrameWidth(), _megaImg->getFrameHeight());

	_rockmanInPos.x = ROCKMAN_X_IN;						// ���� ���� ���� ��ǥ
	_rockmanInPos.y = ROCKMAN_Y_IN;
	_rockmanInRc = RectMakeCenter(_rockmanInPos.x, _rockmanInPos.y, _rockmanIn->GetWidth(), _rockmanIn->GetHeight());

	_chargeImg->SetFrameY(0);							// ������ ������ ���� �� �ʱ�ȭ
	_chargeLvImg = CHARGELV1;
}

void rockman::rockmanDynamic()
{
	_p = new pengdori;									// �ص��� ���� �Ҵ�
	_p->init();

	_hpBar = new progressBar;							// HP ���� �Ҵ�
	_hpBar->init(ROCKMAN_HP_INIT);						// HP BAR X�� ��ǥ, Y�� ��ǥ, ���α���, ���α���
	_currentHP = _maxHP = HP;							// ����ü�� = �ִ�ü�� = 100

	// ���� ���� ���� ���� �Ҵ�
	// ������ �Ϲ� ����, ���� �Ϲ� ����
	// ������ ���� ����1 ����, ���� ���� ����1 ����
	// ������ ���� ����2 ����, ���� ���� ����2 ����

	_rightBullet = new normalRightBullet;				
	_rightBullet->init(ROCKMAN_BULLET_RANGE_INIT);		// ���� ����(źâ), ��Ÿ�

	_leftBullet = new normalLeftBullet;
	_leftBullet->init(ROCKMAN_BULLET_RANGE_INIT);

	_chargeRightShot = new chargeRightBullet;
	_chargeRightShot->init(ROCKMAN_BULLET_RANGE_INIT);

	_chargeLeftShot = new chargeLeftBullet;
	_chargeLeftShot->init(ROCKMAN_BULLET_RANGE_INIT);

	_chargeLv2RightShot = new chargeLv2RightBullet;
	_chargeLv2RightShot->init(ROCKMAN_BULLET_RANGE_INIT);

	_chargeLv2LeftShot = new chargeLv2LeftBullet;
	_chargeLv2LeftShot->init(ROCKMAN_BULLET_RANGE_INIT);
}

void rockman::rockmanMotion()
{
	// Ű�ִϸ��̼� �Ŵ����� Ȱ���� �����̴� �̹��� ���
	// 3D �׷��ȿ��� Ȱ��Ǵ� ������ ������� �̹��� ������ ��� ���
	// image/rockman/ROCKMAN.bmp
	// �ش� ��� �̸�(string), �ش� ��� �̹��� �̸�(const char), 
	// ����� ������ �̹���, ����� �̹����� ����, ����� �̹����� �ӵ�(������), 
	// �ݺ� üũ, �ش� ��� ���� �� ��� �� �̹���, �ش� ��� ���� �� ��µ� �̹��� �Լ��� ��ġ(obj)

	int startRockman[] = KEYANI_START;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanStart", "rockman", startRockman, 7, 7, false, startMotion, this);

	int rightStop[] = KEYANI_ROCKMAN_RIGHT_STOP;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightStop", "rockman", rightStop, 1, 10, true);
	int rightStay[] = KEYANI_ROCKMAN_RIGHT_STAY;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightStay", "rockman", rightStay, 4, 3, true);
	int rightMove[] = KEYANI_ROCKMAN_RIGHT_MOVE;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightMove", "rockman", rightMove, 11, 10, true);
	int arrRightJump[] = KEYANI_ROCKMAN_RIGTH_JUMP;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightJump", "rockman", arrRightJump, 7, 8, false, rightJump, this);
	int arrRightMoveJump[] = KEYANI_ROCKMAN_RIGTH_JUMP;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightMoveJump", "rockman", arrRightMoveJump, 7, 7, false, rightMoveJump, this);
	int arrRightAttack[] = KEYANI_ROCKMAN_RIGHT_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightAttack", "rockman", arrRightAttack, 2, 5, false, rightAttack, this);
	int arrRightMoveAttack[] = KEYANI_ROCKMAN_RIGHT_MOVE_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightMoveAttack", "rockman", arrRightMoveAttack, 10, 10, false, rightMoveAttack, this);
	int arrRightJumpAttack[] = KEYANI_ROCKMAN_RIGHT_JUMP_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightJumpAttack", "rockman", arrRightJumpAttack, 7, 8, false, rightJumpAttack, this);
	int arrRightMoveJumpAttack[] = KEYANI_ROCKMAN_RIGHT_JUMP_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightMoveJumpAttack", "rockman", arrRightMoveJumpAttack, 7, 10, false, rightMoveJumpAttack, this);
	int arrRightHit[] = KEYANI_ROCKMAN_RIGHT_HIT;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanRightHit", "rockman", arrRightHit, 1, 10, true);

	int leftStop[] = KEYANI_ROCKMAN_LEFT_STOP;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftStop", "rockman", leftStop, 1, 10, true);
	int leftStay[] = KEYANI_ROCKMAN_LEFT_STAY;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftStay", "rockman", leftStay, 4, 3, true);
	int leftMove[] = KEYANI_ROCKMAN_LEFT_MOVE;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftMove", "rockman", leftMove, 11, 10, true);
	int arrLeftJump[] = KEYANI_ROCKMAN_LEFT_JUMP;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftJump", "rockman", arrLeftJump, 7, 8, false, leftJump, this);
	int arrLeftMoveJump[] = KEYANI_ROCKMAN_LEFT_JUMP;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftMoveJump", "rockman", arrLeftMoveJump, 7, 7, false, leftMoveJump, this);
	int arrLeftAttack[] = KEYANI_ROCKMAN_LEFT_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftAttack", "rockman", arrLeftAttack, 2, 5, false, leftAttack, this);
	int arrLeftMoveAttack[] = KEYANI_ROCKMAN_LEFT_MOVE_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftMoveAttack", "rockman", arrLeftMoveAttack, 10, 10, false, leftMoveAttack, this);
	int arrLeftJumpAttack[] = KEYANI_ROCKMAN_LEFT_JUMP_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftJumpAttack", "rockman", arrLeftJumpAttack, 7, 8, false, leftJumpAttack, this);
	int arrLeftMoveJumpAttack[] = KEYANI_ROCKMAN_LEFT_JUMP_ATTACK;
	KEYANIMANAGER->addArrayFrameAnimation("rockmanLeftMoveJumpAttack", "rockman", arrLeftMoveJumpAttack, 7, 8, false, leftMoveJumpAttack, this);

	_megaManDirection = ROCKMAN_START;					// ���� ���� ����� ���� (emum��)
	_megaManMotion = KEYANIMANAGER->findAnimation("rockmanStart");
}

void rockman::chargeImageCount()
{
	_chargeImgCount++;
	if (_chargeImgCount % CHARGE_IMAGE_SPEED == 0)
	{
		if (_chargeLvImg == CHARGELV1)
		{
			_chargeImgIndex++;
			_chargeImg->SetFrameX(_chargeImgIndex);
			if (_chargeImgIndex >= _chargeImg->getMaxFrameX()) _chargeImgIndex = -1;
		}

		if (_chargeLvImg == CHARGELV2)
		{
			_chargeImgIndex++;
			_chargeLv2Img->SetFrameX(_chargeImgIndex);
			if (_chargeImgIndex >= _chargeLv2Img->getMaxFrameX()) _chargeImgIndex = -1;
		}

		_chargeImgCount = 0;
	}
}

void rockman::chargeImageLocation()
{
	// ������ ���� ��ġ (�߻� ��ġ)
	// ���ݵ� ī�޶� ���� ���� �ޱ� ���� �߻� ��ġ - ī�޶� ��ǥ���� ���ش�

	if (_isRightShot) _rightBullet->normalRightBulletFire((_megaRc.left + 120) - _cameraX, (_megaRc.top + 67) - _cameraY);
	if (_isLeftShot) _leftBullet->normalLeftBulletFire((_megaRc.left + 30) - _cameraX, (_megaRc.top + 67) - _cameraY);

	if (_isChargeShotRight) _chargeRightShot->chargeRightBulletFire((_megaRc.left + 120) - _cameraX, (_megaRc.top + 67) - _cameraY);
	if (_isChargeShotLeft) _chargeLeftShot->chargeLeftBulletFire((_megaRc.left + 30) - _cameraX, (_megaRc.top + 67) - _cameraY);

	if (_isChargeLv2ShotRight) _chargeLv2RightShot->chargeLv2RightBulletFire((_megaRc.left + 120) - _cameraX, (_megaRc.top + 67) - _cameraY);
	if (_isChargeLv2ShotLeft) _chargeLv2LeftShot->chargeLv2LeftBulletFire((_megaRc.left + 30) - _cameraX, (_megaRc.top + 67) - _cameraY);
}

void rockman::chargeImageRenderControl()
{
	// ������ ���� ������ ���� �Լ�
	// ZŰ�� _isStopChargeShotRight�� true�� �ٲٸ� _chargeShotRightRenderCount ī��Ʈ ����
	// �ش� ī��Ʈ�� ������ ��(CHARGE_RENDER_LIMIT)�� �Ѿ�� ����2�� ����, ������ ���� ����1�� ����
	// ����2�� �� ��� ����2���� �����ϰ� ������ ���� ī��Ʈ(_chargeLv2ShotRightRenderCount)�� �۵�. ���� ����� ����1�� ����
	// ����2�� �Ѿ�� �Ǹ� ����1�� ī��Ʈ�� bool ������ 0���� �ʱ�ȭ

	if (_isStopChargeShotRight) _chargeShotRightRenderCount++;
	if (CHARGE_RENDER_LIMIT == _chargeShotRightRenderCount) _isStopChargeShotRight = false;
	else if (CHARGE_RENDER_LIMIT <= _chargeShotRightRenderCount) _chargeShotRightRenderCount = 0;

	if (_isStopChargeLv2ShotRight) _chargeLv2ShotRightRenderCount++;
	if (CHARGE_RENDER_LIMIT == _chargeLv2ShotRightRenderCount) _isStopChargeLv2ShotRight = false;
	else if (CHARGE_RENDER_LIMIT <= _chargeLv2ShotRightRenderCount) _chargeLv2ShotRightRenderCount = 0;

	if (_isStopChargeShotLeft) _chargeShotLeftRenderCount++;
	if (CHARGE_RENDER_LIMIT == _chargeShotLeftRenderCount) _isStopChargeShotLeft = false;
	else if (CHARGE_RENDER_LIMIT <= _chargeShotLeftRenderCount) _chargeShotLeftRenderCount = 0;

	if (_isStopChargeLv2ShotLeft) _chargeLv2ShotLeftRenderCount++;
	if (CHARGE_RENDER_LIMIT == _chargeLv2ShotLeftRenderCount) _isStopChargeLv2ShotLeft = false;
	else if (CHARGE_RENDER_LIMIT <= _chargeLv2ShotLeftRenderCount) _chargeLv2ShotLeftRenderCount = 0;
}

void rockman::hpSet()
{
	// HP BAR ����

	_hpBar->setX(ROCKMAN_HP_BAR_X);
	_hpBar->setY(ROCKMAN_HP_BAR_Y);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
}

void rockman::enemyCountLimit()
{
	// ���ʹ� ���� ���� �� ������ ��� ����
	// ���ʹ̰� ����ϸ� _countEnemy�� ī��Ʈ ����
	// �����ص� ���� �����ϸ� false ���� �������� ȭ�鿡�� ������� ����� (�ش� bool���� true�϶��� ��½�Ų��)

	if (_isEnemyDelete) _countEnemy++;

	if (_countEnemy == ROCKMAN_HP_ITEM_DROP_LIMIT)
	{
		_isEnemyDeleteHp = false;
	}

	if (_countEnemy == ENEMY_BOOM_LIMIT)
	{
		_countEnemy = 0;
		_isEnemyDelete = false;
	}
}

void rockman::rockmanKeySet()
{
	// ���� Ű�Ŵ���
	// �̵� = ����Ű, ���� = ZŰ, ���� = XŰ
	// Ư������(����) = ZŰ ������ �ֱ�
	// �ش� Ű���� ��ư�� ������ Ű�ִϸ��̼ǿ� ���ο� ��(����)�� �־ �ش� ������ �۵��ϰ� �����

	// _index
	// READY ���� ��� ī��Ʈ
	// _enemy->getMotion(), _p->getMotion()
	// ���ʹ� Ȥ�� �ص����� ����(RECT)�� ����(RECT)�� ���߸�(InterSectRect) �ش� ���� ��½��Ѽ� ������ ����(�ǰ� ���)�� �����Ų��
	// _isHitOn, _hitCheck
	// �ǰ��ϸ� �ش� bool ���� true�� �ٲ�鼭 ī��Ʈ�ǰ�, �� ī��Ʈ ���ȸ� �ǰ� ����� �����Ѵ�

	if (_index == INDEX_LIMIT)
	{
		_megaManDirection = ROCKMAN_START;
		_megaManMotion = KEYANIMANAGER->findAnimation("rockmanStart");
		_megaManMotion->start();
	}

	if (_enemy->getMotion() == 1 || _p->getMotion() == 1)
	{
		_megaManDirection = ROCKMAN_RIGHT_HIT;
		_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightHit");
		_megaManMotion->start();

		_isHitOn = true;
	}

	if (_isHitOn) _hitCheck++;

	if (_hitCheck >= HIT_MOSTION_LIMIT)
	{
		setRockManDirection(ROCKMAN_RIGHT_STAY);
		setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightStay"));
		getRockManMotion()->start();

		_hitCheck = 0;
		_isHitOn = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_megaManDirection = ROCKMAN_RIGHT_MOVE;
		_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMove");
		_megaManMotion->start();
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_megaManDirection = ROCKMAN_RIGHT_STAY;
		_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightStay");
		_megaManMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_megaManDirection = ROCKMAN_LEFT_MOVE;
		_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMove");
		_megaManMotion->start();
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_megaManDirection = ROCKMAN_LEFT_STAY;
		_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftStay");
		_megaManMotion->start();
	}
	
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (_megaManDirection == ROCKMAN_RIGHT_STOP
			|| _megaManDirection == ROCKMAN_RIGHT_STAY
			|| _megaManDirection == ROCKMAN_RIGHT_MOVE
			|| _megaManDirection == ROCKMAN_RIGHT_JUMP
			|| _megaManDirection == ROCKMAN_RIGHT_MOVE_JUMP)
		{
			_chargeShotRightCount++;
		}
		else if (_megaManDirection == ROCKMAN_LEFT_STOP
			|| _megaManDirection == ROCKMAN_LEFT_STAY
			|| _megaManDirection == ROCKMAN_LEFT_MOVE
			|| _megaManDirection == ROCKMAN_LEFT_JUMP
			|| _megaManDirection == ROCKMAN_LEFT_MOVE_JUMP)
		{
			_chargeShotLeftCount++;
		}
	}

	if (CHARGE_LV1_CHECK <= _chargeShotRightCount)
	{
		_isChargeRightCheck = true;
		_chargeLvImg = CHARGELV1;
	}

	if (CHARGE_LV2_CHECK <= _chargeShotRightCount)
	{
		_isChargeLv2RightCheck = true;
		_chargeLvImg = CHARGELV2;
	}

	if (_isChargeLv2RightCheck) _isChargeRightCheck = false;

	if (CHARGE_LV1_CHECK <= _chargeShotLeftCount)
	{
		_isChargeLeftCheck = true;
		_chargeLvImg = CHARGELV1;
	}

	if (CHARGE_LV2_CHECK <= _chargeShotLeftCount)
	{
		_isChargeLv2LeftCheck = true;
		_chargeLvImg = CHARGELV2;
	}

	if (_isChargeLv2LeftCheck) _isChargeLeftCheck = false;

	if (_isChargeRightCheck)
	{
		if (!_isChargeShotRight && !_isStopChargeShotRight)
		{
			if (KEYMANAGER->isOnceKeyUp('Z'))
			{
				_isChargeShotRight = true;
				_isStopChargeShotRight = true;
				_chargeShotRightCount = 0;

				if (_megaManDirection == ROCKMAN_RIGHT_STOP
					|| _megaManDirection == ROCKMAN_RIGHT_STAY)
				{
					_megaManDirection = ROCKMAN_RIGHT_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_RIGHT_MOVE)
				{
					_megaManDirection = ROCKMAN_RIGHT_MOVE_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMoveAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_RIGHT_JUMP)
				{
					_megaManDirection = ROCKMAN_RIGHT_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightJumpAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_RIGHT_MOVE_JUMP)
				{
					_megaManDirection = ROCKMAN_RIGHT_MOVE_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMoveJumpAttack");
					_megaManMotion->start();
				}
			}
		}
		else if (_isChargeShotRight) _isChargeShotRight = false;
		else if (_isChargeRightCheck) _isChargeRightCheck = false;
	}

	if (_isChargeLv2RightCheck)
	{
		if (!_isChargeLv2ShotRight && !_isStopChargeLv2ShotRight)
		{
			if (KEYMANAGER->isOnceKeyUp('Z'))
			{
				_isChargeLv2ShotRight = true;
				_isStopChargeLv2ShotRight = true;
				_chargeShotRightCount = 0;

				if (_megaManDirection == ROCKMAN_RIGHT_STOP
					|| _megaManDirection == ROCKMAN_RIGHT_STAY)
				{
					_megaManDirection = ROCKMAN_RIGHT_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_RIGHT_MOVE)
				{
					_megaManDirection = ROCKMAN_RIGHT_MOVE_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMoveAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_RIGHT_JUMP)
				{
					_megaManDirection = ROCKMAN_RIGHT_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightJumpAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_RIGHT_MOVE_JUMP)
				{
					_megaManDirection = ROCKMAN_RIGHT_MOVE_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMoveJumpAttack");
					_megaManMotion->start();
				}
			}
		}
		else if (_isChargeLv2ShotRight) _isChargeLv2ShotRight = false;
		else if (_isChargeLv2RightCheck) _isChargeLv2RightCheck = false;
	}

	if (_isChargeLeftCheck)
	{
		if (!_isChargeShotLeft && !_isStopChargeShotLeft)
		{
			if (KEYMANAGER->isOnceKeyUp('Z'))
			{
				_isChargeShotLeft = true;
				_isStopChargeShotLeft = true;
				_chargeShotLeftCount = 0;

				if (_megaManDirection == ROCKMAN_LEFT_STOP
					|| _megaManDirection == ROCKMAN_LEFT_STAY)
				{
					_megaManDirection = ROCKMAN_LEFT_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_LEFT_MOVE)
				{
					_megaManDirection = ROCKMAN_LEFT_MOVE_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMoveAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_LEFT_JUMP)
				{
					_megaManDirection = ROCKMAN_LEFT_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftJumpAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_LEFT_MOVE_JUMP)
				{
					_megaManDirection = ROCKMAN_LEFT_MOVE_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMoveJumpAttack");
					_megaManMotion->start();
				}
			}
		}
		else if (_isChargeShotLeft) _isChargeShotLeft = false;
		else if (_isChargeLeftCheck) _isChargeLeftCheck = false;
	}

	if (_isChargeLv2LeftCheck)
	{
		if (!_isChargeLv2ShotLeft && !_isStopChargeLv2ShotLeft)
		{
			if (KEYMANAGER->isOnceKeyUp('Z'))
			{
				_isChargeLv2ShotLeft = true;
				_isStopChargeLv2ShotLeft = true;
				_chargeShotLeftCount = 0;

				if (_megaManDirection == ROCKMAN_LEFT_STOP
					|| _megaManDirection == ROCKMAN_LEFT_STAY)
				{
					_megaManDirection = ROCKMAN_LEFT_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_LEFT_MOVE)
				{
					_megaManDirection = ROCKMAN_LEFT_MOVE_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMoveAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_LEFT_JUMP)
				{
					_megaManDirection = ROCKMAN_LEFT_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftJumpAttack");
					_megaManMotion->start();
				}

				if (_megaManDirection == ROCKMAN_LEFT_MOVE_JUMP)
				{
					_megaManDirection = ROCKMAN_LEFT_MOVE_JUMP_ATTACK;
					_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMoveJumpAttack");
					_megaManMotion->start();
				}
			}
		}
		else if (_isChargeLv2ShotLeft) _isChargeLv2ShotLeft = false;
		else if (_isChargeLv2LeftCheck) _isChargeLv2LeftCheck = false;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_chargeShotRightCount = 0;
		_chargeShotLeftCount = 0;

		if (_megaManDirection == ROCKMAN_RIGHT_STOP
			|| _megaManDirection == ROCKMAN_RIGHT_STAY
			|| _megaManDirection == ROCKMAN_RIGHT_MOVE
			|| _megaManDirection == ROCKMAN_RIGHT_JUMP
			|| _megaManDirection == ROCKMAN_RIGHT_MOVE_JUMP) _isRightShot = true;

		if (_megaManDirection == ROCKMAN_LEFT_STOP
			|| _megaManDirection == ROCKMAN_LEFT_STAY
			|| _megaManDirection == ROCKMAN_LEFT_MOVE
			|| _megaManDirection == ROCKMAN_LEFT_JUMP
			|| _megaManDirection == ROCKMAN_LEFT_MOVE_JUMP) _isLeftShot = true;

		if (_isRightShot)
		{
			if (_megaManDirection == ROCKMAN_RIGHT_STOP
				|| _megaManDirection == ROCKMAN_RIGHT_STAY)
			{
				_megaManDirection = ROCKMAN_RIGHT_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightAttack");
				_megaManMotion->start();
			}

			if (_megaManDirection == ROCKMAN_RIGHT_MOVE)
			{
				_megaManDirection = ROCKMAN_RIGHT_MOVE_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMoveAttack");
				_megaManMotion->start();
			}

			if (_megaManDirection == ROCKMAN_RIGHT_JUMP)
			{
				_megaManDirection = ROCKMAN_RIGHT_JUMP_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightJumpAttack");
				_megaManMotion->start();
			}

			if (_megaManDirection == ROCKMAN_RIGHT_MOVE_JUMP)
			{
				_megaManDirection = ROCKMAN_RIGHT_MOVE_JUMP_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMoveJumpAttack");
				_megaManMotion->start();
			}
		}

		if (_isLeftShot)
		{
			if (_megaManDirection == ROCKMAN_LEFT_STOP
				|| _megaManDirection == ROCKMAN_LEFT_STAY)
			{
				_megaManDirection = ROCKMAN_LEFT_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftAttack");
				_megaManMotion->start();
			}

			if (_megaManDirection == ROCKMAN_LEFT_MOVE)
			{
				_megaManDirection = ROCKMAN_LEFT_MOVE_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMoveAttack");
				_megaManMotion->start();
			}

			if (_megaManDirection == ROCKMAN_LEFT_JUMP)
			{
				_megaManDirection = ROCKMAN_LEFT_JUMP_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftJumpAttack");
				_megaManMotion->start();
			}

			if (_megaManDirection == ROCKMAN_LEFT_MOVE_JUMP)
			{
				_megaManDirection = ROCKMAN_LEFT_MOVE_JUMP_ATTACK;
				_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMoveJumpAttack");
				_megaManMotion->start();
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_jumpPower = JUMP_POWER;

		if (_megaManDirection == ROCKMAN_RIGHT_STOP
			|| _megaManDirection == ROCKMAN_RIGHT_STAY)
		{
			_megaManDirection = ROCKMAN_RIGHT_JUMP;
			_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightJump");
			_megaManMotion->start();
		}

		if (_megaManDirection == ROCKMAN_RIGHT_MOVE)
		{
			_megaManDirection = ROCKMAN_RIGHT_MOVE_JUMP;
			_megaManMotion = KEYANIMANAGER->findAnimation("rockmanRightMoveJump");
			_megaManMotion->start();
		}

		if (_megaManDirection == ROCKMAN_LEFT_STOP
			|| _megaManDirection == ROCKMAN_LEFT_STAY)
		{
			_megaManDirection = ROCKMAN_LEFT_JUMP;
			_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftJump");
			_megaManMotion->start();
		}

		if (_megaManDirection == ROCKMAN_LEFT_MOVE)
		{
			_megaManDirection = ROCKMAN_LEFT_MOVE_JUMP;
			_megaManMotion = KEYANIMANAGER->findAnimation("rockmanLeftMoveJump");
			_megaManMotion->start();
		}
	}
}

void rockman::rockmanPixelCheck()
{
	// �ȼ� �浹 �Լ�
	// ����(RECT)�� Ư�� �÷��� ������ � ���� ���.
	// ���� ��ġ�� ���� ������ ������(_rockProbeY) - ����(RECT) ��, ������ + ����(RECT) �Ʒ�
	// ���� ������ ������ RECT�� Y������ ���� ������ �� ��(TOP)�� �Ʒ�(BOTTOM)�� ����

	// 255, 0, 0	= �ٴ�	(�⺻)	����!
	// ����ó��: ����, �̵� ����, ���� ����, �̵� ���� ����

	if (_megaManDirection == ROCKMAN_START ||
		_megaManDirection == ROCKMAN_RIGHT_STOP ||
		_megaManDirection == ROCKMAN_RIGHT_STAY ||
		_megaManDirection == ROCKMAN_RIGHT_MOVE ||
		_megaManDirection == ROCKMAN_RIGHT_ATTACK ||
		_megaManDirection == ROCKMAN_RIGHT_MOVE_ATTACK ||
		_megaManDirection == ROCKMAN_RIGHT_HIT ||
		_megaManDirection == ROCKMAN_LEFT_STOP ||
		_megaManDirection == ROCKMAN_LEFT_STAY ||
		_megaManDirection == ROCKMAN_LEFT_MOVE ||
		_megaManDirection == ROCKMAN_LEFT_ATTACK ||
		_megaManDirection == ROCKMAN_LEFT_MOVE_ATTACK)
	{
		for (int i = _rockProbeY - ROCKMAN_PROBE_Y_UP; i < _rockProbeY + ROCKMAN_PROBE_Y_DOWN; ++i)
		{
			// �÷��� �Ǻ��� ������ ���� ��׶��忡 �׸��� (render�� ���� �ʴ´�)

			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixmap")->getMemDC(), _x, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			// �ٴ�
			// ���� ��ŭ �ݺ�(i)�� ���� ������ ����� �������� ���Ѵ�
			// _megaImg->getFrameHeight() / 2 == ���� �̹��� ũ���� ����
			// �ٴڿ� ��� ���� �����°� �߷��� 0���� �ʱ�ȭ�Ͽ� �ٴڿ� ������ ���� ���´�

			if (PROBE_RGB_RED)
			{
				_y = i - _megaImg->getFrameHeight() / 2;
				_jumpPower = 0;
				_gravity = 0;
				break;
			}
		}
	}
}

void rockman::rockmanSpeedSwitch()
{
	// �ش� ������ �ϰ� �ִ� ���� �̵��� �� �ֵ��� �ӵ��� ���ϰų� ���ش�

	switch (_megaManDirection)
	{
		case ROCKMAN_RIGHT_MOVE: case ROCKMAN_RIGHT_MOVE_ATTACK:
		_x += ROCKMAN_SPEED_NORMAL;
		break;

		case ROCKMAN_RIGHT_MOVE_JUMP: case ROCKMAN_RIGHT_MOVE_JUMP_ATTACK:
		_x += ROCKMAN_SPEED_JUMP;
		break;

		case ROCKMAN_LEFT_MOVE: case ROCKMAN_LEFT_MOVE_ATTACK:
		_x -= ROCKMAN_SPEED_NORMAL;
		break;

		case ROCKMAN_LEFT_MOVE_JUMP: case ROCKMAN_LEFT_MOVE_JUMP_ATTACK:
		_x -= ROCKMAN_SPEED_JUMP;
		break;
	}
}

void rockman::rockmanJump()
{
	// ������ �õ��ϸ� ������ Y�࿡�� �������� ���� ���� �ö󰡰� �Ѵ�
	// �� �� ������ �� ��ŭ Y���� �̵��ϸ� �ٽ� �߷°� ��ŭ�� ���� ������ �ٴ����� �������� ����� (Y���� �������� �����)

	_y -= _jumpPower;
	_jumpPower -= (_gravity = GRAVITY);
}

void rockman::itemCollision()
{
	// ������ ȹ�� ����
	// �����۵� RECT�� ���� InterSectRect�� �浹ó���Ѵ�

	RECT temp;
	if (IntersectRect(&temp, &_megaRc, &_enemy->getItemRc())) _currentHP = HP;
}

void rockman::rockmanInShow()
{
	if (_index == ROCKMAN_IN_COUNT) _isCheckIn = true;

	if (_isCheckIn)
	{
		_rockmanInRc.top += ROCKMAN_IN_SPEED;
		_rockmanInRc.bottom += ROCKMAN_IN_SPEED;
	}

	if (_rockmanInRc.bottom >= _megaRc.top) _isCheckIn = false;
}

void rockman::bulletRender()
{
	_rightBullet->render();
	_leftBullet->render();

	if (_isStopChargeShotRight) _chargeRightShot->render();
	if (_isStopChargeShotLeft) _chargeLeftShot->render();

	if (_isChargeRightCheck || _isChargeLeftCheck) _chargeImg->frameRender(getMemDC(), _megaRc.left - _cameraX, _megaRc.top - _cameraY);
	if (_isChargeLv2RightCheck || _isChargeLv2LeftCheck) _chargeLv2Img->frameRender(getMemDC(), _megaRc.left - _cameraX, _megaRc.top - _cameraY);

	if (_isStopChargeLv2ShotRight) _chargeLv2RightShot->render();
	if (_isStopChargeLv2ShotLeft) _chargeLv2LeftShot->render();
}

void rockman::normalBulletCollision()
{
	// ���ʹ� �浹 ó��
	// ������ ����(RECT)�� ���ʹ�(RECT)�� �浹������
	// �浹�ϴ� ���� ���ʹ��� X�� ��ǥ�� Y�� ��ǥ�� �����Ͽ� ��������
	// �浹 �� ���ʹ̴� �����ǰ�(deleteMinion) �Բ� ������ ����(deleteNormalRightBullet)�� �����ȴ�.
	// �浹 �� _countEnemy�� ī��Ʈ�� �����ؼ� ���� ����� ������ ����� �����Ѵ�
	// �ش� �浹 ó���� vector �������� ������ ���ʹ��� ������ ��ŭ�� �ݺ��Ѵ�

	RECT temp;
	for (int i = 0; i < _rightBullet->getVNormalBullet().size(); ++i)
	{
		for (int j = 0; j < _enemy->getVMinion().size(); ++j)
		{
			if (IntersectRect(&temp, &_rightBullet->getVNormalBullet()[i].rc, &_enemy->getVMinion()[j]->getRect()))
			{
				_enemy->posCheck(_enemy->getVMinion()[j]->getEnemyX(), _enemy->getVMinion()[j]->getEnemyY());
				_countEnemy++;
				_enemy->deleteMinion(j);
				_rightBullet->deleteNormalRightBullet(i);
				_isEnemyDelete = true;
				_isEnemyDeleteHp = true;
				break;
			}
		}
	}

	for (int i = 0; i < _leftBullet->getVNormalBullet().size(); ++i)
	{
		for (int j = 0; j < _enemy->getVMinion().size(); ++j)
		{
			if (IntersectRect(&temp, &_leftBullet->getVNormalBullet()[i].rc, &_enemy->getVMinion()[j]->getRect()))
			{
				_enemy->posCheck(_enemy->getVMinion()[j]->getEnemyX(), _enemy->getVMinion()[j]->getEnemyY());
				_countEnemy++;
				_enemy->deleteMinion(j);
				_leftBullet->deleteNormalLeftBullet(i);
				_isEnemyDelete = true;
				_isEnemyDeleteHp = true;
				break;
			}
		}
	}
}

void rockman::normalBulletBossCollision()
{
	// �ص��� �浹 ó��
	// �⺻���� ���� ���ʹ̿� �����ϳ� ���� ���� ��� �����(hitDamage) ���� �Ѱ��༭ ���ط����� ����Ѵ�
	// �ǰ� ��� ����� ���� _pMotion�� �Բ� �������ش�

	RECT temp;
	RECT rc = RectMake(_p->getPengdoriRc().left -_cameraX,
		_p->getPengdoriRc().top -_cameraY,
		_p->getPengdoriImage()->getFrameWidth(),
		_p->getPengdoriImage()->getFrameHeight());

	for (int i = 0; i < _rightBullet->getVNormalBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &_rightBullet->getVNormalBullet()[i].rc, &rc))
		{
			_rightBullet->deleteNormalRightBullet(i);
			_p->hitDamage(ATTACK);
			_pMotion = 1;
			break;
		}
	}

	for (int i = 0; i < _leftBullet->getVNormalBullet().size(); ++i)
	{
		if (IntersectRect(&temp, &_leftBullet->getVNormalBullet()[i].rc, &rc))
		{
			_leftBullet->deleteNormalLeftBullet(i);
			_p->hitDamage(ATTACK);
			_pMotion = 1;
			break;
		}
	}
}

void rockman::hitDamage(float damage)
{
	// ���ʹ�, �ص����� ����(�浹)�� ���� ��� �Է��� ���� �Ѿ�ͼ� �ش� �� ��ŭ ü���� ���̳ʽ� ���ش�

	_currentHP -= damage;
}

// Ű�ִϸŴ��� ���ۿ��� �ش� ��� ���� �� ����� ��ǿ� ���� �־��־��� ����� ���
// �ش� �Լ����� ���� ���� � ����� ������ �������ش�

void rockman::startMotion(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_RIGHT_STOP);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightStop"));
	r->getRockManMotion()->start();
}

void rockman::rightAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_RIGHT_STOP);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightStop"));
	r->getRockManMotion()->start();
}

void rockman::rightMoveAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_RIGHT_MOVE);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightMove"));
	r->getRockManMotion()->start();
}

void rockman::rightJump(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_RIGHT_STAY);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightStay"));
	r->getRockManMotion()->start();
}

void rockman::rightMoveJump(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_RIGHT_STOP);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightStop"));
	r->getRockManMotion()->start();
}

void rockman::rightJumpAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_RIGHT_STOP);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightStop"));
	r->getRockManMotion()->start();
}

void rockman::rightMoveJumpAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_RIGHT_STAY);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanRightStay"));
	r->getRockManMotion()->start();
}

void rockman::leftJump(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_LEFT_STAY);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanLeftStay"));
	r->getRockManMotion()->start();
}

void rockman::leftMoveJump(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_LEFT_STOP);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanLeftStop"));
	r->getRockManMotion()->start();
}

void rockman::leftAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_LEFT_STOP);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanLeftStop"));
	r->getRockManMotion()->start();
}

void rockman::leftMoveAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_LEFT_MOVE);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanLeftMove"));
	r->getRockManMotion()->start();
}

void rockman::leftJumpAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_LEFT_STOP);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanLeftStop"));
	r->getRockManMotion()->start();
}

void rockman::leftMoveJumpAttack(void * obj)
{
	rockman* r = (rockman*)obj;

	r->setRockManDirection(ROCKMAN_LEFT_STAY);
	r->setRockManMotion(KEYANIMANAGER->findAnimation("rockmanLeftStay"));
	r->getRockManMotion()->start();
}