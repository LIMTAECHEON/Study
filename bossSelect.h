#pragma once

#include "gameNode.h"
#include "Alldefine.h"

class bossSelect: public gameNode
{
private:

	RECT _bossSelUpRc;			// 팽도리 출현 연출 상단 RECT
	POINT _bossSelUpPos;		// 팽도리 출현 연출 상단 좌표
	image* _bossSelUpImg;		// 팽도리 출현 연출 상단 이미지

	RECT _bossSelDownRc;		// 팽도리 출현 연출 하단 RECT
	POINT _bossSelDownPos;		// 팽도리 출현 연출 하단 좌표
	image* _bossSelDownImg;		// 팽도리 출현 연출 하단 이미지

	RECT _bossNameRc;			// 팽도리 이름 출력 RECT
	POINT _bossNamePos;			// 팽도리 이름 좌표
	image* _bossNameImg;		// 팽도리 이름 이미지

	image* _bossSelImg;			// 팽도리 출현 연출 배경

	RECT _bossMoveRc;			// 팽도리 등장씬 아이콘 RECT
	POINT _bossMovePos;			// 팽도리 등장씬 아이콘 좌표
	image* _bossMoveImg;		// 팽도리 등장씬 아이콘 이미지

	int _count = 0;				// 팽도리 프레임 변수(속도조절)
	int _index = 0;				// 팽도리 프레임 변수(프레임출력)

public:

	bossSelect();
	~bossSelect();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();		// 이미지 좌표 셋팅 함수
	void imageMoveSpeedSet();	// 팽도리 등장 백그라운드 이미지 움직임
	void imageSetFrame();		// 팽도리 움직임 프레임
};

