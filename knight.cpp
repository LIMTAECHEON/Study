#include "stdafx.h"
#include "knight.h"


knight::knight()
{
}


knight::~knight()
{
}

HRESULT knight::init()
{
	_image = IMAGEMANAGER->addFrameImage("knight", "knight.bmp", 0, 0, 612, 312, 9, 4, true, RGB(255, 0, 255));

	_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;

	_isJump = false;
	_JumpPower = _Gravity = 0;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_ySave = _y;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightStop", "knight", rightStop, 1, 6, true);

	int leftStop[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftStop", "knight", leftStop, 1, 6, true);

	int rightMove[] = { 1, 2, 3, 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightMove", "knight", rightMove, 6, 10, true);

	int leftMove[] = { 10, 11, 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftMove", "knight", leftMove, 6, 10, true);

	int arrRightAttack[] = { 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightAttack", "knight", arrRightAttack, 2, 10, false, rightFire, this);

	int arrLeftAttack[] = { 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftAttack", "knight", arrLeftAttack, 2, 10, false, leftFire, this);

	int sitRight[] = {18};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightSit", "knight", sitRight, 1, 18, true);
	
	int sitLeft[] = {27};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftSit", "knight", sitLeft, 1, 27, true);

	int sitRightAttack[] = { 19, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightSitAttack", "knight", sitRightAttack, 2, 10, false, rightSitFire, this);

	int sitLeftAttack[] = { 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftSitAttack", "knight", sitLeftAttack, 2, 10, false, leftSitFire, this);

	int RightJump[] = { 25 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightJump", "knight", RightJump, 1, 25, true);

	int LeftJump[] = { 34 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftJump", "knight", LeftJump, 1, 34, true);

	int rightMoveJump[] = {21};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightMoveJump", "knight", rightMoveJump, 1, 21, true);

	int leftMoveJump[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftMoveJump", "knight", leftMoveJump, 1, 30, true);

	_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");

	return S_OK;
}

void knight::release()
{
}

void knight::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_MOVE;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightMove");
		_knightMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
		_knightMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_MOVE;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftMove");
		_knightMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
		_knightMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_SIT;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightSit");
			_knightMotion->start();
		}
		if (_knightDirection == KNIGHTDIRECTION_LEFT_STOP)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_SIT;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftSit");
			_knightMotion->start();
		}

	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_knightDirection == KNIGHTDIRECTION_RIGHT_SIT)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
			_knightMotion->start();
		}
		if (_knightDirection == KNIGHTDIRECTION_LEFT_SIT)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_STOP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
			_knightMotion->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP ||
			_knightDirection == KNIGHTDIRECTION_RIGHT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_ATTACK;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightAttack");
			_knightMotion->start();
		}

		if (_knightDirection == KNIGHTDIRECTION_LEFT_STOP ||
			_knightDirection == KNIGHTDIRECTION_LEFT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_ATTACK;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftAttack");
			_knightMotion->start();
		}

		if (_knightDirection == KNIGHTDIRECTION_RIGHT_SIT)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_SIT_ATTACK;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightSitAttack");
			_knightMotion->start();
		}

		if (_knightDirection == KNIGHTDIRECTION_LEFT_SIT)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_SIT_ATTACK;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftSitAttack");
			_knightMotion->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_isJump = true;
		_Gravity = 0.2f;
		_JumpPower = 5;

		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP ||
			_knightDirection == KNIGHTDIRECTION_RIGHT_SIT)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightJump");
			_knightMotion->start();
		}

		if (_knightDirection == KNIGHTDIRECTION_LEFT_STOP ||
			_knightDirection == KNIGHTDIRECTION_LEFT_SIT)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftJump");
			_knightMotion->start();
		}

		if (_knightDirection == KNIGHTDIRECTION_RIGHT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_MOVE_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightMoveJump");
			_knightMotion->start();
		}

		if (_knightDirection == KNIGHTDIRECTION_LEFT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_MOVE_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftMoveJump");
			_knightMotion->start();
		}
	}

	switch (_knightDirection)
	{
		case KNIGHTDIRECTION_RIGHT_JUMP:
		if (_isJump)
		{
			_y -= _JumpPower;
			_JumpPower -= _Gravity;
		}
		if (_y >= _ySave)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
			_knightMotion->start();
		}
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

		case KNIGHTDIRECTION_RIGHT_MOVE: 
			_x += KNIGHTSPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

		case KNIGHTDIRECTION_RIGHT_MOVE_JUMP:

		if (_isJump)
		{
			_y -= _JumpPower;
			_JumpPower -= _Gravity;
		}

		if (_y >= _ySave)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
			_knightMotion->start();
		}

			_x += KNIGHTSPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;

		case KNIGHTDIRECTION_LEFT_JUMP:
			if (_isJump)
			{
				_y -= _JumpPower;
				_JumpPower -= _Gravity;
			}
			if (_y >= _ySave)
			{
				_knightDirection = KNIGHTDIRECTION_LEFT_STOP;
				_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
				_knightMotion->start();
			}
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;

		case KNIGHTDIRECTION_LEFT_MOVE:
			_x -= KNIGHTSPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;

		case KNIGHTDIRECTION_LEFT_MOVE_JUMP:

			if (_isJump)
			{
				_y -= _JumpPower;
				_JumpPower -= _Gravity;
			}

			if (_y >= _ySave)
			{
				_knightDirection = KNIGHTDIRECTION_LEFT_STOP;
				_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
				_knightMotion->start();
			}

			_x -= KNIGHTSPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
	}

	KEYANIMANAGER->update();
}

void knight::render()
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _knightMotion);
}

void knight::rightFire(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

void knight::leftFire(void * obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftStop"));
	k->getKnightMotion()->start();
}

void knight::rightSitFire(void * obj)
{
	knight* k = (knight*)obj;
	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_SIT);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightSit"));
	k->getKnightMotion()->start();
}

void knight::leftSitFire(void * obj)
{
	knight* k = (knight*)obj;
	k->setKnightDirection(KNIGHTDIRECTION_LEFT_SIT);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftSit"));
	k->getKnightMotion()->start();
}
