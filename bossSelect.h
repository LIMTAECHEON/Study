#pragma once

#include "gameNode.h"
#include "Alldefine.h"

class bossSelect: public gameNode
{
private:

	RECT _bossSelUpRc;			// �ص��� ���� ���� ��� RECT
	POINT _bossSelUpPos;		// �ص��� ���� ���� ��� ��ǥ
	image* _bossSelUpImg;		// �ص��� ���� ���� ��� �̹���

	RECT _bossSelDownRc;		// �ص��� ���� ���� �ϴ� RECT
	POINT _bossSelDownPos;		// �ص��� ���� ���� �ϴ� ��ǥ
	image* _bossSelDownImg;		// �ص��� ���� ���� �ϴ� �̹���

	RECT _bossNameRc;			// �ص��� �̸� ��� RECT
	POINT _bossNamePos;			// �ص��� �̸� ��ǥ
	image* _bossNameImg;		// �ص��� �̸� �̹���

	image* _bossSelImg;			// �ص��� ���� ���� ���

	RECT _bossMoveRc;			// �ص��� ����� ������ RECT
	POINT _bossMovePos;			// �ص��� ����� ������ ��ǥ
	image* _bossMoveImg;		// �ص��� ����� ������ �̹���

	int _count = 0;				// �ص��� ������ ����(�ӵ�����)
	int _index = 0;				// �ص��� ������ ����(���������)

public:

	bossSelect();
	~bossSelect();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();		// �̹��� ��ǥ ���� �Լ�
	void imageMoveSpeedSet();	// �ص��� ���� ��׶��� �̹��� ������
	void imageSetFrame();		// �ص��� ������ ������
};

