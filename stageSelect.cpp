#include "stdafx.h"
#include "stageSelect.h"

stageSelect::stageSelect() { }
stageSelect::~stageSelect() { }

HRESULT stageSelect::init()
{
	_stageImg	= BOSS_SELECT_IMAGE; 	// �������� ����â �̹���
	_selectImg	= SELECT_ICON_IMAGE;	// �������� ���� ������ �̹���

	imageSetInit();						// �̹��� ��ǥ ���� �Լ�

	return S_OK;
}

void stageSelect::release()
{
}

void stageSelect::update()
{
	imageSetFrame();					// �������� ���� ������ ������
}

void stageSelect::render()
{
	_stageImg->render(getMemDC());
	_selectImg->frameRender(getMemDC(), _iconRc.left, _iconRc.top);
}

void stageSelect::imageSetInit()
{
	_iconPos.x = STAGE_SELECT_ICON_X;	// �������� ���� ������ ��ǥ
	_iconPos.y = STAGE_SELECT_ICON_Y;
	_iconRc = RectMakeCenter(_iconPos.x, _iconPos.y, _selectImg->getFrameWidth(), _selectImg->getFrameHeight());

	_selectImg->SetFrameY(0);			// �������� ���� ������ ������ ���� ��ȣ
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
