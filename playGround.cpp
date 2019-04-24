#include "stdafx.h"
#include "playGround.h"

playGround::playGround() { }
playGround::~playGround() { }

HRESULT playGround::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("loading", new loadingScene);		// 로딩 화면 (타이틀 화면)
	SCENEMANAGER->addScene("select", new stageSelect);			// 보스선택 화면
	SCENEMANAGER->addScene("bossSel", new bossSelect);			// 보스등장 화면
	SCENEMANAGER->addScene("map", new stageMap);				// 인게임 화면

	SCENEMANAGER->changeScene("loading");						// 로딩 화면씬 우선 순위

	SOUNDMANAGER->addSound("01", "sound/01.mp3", true, false);	// 타이틀 곡
	SOUNDMANAGER->addSound("02", "sound/02.mp3", true, false);	// 보스 선택창 곡
	SOUNDMANAGER->addSound("03", "sound/03.mp3", true, false);	// 보스 등장 화면 곡
	SOUNDMANAGER->addSound("04", "sound/04.mp3", true, true);	// 스테이지 테마곡

	_sceneCount = 0;											// 화면 전환 카운터

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

	// ENTER키를 누르면 _sceneCount가 +1씩 증가
	// _sceneCount의 정수값에 따라 SCENEMANAGER, SOUNDMANAGER를 switch문으로 호출
	
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
	
	// 현재 프레임, 실행 시간 등을 알아볼 수 있는 디버깅용 함수

	if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC());

	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

