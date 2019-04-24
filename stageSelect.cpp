#include "stdafx.h"
#include "stageSelect.h"

stageSelect::stageSelect() { }
stageSelect::~stageSelect() { }

HRESULT stageSelect::init()
{
	_stageImg	= BOSS_SELECT_IMAGE; 	// 스테이지 선택창 이미지
	_selectImg	= SELECT_ICON_IMAGE;	// 스테이지 선택 아이콘 이미지

	imageSetInit();						// 이미지 좌표 셋팅 함수

	return S_OK;
}

void stageSelect::release()
{
}

void stageSelect::update()
{
	imageSetFrame();					// 스테이지 선택 아이콘 프레임
}

void stageSelect::render()
{
	_stageImg->render(getMemDC());
	_selectImg->frameRender(getMemDC(), _iconRc.left, _iconRc.top);
}

void stageSelect::imageSetInit()
{
	_iconPos.x = STAGE_SELECT_ICON_X;	// 스테이지 선택 아이콘 좌표
	_iconPos.y = STAGE_SELECT_ICON_Y;
	_iconRc = RectMakeCenter(_iconPos.x, _iconPos.y, _selectImg->getFrameWidth(), _selectImg->getFrameHeight());

	_selectImg->SetFrameY(0);			// 스테이지 선택 아이콘 프레임 시작 번호
}

void stageSelect::imageSetFrame()
{
	_count++;
	if (_count % STAGE_SELECT_ICON_IMAGESPEED == 0)
	{
		_index++;
		_selectImg->SetFrameX(_index);
		if (_index >= _selectImg->getMaxFrameX()) _index = -1;
		_count = 0;
	}
}
