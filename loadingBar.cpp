#include "stdafx.h"
#include "loadingBar.h"

loadingBar::loadingBar()
{
}

loadingBar::~loadingBar()
{
}

HRESULT loadingBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("frontLoadBar", "image/ui/hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("backLoadBar", "image/ui/hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
	_width = _progressBarBottom->GetWidth();

	return S_OK;
}

void loadingBar::release()
{
}

void loadingBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->GetWidth(), _progressBarTop->GetHeight());
}

void loadingBar::render()
{
	//������ �׷��ִ� ���� ������ �޴´�. �׷����� ������� ������ ���´�
	IMAGEMANAGER->render("backLoadBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		_y + _progressBarBottom->GetHeight() / 2, 0, 0,
		_progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	//�տ� �׷����� �������� ����ũ�⸦ �����Ѵ�.
	IMAGEMANAGER->render("frontLoadBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		_y + _progressBarBottom->GetHeight() / 2, 0, 0,
		_width, _progressBarBottom->GetHeight());
}

void loadingBar::setGauge(float currentGauge, float maxGauge)
{
	//��ġ�� ������ ������ش�.
	_width = (currentGauge / maxGauge) * _progressBarBottom->GetWidth();
}
