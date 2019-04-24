#pragma once

#include "gameNode.h"
#include "Alldefine.h"
#include "bullet.h"

enum typeEnemy									 // ���ʹ� ���� enum��, ���ǻ� �̸��� ENEMY�� ����
{
	ENEMY01,
	ENEMY02,
	ENEMY03,
	ENEMY04,
	ENEMY05,
	ENEMY06,
	ENEMY07,
	ENEMY08,
	ENEMY09,
	ENEMY10,
	ENEMY11,
	ENEMY12,
	ENEMY13,	
	ENEMY14,
	ENEMY15,
};

struct tagEnemy									// ���ʹ� ���� ����ü
{
	image* imageName;							// �̹���
	RECT rc;									// RECT
	POINTFLOAT pos;								// ��ǥ
	float angle;								// ����
	float speed;								// �ӵ�
	float speedFast;							// �� �� ���� �ӵ�
};

// enemy -> minion, minion2, minion3 Ŭ������ public�� ����
// ���� �ٸ� ������ �����Ӱ� �̹���, ���� ������ �����ϱ� ����

class enemy: public gameNode
{
protected:

	tagEnemy _enemy;							// ���ʹ� ���� enum��
	typeEnemy _state;							// ���ʹ� ���� enum��

	bullet* _bullet;							// bullet Ŭ����

	int _currentFrameX, _currentFrameY = 0;		// �̹��� ������ ����
	int _count = 0;								// ���ʹ� ������ ����(�ӵ�����)
	int _fireCount = 0;							// ���ʹ� ���� ����
	int _rndFireCount = 0;						// ���ʹ� ���� Ƚ�� ����

	float _cameraX;								// stageMap _cameraX set ����
	float _cameraY;								// stageMap _cameraY set ����

public:

	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update(float cameraX, float cameraY);
	virtual void render();
	
	virtual void enemyImageManager();			// �̹��� �Ŵ��� �Լ�
	virtual void imageSetFrame();				// ���ʹ� ������ �̹��� ������
	virtual void enemySet();					// ���ʹ� ������ ���� �Լ�
	virtual bool enemyFire();					// ���ʹ� ���� Ƚ�� ���� �Լ�
	virtual void setType(int type);				// ���ʹ� �Ŵ��� Ÿ�� get/set �Լ�

	// enemy ����&�Լ��� �ٸ� Ŭ�������� ����ϱ� ���� get �Լ�

	virtual float getEnemyX() { return _enemy.pos.x; }
	virtual float getEnemyY() { return _enemy.pos.y; }
	virtual tagEnemy getEnemy() { return _enemy; }
	virtual typeEnemy getState() { return _state; }
	virtual RECT getRect() { return _enemy.rc; }
	virtual image* getImage() { return _enemy.imageName; }
};

