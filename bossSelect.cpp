#include "stdafx.h"
#include "bossSelect.h"

bossSelect::bossSelect() { }
bossSelect::~bossSelect() { }

HRESULT bossSelect::init()
{
	_bossSelUpImg	= BOSS_SELECT_BACKGROUND_UP_IMAGE;		// �ص��� ���� ��� �� �̹���
	_bossSelDownImg = BOSS_SELECT_BACKGROUND_DOWN_IMAGE;	// �ص��� ���� �ϴ� �� �̹���
	_bossSelImg		= BOSS_SELECT_BACKGROUND_IMAGE;			// �ص��� ���� ���
	_bossMoveImg	= BOSS_SELECT_MOSTION_IMAGE;			// �ص��� ���� �ε�!
	_bossNameImg	= BOSS_SELECT_NAME_IMAGE;				// �ص��� �̸�

	imageSetInit();											// �̹��� ��ǥ ���� �Լ�

	return S_OK;
}

void bossSelect::release()
{
}

void bossSelect::update()
{
	imageMoveSpeedSet();									// �ص��� ���� ��׶��� �̹��� ������
	imageSetFrame();										// �ص��� ������ ������
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
	_bossNamePos.x = BOSS_NAME_HUD_X;						// �ص��� ����(���̽� �ر��) ��ǥ
	_bossNamePos.y = BOSS_NAME_HUD_Y;
	_bossNameRc = RectMakeCenter(_bossNamePos.x, _bossNamePos.y, _bossNameImg->GetCenterX(), _bossNameImg->GetCenterY());

	_bossSelUpPos.x = BOSS_SELECT_UP_BACK_IMAGE_X;			// �ص��� ���� ���(�ﰢ��) ��ǥ
	_bossSelUpPos.y = BOSS_SELECT_UP_BACK_IMAGE_Y;
	_bossSelUpRc = RectMakeCenter(_bossSelUpPos.x, _bossSelUpPos.y, _bossSelUpImg->GetCenterX(), _bossSelUpImg->GetCenterY());

	_bossSelDownPos.x = BOSS_SELECT_DOWN_BACK_IMAGE_X;		// �ص��� ���� �ϴ�(�ñ׸� �ΰ�) ��ǥ
	_bossSelDownPos.y = BOSS_SELECT_DOWN_BACK_IMAGE_Y;
	_bossSelDownRc = RectMakeCenter(_bossSelDownPos.x, _bossSelDownPos.y, _bossSelDownImg->GetCenterX(), _bossSelDownImg->GetCenterY());

	_bossMovePos.x = BOSS_MOTION_X;							// �ص��� �����(���� �̹���) ��ǥ
	_bossMovePos.y = BOSS_MOTION_Y;
	_bossMoveRc = RectMakeCenter(_bossMovePos.x, _bossMovePos.y, _bossMoveImg->getFrameWidth(), _bossMoveImg->getFrameHeight());
}

void bossSelect::imageMoveSpeedSet()
{
	// �߾ӿ��� ���� �̹����� ���������� �����Ͽ� �̸� ����ϰ�
	// ȭ�� ��ܰ� ȭ�� �ϴܿ��� ���� ���� ������ �����̸鼭 ���
	// ���� �̸��� ���̾� �ٷ� �����ϱ� ���� �ӵ��� �ٸ��� ����

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
