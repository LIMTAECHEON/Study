#pragma once
#include <vector>
#include "gameNode.h"

struct tagBullet
{
	image* bulletImg;
	RECT rc;
	POINTFLOAT pos;
	float radius;
	float speed;
	float fireX, fireY;
	bool isFire;
	int count;
};

class playBullet : public gameNode
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _playBulletMax;

public:
	playBullet();
	~playBullet();

	HRESULT init(int playBulletMax, float range);
	void release();
	void update();
	void render();

	void playBulletFire(float x, float y);
	void playBulletMove();
	void deletePlayBullet(int playBulletMax);

	vector<tagBullet> getVPlayBullet()				{ return _vBullet; }
	vector<tagBullet>::iterator getVIPlayBullet()	{ return _viBullet; }
};

class playBullet2 : public gameNode
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _playBullet2Max;

public:
	playBullet2();
	~playBullet2();

	HRESULT init(int playBullet2Max, float range);
	void release();
	void update();
	void render();

	void playBullet2Fire(float x, float y);
	void playBullet2Move();
	void deletePlayBullet2(int playBullet2Max);

	vector<tagBullet> getVPlayBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIPlayBullet() { return _viBullet; }
};

class bossBullet : public gameNode
{
private:
	vector<tagBullet>				_vBullet;
	vector<tagBullet>::iterator		_viBullet;

	float _range;
	int _bossBulletMax;

public:
	bossBullet();
	~bossBullet();

	HRESULT init(int bossBulletMax, float range);
	void release();
	void update();
	void render();

	void bossBulletFire(float x, float y);
	void bossBulletMove();
	void deleteBossBullet(int bossBulletMax);

	vector<tagBullet> getVBossBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBossBullet() { return _viBullet; }
};
