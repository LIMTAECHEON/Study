#include "stdafx.h"
#include "UI.h"


UI::UI()
{
}


UI::~UI()
{
}

HRESULT UI::init()
{
	IMAGEMANAGER->addImage("이름", "name.bmp", 108, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력", "life.bmp", 134, 99, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("보스체력1", "hp01.bmp", 162, 39, true, RGB(255, 0, 255));

	return S_OK;
}

void UI::release()
{
}

void UI::update()
{

}

void UI::render()
{
	//IMAGEMANAGER->findImage("이름")->render(getMemDC(), 150, 80);
	//IMAGEMANAGER->findImage("체력")->render(getMemDC(), 30, 20);
	//IMAGEMANAGER->findImage("보스체력1")->render(getMemDC(), 330, 550);
}
