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
	IMAGEMANAGER->addImage("�̸�", "name.bmp", 108, 33, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü��", "life.bmp", 134, 99, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("����ü��1", "hp01.bmp", 162, 39, true, RGB(255, 0, 255));

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
	//IMAGEMANAGER->findImage("�̸�")->render(getMemDC(), 150, 80);
	//IMAGEMANAGER->findImage("ü��")->render(getMemDC(), 30, 20);
	//IMAGEMANAGER->findImage("����ü��1")->render(getMemDC(), 330, 550);
}
