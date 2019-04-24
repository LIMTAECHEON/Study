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

	//프로그레스 바 이미지의 크기가 가로크기가 된다.
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
	//렌더는 그려주는 순서 영향을 받는다. 그려지는 순서대로 앞으로 나온다
	IMAGEMANAGER->render("backLoadBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		_y + _progressBarBottom->GetHeight() / 2, 0, 0,
		_progressBarBottom->GetWidth(), _progressBarBottom->GetHeight());

	//앞에 그려지는 게이지의 가로크기를 조절한다.
	IMAGEMANAGER->render("frontLoadBar", getMemDC(),
		_rcProgress.left + _progressBarBottom->GetWidth() / 2,
		_y + _progressBarBottom->GetHeight() / 2, 0, 0,
		_width, _progressBarBottom->GetHeight());
}

void loadingBar::setGauge(float currentGauge, float maxGauge)
{
	//수치가 들어오면 계산해준다.
	_width = (currentGauge / maxGauge) * _progressBarBottom->GetWidth();
}
