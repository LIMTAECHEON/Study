#pragma once

#include "gameNode.h"
#include "Alldefine.h"

class stageSelect: public gameNode
{
private:

	image* _stageImg;		// 스테이지 선택창 이미지

	RECT _iconRc;			// 스테이지 선택 아이콘
	POINT _iconPos;			// 스테이지 선택 아이콘 좌표
	image* _selectImg;		// 스테이지 선택 아이콘 이미지

	int _count = 0;			// 스테이지 선택 아이콘 프레임 변수(속도조절)
	int _index = 0;			// 스테이지 선택 아이콘 프레임 변수(프레임출력)

public:

	stageSelect();
	~stageSelect();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();	// 이미지 좌표 셋팅 함수
	void imageSetFrame();	// 스테이지 선택 아이콘 프레임
};

