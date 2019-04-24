#include "stdafx.h"
#include "playGround.h"

playGround::playGround() { }
playGround::~playGround() { }

HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("loading", new loadingScene);		// �ε� ȭ�� (Ÿ��Ʋ ȭ��)
	SCENEMANAGER->addScene("select", new stageSelect);			// �������� ȭ��
	SCENEMANAGER->addScene("bossSel", new bossSelect);			// �������� ȭ��
	SCENEMANAGER->addScene("map", new stageMap);				// �ΰ��� ȭ��

	SCENEMANAGER->changeScene("loading");						// �ε� ȭ��� �켱 ����

	SOUNDMANAGER->addSound("01", "sound/01.mp3", true, false);	// Ÿ��Ʋ ��
	SOUNDMANAGER->addSound("02", "sound/02.mp3", true, false);	// ���� ����â ��
	SOUNDMANAGER->addSound("03", "sound/03.mp3", true, false);	// ���� ���� ȭ�� ��
	SOUNDMANAGER->addSound("04", "sound/04.mp3", true, true);	// �������� �׸���

	_sceneCount = 0;											// ȭ�� ��ȯ ī����

	return S_OK;
}

void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

	// ENTERŰ�� ������ _sceneCount�� +1�� ����
	// _sceneCount�� �������� ���� SCENEMANAGER, SOUNDMANAGER�� switch������ ȣ��
	
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _sceneCount++;

	switch (_sceneCount)
	{
		case 0:
		//SOUNDMANAGER->play("02", VOLUME);
		break;

		case 1:
		SCENEMANAGER->changeScene("select");
		//SOUNDMANAGER->stop("01");
		//SOUNDMANAGER->play("03", VOLUME);
		break;

		case 2:
		SCENEMANAGER->changeScene("bossSel");
		//SOUNDMANAGER->stop("02");
		//SOUNDMANAGER->play("04", VOLUME);
		break;
	
		case 3:
		SCENEMANAGER->changeScene("map");
		//SOUNDMANAGER->stop("03");
		break;
	}
}

void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//===========================================================

	SCENEMANAGER->render();
	
	// ���� ������, ���� �ð� ���� �˾ƺ� �� �ִ� ������ �Լ�

	if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC());

	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

