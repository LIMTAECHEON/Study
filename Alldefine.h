#pragma once

// Ŭ���� �� ������ Ȥ�� �Ŵ��� �ʱ�ȭ ���� define�� ���
// 0, NULL�� ������ ��� ���� �̰��� ��Ƶд�.
// �ֻ���� �������� ����ϴ� define������, ��� Ŭ�������� �������� ��� ������ ��.
// �������� const ������ �����ؼ� ����ϵ��� ����!

// ===================== IMAGEMANAGER ����

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

// ===================== Ŭ���� ���� ���

#define VOLUME								1.0f								// ��� ���� ����
#define HP									100									// �⺻ HP
#define ATTACK								5									// ���ݷ�
#define HIT_MOSTION_LIMIT					30									// �ǰ� ��� ���� ī��Ʈ
#define CAMERA_X							_playerX - WINSIZEX / 2 + 100		// ī�޶� X�� ��ǥ
#define CAMERA_Y							_playerY - WINSIZEY / 2 - 100		// ī�޶� Y�� ��ǥ
#define BOSS_ROOM_CAMERA_X					7025								// �ص��� ī�޶� ���� X�� ��ǥ
#define BOSS_ROOM_CAMERA_Y					350									// �ص��� ī�޶� ���� Y�� ��ǥ
#define PROBE_RGB_RED						(r == 255 && g == 0 && b == 0)		// �ȼ� �浹 ����

// ==================== title Ŭ���� ���� ���

#define ROCKMAN_ICON_X						150									// �ϸ� ������ ��ġ X�� ��ǥ
#define ROCKMAN_ICON_Y						450									// �ϸ� ������ ��ġ Y�� ��ǥ
#define ROCKMAN_ICON_IMAGE_SPEED			15									// �ϸ� ������ ������
#define GAME_START_MENU_X					320									// ���� ���� �޴� X�� ��ǥ
#define GAME_START_MENU_Y					450									// ���� ���� �޴� Y�� ��ǥ

// =================== stageSelect Ŭ���� ���� ���

#define STAGE_SELECT_ICON_X					475									// ���� ���� ������ ��ġ X�� ��ǥ
#define STAGE_SELECT_ICON_Y					100									// ���� ���� ������ ��ġ Y�� ��ǥ
#define STAGE_SELECT_ICON_IMAGESPEED		5									// �������� ���� ������ ������

// =================== bossSelect Ŭ���� ���� ���

#define BOSS_SELECT_UP_BACK_IMAGE_X			200									// �ص��� ���� ���� ��� �̹��� X�� ��ǥ
#define BOSS_SELECT_UP_BACK_IMAGE_Y			0									// �ص��� ���� ���� ��� �̹��� Y�� ��ǥ
#define BOSS_SELECT_DOWN_BACK_IMAGE_X		300									// �ص��� ���� ���� �ϴ� �̹��� X�� ��ǥ
#define BOSS_SELECT_DOWN_BACK_IMAGE_Y		500									// �ص��� ���� ���� �ϴ� �̹��� Y�� ��ǥ
#define BOSS_SELECT_BACK_IMAGE_STOP_Y		WINSIZEY / 2 - 50					// �ص��� ���� ���� ����Ʈ �ϴ� �̹��� ���� ��ġ ��ǥ
#define BOSS_NAME_HUD_X						280									// �ص��� ���� ���� �̸� �̹��� X�� ��ǥ
#define BOSS_NAME_HUD_Y						800									// �ص��� ���� ���� �̸� �̹��� Y�� ��ǥ
#define BOSS_NAME_HUD_STOP_Y				420									// �ص��� ���� ���� �̸� �̹��� ���� ��ġ ��ǥ
#define BOSS_MOTION_X						WINSIZEX / 2						// �ص��� �ε�! X ��ǥ
#define BOSS_MOTION_Y						270									// �ص��� �ε�! Y ��ǥ
#define BOSS_MOTION_ICON_IMAGE_SPEED		20									// �ص��� ������ ������
#define BACK_IMAGE_MOVE_SPEED				5									// �ص��� ���� ���, �ϴ� �̹��� �̵� �ӵ�
#define NAME_HUD_MOVE_SPEED					3									// �ص��� �̸� �̵� �ӵ�

// =================== stageMap Ŭ���� ���� ���

#define READY_HUD_X							0									// READY ���� ��� X�� ��ǥ
#define READY_HUD_Y							200									// READY ���� ��� Y�� ��ǥ
#define READY_HUD_IMAGE_SPEED				5									// READY ���� �̹��� ������ �ӵ�
#define MAP_Z_ORDER_X						2874								// ���� Z-ORDER ���� X�� ��ǥ
#define MAP_Z_ORDER_Y						960									// ���� Z-ORDER ���� Y�� ��ǥ
#define BOSS_ROOM_CAMERA_X_STOP				7030								// �ص��� ī�޶� ���� �ִ��� X�� ��ǥ
#define BOSS_DOOR_ONE_X						6450								// �ص��� ù��° �湮 X�� ��ǥ
#define BOSS_DOOR_TWO_X						7215								// �ص��� �ι�° �湮 X�� ��ǥ
#define BOSS_DOOR_Y							700									// �ص��� ���� �湮 Y�� ��ǥ
#define DOOR_IMAGE_SPEED					15									// �ص��� �湮 �̹��� ������
#define INDEX_LIMIT							16									// index �� ���� ī��Ʈ
#define READY_IMAGE_LIMIT					17									// READY �̹��� �� ��� ���� ī��Ʈ

// ==================== loadingScene Ŭ���� ���� ���

#define LOADING_MAX							1000								// �ִ� �ε� �ð�
#define LOADING_BAR_INIT					45, WINSIZEY - 100, 550, 20			// �ε��� X�� ��ǥ, Y�� ��ǥ, ����ũ��, ����ũ��
#define LOADING_MAN_X						690									// �ε��� X�� ��ǥ
#define LOADING_MAN_Y						450									// �ε��� Y�� ��ǥ
#define LOADING_MAN_ICON_IMAGE_SPEED		20									// �ε��� �̹��� ������

// ==================== enemy Ŭ���� ���� ���

#define ENEMY_SPEED							2									// ���ʹ� �⺻ �̵� �ӵ�
#define ENEMY_FAST_SPEED					10									// ���ʹ� �̵� �ӵ� ��
#define ENEMY_FIRE_RANDOM					RND->getFromIntTo(50, 200)			// ���ʹ� ���� ������ ����
#define ENEMY_IMAGE_SPEED_01				5									// ���ʹ� ������ 01
#define ENEMY_IMAGE_SPEED_02				10									// ���ʹ� ������ 02
#define ENEMY_SPEED_MINUS					-1									// ���ʹ� ���̳ʽ� �ӵ�
#define ENEMY_ANGLE							0.02f								// ���ʹ� �̵� ����
#define ENEMY02_Y_UP_LIMIT					900									// ENEMY02 Y�� ��ǥ ����
#define ENEMY02_Y_DOWN_LIMIT				1050								// ENEMY02 Y�� ��ǥ ����
#define ENEMY03_Y_UP_LIMIT					1080								// ENEMY03 Y�� ��ǥ ����
#define ENEMY03_Y_DOWN_LIMIT				1250								// ENEMY03 Y�� ��ǥ ����
#define ENEMY06_X							3200 - cosf(_enemy.angle) * 100		// ENEMY06 X�� ��ǥ
#define ENEMY06_Y							950 + -sinf(_enemy.angle) * 50		// ENEMY06 Y�� ��ǥ
#define ENEMY07_X							3250 - cosf(_enemy.angle) * 100		// ENEMY07 X�� ��ǥ
#define ENEMY07_Y							1050 + -sinf(_enemy.angle) * 50		// ENEMY07 Y�� ��ǥ
#define ENEMY08_X							3300 - cosf(_enemy.angle) * 100		// ENEMY08 X�� ��ǥ
#define ENEMY08_Y							1250 + -sinf(_enemy.angle) * 50		// ENEMY08 Y�� ��ǥ
#define ENEMY09_X							3350 - cosf(_enemy.angle) * 100		// ENEMY09 X�� ��ǥ
#define ENEMY09_Y							1350 + -sinf(_enemy.angle) * 50		// ENEMY09 Y�� ��ǥ
#define ENEMY10_11_Y_UP_LIMIT				4800								// ENEMY10, 11 Y�� ��ǥ ����
#define ENEMY10_11_Y_DOWN_LIMIT				3700								// EMEMY10, 11 Y�� ��ǥ ����
#define ENEMY14_Y_UP_LIMIT					1593								// ENEMY14 Y�� ��ǥ ����
#define ENEMY14_Y_DOWN_LIMIT				1300								// ENEMY14 Y�� ��ǥ ����
#define ENEMY15_Y_UP_LIMIT					800									// ENEMY15 Y�� ��ǥ ����
#define ENEMY15_Y_DOWN_LIMIT				1070								// ENEMY15 Y�� ��ǥ ����

// ==================== enemyManager Ŭ���� ���� ���

#define BULLET_INIT							"snow_Bullet", 100, 300				// ���ʹ� ����, �̸�, ����, ��Ÿ�
#define BOOM_IMAGE_SPEED					8									// ���� ���� ������
#define ITEM_IMAGE_SPEED					10									// ������ ������
#define ITME_DROP_SPEED						10									// ������ ��� �ӵ�
#define ITEM_PROBE_Y_UP						10									// ������ �ȼ� �浹 üũ ���� ���
#define ITEM_PROBE_Y_DOWN					25									// ������ �ȼ� �浹 üũ ���� �ϴ�
#define ENEMY_COUNT_01						270									// ���ʹ� ���� ī��Ʈ 01
#define ENEMY_COUNT_02						310									// ���ʹ� ���� ī��Ʈ 02
#define ENEMY_COUNT_03						400									// ���ʹ� ���� ī��Ʈ 03
#define ENEMY_COUNT_04						700									// ���ʹ� ���� ī��Ʈ 04
#define ENEMY_COUNT_05						1150								// ���ʹ� ���� ī��Ʈ 05
#define ENEMY_COUNT_06						1550								// ���ʹ� ���� ī��Ʈ 06
#define ENEMY_COUNT_07						1700								// ���ʹ� ���� ī��Ʈ 07
#define CAMERA_X_MINUS						600									// ���ϸ� ���� ī�޶� ���� ��
#define ENEMY_INIT_CHECK01					"Bee", PointMake(1300, 1000)		// ���ʹ� ���� ��ǥ 01
#define ENEMY_INIT_CHECK02					"Drop", PointMake(1406, 1000)		// ���ʹ� ���� ��ǥ 02
#define ENEMY_INIT_CHECK03					"Bee", PointMake(2700, 900)			// ���ʹ� ���� ��ǥ 03
#define ENEMY_INIT_CHECK04					"Bee", PointMake(2900, 1000)		// ���ʹ� ���� ��ǥ 04
#define ENEMY_INIT_CHECK05					"Snow", PointMake(2700, 1000)		// ���ʹ� ���� ��ǥ 05
#define ENEMY_INIT_CHECK06					"Bat", PointMake(3200, 950)			// ���ʹ� ���� ��ǥ 06
#define ENEMY_INIT_CHECK07					"Bat", PointMake(3250, 1050)		// ���ʹ� ���� ��ǥ 07
#define ENEMY_INIT_CHECK08					"Bat", PointMake(3300, 1250)		// ���ʹ� ���� ��ǥ 08
#define ENEMY_INIT_CHECK09					"Bat", PointMake(3350, 1350)		// ���ʹ� ���� ��ǥ 09
#define ENEMY_INIT_CHECK10					"Gong", PointMake(3888, 1870)		// ���ʹ� ���� ��ǥ 10
#define ENEMY_INIT_CHECK11					"Gong", PointMake(4500, 1870)		// ���ʹ� ���� ��ǥ 11
#define ENEMY_INIT_CHECK12					"Turret", PointMake(4949, 1785)		// ���ʹ� ���� ��ǥ 12
#define ENEMY_INIT_CHECK13					"TurretM", PointMake(6165, 1593)	// ���ʹ� ���� ��ǥ 13
#define ENEMY_INIT_CHECK14					"Drop", PointMake(5736, 1100)		// ���ʹ� ���� ��ǥ 14
#define ENEMY_INIT_CHECK15					"Drop", PointMake(5552, 1100)		// ���ʹ� ���� ��ǥ 15
#define ENEMY_INIT_CHECK16					"Turret2", PointMake(5296, 1280)	// ���ʹ� ���� ��ǥ 16

// ==================== rockman Ŭ���� ���� ���

#define ROCKMAN_SPEED_NORMAL				5									// ���� �⺻ �̵� �ӵ�
#define ROCKMAN_SPEED_JUMP					7									// ���� ���� �̵� �ӵ�
#define ROCKMAN_X							400									// ���� X�� ��ǥ
#define ROCKMAN_Y							1176								// ���� Y�� ��ǥ
#define ROCKMAN_X_IN						410									// ���� ���� ���� X�� ��ǥ
#define ROCKMAN_Y_IN						700									// ���� ���� ���� Y�� ��ǥ
#define ROCKMAN_IN_COUNT					16									// ���� ���� ���� ���� ī��Ʈ
#define ROCKMAN_IN_SPEED					25									// ���� ���� ���� �ӵ�
#define ROCKMAN_HP_BAR_X					66									// ���� HP BAR X�� ��ǥ
#define ROCKMAN_HP_BAR_Y					123									// ���� HP BAR Y�� ��ǥ
#define ROCKMAN_HP_HUD_X					78									// ���� HP HUD X�� ��ǥ
#define ROCKMAN_HP_HUD_Y					192									// ���� HP HUD Y�� ��ǥ
#define ROCKMAN_BULLET_RANGE_INIT			100, WINSIZEY						// ���� ����, ��Ÿ�
#define ROCKMAN_HP_INIT						66, 123, 24, 99						// HP X�� ��ǥ, Y�� ��ǥ, ����ũ��, ����ũ��
#define ROCKMAN_HP_ITEM_DROP_LIMIT			40									// HP ������ ���� ���� ī��Ʈ
#define ENEMY_BOOM_LIMIT					45									// ���ʹ� ���� ����Ʈ ���� ���� ī��Ʈ
#define CHARGE_IMAGE_SPEED					10									// ������ ����Ʈ ������
#define CHARGE_RENDER_LIMIT					30									// ������ ����Ʈ �� ���� ī��Ʈ
#define CHARGE_LV1_CHECK					20									// ������ ����1 üũ ī��Ʈ
#define CHARGE_LV2_CHECK					40									// ������ ����2 üũ ī��Ʈ
#define JUMP_POWER							10.0f								// ���� ������
#define GRAVITY								0.4f								// ���� �߷�
#define ROCKMAN_PROBE_Y_UP					10									// ���� �ȼ� �浹 üũ ���� ���
#define ROCKMAN_PROBE_Y_DOWN				25									// ���� �ȼ� �浹 üũ ���� �ϴ�
#define KEYANI_START						{5,6,7,8,9,10,11}					// Ű�ִϸ��̼� ���� ���� ����!
#define KEYANI_ROCKMAN_RIGHT_STOP			{0}									// Ű�ִϸ��̼� ���� ������ ����
#define KEYANI_ROCKMAN_RIGHT_STAY			{0,1,2,3}							// Ű�ִϸ��̼� ���� ������ �Ŀ� �Ŀ�!
#define KEYANI_ROCKMAN_RIGHT_MOVE			{25,26,27,28,29,30,31,32,33,34,35}	// Ű�ִϸ��̼� ���� ������ �̵�
#define KEYANI_ROCKMAN_RIGTH_JUMP			{72,73,74,75,76,77,78}				// Ű�ִϸ��̼� ���� ������ ����&�̵� ����
#define KEYANI_ROCKMAN_RIGHT_ATTACK			{16,17}								// Ű�ִϸ��̼� ���� ������ ����
#define KEYANI_ROCKMAN_RIGHT_MOVE_ATTACK	{49,50,51,52,53,54,55,56,57,58}		// Ű�ִϸ��̼� ���� ������ �̵� ����
#define KEYANI_ROCKMAN_RIGHT_JUMP_ATTACK	{96,97,98,99,100,101,102}			// Ű�ִϸ��̼� ���� ������ ���� ����&�̵� ���� ����
#define KEYANI_ROCKMAN_RIGHT_HIT			{22}								// Ű�ִϸ��̼� ���� �ƾ�!
#define KEYANI_ROCKMAN_LEFT_STOP			{12}								// Ű�ִϸ��̼� ���� ���� ����
#define KEYANI_ROCKMAN_LEFT_STAY			{12,13,14,15}						// Ű�ִϸ��̼� ���� ���� �Ŀ� �Ŀ�!
#define KEYANI_ROCKMAN_LEFT_MOVE			{37,38,39,40,41,42,43,44,45,46,47}	// Ű�ִϸ��̼� ���� ���� �̵�
#define KEYANI_ROCKMAN_LEFT_JUMP			{84,85,86,87,88,89,90}				// Ű�ִϸ��̼� ���� ���� ����&�̵� ����
#define KEYANI_ROCKMAN_LEFT_ATTACK			{18,19}								// Ű�ִϸ��̼� ���� ���� ����
#define KEYANI_ROCKMAN_LEFT_MOVE_ATTACK		{60,61,62,63,64,65,66,67,68,69}		// Ű�ִϸ��̼� ���� ���� �̵� ����
#define KEYANI_ROCKMAN_LEFT_JUMP_ATTACK		{108,109,110,111,112,113,114}		// Ű�ִϸ��̼� ���� ���� ���� ����& �̵� ���� ����

// ==================== pengdori Ŭ���� ���� ���

#define PENGDORI_SPEED						8									// �ص��� �⺻ �̵� �ӵ�
#define PENGDORI_X							7722								// �ص��� X�� ��ǥ
#define PENGDORI_Y							825									// �ص��� Y�� ��ǥ
#define PENGDORI_HP_INIT					748, 122, 24, 99					// HP X�� ��ǥ, Y�� ��ǥ, ����ũ��, ����ũ��
#define PENGDORI_HP_BAR_X					748									// �ص��� HP BAR X�� ��ǥ
#define PENGDORI_HP_BAR_Y					122									// �ص��� HP BAR Y�� ��ǥ
#define PENGDORI_HP_HUD_X					760									// �ص��� HP HUD X�� ��ǥ
#define PENGDORI_HP_HUD_Y					192									// �ص��� HP HUD Y�� ��ǥ
#define CLOUD_ONE_X							7600								// �ص��� ù��° Ư������(����) X�� ��ǥ
#define CLOUD_TWO_X							7300								// �ص��� �ι�° Ư������(����) X�� ��ǥ
#define CLOUD_Y								450									// �ص��� Ư������(����) Y�� ��ǥ
#define PENGDORI_BULLET_RANGE_INIT			100, 300							// �ص��� �Ϲݰ��� ����, ��Ÿ�
#define PENGDORI_CLOUD_BULLET_RANGE_INIT	100, 200							// �ص��� Ư������ ����, ��Ÿ�
#define PENGDORI_CLOUD_IMAGE_SPEED			10									// �ص��� Ư������(����) �̹��� ������
#define ATTACK_SP							20									// �ص��� ���ݷ� 02
#define PENGDORI_COUNT_MOTION01				100									// �ص��� ���� ���� 01
#define PENGDORI_COUNT_MOTION02				150									// �ص��� ���� ���� 02
#define PENGDORI_COUNT_MOTION03				200									// �ص��� ���� ���� 03
#define PENGDORI_COUNT_MOTION04				250									// �ص��� ���� ���� 04
#define PENGDORI_COUNT_MOTION05				400									// �ص��� ���� ���� 05
#define PENGDORI_LEFT_GOODBOY_STOP_LIMIT	7700								// �ص��� ���� �����̵� ����
#define PENGDORI_RIGHT_GOODBOY_STOP_LIMIT	7200								// �ص��� ������ �����̵� ����
#define CLOUD_RENDER_LIMIT					250									// �ص��� Ư������(����) ���� ���� ī��Ʈ
#define KEYANI_PENGDORI_LEFT_STOP			{0}									// Ű�ִϸ��̼� �ص��� ���� ����
#define KEYANI_PENGDORI_LEFT_STAY			{0,1,2,3}							// Ű�ִϸ��̼� �ص��� ���� ��ĩ ��ĩ
#define KEYANI_PENGDORI_LEFT_HIT			{8}									// Ű�ִϸ��̼� �ص��� ���� �ƾ�!
#define KEYANI_PENGDORI_LEFT_ATTACK			{5,6}								// Ű�ִϸ��̼� �ص��� ���� ����
#define KEYANI_PENGDORI_LEFT_GOODBOY		{13}								// Ű�ִϸ��̼� �ص��� ���� �����̵�
#define KEYANI_PENGDORI_RIGHT_GOODBOY		{14}								// Ű�ִϸ��̼� �ص��� ������ �����̵�

