#include "stdafx.h"
#include "bossSelect.h"

bossSelect::bossSelect() { }
bossSelect::~bossSelect() { }

HRESULT bossSelect::init()
{
	_bossSelUpImg	= BOSS_SELECT_BACKGROUND_UP_IMAGE;		// 팽도리 출현 상단 백 이미지
	_bossSelDownImg = BOSS_SELECT_BACKGROUND_DOWN_IMAGE;	// 팽도리 출현 하단 백 이미지
	_bossSelImg		= BOSS_SELECT_BACKGROUND_IMAGE;			// 팽도리 출현 배경
	_bossMoveImg	= BOSS_SELECT_MOSTION_IMAGE;			// 팽도리 등장 두둥!
	_bossNameImg	= BOSS_SELECT_NAME_IMAGE;				// 팽도리 이름

	imageSetInit();											// 이미지 좌표 셋팅 함수

	return S_OK;
}

void bossSelect::release()
{
}

void bossSelect::update()
{
	imageMoveSpeedSet();									// 팽도리 등장 백그라운드 이미지 움직임
	imageSetFrame();										// 팽도리 움직임 프레임
}

void bossSelect::render()
{
	_bossSelImg->render(getMemDC());
	_bossSelUpImg->render(getMemDC(), _bossSelUpRc.left, _bossSelUpRc.top);
	_bossSelDownImg->render(getMemDC(), _bossSelDownRc.left, _bossSelDownRc.top);
	_bossNameImg->render(getMemDC(), _bossNameRc.left, _bossNameRc.top);
	_bossMoveImg->frameRender(getMemDC(), _bossMoveRc.left, _bossMoveRc.top);
}

void bossSelect::imageSetInit()
{
	_bossNamePos.x = BOSS_NAME_HUD_X;						// 팽도리 글자(아이시 팽기고) 좌표
	_bossNamePos.y = BOSS_NAME_HUD_Y;
	_bossNameRc = RectMakeCenter(_bossNamePos.x, _bossNamePos.y, _bossNameImg->GetCenterX(), _bossNameImg->GetCenterY());

	_bossSelUpPos.x = BOSS_SELECT_UP_BACK_IMAGE_X;			// 팽도리 출현 상단(삼각형) 좌표
	_bossSelUpPos.y = BOSS_SELECT_UP_BACK_IMAGE_Y;
	_bossSelUpRc = RectMakeCenter(_bossSelUpPos.x, _bossSelUpPos.y, _bossSelUpImg->GetCenterX(), _bossSelUpImg->GetCenterY());

	_bossSelDownPos.x = BOSS_SELECT_DOWN_BACK_IMAGE_X;		// 팽도리 출현 하단(시그마 로고) 좌표
	_bossSelDownPos.y = BOSS_SELECT_DOWN_BACK_IMAGE_Y;
	_bossSelDownRc = RectMakeCenter(_bossSelDownPos.x, _bossSelDownPos.y, _bossSelDownImg->GetCenterX(), _bossSelDownImg->GetCenterY());

	_bossMovePos.x = BOSS_MOTION_X;							// 팽도리 등장씬(보스 이미지) 좌표
	_bossMovePos.y = BOSS_MOTION_Y;
	_bossMoveRc = RectMakeCenter(_bossMovePos.x, _bossMovePos.y, _bossMoveImg->getFrameWidth(), _bossMoveImg->getFrameHeight());
}

void bossSelect::imageMoveSpeedSet()
{
	// 중앙에는 보스 이미지를 프레임으로 렌더하여 미리 출력하고
	// 화면 상단과 화면 하단에서 보스 등장 연출을 움직이면서 출력
	// 보스 이름은 뒤이어 바로 렌더하기 위해 속도를 다르게 선언

	_bossSelUpRc.top += BACK_IMAGE_MOVE_SPEED;
	_bossSelUpRc.bottom += BACK_IMAGE_MOVE_SPEED;

	_bossSelDownRc.top -= BACK_IMAGE_MOVE_SPEED;
	_bossSelDownRc.bottom -= BACK_IMAGE_MOVE_SPEED;

	_bossNameRc.top -= NAME_HUD_MOVE_SPEED;
	_bossNameRc.bottom -= NAME_HUD_MOVE_SPEED;

	if (_bossSelDownRc.bottom <= BOSS_SELECT_BACK_IMAGE_STOP_Y)
	{
		_bossSelDownRc.top += BACK_IMAGE_MOVE_SPEED;
		_bossSelDownRc.bottom += BACK_IMAGE_MOVE_SPEED;
	}

	if (_bossSelUpRc.bottom >= _bossSelDownRc.bottom)
	{
		_bossSelUpRc.top -= BACK_IMAGE_MOVE_SPEED;
		_bossSelUpRc.bottom -= BACK_IMAGE_MOVE_SPEED;
	}

	if (_bossNameRc.top <= BOSS_NAME_HUD_STOP_Y)
	{
		_bossNameRc.top += NAME_HUD_MOVE_SPEED;
		_bossNameRc.bottom += NAME_HUD_MOVE_SPEED;
	}
}

void bossSelect::imageSetFrame()
{
	_count++;
	if (_count % BOSS_MOTION_ICON_IMAGE_SPEED == 0)
	{
		_index++;
		_bossMoveImg->SetFrameX(_index);
		if (_index >= _bossMoveImg->getMaxFrameX()) _index = 3;
		_count = 0;
	}
}
