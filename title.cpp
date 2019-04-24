#include "stdafx.h"
#include "title.h"

title::title() { }
title::~title() { }

HRESULT title::init()
{
	_titleImg = TITLE_IMAGE;					// 시작 로고 이미지
	_rockmanImg = CLASSICE_ROCKMAN_ICON_IMAGE;	// 록맨(아이콘) 이미지
	_gsImg	= GAMESTART_IMAGE;					// 게임 시작 메뉴 이미지
	
	imageSetInit();								// 이미지 좌표 셋팅 함수

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	imageSetFrame();							// 클래식 록맨 아이콘 프레임
}

void title::render()
{
	_titleImg->render(getMemDC());										
	_rockmanImg->frameRender(getMemDC(), _iconRc.left, _iconRc.top);	
	_gsImg->render(getMemDC(), _gsRc.left, _gsRc.top);					
}

void title::imageSetInit()
{
	_gsPos.x = GAME_START_MENU_X;				// 게임 시작 메뉴 좌표
	_gsPos.y = GAME_START_MENU_Y;
	_gsRc = RectMakeCenter(_gsPos.x, _gsPos.y, _gsImg->GetCenterX(), _gsImg->GetCenterY());

	_iconPos.x = ROCKMAN_ICON_X;				// 록맨 아이콘 좌표
	_iconPos.y = ROCKMAN_ICON_Y;
	_iconRc = RectMakeCenter(_iconPos.x, _iconPos.y, _rockmanImg->getFrameWidth(), _rockmanImg->getFrameHeight());

	_rockmanImg->SetFrameY(0);					// 록맨 아이콘 프레임 시작 번호
}

void title::imageSetFrame()
{
	// _count 반복 속도에 따라 _index가 반복 증가
	// _index 수 만큼 이미지 프레임 출력, _index가 최대 프레임 수치를 넘으면 _index 초기화

	_count++;
	if (_count % ROCKMAN_ICON_IMAGE_SPEED == 0)
	{
		_index++;
		_rockmanImg->SetFrameX(_index);
		if (_index >= _rockmanImg->getMaxFrameX()) _index = -1;

		_count = 0;
	}
}
