#pragma once

#include "gameNode.h"
#include "Alldefine.h"

class title: public gameNode
{
private:

	image* _titleImg;		// 시작 로고 이미지

	RECT _iconRc;			// 록맨 아이콘
	POINT _iconPos;			// 록맨 아이콘 좌표
	image* _rockmanImg;		// 록맨 아이콘 이미지
	int _count = 0;			// 록맨 아이콘 프레임 변수(속도조절)
	int _index = 0;			// 록맨 아이콘 프레임 변수(프레임출력)

	RECT _gsRc;				// 게임 시작
	POINT _gsPos;			// 게임 시작 좌표
	image* _gsImg;			// 게임 시작 이미지

	RECT _omRc;				// 게임 옵션
	POINT _omPos;			// 게임 옵션 좌표
	image* _omImg;			// 게임 옵션 이미지

public:

	title();
	~title();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();	// 이미지 좌표 셋팅 함수
	void imageSetFrame();	// 클래식 록맨 아이콘 프레임
};

