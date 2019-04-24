#pragma once

// 클래스 내 정수값 혹은 매니저 초기화 관련 define문 헤더
// 0, NULL을 제외한 모든 값을 이곳에 모아둔다.
// 최상단은 공용으로 사용하는 define문으로, 모든 클래스에서 공용으로 사용 가능한 값.
// 다음에는 const 변수로 선언해서 사용하도록 하자!

// ===================== IMAGEMANAGER 통합

#define TITLE_IMAGE							IMAGEMANAGER->addImage("main", "image/title/start_title.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0))		
#define CLASSICE_ROCKMAN_ICON_IMAGE			IMAGEMANAGER->addFrameImage("icon", "image/ui/start_rm.bmp", 0, 0, 360, 90, 4, 1, true, RGB(255, 0, 255))
#define GAMESTART_IMAGE						IMAGEMANAGER->addImage("start", "image/ui/start_s.bmp", 366, 27, false, RGB(0, 0, 0))

#define LOADING_BACKGROUND_IMAGE			IMAGEMANAGER->addImage("set", "image/ui/test.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0))
#define LOADINGMAN_IMAGE					IMAGEMANAGER->addFrameImage("loadMan", "image/ui/loadman.bmp", 0, 0, 408, 192, 4, 1, true, RGB(255, 0, 255))

#define BOSS_SELECT_IMAGE					IMAGEMANAGER->addImage("select", "image/title/stage_sel.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0))
#define SELECT_ICON_IMAGE					IMAGEMANAGER->addFrameImage("selIcon", "image/ui/stage_icon.bmp", 0, 0, 540, 114, 4, 1, true, RGB(255, 0, 255))

#define BOSS_SELECT_BACKGROUND_IMAGE		IMAGEMANAGER->addImage("bossSel", "image/title/boss_back.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0))	
#define BOSS_SELECT_BACKGROUND_UP_IMAGE		IMAGEMANAGER->addImage("selUp", "image/title/boss_sel_up.bmp", 800, 244, false, RGB(0, 0, 0))
#define BOSS_SELECT_BACKGROUND_DOWN_IMAGE	IMAGEMANAGER->addImage("selDown", "image/title/boss_sel_down.bmp", 348, 244, true, RGB(255, 0, 255))
#define BOSS_SELECT_MOSTION_IMAGE			IMAGEMANAGER->addFrameImage("bossMove", "image/title/boss_sel_move.bmp", 0, 0, 750, 150, 5, 1, true, RGB(255, 0, 255))
#define BOSS_SELECT_NAME_IMAGE				IMAGEMANAGER->addImage("bossName", "image/title/boss_name.bmp", 430, 82, true, RGB(255, 0, 255))

#define GAME_MAP_IMAGE						IMAGEMANAGER->addImage("map", "image/map/27013_1.bmp", 7833, 2127, true, RGB(255, 0, 255))
#define GAME_PIX_MAP_IMAGE					IMAGEMANAGER->addImage("pixmap", "image/map/27013_pix.bmp", 7833, 2127, true, RGB(255, 0, 255))
#define MAP_Z_ORDER_IMAGE					IMAGEMANAGER->addImage("mapX", "image/map/27013_1_back.bmp", 144, 276, true, RGB(255, 0, 255))
#define BOSS_ROOM_DOOR_IMAGE				IMAGEMANAGER->addFrameImage("door", "image/map/door2.bmp", 0, 0, 384, 144, 4, 1, true, RGB(255, 0, 255))
#define BOSS_ROOM_DOOR2_IMAGE				IMAGEMANAGER->addFrameImage("door2", "image/map/door2.bmp", 0, 0, 384, 144, 4, 1, true, RGB(255, 0, 255))
#define READY_IMAGE							IMAGEMANAGER->addFrameImage("ready", "image/ui/READY.bmp", 0, 0, 1512, 45, 12, 1, true, RGB(255, 0, 255))

#define ENEMY_EXPLOSION_IMAGE				IMAGEMANAGER->addFrameImage("boom", "image/effect/boom.bmp", 0, 0, 672, 96, 7, 1, true, RGB(255, 0, 255))
#define ITEM_IMAGE							IMAGEMANAGER->addFrameImage("hp", "image/item/hp.bmp", 0, 0, 96, 48, 2, 1, true, RGB(255, 0, 255))

#define ROCKMAN_IMAGE						IMAGEMANAGER->addFrameImage("rockman", "image/rockman/ROCKMAN.bmp", 0, 0, 1800, 1500, 12, 10, true, RGB(255, 0, 255))
#define ROCKMAN_IN							IMAGEMANAGER->addImage("in", "image/rockman/rockman_in.bmp", 150, 150, true, RGB(255, 0, 255))
#define ROCKMAN_HP_HUD_IMAGE				IMAGEMANAGER->addImage("hpbar", "image/ui/hp_bar.bmp", 48, 162, true, RGB(255, 0, 255))
#define CHARGE_LV1_IMAGE					IMAGEMANAGER->addFrameImage("charge", "image/effect/charg_o.bmp", 0, 0, 1650, 150, 11, 1, true, RGB(255, 0, 255))
#define CHARGE_LV2_IMAGE					IMAGEMANAGER->addFrameImage("chargeLv2", "image/effect/charg_t.bmp", 0, 0, 1650, 150, 11, 1, true, RGB(255, 0, 255))
#define GAMEOVER_IMAGE						IMAGEMANAGER->addImage("over", "image/ui/over.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255))

#define PENGDORI_IMAGE						IMAGEMANAGER->addFrameImage("pengdori", "image/pengdori/PENGDORI.bmp", 0, 0, 705, 360, 5, 3, true, RGB(255, 0, 255))
#define PENGDORI_HP_HUD_IMAGE				IMAGEMANAGER->addImage("hpbarBoss", "image/ui/b_hp_bar.bmp", 48, 162, true, RGB(255, 0, 255))
#define PENGDORI_CLOUD_IMAGE				IMAGEMANAGER->addFrameImage("cloud", "image/pengdori/cloud.bmp", 0, 0, 534, 82, 3, 1, true, RGB(255, 0, 255))
#define GAMECLEAR_IMAGE						IMAGEMANAGER->addImage("clear", "image/ui/clear.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255))

// ===================== 클래스 공용 상수

#define VOLUME								1.0f								// 배경 음악 볼륨
#define HP									100									// 기본 HP
#define ATTACK								5									// 공격력
#define HIT_MOSTION_LIMIT					30									// 피격 모션 제한 카운트
#define CAMERA_X							_playerX - WINSIZEX / 2 + 100		// 카메라 X축 좌표
#define CAMERA_Y							_playerY - WINSIZEY / 2 - 100		// 카메라 Y축 좌표
#define BOSS_ROOM_CAMERA_X					7025								// 팽도리 카메라 고정 X축 좌표
#define BOSS_ROOM_CAMERA_Y					350									// 팽도리 카메라 고정 Y축 좌표
#define PROBE_RGB_RED						(r == 255 && g == 0 && b == 0)		// 픽셀 충돌 색상

// ==================== title 클래스 관련 상수

#define ROCKMAN_ICON_X						150									// 록맨 아이콘 위치 X축 좌표
#define ROCKMAN_ICON_Y						450									// 록맨 아이콘 위치 Y축 좌표
#define ROCKMAN_ICON_IMAGE_SPEED			15									// 록맨 아이콘 프레임
#define GAME_START_MENU_X					320									// 게임 시작 메뉴 X축 좌표
#define GAME_START_MENU_Y					450									// 게임 시작 메뉴 Y축 좌표

// =================== stageSelect 클래스 관련 상수

#define STAGE_SELECT_ICON_X					475									// 보스 선택 아이콘 위치 X축 좌표
#define STAGE_SELECT_ICON_Y					100									// 보스 선택 아이콘 위치 Y축 좌표
#define STAGE_SELECT_ICON_IMAGESPEED		5									// 스테이지 선택 아이콘 프레임

// =================== bossSelect 클래스 관련 상수

#define BOSS_SELECT_UP_BACK_IMAGE_X			200									// 팽도리 출현 연출 상단 이미지 X축 좌표
#define BOSS_SELECT_UP_BACK_IMAGE_Y			0									// 팽도리 출현 연출 상단 이미지 Y축 좌표
#define BOSS_SELECT_DOWN_BACK_IMAGE_X		300									// 팽도리 출현 연출 하단 이미지 X축 좌표
#define BOSS_SELECT_DOWN_BACK_IMAGE_Y		500									// 팽도리 출현 연출 하단 이미지 Y축 좌표
#define BOSS_SELECT_BACK_IMAGE_STOP_Y		WINSIZEY / 2 - 50					// 팽도리 출현 연출 이펙트 하단 이미지 정지 위치 좌표
#define BOSS_NAME_HUD_X						280									// 팽도리 출현 연출 이름 이미지 X축 좌표
#define BOSS_NAME_HUD_Y						800									// 팽도리 출현 연출 이름 이미지 Y축 좌표
#define BOSS_NAME_HUD_STOP_Y				420									// 팽도리 출현 연출 이름 이미지 정지 위치 좌표
#define BOSS_MOTION_X						WINSIZEX / 2						// 팽도리 두둥! X 좌표
#define BOSS_MOTION_Y						270									// 팽도리 두둥! Y 좌표
#define BOSS_MOTION_ICON_IMAGE_SPEED		20									// 팽도리 아이콘 프레임
#define BACK_IMAGE_MOVE_SPEED				5									// 팽도리 출현 상단, 하단 이미지 이동 속도
#define NAME_HUD_MOVE_SPEED					3									// 팽도리 이름 이동 속도

// =================== stageMap 클래스 관련 상수

#define READY_HUD_X							0									// READY 글자 출력 X축 좌표
#define READY_HUD_Y							200									// READY 글자 출력 Y축 좌표
#define READY_HUD_IMAGE_SPEED				5									// READY 글자 이미지 프레임 속도
#define MAP_Z_ORDER_X						2874								// 지도 Z-ORDER 적용 X축 좌표
#define MAP_Z_ORDER_Y						960									// 지도 Z-ORDER 적용 Y축 좌표
#define BOSS_ROOM_CAMERA_X_STOP				7030								// 팽도리 카메라 고정 최대폭 X축 좌표
#define BOSS_DOOR_ONE_X						6450								// 팽도리 첫번째 방문 X축 좌표
#define BOSS_DOOR_TWO_X						7215								// 팽도리 두번째 방문 X축 좌표
#define BOSS_DOOR_Y							700									// 팽도리 공용 방문 Y축 좌표
#define DOOR_IMAGE_SPEED					15									// 팽도리 방문 이미지 프레임
#define INDEX_LIMIT							16									// index 값 제한 카운트
#define READY_IMAGE_LIMIT					17									// READY 이미지 값 출력 제한 카운트

// ==================== loadingScene 클래스 관련 상수

#define LOADING_MAX							1000								// 최대 로딩 시간
#define LOADING_BAR_INIT					45, WINSIZEY - 100, 550, 20			// 로딩바 X축 좌표, Y축 좌표, 가로크기, 세로크기
#define LOADING_MAN_X						690									// 로딩맨 X축 좌표
#define LOADING_MAN_Y						450									// 로딩맨 Y축 좌표
#define LOADING_MAN_ICON_IMAGE_SPEED		20									// 로딩맨 이미지 프레임

// ==================== enemy 클래스 관련 상수

#define ENEMY_SPEED							2									// 에너미 기본 이동 속도
#define ENEMY_FAST_SPEED					10									// 에너미 이동 속도 업
#define ENEMY_FIRE_RANDOM					RND->getFromIntTo(50, 200)			// 에너미 공격 무작위 범위
#define ENEMY_IMAGE_SPEED_01				5									// 에너미 프레임 01
#define ENEMY_IMAGE_SPEED_02				10									// 에너미 프레임 02
#define ENEMY_SPEED_MINUS					-1									// 에너미 마이너스 속도
#define ENEMY_ANGLE							0.02f								// 에너미 이동 각도
#define ENEMY02_Y_UP_LIMIT					900									// ENEMY02 Y축 좌표 제한
#define ENEMY02_Y_DOWN_LIMIT				1050								// ENEMY02 Y축 좌표 제한
#define ENEMY03_Y_UP_LIMIT					1080								// ENEMY03 Y축 좌표 제한
#define ENEMY03_Y_DOWN_LIMIT				1250								// ENEMY03 Y축 좌표 제한
#define ENEMY06_X							3200 - cosf(_enemy.angle) * 100		// ENEMY06 X축 좌표
#define ENEMY06_Y							950 + -sinf(_enemy.angle) * 50		// ENEMY06 Y축 좌표
#define ENEMY07_X							3250 - cosf(_enemy.angle) * 100		// ENEMY07 X축 좌표
#define ENEMY07_Y							1050 + -sinf(_enemy.angle) * 50		// ENEMY07 Y축 좌표
#define ENEMY08_X							3300 - cosf(_enemy.angle) * 100		// ENEMY08 X축 좌표
#define ENEMY08_Y							1250 + -sinf(_enemy.angle) * 50		// ENEMY08 Y축 좌표
#define ENEMY09_X							3350 - cosf(_enemy.angle) * 100		// ENEMY09 X축 좌표
#define ENEMY09_Y							1350 + -sinf(_enemy.angle) * 50		// ENEMY09 Y축 좌표
#define ENEMY10_11_Y_UP_LIMIT				4800								// ENEMY10, 11 Y축 좌표 제한
#define ENEMY10_11_Y_DOWN_LIMIT				3700								// EMEMY10, 11 Y축 좌표 제한
#define ENEMY14_Y_UP_LIMIT					1593								// ENEMY14 Y축 좌표 제한
#define ENEMY14_Y_DOWN_LIMIT				1300								// ENEMY14 Y축 좌표 제한
#define ENEMY15_Y_UP_LIMIT					800									// ENEMY15 Y축 좌표 제한
#define ENEMY15_Y_DOWN_LIMIT				1070								// ENEMY15 Y축 좌표 제한

// ==================== enemyManager 클래스 관련 상수

#define BULLET_INIT							"snow_Bullet", 100, 300				// 에너미 공격, 이름, 수량, 사거리
#define BOOM_IMAGE_SPEED					8									// 폭파 연출 프레임
#define ITEM_IMAGE_SPEED					10									// 아이템 프레임
#define ITME_DROP_SPEED						10									// 아이템 드랍 속도
#define ITEM_PROBE_Y_UP						10									// 아이템 픽셀 충돌 체크 범위 상단
#define ITEM_PROBE_Y_DOWN					25									// 아이템 픽셀 충돌 체크 범위 하단
#define ENEMY_COUNT_01						270									// 에너미 등장 카운트 01
#define ENEMY_COUNT_02						310									// 에너미 등장 카운트 02
#define ENEMY_COUNT_03						400									// 에너미 등장 카운트 03
#define ENEMY_COUNT_04						700									// 에너미 등장 카운트 04
#define ENEMY_COUNT_05						1150								// 에너미 등장 카운트 05
#define ENEMY_COUNT_06						1550								// 에너미 등장 카운트 06
#define ENEMY_COUNT_07						1700								// 에너미 등장 카운트 07
#define CAMERA_X_MINUS						600									// 에니머 삭제 카메라 제한 값
#define ENEMY_INIT_CHECK01					"Bee", PointMake(1300, 1000)		// 에너미 등장 좌표 01
#define ENEMY_INIT_CHECK02					"Drop", PointMake(1406, 1000)		// 에너미 등장 좌표 02
#define ENEMY_INIT_CHECK03					"Bee", PointMake(2700, 900)			// 에너미 등장 좌표 03
#define ENEMY_INIT_CHECK04					"Bee", PointMake(2900, 1000)		// 에너미 등장 좌표 04
#define ENEMY_INIT_CHECK05					"Snow", PointMake(2700, 1000)		// 에너미 등장 좌표 05
#define ENEMY_INIT_CHECK06					"Bat", PointMake(3200, 950)			// 에너미 등장 좌표 06
#define ENEMY_INIT_CHECK07					"Bat", PointMake(3250, 1050)		// 에너미 등장 좌표 07
#define ENEMY_INIT_CHECK08					"Bat", PointMake(3300, 1250)		// 에너미 등장 좌표 08
#define ENEMY_INIT_CHECK09					"Bat", PointMake(3350, 1350)		// 에너미 등장 좌표 09
#define ENEMY_INIT_CHECK10					"Gong", PointMake(3888, 1870)		// 에너미 등장 좌표 10
#define ENEMY_INIT_CHECK11					"Gong", PointMake(4500, 1870)		// 에너미 등장 좌표 11
#define ENEMY_INIT_CHECK12					"Turret", PointMake(4949, 1785)		// 에너미 등장 좌표 12
#define ENEMY_INIT_CHECK13					"TurretM", PointMake(6165, 1593)	// 에너미 등장 좌표 13
#define ENEMY_INIT_CHECK14					"Drop", PointMake(5736, 1100)		// 에너미 등장 좌표 14
#define ENEMY_INIT_CHECK15					"Drop", PointMake(5552, 1100)		// 에너미 등장 좌표 15
#define ENEMY_INIT_CHECK16					"Turret2", PointMake(5296, 1280)	// 에너미 등장 좌표 16

// ==================== rockman 클래스 관련 상수

#define ROCKMAN_SPEED_NORMAL				5									// 엑스 기본 이동 속도
#define ROCKMAN_SPEED_JUMP					7									// 엑스 점프 이동 속도
#define ROCKMAN_X							400									// 엑스 X축 좌표
#define ROCKMAN_Y							1176								// 엑스 Y축 좌표
#define ROCKMAN_X_IN						410									// 엑스 등장 연출 X축 좌표
#define ROCKMAN_Y_IN						700									// 엑스 등장 연출 Y축 좌표
#define ROCKMAN_IN_COUNT					16									// 엑스 등장 연출 제어 카운트
#define ROCKMAN_IN_SPEED					25									// 엑스 등장 연출 속도
#define ROCKMAN_HP_BAR_X					66									// 엑스 HP BAR X축 좌표
#define ROCKMAN_HP_BAR_Y					123									// 엑스 HP BAR Y축 좌표
#define ROCKMAN_HP_HUD_X					78									// 엑스 HP HUD X축 좌표
#define ROCKMAN_HP_HUD_Y					192									// 엑스 HP HUD Y축 좌표
#define ROCKMAN_BULLET_RANGE_INIT			100, WINSIZEY						// 공격 수량, 사거리
#define ROCKMAN_HP_INIT						66, 123, 24, 99						// HP X축 좌표, Y축 좌표, 가로크기, 세로크기
#define ROCKMAN_HP_ITEM_DROP_LIMIT			40									// HP 아이템 렌더 제한 카운트
#define ENEMY_BOOM_LIMIT					45									// 에너미 폭파 이펙트 랜더 제한 카운트
#define CHARGE_IMAGE_SPEED					10									// 차지샷 이펙트 프레임
#define CHARGE_RENDER_LIMIT					30									// 차지샷 이펙트 값 제한 카운트
#define CHARGE_LV1_CHECK					20									// 차지샷 레벨1 체크 카운트
#define CHARGE_LV2_CHECK					40									// 차지샷 레벨2 체크 카운트
#define JUMP_POWER							10.0f								// 엑스 점프력
#define GRAVITY								0.4f								// 엑스 중력
#define ROCKMAN_PROBE_Y_UP					10									// 엑스 픽셀 충돌 체크 범위 상단
#define ROCKMAN_PROBE_Y_DOWN				25									// 엑스 픽셀 충돌 체크 범위 하단
#define KEYANI_START						{5,6,7,8,9,10,11}					// 키애니메이션 엑스 등장 슈웅!
#define KEYANI_ROCKMAN_RIGHT_STOP			{0}									// 키애니메이션 엑스 오른쪽 정지
#define KEYANI_ROCKMAN_RIGHT_STAY			{0,1,2,3}							// 키애니메이션 엑스 오른쪽 후욱 후욱!
#define KEYANI_ROCKMAN_RIGHT_MOVE			{25,26,27,28,29,30,31,32,33,34,35}	// 키애니메이션 엑스 오른쪽 이동
#define KEYANI_ROCKMAN_RIGTH_JUMP			{72,73,74,75,76,77,78}				// 키애니메이션 엑스 오른쪽 점프&이동 점프
#define KEYANI_ROCKMAN_RIGHT_ATTACK			{16,17}								// 키애니메이션 엑스 오른쪽 공격
#define KEYANI_ROCKMAN_RIGHT_MOVE_ATTACK	{49,50,51,52,53,54,55,56,57,58}		// 키애니메이션 엑스 오른쪽 이동 공격
#define KEYANI_ROCKMAN_RIGHT_JUMP_ATTACK	{96,97,98,99,100,101,102}			// 키애니메이션 엑스 오른쪽 점프 공격&이동 점프 공격
#define KEYANI_ROCKMAN_RIGHT_HIT			{22}								// 키애니메이션 엑스 아야!
#define KEYANI_ROCKMAN_LEFT_STOP			{12}								// 키애니메이션 엑스 왼쪽 정지
#define KEYANI_ROCKMAN_LEFT_STAY			{12,13,14,15}						// 키애니메이션 엑스 왼쪽 후욱 후욱!
#define KEYANI_ROCKMAN_LEFT_MOVE			{37,38,39,40,41,42,43,44,45,46,47}	// 키애니메이션 엑스 왼쪽 이동
#define KEYANI_ROCKMAN_LEFT_JUMP			{84,85,86,87,88,89,90}				// 키애니메이션 엑스 왼쪽 점프&이동 점프
#define KEYANI_ROCKMAN_LEFT_ATTACK			{18,19}								// 키애니메이션 엑스 왼쪽 공격
#define KEYANI_ROCKMAN_LEFT_MOVE_ATTACK		{60,61,62,63,64,65,66,67,68,69}		// 키애니메이션 엑스 왼쪽 이동 공격
#define KEYANI_ROCKMAN_LEFT_JUMP_ATTACK		{108,109,110,111,112,113,114}		// 키애니메이션 엑스 왼쪽 점프 공격& 이동 점프 공격

// ==================== pengdori 클래스 관련 상수

#define PENGDORI_SPEED						8									// 팽도리 기본 이동 속도
#define PENGDORI_X							7722								// 팽도리 X축 좌표
#define PENGDORI_Y							825									// 팽도리 Y축 좌표
#define PENGDORI_HP_INIT					748, 122, 24, 99					// HP X축 좌표, Y축 좌표, 가로크기, 세로크기
#define PENGDORI_HP_BAR_X					748									// 팽도리 HP BAR X축 좌표
#define PENGDORI_HP_BAR_Y					122									// 팽도리 HP BAR Y축 좌표
#define PENGDORI_HP_HUD_X					760									// 팽도리 HP HUD X축 좌표
#define PENGDORI_HP_HUD_Y					192									// 팽도리 HP HUD Y축 좌표
#define CLOUD_ONE_X							7600								// 팽도리 첫번째 특수공격(구름) X축 좌표
#define CLOUD_TWO_X							7300								// 팽도리 두번째 특수공격(구름) X축 좌표
#define CLOUD_Y								450									// 팽도리 특수공격(구름) Y축 좌표
#define PENGDORI_BULLET_RANGE_INIT			100, 300							// 팽도리 일반공격 수량, 사거리
#define PENGDORI_CLOUD_BULLET_RANGE_INIT	100, 200							// 팽도리 특수공격 수량, 사거리
#define PENGDORI_CLOUD_IMAGE_SPEED			10									// 팽도리 특수공격(구름) 이미지 프레임
#define ATTACK_SP							20									// 팽도리 공격력 02
#define PENGDORI_COUNT_MOTION01				100									// 팽도리 공격 연출 01
#define PENGDORI_COUNT_MOTION02				150									// 팽도리 공격 연출 02
#define PENGDORI_COUNT_MOTION03				200									// 팽도리 공격 연출 03
#define PENGDORI_COUNT_MOTION04				250									// 팽도리 공격 연출 04
#define PENGDORI_COUNT_MOTION05				400									// 팽도리 공격 연출 05
#define PENGDORI_LEFT_GOODBOY_STOP_LIMIT	7700								// 팽도리 왼쪽 슬라이드 제한
#define PENGDORI_RIGHT_GOODBOY_STOP_LIMIT	7200								// 팽도리 오른쪽 슬라이드 제한
#define CLOUD_RENDER_LIMIT					250									// 팽도리 특수공격(구름) 렌더 제한 카운트
#define KEYANI_PENGDORI_LEFT_STOP			{0}									// 키애니메이션 팽도리 왼쪽 정지
#define KEYANI_PENGDORI_LEFT_STAY			{0,1,2,3}							// 키애니메이션 팽도리 왼쪽 둠칫 둠칫
#define KEYANI_PENGDORI_LEFT_HIT			{8}									// 키애니메이션 팽도리 왼쪽 아야!
#define KEYANI_PENGDORI_LEFT_ATTACK			{5,6}								// 키애니메이션 팽도리 왼쪽 공격
#define KEYANI_PENGDORI_LEFT_GOODBOY		{13}								// 키애니메이션 팽도리 왼쪽 슬라이드
#define KEYANI_PENGDORI_RIGHT_GOODBOY		{14}								// 키애니메이션 팽도리 오른쪽 슬라이드

