#pragma once

#include "gameNode.h"
#include "enemy.h"
#include "minion.h"
#include "minion2.h"
#include "minion3.h"

class bullet;
class rockman;
class stageMap;

class enemyManager: public gameNode
{
private:

	typedef vector<enemy*>			 vEnemy;		// ���ʹ� vector
	typedef vector<enemy*>::iterator viEnemy;

private:

	vEnemy _vMinion;								// �⺻ �̴Ͼ� ����
	viEnemy _viMinion;
	
	bullet* _bullet;								// ���� (���� �Ѿ�)

	rockman* _rm;									// rockman Ŭ����
	enemy* _enemy;									// enemy Ŭ����

	image* _boomImg;								// ���� �̹���
	RECT _boomRc;									// ���� RECT
	POINTFLOAT _boomPos;							// ���� �̹��� ��ǥ

	image* _itemImg;								// ������ �̹���
	RECT _itemRc;									// ������ RECT
	POINTFLOAT _itemPos;							// ������ �̹��� ��ǥ
	float _itemProbeY = 0;							// ������ �ȼ� �浹 ���� Y�� ����

	int _count = 0;									// ���� ���� ������ ����(�ӵ�����)	
	int _index = 0;									// ���� ���� ������ ����(���������)

	int _count2 = 0;								// ������ ������ ����(�ӵ�����)	
	int _index2 = 0;								// ������ ������ ����(���������)

	int _motion = 0;								// �浹 ó�� Ȯ�� ����

	int _enemyShowCount = 0;						// ���ʹ� ���� ī��Ʈ

	bool _check01 = false;							// ������ ���� ���� ���ʹ� ���� �ð� ���� bool ����
	bool _check02 = false;
	bool _check03 = false;
	bool _check04 = false;
	bool _check05 = false;
	bool _check06 = false;
	bool _check07 = false;

	float _checkX;									// ����, ������ ��ǥ ����� X�� ��ǥ ����
	float _checkY;									// ����, ������ ��ǥ ����� Y�� ��ǥ ����

	float _cameraX;									// stageMap _cameraX set ����
	float _cameraY;									// stageMap _cameraY set ����

public:

	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageInit();								// �̹��� ��ǥ ���� �Լ�
	void enemyManagerDynamic();						// ���� �Ҵ� �Լ�
	void setMinion(int type);						// enemy Ŭ���� ��ǥ, Ÿ�� ���� �Ҵ� �Լ�
	void deleteMinion(int enemyNum);				// minion ���� �Լ�
	void imageSetFrame();							// �̹��� ������ �Լ�
	void minionBulletFire();						// ���ʹ� ���� �Լ�
	void collision();								// ���ʹ� ���� ���� �浹 �Լ�
	void itmePixelCheck();							// ������ �ȼ� �浹 �Լ�
	void posCheck(float x, float y);				// ���� ����, ������ ��ǥ �Լ�
	void deleteSpinMinion();						// ���ʹ� ���� �Լ�

	// enemyManager ����&�Լ��� �ٸ� Ŭ�������� ����ϱ� ���� get �Լ�
	 
	int getMotion() { return _motion; }
	enemy* getEnemy() { return _enemy; }
	RECT getItemRc() { return _itemRc; }
	
	vector<enemy*> getVMinion() { return _vMinion; }
	vector<enemy*>::iterator getVIMinion() { return _viMinion; }

	// ���� Ŭ����(stageMap) Set �Լ� 

	void setCameraX(float cameraX) { _cameraX = cameraX; }
	void setCameraY(float cameraY) { _cameraY = cameraY; }

	// rockman Ŭ������ �̾��ִ� ��巹�� ��ũ �Լ�

	void setRockmanMemoryAddressLink(rockman* player) { _rm = player; }
};

