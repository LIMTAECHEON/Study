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

	//프로그레스 바 이미지의 크기가 가로크기가 된다.
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
	//렌더는 그려주는 순서 영향을 받는다. 그려지는 순서대로 앞으로 나온다
	IMAGEMANAGER->render("backBar", getMemDC(),
		_x,
		_y , 
		0, 0,
		_progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());
	
	//앞에 그려지는 게이지의 가로크기를 조절한다.
	IMAGEMANAGER->render("frontBar", getMemDC(),
		_rcProgress.left,
		_rcProgress.top, 
		0, 0,
		_width, _height);
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	//수치가 들어오면 계산해준다.
	_height = (currentGauge / maxGauge) * _progressBarBottom->GetHeight();
}
