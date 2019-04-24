#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("frontBar", "image/ui/hp01.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("backBar", "image/ui/hp02.bmp", x, y, width, height, true, RGB(255, 0, 255));

	//���α׷��� �� �̹����� ũ�Ⱑ ����ũ�Ⱑ �ȴ�.
	_width = _progressBarBottom->GetWidth();
	_height = _progressBarBottom->GetHeight();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMake(_x, _y + _progressBarBottom->GetHeight() - _height, _progressBarTop->GetWidth(), _height);
}

void progressBar::render()
{
	//������ �׷��ִ� ���� ������ �޴´�. �׷����� ������� ������ ���´�
	IMAGEMANAGER->render("backBar", getMemDC(),
		_x,
		_y , 
		0, 0,
		_progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());
	
	//�տ� �׷����� �������� ����ũ�⸦ �����Ѵ�.
	IMAGEMANAGER->render("frontBar", getMemDC(),
		_rcProgress.left,
		_rcProgress.top, 
		0, 0,
		_width, _height);
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//��ġ�� ������ ������ش�.
	_height = (currentGauge / maxGauge) * _progressBarBottom->GetHeight();
}
