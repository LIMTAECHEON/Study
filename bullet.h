#pragma once
#include "gameNode.h"
#include <vector>		// ���͸�! ������ �����̳�

struct  tagBullet		// ����(�Ϲ�����) ����ü
{
	image* img;			// �̹���
	RECT rc;			// RECT
	POINTFLOAT pos;		// ��ǥ
	POINTFLOAT firePos;	// �߻���ġ
	float angle;		// ����
	float radius;		// ������
	float speed;		// ���ǵ�
	bool isFire;		// �߻� ���� BOOL ����
	int count;			// ������ ī��Ʈ
};

// bullet�� ���ʹ� ���� �⺻ ����, �ص��� ���� �⺻ ����, Ư�� ���� 01, Ư�� ���� 02,
// �⺻ ���� ������, �⺻ ���� ����, ���� ���� ����1 ������, ���� ���� ����1 ����, ���� ���� ����2 ������, ���� ���� ����2 ����

// ======================================================================================================= [�ص��� & ���ʹ�]

class bullet : public gameNode				// ================================= ���ʹ�(����)
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

	float _cameraX;
	float _cameraY;
	
public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void bulletFire(float x, float y, float angle, float speed);
	void bulletMove();
	void deleteBullet(int bulletNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
};

class bossBullet : public gameNode				// ================================= �ص���(�Ϲ�)
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _bossBulletMax;

	float _cameraX;
	float _cameraY;
public:
	bossBullet();
	~bossBullet();

	HRESULT init(int bossBulletMax, float range);
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void bossBulletFire(float x, float y);
	void bossBulletMove();
	void deleteBossBullet(int bossBulletMax);

	vector<tagBullet> getVBossBullet() { return _vBullet;}
	vector<tagBullet>::iterator getVIBossBullet() { return _viBullet; }
};

class bossBullet2 : public gameNode				// ================================= �ص���(Ư��)
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _bossBulletMax;

	float _cameraX;
	float _cameraY;
public:
	bossBullet2();
	~bossBullet2();

	HRESULT init(int bossBullet2Max, float range);
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void bossBullet2Fire(float x, float y);
	void bossBullet2Move();
	void deleteBossBullet2(int bossBullet2Max);

	vector<tagBullet> getVBossBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBossBullet() { return _viBullet; }
};

class bossBullet3 : public gameNode				// ================================= �ص���(Ư��)
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _bossBulletMax;

	float _cameraX;
	float _cameraY;
public:
	bossBullet3();
	~bossBullet3();

	HRESULT init(int bossBullet3Max, float range);
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void bossBullet3Fire(float x, float y);
	void bossBullet3Move();
	void deleteBossBullet3(int bossBullet3Max);

	vector<tagBullet> getVBossBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBossBullet() { return _viBullet; }
};

class bossBullet4 : public gameNode				
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _bossBulletMax;

	float _cameraX;
	float _cameraY;
public:
	bossBullet4();
	~bossBullet4();

	HRESULT init(int bossBullet4Max, float range);
	void release();
	void update(float cameraX, float cameraY);
	void render();

	void bossBullet4Fire(float x, float y);
	void bossBullet4Move();
	void deleteBossBullet4(int bossBullet4Max);

	vector<tagBullet> getVBossBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBossBullet() { return _viBullet; }
};

// ======================================================================================================= [����(�ϸ�) �Ϲ�/���� ��/��]

class normalRightBullet : public gameNode	// ================================= �Ϲ����� ������
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _normalRightBulletMax;

	float _cameraX;
	float _cameraY;

public:
	normalRightBullet();
	~normalRightBullet();

	HRESULT init(int normalBulletMax, float range);
	void release();
	void update();
	void render();

	void normalRightBulletFire(float x, float y);
	void normalRightBulletMove();
	void deleteNormalRightBullet(int normalBulletMax);

	vector<tagBullet> getVNormalBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVINormalBullet() { return _viBullet; }
};

class normalLeftBullet : public gameNode	// ================================= �Ϲ����� ����
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _normalLeftBulletMax;

public:
	normalLeftBullet();
	~normalLeftBullet();

	HRESULT init(int normalBulletMax, float range);
	void release();
	void update();
	void render();

	void normalLeftBulletFire(float x, float y);
	void normalLeftBulletMove();
	void deleteNormalLeftBullet(int normalBulletMax);

	vector<tagBullet> getVNormalBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVINormalBullet() { return _viBullet; }
};

class chargeRightBullet : public gameNode	// ================================= ������ ������
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	float _range;
	int _chargeRightBulletMax;
public:
	chargeRightBullet();
	~chargeRightBullet();

	HRESULT init(int chargeBulletMax, float range);
	void release();
	void update();
	void render();

	void chargeRightBulletFire(float x, float y);
	void chargeRightBulletMove();
	void deleteChargeRightBullet(int chargeBulletMax);

	vector<tagBullet> getVChargeBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIChargeBullet() { return _viBullet; }
};

class chargeLeftBullet : public gameNode	// ================================= ������ ����
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	float _range;
	int _chargeLeftBulletMax;
public:
	chargeLeftBullet();
	~chargeLeftBullet();

	HRESULT init(int chargeBulletMax, float range);
	void release();
	void update();
	void render();

	void chargeLeftBulletFire(float x, float y);
	void chargeLeftBulletMove();
	void deleteChargeLeftBullet(int chargeBulletMax);

	vector<tagBullet> getVChargeBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIChargeBullet() { return _viBullet; }
};

class chargeLv2RightBullet : public gameNode	// ================================= ������ ����2 ������
{
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	float _range;
	int _chargeRightBulletMax;
public:
	chargeLv2RightBullet();
	~chargeLv2RightBullet();

	HRESULT init(int chargeLv2BulletMax, float range);
	void release();
	void update();
	void render();

	void chargeLv2RightBulletFire(float x, float y);
	void chargeLv2RightBulletMove();
	void deleteChargeLv2RightBullet(int chargeLv2BulletMax);

	vector<tagBullet> getVChargeBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIChargeBullet() { return _viBullet; }
};

class chargeLv2LeftBullet : public gameNode	// ================================= ������ ����2 ����
{
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	float _range;
	int _chargeLeftBulletMax;

public:
	chargeLv2LeftBullet();
	~chargeLv2LeftBullet();

	HRESULT init(int chargeLv2BulletMax, float range);
	void release();
	void update();
	void render();

	void chargeLv2LeftBulletFire(float x, float y);
	void chargeLv2LeftBulletMove();
	void deleteChargeLv2LeftBullet(int chargeLv2BulletMax);

	vector<tagBullet> getVChargeBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIChargeBullet() { return _viBullet; }
};
