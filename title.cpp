#include "stdafx.h"
#include "title.h"

title::title() { }
title::~title() { }

HRESULT title::init()
{
	_titleImg = TITLE_IMAGE;					// ���� �ΰ� �̹���
	_rockmanImg = CLASSICE_ROCKMAN_ICON_IMAGE;	// �ϸ�(������) �̹���
	_gsImg	= GAMESTART_IMAGE;					// ���� ���� �޴� �̹���
	
	imageSetInit();								// �̹��� ��ǥ ���� �Լ�

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	imageSetFrame();							// Ŭ���� �ϸ� ������ ������
}

void title::render()
{
	_titleImg->render(getMemDC());										
	_rockmanImg->frameRender(getMemDC(), _iconRc.left, _iconRc.top);	
	_gsImg->render(getMemDC(), _gsRc.left, _gsRc.top);					
}

void title::imageSetInit()
{
	_gsPos.x = GAME_START_MENU_X;				// ���� ���� �޴� ��ǥ
	_gsPos.y = GAME_START_MENU_Y;
	_gsRc = RectMakeCenter(_gsPos.x, _gsPos.y, _gsImg->GetCenterX(), _gsImg->GetCenterY());

	_iconPos.x = ROCKMAN_ICON_X;				// �ϸ� ������ ��ǥ
	_iconPos.y = ROCKMAN_ICON_Y;
	_iconRc = RectMakeCenter(_iconPos.x, _iconPos.y, _rockmanImg->getFrameWidth(), _rockmanImg->getFrameHeight());

	_rockmanImg->SetFrameY(0);					// �ϸ� ������ ������ ���� ��ȣ
}

void title::imageSetFrame()
{
	// _count �ݺ� �ӵ��� ���� _index�� �ݺ� ����
	// _index �� ��ŭ �̹��� ������ ���, _index�� �ִ� ������ ��ġ�� ������ _index �ʱ�ȭ

	_count++;
	if (_count % ROCKMAN_ICON_IMAGE_SPEED == 0)
	{
		_index++;
		_rockmanImg->SetFrameX(_index);
		if (_index >= _rockmanImg->getMaxFrameX()) _index = -1;

		_count = 0;
	}
}
