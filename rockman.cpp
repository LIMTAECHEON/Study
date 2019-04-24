#include "stdafx.h"
#include "rockman.h"
#include "pengdori.h"									// 전방선언 클래스 헤더
#include "enemyManager.h"								// 전방선언 클래스 헤더

rockman::rockman() {}
rockman::~rockman() {}

HRESULT rockman::init()
{
	_megaImg = ROCKMAN_IMAGE;							// 엑스 이미지
	_rockmanIn = ROCKMAN_IN;							// 엑스 등장 연출
	_hpHUDImg = ROCKMAN_HP_HUD_IMAGE;					// HP HUD 이미지
	_chargeImg = CHARGE_LV1_IMAGE;						// 차지샷 이펙트 레벨1 이미지
	_chargeLv2Img = CHARGE_LV2_IMAGE;					// 차지샷 이펙트 레벨2 이미지
	_overImg = GAMEOVER_IMAGE;							// 게임 오버

	imageInit();										// 이미지 좌표 셋팅 함수
	rockmanDynamic();									// 동적 할당 함수
	rockmanMotion();									// 엑스 키애니메이션 함수
	
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

	rockmanJump();										// 엑스 점프 관련 함수
	rockmanPixelCheck();								// 엑스 픽셀 충돌 함수
	rockmanKeySet();									// 엑스 버튼 입력 함수
	rockmanSpeedSwitch();								// 엑스 모션 속도 제어 Switch문 함수
	hpSet();											// 엑스 HP BAR 함수

	chargeImageCount();									// 차지샷 이펙트 프레임 함수
	chargeImageLocation();								// 차지샷 발사 좌표 함수
	chargeImageRenderControl();							// 차지샷 이펙트 렌더 관리 함수
	
	_rightBullet->update();
	_leftBullet->update();
	_chargeRightShot->update();
	_chargeLeftShot->update();
	_chargeLv2RightShot->update();
	_chargeLv2LeftShot->update();

	normalBulletCollision();							// 엑스 공격 충돌 처리 함수 (에너미)
	normalBulletBossCollision();						// 엑스 공격 충돌 처리 함수 (보스)
	
	enemyCountLimit();									// 에너미 폭파 이펙트 카운트 제어 함수
	itemCollision();									// 아이템 이펙트 카운트 제어 함수

	rockmanInShow();									// 엑스 등장 연출 함수

	_isRightShot = _isLeftShot = false;					// 발사 상태 false 값으로 상태 초기화

	_rockProbeY = _y + _megaImg->getFrameHeight() / 2;
	_megaRc = RectMakeCenter(_x, _y, _megaImg->getFrameWidth(), _megaImg->getFrameHeight());
	
	// ===== 테스트

	if (KEYMANAGER->isOnceKeyDown('Q')) _currentHP -= 20;
}

void rockman::render()
{
	// 현재체력(_currentHP)이 1 이상이면 캐릭터, HP 이미지를 출력하고
	// 현재체력(_currentHP)이 0 미만이면 게임오버 이미지 출력하면서 캐릭터와 HP 이미지 출력을 종료한다

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

	// ========== 디버깅

	//if (KEYMANAGER->isToggleKey(VK_TAB))
	//{
	//	char str[128]; // 출력 테스트용 
	//	sprintf_s(str, "[엑스X축]: %f, [엑스Y축]: %f", _x, _y);
	//	TextOut(getMemDC(), 0, 60, str, strlen(str));
	//	sprintf_s(str, "[카메라X축]: %f, [카메라Y축]: %f", _cameraX, _cameraY);
	//	TextOut(getMemDC(), 0, 80, str, strlen(str));
	//	sprintf_s(str, "[카운트]: %d", _countEnemy);
	//	TextOut(getMemDC(), 0, 120, str, strlen(str));
	//}
}

void rockman::imageInit()
{
	_hpHUDX = ROCKMAN_HP_HUD_X;							// 엑스 HP HUD 좌표
	_hpHUDY = ROCKMAN_HP_HUD_Y;
	_hpHUDRc = RectMakeCenter(_hpHUDX, _hpHUDY, _hpHUDImg->GetWidth(), _hpHUDImg->GetHeight());

	_x = ROCKMAN_X;										// 엑스 최초 시작 좌표
	_y = ROCKMAN_Y;
	_rockProbeY = _y + _megaImg->getFrameHeight() / 2;	// 엑스 픽셀 충돌 체크 범위
	_megaRc = RectMakeCenter(_x, _y, _megaImg->getFrameWidth(), _megaImg->getFrameHeight());

	_rockmanInPos.x = ROCKMAN_X_IN;						// 엑스 등장 연출 좌표
	_rockmanInPos.y = ROCKMAN_Y_IN;
	_rockmanInRc = RectMakeCenter(_rockmanInPos.x, _rockmanInPos.y, _rockmanIn->GetWidth(), _rockmanIn->GetHeight());

	_chargeImg->SetFrameY(0);							// 차지샷 프레임 시작 값 초기화
	_chargeLvImg = CHARGELV1;
}

void rockman::rockmanDynamic()
{
	_p = new pengdori;									// 팽도리 동적 할당
	_p->init();

	_hpBar = new progressBar;							// HP 동적 할당
	_hpBar->init(ROCKMAN_HP_INIT);						// HP BAR X축 좌표, Y축 좌표, 가로길이, 세로길이
	_currentHP = _maxHP = HP;							// 현재체력 = 최대체력 = 100

	// 엑스 공격 관련 동적 할당
	// 오른쪽 일반 공격, 왼쪽 일반 공격
	// 오른쪽 차지 레벨1 공격, 왼쪽 차지 레벨1 공격
	// 오른쪽 차지 레벨2 공격, 왼쪽 차지 레벨2 공격

	_rightBullet = new normalRightBullet;				
	_rightBullet->init(ROCKMAN_BULLET_RANGE_INIT);		// 공격 수량(탄창), 사거리

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
	// 키애니메이션 매니저를 활용한 움직이는 이미지 출력
	// 3D 그래픽에서 활용되는 구조로 만들어진 이미지 프레임 출력 방식
	// image/rockman/ROCKMAN.bmp
	// 해당 모션 이름(string), 해당 모션 이미지 이름(const char), 
	// 출력할 순서의 이미지, 출력할 이미지의 갯수, 출력할 이미지의 속도(프레임), 
	// 반복 체크, 해당 모션 종료 후 출력 될 이미지, 해당 모션 종료 후 출력될 이미지 함수의 위치(obj)

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

	_megaManDirection = ROCKMAN_START;					// 최초 시작 모션의 종류 (emum문)
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
	// 엑스의 공격 위치 (발사 위치)
	// 공격도 카메라 값을 적용 받기 위해 발사 위치 - 카메라 좌표값을 해준다

	if (_isRightShot) _rightBullet->normalRightBulletFire((_megaRc.left + 120) - _cameraX, (_megaRc.top + 67) - _cameraY);
	if (_isLeftShot) _leftBullet->normalLeftBulletFire((_megaRc.left + 30) - _cameraX, (_megaRc.top + 67) - _cameraY);

	if (_isChargeShotRight) _chargeRightShot->chargeRightBulletFire((_megaRc.left + 120) - _cameraX, (_megaRc.top + 67) - _cameraY);
	if (_isChargeShotLeft) _chargeLeftShot->chargeLeftBulletFire((_megaRc.left + 30) - _cameraX, (_megaRc.top + 67) - _cameraY);

	if (_isChargeLv2ShotRight) _chargeLv2RightShot->chargeLv2RightBulletFire((_megaRc.left + 120) - _cameraX, (_megaRc.top + 67) - _cameraY);
	if (_isChargeLv2ShotLeft) _chargeLv2LeftShot->chargeLv2LeftBulletFire((_megaRc.left + 30) - _cameraX, (_megaRc.top + 67) - _cameraY);
}

void rockman::chargeImageRenderControl()
{
	// 차지샷 연출 관리를 위한 함수
	// Z키로 _isStopChargeShotRight를 true로 바꾸면 _chargeShotRightRenderCount 카운트 시작
	// 해당 카운트가 설정한 값(CHARGE_RENDER_LIMIT)을 넘어가면 레벨2로 변경, 이하일 경우는 레벨1이 적용
	// 레벨2가 될 경우 레벨2에도 동일하게 선언한 변수 카운트(_chargeLv2ShotRightRenderCount)가 작동. 구조 방식은 레벨1과 동일
	// 레벨2로 넘어가게 되면 레벨1의 카운트와 bool 변수는 0으로 초기화

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
	// HP BAR 셋팅

	_hpBar->setX(ROCKMAN_HP_BAR_X);
	_hpBar->setY(ROCKMAN_HP_BAR_Y);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
}

void rockman::enemyCountLimit()
{
	// 에너미 폭파 연출 및 아이템 드랍 설정
	// 에너미가 사망하면 _countEnemy가 카운트 시작
	// 설정해둔 값에 도달하면 false 값을 내보내서 화면에서 사라지게 만든다 (해당 bool값이 true일때만 출력시킨다)

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
	// 엑스 키매니저
	// 이동 = 방향키, 공격 = Z키, 점프 = X키
	// 특수공격(차지) = Z키 누르고 있기
	// 해당 키보드 버튼을 누르면 키애니메이션에 새로운 값(동작)을 넣어서 해당 동작이 작동하게 만든다

	// _index
	// READY 글자 출력 카운트
	// _enemy->getMotion(), _p->getMotion()
	// 에너미 혹은 팽도리의 공격(RECT)이 엑스(RECT)를 맞추면(InterSectRect) 해당 값을 출력시켜서 엑스의 동작(피격 모션)을 변경시킨다
	// _isHitOn, _hitCheck
	// 피격하면 해당 bool 값이 true로 바뀌면서 카운트되고, 그 카운트 동안만 피격 모션을 유지한다

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
	// 픽셀 충돌 함수
	// 엑스(RECT)가 특정 컬러를 만나면 어떤 값을 출력.
	// 검출 위치는 따로 선언한 범위값(_rockProbeY) - 엑스(RECT) 위, 범위값 + 엑스(RECT) 아래
	// 엑스 범위는 엑스의 RECT를 Y축으로 반을 나눴을 때 위(TOP)와 아래(BOTTOM)로 구분

	// 255, 0, 0	= 바닥	(기본)	빨강!
	// 예외처리: 점프, 이동 점프, 점프 공격, 이동 점프 공격

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
			// 컬러를 판별한 지도를 따로 백그라운드에 그린다 (render를 하지 않는다)

			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixmap")->getMemDC(), _x, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			// 바닥
			// 범위 만큼 반복(i)을 하지 않으면 제대로 검출하지 못한다
			// _megaImg->getFrameHeight() / 2 == 엑스 이미지 크기의 절반
			// 바닥에 닿는 순간 점프력과 중력을 0으로 초기화하여 바닥에 박히는 것을 막는다

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
	// 해당 동작을 하고 있는 동안 이동할 수 있도록 속도를 더하거나 빼준다

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
	// 점프를 시도하면 엑스의 Y축에서 점프력을 빼서 위로 올라가게 한다
	// 그 후 점프력 값 만큼 Y축이 이동하면 다시 중력값 만큼을 빼서 서서히 바닥으로 내려가게 만든다 (Y축이 내려가게 만든다)

	_y -= _jumpPower;
	_jumpPower -= (_gravity = GRAVITY);
}

void rockman::itemCollision()
{
	// 아이템 획득 관련
	// 아이템도 RECT로 만들어서 InterSectRect로 충돌처리한다

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
	// 에너미 충돌 처리
	// 엑스의 공격(RECT)과 에너미(RECT)가 충돌했을때
	// 충돌하는 순간 에너미의 X축 좌표와 Y축 좌표를 저장하여 내보낸다
	// 충돌 시 에너미는 삭제되고(deleteMinion) 함께 엑스의 공격(deleteNormalRightBullet)도 삭제된다.
	// 충돌 시 _countEnemy가 카운트를 시작해서 폭파 연출과 아이템 드랍을 제어한다
	// 해당 충돌 처리는 vector 시퀸스로 선언한 에너미의 사이즈 만큼을 반복한다

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
	// 팽도리 충돌 처리
	// 기본적인 식은 에너미와 동일하나 삭제 과정 대신 대미지(hitDamage) 값을 넘겨줘서 피해량으로 계산한다
	// 피격 모션 출력을 위해 _pMotion도 함께 내보내준다

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
	// 에너미, 팽도리의 공격(충돌)을 당할 경우 입력한 값이 넘어와서 해당 값 만큼 체력을 마이너스 해준다

	_currentHP -= damage;
}

// 키애니매니저 동작에서 해당 모션 종료 후 출력할 모션에 값을 넣어주었던 모션일 경우
// 해당 함수에서 종료 후의 어떤 모션이 될지를 결정해준다

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