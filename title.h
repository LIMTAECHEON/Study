#pragma once

#include "gameNode.h"
#include "Alldefine.h"

class title: public gameNode
{
private:

	image* _titleImg;		// ���� �ΰ� �̹���

	RECT _iconRc;			// �ϸ� ������
	POINT _iconPos;			// �ϸ� ������ ��ǥ
	image* _rockmanImg;		// �ϸ� ������ �̹���
	int _count = 0;			// �ϸ� ������ ������ ����(�ӵ�����)
	int _index = 0;			// �ϸ� ������ ������ ����(���������)

	RECT _gsRc;				// ���� ����
	POINT _gsPos;			// ���� ���� ��ǥ
	image* _gsImg;			// ���� ���� �̹���

	RECT _omRc;				// ���� �ɼ�
	POINT _omPos;			// ���� �ɼ� ��ǥ
	image* _omImg;			// ���� �ɼ� �̹���

public:

	title();
	~title();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();	// �̹��� ��ǥ ���� �Լ�
	void imageSetFrame();	// Ŭ���� �ϸ� ������ ������
};

