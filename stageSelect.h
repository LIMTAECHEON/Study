#pragma once

#include "gameNode.h"
#include "Alldefine.h"

class stageSelect: public gameNode
{
private:

	image* _stageImg;		// �������� ����â �̹���

	RECT _iconRc;			// �������� ���� ������
	POINT _iconPos;			// �������� ���� ������ ��ǥ
	image* _selectImg;		// �������� ���� ������ �̹���

	int _count = 0;			// �������� ���� ������ ������ ����(�ӵ�����)
	int _index = 0;			// �������� ���� ������ ������ ����(���������)

public:

	stageSelect();
	~stageSelect();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();	// �̹��� ��ǥ ���� �Լ�
	void imageSetFrame();	// �������� ���� ������ ������
};

