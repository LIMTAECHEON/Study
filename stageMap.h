#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "enemyManager.h"
#include "rockman.h"		// PlayGround/rockman
#include "pengdori.h"

class stageMap: public gameNode
{
private:

	image* _map;			// ���� ��ü �� �̹���
	image* _pixMap;			// ���� ��ü �� �ȼ��浹 üũ �̹���

	image* _mapZ;
	RECT _mapZRc;
	POINTFLOAT _mapZPos;
	
	image* _doorImg;		// �ص��� ù��° �湮 �̹���
	RECT _doorRc;			// �ص��� ù��° �湮 RECT
	POINTFLOAT _doorPos;	// �ص��� ù��° �湮 POINT ��ǥ

	image* _door2Img;
	RECT _door2Rc;			// �ص��� �ι�° �湮 RECT
	POINTFLOAT _door2Pos;	// �ص��� �ι�° �湮 POINT ��ǥ

	bool _isOpen = false;	// ù��° �湮 BOOL ����
	bool _isOpen2 = false;	// �ι�° �湮 BOOL ����

	rockman* _rockman;		// rockman Ŭ����
	pengdori* _boss;		// pengdori Ŭ����
	enemyManager* _enemy;	// enemyManager Ŭ����
	
	RECT _readyRc;			// READY ���� RECT
	POINT _readyPos;		// READY ���� POINT ��ǥ
	image* _readyImg;		// READY ���� �̹���

	int _count = 0;			// READY ���� ������ ����(�ӵ�����)
	int _index = 0;			// READY ���� ������ ����(���������)
	bool _readyHUDCount;	// READY ���� ��� ���� BOOL ����

	int _count2 = 0;		// DOOR1 ������ ����(�ӵ�����)
	int _index2 = 0;		// DOOR1 ���� ������ ����(���������)

	int _count3 = 0;		// DOOR2 ���� ������ ����(�ӵ�����)
	int _index3 = 0;		// DOOR2 ���� ������ ����(���������)

	float _playerX;			// rockman Ŭ���� X�� ��ǥ ������ ���� ����
	float _playerY;			// rockman Ŭ���� Y�� ��ǥ ������ ���� ����

	float _cameraX;			// ī�޶� ���� X�� ��ǥ
	float _cameraY;			// ī�޶� ���� Y�� ��ǥ
	bool _cameraStop;		// �ص��� ī�޶� ���� BOOL ����

public:

	stageMap();
	~stageMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imageSetInit();	// �̹��� ��ǥ ���� �Լ�
	void stageMapDynamic();	// ���� �Ҵ� �Լ�
	void bossRoomLimit();	// �ص��� �� ī�޶� ���� �Լ�
	void cameraSet();		// ī�޶� ����(get/set) �Լ�
	void imageSetFrame();	// READY �̹��� ������

	// rockman Ŭ���� ī�޶� ��ǥ�� �ޱ� ���� ��ǥ �� �Լ� ����
	// rockman Ŭ���� ���� �̹��� ����� �����ϱ� ���� index �� �Լ� ����
	float getCameraX() { return _cameraX;}
	float getCameraY() { return _cameraY;}
	int getIndex() { return _index; }
};

