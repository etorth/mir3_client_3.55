#ifndef _DEFINE_H
#define _DEFINE_H




/******************************************************************************************************************
	#1. File Names
*******************************************************************************************************************/
#define MIR2_PATCH_FILE_NAME		"\\Mir3Patch.exe"
#define MIR2_TS_PATCH_FILE_NAME		"\\Mir3TestPatch.exe"
#define MIR2_PATCH_DAT_NAME			"\\~Mir3Patch.dat"
#define	MIR3_MODEINI_NAME			"\\mode.ini"


/******************************************************************************************************************
	#1. Procedeure Define
*******************************************************************************************************************/
#define _LOGIN_PROC					0
#define _SVR_SEL_PROC				1
#define _CHAR_SEL_PROC				2
#define _GAME_PROC					3




/******************************************************************************************************************
	#1. Mouse Wheel Define
*******************************************************************************************************************/
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL				WM_MOUSELAST+1 
#endif





/******************************************************************************************************************
	#1. User Define Message
*******************************************************************************************************************/
#define _WM_USER_MSG_INPUTTED		WM_USER + 1005				// 에디트박스 입력메시지. 메시지가 커맨드일경우 wParam값은 TRUE로 세팅된다.
#define _WM_MSGBOX_RETURN			WM_USER + 1006				// 
#define _WM_USER_MSG_CTRLNUM		WM_USER + 1007				// 
#define _WM_USER_MSG_ALTNUM			WM_USER + 1008				// 
#define ID_SOCKCLIENT_EVENT_MSG		WM_USER + 1000				// 소켓이벤트메시지.

/******************************************************************************************************************
	#1. Nprotect Message
*******************************************************************************************************************/
#define WM_NPROTECT_EXIT_TWO		WM_USER + 10001


/******************************************************************************************************************
	#1. Image Define Message
*******************************************************************************************************************/
// 기본맵데이타.
#define _IMAGE_TILES				0
#define _IMAGE_TILES30				1
#define _IMAGE_TILES5				2
#define _IMAGE_SMTILES				3
#define _IMAGE_HOUSES				4
#define _IMAGE_CLIFFS				5
#define _IMAGE_DUNGEONS				6
#define _IMAGE_INNERS				7
#define _IMAGE_FUNITURES			8
#define _IMAGE_WALLS				9
#define _IMAGE_SMOBJECTS			10
#define _IMAGE_ANIMATIONS			11
#define _IMAGE_OBJECT1				12
#define _IMAGE_OBJECT2				13
// 푸른지역맵데이타.
#define _IMAGE_WOOD_TILES			14
#define _IMAGE_WOOD_TILES30			15
#define _IMAGE_WOOD_TILES5			16
#define _IMAGE_WOOD_SMTILES			17
#define _IMAGE_WOOD_HOUSES			18
#define _IMAGE_WOOD_CLIFFS			19
#define _IMAGE_WOOD_DUNGEONS		20
#define _IMAGE_WOOD_INNERS			21
#define _IMAGE_WOOD_FUNITURES		22
#define _IMAGE_WOOD_WALLS			23
#define _IMAGE_WOOD_SMOBJECTS		24
#define _IMAGE_WOOD_ANIMATIONS		25
#define _IMAGE_WOOD_OBJECT1			26
#define _IMAGE_WOOD_OBJECT2			27
// 사막지역맵데이타.
#define _IMAGE_SAND_TILES			28
#define _IMAGE_SAND_TILES30			29
#define _IMAGE_SAND_TILES5			30
#define _IMAGE_SAND_SMTILES			31
#define _IMAGE_SAND_HOUSES			32
#define _IMAGE_SAND_CLIFFS			33
#define _IMAGE_SAND_DUNGEONS		34
#define _IMAGE_SAND_INNERS			35
#define _IMAGE_SAND_FUNITURES		36
#define _IMAGE_SAND_WALLS			37
#define _IMAGE_SAND_SMOBJECTS		38
#define _IMAGE_SAND_ANIMATIONS		39
#define _IMAGE_SAND_OBJECT1			40
#define _IMAGE_SAND_OBJECT2			41
// 정글지역맵데이타.
#define _IMAGE_FOREST_TILES			42
#define _IMAGE_FOREST_TILES30		43
#define _IMAGE_FOREST_TILES5		44
#define _IMAGE_FOREST_SMTILES		45
#define _IMAGE_FOREST_HOUSES		46
#define _IMAGE_FOREST_CLIFFS		47
#define _IMAGE_FOREST_DUNGEONS		48
#define _IMAGE_FOREST_INNERS		49
#define _IMAGE_FOREST_FUNITURES		50
#define _IMAGE_FOREST_WALLS			51
#define _IMAGE_FOREST_SMOBJECTS		52
#define _IMAGE_FOREST_ANIMATIONS	53
#define _IMAGE_FOREST_OBJECT1		54
#define _IMAGE_FOREST_OBJECT2		55
// 설원지역맵데이타.
#define _IMAGE_SNOW_TILES			56
#define _IMAGE_SNOW_TILES30			57
#define _IMAGE_SNOW_TILES5			58
#define _IMAGE_SNOW_SMTILES			59
#define _IMAGE_SNOW_HOUSES			60
#define _IMAGE_SNOW_CLIFFS			61
#define _IMAGE_SNOW_DUNGEONS		62
#define _IMAGE_SNOW_INNERS			63
#define _IMAGE_SNOW_FUNITURES		64
#define _IMAGE_SNOW_WALLS			65
#define _IMAGE_SNOW_SMOBJECTS		66
#define _IMAGE_SNOW_ANIMATIONS		67
#define _IMAGE_SNOW_OBJECT1			68
#define _IMAGE_SNOW_OBJECT2			69

#define _IMAGE_INTER				70
#define _IMAGE_M_HUMAN				71
#define _IMAGE_M_WEAPON1			72
#define _IMAGE_M_WEAPON2			73
#define _IMAGE_M_WEAPON3			74
#define _IMAGE_M_WEAPON4			75
#define _IMAGE_WM_HUMAN				76
#define _IMAGE_WM_WEAPON1			77
#define _IMAGE_WM_WEAPON2			78
#define _IMAGE_WM_WEAPON3			79
#define _IMAGE_WM_WEAPON4			80
#define _IMAGE_MAGIC				81
#define _IMAGE_ITEM_INVENTORY		82
#define _IMAGE_ITEM_EQUIP			83
#define _IMAGE_ITEM_GROUND			84
#define _IMAGE_MICON				85
#define _IMAGE_PROGUSE				86
#define _IMAGE_HORSE				87
#define _IMAGE_MONSTER1				88
#define _IMAGE_MONSTER2				89
#define _IMAGE_MONSTER3				90
#define _IMAGE_MONSTER4				91
#define _IMAGE_MONSTER5				92
#define _IMAGE_MONSTER6				93
#define _IMAGE_MONSTER7				94
#define _IMAGE_MONSTER8				95
#define _IMAGE_MONSTER9				96
#define _IMAGE_MONSTER10			97
#define _IMAGE_MONSTER11			98
#define _IMAGE_MONSTER12			99
#define _IMAGE_MONSTER13			100
#define _IMAGE_MONSTER14			101
#define _IMAGE_MONSTER15			102
#define _IMAGE_MONSTER16			103
#define _IMAGE_MONSTER17			104
#define _IMAGE_MONSTER18			105
#define _IMAGE_MONSTER19			106
#define _IMAGE_MONSTER20			107
#define _IMAGE_SMONSTER1			108
#define _IMAGE_SMONSTER2			109
#define _IMAGE_SMONSTER3			110
#define _IMAGE_SMONSTER4			111
#define _IMAGE_SMONSTER5			112
#define _IMAGE_SMONSTER6			113
#define _IMAGE_SMONSTER7			114
#define _IMAGE_SMONSTER8			115
#define _IMAGE_SMONSTER9			116
#define _IMAGE_SMONSTER10			117
#define _IMAGE_SMONSTER11			118
#define _IMAGE_SMONSTER12			119
#define _IMAGE_SMONSTER13			120
#define _IMAGE_SMONSTER14			121
#define _IMAGE_SMONSTER15			122
#define _IMAGE_SMONSTER16			123
#define _IMAGE_SMONSTER17			124
#define _IMAGE_SMONSTER18			125
#define _IMAGE_SMONSTER19			126
#define _IMAGE_SMONSTER20			127
#define _IMAGE_NPC					128
#define _IMAGE_MONMAGIC				129
#define _IMAGE_MONSMALL				130
#define _IMAGE_M_HAIR				131
#define _IMAGE_M_HELMET1			132
#define _IMAGE_WM_HAIR				133
#define _IMAGE_WM_HELMET1			134
#define _IMAGE_DMONSTER1			135
#define _IMAGE_SDMONSTER1			136
#define _IMAGE_MAGICEX				137
#define _IMAGE_MONMAGICEX			138
#define _IMAGE_ITEM_STORE			139
#define _IMAGE_MONMAGICEX2			140
#define _IMAGE_MONSTER54			141
#define _IMAGE_FLAG					142
#define _IMAGE_MONMAGICEX3			143
#define _IMAGE_M_HELMET2			144
#define _IMAGE_WM_HELMET2			145
#define _IMAGE_M_WEAPON5			146
#define _IMAGE_WM_WEAPON5			147
#define _IMAGE_MONMAGICEX4			148
#define _IMAGE_MAGICEX2				149
#define _IMAGE_MONSTER21			150
#define _IMAGE_SMONSTER21			151
#define _IMAGE_SHORSE				152
#define _IMAGE_M_WEAPON10			153
#define _IMAGE_WM_WEAPON10			154
#define _IMAGE_MONSTER22			155
#define _IMAGE_SMONSTER22			156
#define _IMAGE_MAGICEX3				157
#define _IMAGE_MONMAGICEX5			158
#define _IMAGE_INTER1				159
#define	_IMAGE_M_ARMOREFT			160
#define _IMAGE_WM_ARMOREFT			161

#define _MAX_MONSTER_IMAGE			20

#define _MAX_IMAGE					160

#define _TEXTR_FILE_MAGIC			0
#define _TEXTR_FILE_MONMAGIC		1
#define _TEXTR_FILE_MAP				2
#define _TEXTR_FILE_INTER			3
#define _TEXTR_FILE_PARTICLE		4

#define _MAX_TEXTR_FILE				5

/******************************************************************************************************************
	#1. GameProc Define
*******************************************************************************************************************/
#define _VIEW__WITH_NORMAL			0
#define _VIEW__WITH_INVEN			1
#define _VIEW__WITH_STATUS			2

#define _VIEW__INVEN_GAP			3
#define _VIEW__STATUS_GAP			-3



/******************************************************************************************************************
	#1. Item Define
*******************************************************************************************************************/
#define _ITEM_MAX_STATE				50

#define _ITEM_TYPE_INVENTORY		0
#define _ITEM_TYPE_EQUIP			1
#define _ITEM_TYPE_GROUND			2
#define _ITEM_TYPE_STORE			3

#define _INVENTORY_CELL_WIDTH		38
#define _INVENTORY_CELL_HEIGHT		38

#define _NEW_INVENTORY_CELL_WIDTH	38
#define _NEW_INVENTORY_CELL_HEIGHT	38

#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // 투과색.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // 검정색.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // 흰색.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // 빨강.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // 녹색.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // 푸른색
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // 노랑색.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // 주황색

#define _USER_NAMECLR1				255	//RGB(255, 255, 255); 흰색
#define _USER_NAMECLR2				251	//RGB(255, 255,   0); 노란색
#define _USER_NAMECLR3				249	//RGB(255,   0,   0); 빨간색
#define _USER_NAMECLR4				125	//RGB(255,   0,   0); ??색(결계안 몬스터색)
#define _USER_NAMECLR5				47	//RGB(165,  99,  57); 갈색
#define _USER_NAMECLR6				180	//RGB(  0,   0, 255); 푸른색
#define _USER_NAMECLR7				69	//RGB(239, 107,   0); 주황색
#define _USER_NAMECLR8				221	//RGB(  0, 148,   0); 녹색
#define _USER_NAMECLR9				254	//RGB(  0, 255, 255); 색
#define _USER_NAMECLR10				147	//RGB(140, 214, 239); 색
#define _USER_NAMECLR11				154	//RGB( 57, 181, 239); 색
#define _USER_NAMECLR12				229	//RGB(119, 136, 255); 색
#define _USER_NAMECLR13				168	//RGB(  0, 123, 222); 색
#define _USER_NAMECLR14				252	//RGB(  0,   0, 255); 색




/******************************************************************************************************************
	#1. Actor Define
*******************************************************************************************************************/
#define _GENDER_MAN					0
#define _GENDER_WOMAN				1
#define _GENDER_FLAG				4
#define _GENDER_NPC					5
#define _GENDER_MON					3//77

#define _TARGETRGN_GAPX				10
#define _TARGETRGN_GAPY				8

#define _MAX_HERO_KIND				9
#define _MAX_MON_KIND				255
#define _MAX_NPC_KIND				200

#define _MAX_DIRECTION				8
#define _DIRECTION_LIST_1			0
#define _DIRECTION_LIST_2			1
#define _DIRECTION_LIST_3			2
#define _DIRECTION_LIST_4			3
#define _DIRECTION_LIST_5			4
#define _DIRECTION_LIST_6			5	 
#define _DIRECTION_LIST_7			6
#define _DIRECTION_LIST_8			7	

#define _DEFAULT_SPELLFRAME			10
#define _DEFAULT_DELAYTIME			300

#define _HAIR_NONE					0
#define _MAX_HAIR					30

#define _WEAPON_NONE				0		
#define _MAX_WEAPON					50

#define _HORSE_NONE					0
#define _MAX_HORSE					5

#define	_MAX_WEAPON_MTN				25
#define	_MAX_WEAPON_FRAME			3000

#define	_START_HORSE_FRAME			2320
#define	_START_HORSE_MTN			29
#define	_MAX_HORSE_FRAME			400

#define _MY_CENTER_XPOS				400
#define _MY_CENTER_YPOS	    		243

#define _MAX_CHAT_LINE				5
#define _CHAT_WIDTH					144
//#define _GAPX_TILE_CHAR_MAP		11
//#define _GAPY_TILE_CHAR_MAP		11 
#define _GAPX_TILE_CHAR_MAP			12
#define _GAPY_TILE_CHAR_MAP			13
#define _CHAR_CENTER_XPOS			400
#define _CHAR_CENTER_YPOS	    	243

#define _CHAR_CENTER_XPOS_INVEN 	260
#define _CHAR_CENTER_YPOS_INVEN   	243

#define _CHAR_CENTER_XPOS_STATUS	555
#define _CHAR_CENTER_YPOS_STATUS	243

#define _SPEED_WALK					1
#define _SPEED_RUN					2
#define _SPEED_HORSERUN				3

#define _MOTION_LOCKTIME			1000
#define _WARMODE_TIME				1000

#define _JOB_GUNGSA					3
#define _JOB_DOSA					2
#define _JOB_SULSA					1
#define _JOB_JUNSA					0

#define _STATE_RED					64690
#define _STATE_GREEN				2016
#define _STATE_BLUE					38079//25407//31
#define _STATE_YELLOW				65504
#define _STATE_FUCHSIA				64511
#define _STATE_GRAY					0
#define _STATE_ABLEND				1
#define _STATE_SHIELDUSE			2
#define _STATE_NOTUSED				0XFFFF
#define _STATE_BRIGHTBLUE			37000
#define _STATE_BRIGHTBLUE1			39000
#define _STATE_BRIGHTBLUE2			36000


#define _RUN_MINHEALTH				10

#define _DIG_NORMAL					0
#define _DIG_UP						1
#define _DIG_DOWN					2
#define _DIG_DOWNDEL				3


/******************************************************************************************************************
	#1. Sprite Define
*******************************************************************************************************************/
// Hero의 동작 정의.(게임내의 모든 동작을 정의한다.)

#define _MAX_HERO_MTN				33			// 최대 동작갯수.
#define _MAX_HERO_FRAME				3000		// 다음 Hero로 넘어가는 최대 프레임 갯수.
#define	_MAX_HERO_REALFRAME			2640

#define _MT_STAND					0			// 유휴동작.
#define _MT_ARROWATTACK				1			// 활공격.
#define _MT_SPELL1					2			// 마법 시전1.
#define _MT_SPELL2					3			// 마법 공격 시전2.
#define _MT_HOLD					4			// 견디기.
#define _MT_PUSHBACK				5			// 뒤로 밀려나기.
#define _MT_PUSHBACKFLY				6			// 뒤로 날라서 밀려나기.
#define _MT_ATTACKMODE				7			// 전투모드.
#define _MT_CUT						8			// 고기 썰기.
#define _MT_ONEVSWING				9			// 한손 종베기.(동작 9번부터 14번까지에서 무기의 종류에 따라 동작이 정해진다.)
#define _MT_TWOVSWING				10			// 두손 종베기.
#define _MT_ONEHSWING				11			// 한손 횡베기.
#define _MT_TWOHSWING				12			// 두손 횡베기.	
#define _MT_SPEARVSWING				13			// 창 종베기.
#define _MT_SPEARHSWING				14			// 창 횡베기.
#define _MT_HITTED					15			// 맞기.
#define _MT_WHEELWIND				16			// 돌면서 베기.
#define _MT_RANDSWING				17			// 마구 베기.
#define _MT_BACKDROPKICK			18			// 뒤돌아 차기.
#define _MT_DIE						19			// 죽기.
#define _MT_SPECIALDIE				20			// 튀어올라 죽기.
#define _MT_WALK					21			// 걷기.
#define _MT_RUN						22			// 달리기.
#define _MT_MOODEPO					23			// 무태보 뛰기.
#define _MT_ROLL					24			// 구르기.
#define _MT_FISHSTAND				25			// 낚시모드 유휴.
#define _MT_FISHHAND				26			// 낚시모드.
#define _MT_FISHTHROW				27			// 낚시줄 던지기.
#define _MT_FISHPULL				28			// 낚시줄 당기기.
#define _MT_HORSESTAND				29			// 승마모드 유휴.
#define _MT_HORSEWALK				30			// 승마모드 걷기.
#define _MT_HORSERUN				31			// 승마모드 달리기.
#define _MT_HORSEHIT				32			// 승마모드 맞기.

// Monster의 동작 정의.(게임내의 모든 동작을 정의한다.)
#define _MAX_MON_MTN				11			// 최대 동작갯수.
#define _MAX_MON_FRAME				1000		// 다음 Mon로 넘어가는 최대 프레임 갯수.

#define _MT_MON_STAND				0			// 유휴동작.
#define _MT_MON_WALK				1			// 걷기동작.
#define _MT_MON_ATTACK_A			2			// 일반공격동작1.
#define _MT_MON_HITTED				3			// 맞기동작.
#define _MT_MON_DIE					4			// 죽기동작.
#define _MT_MON_ATTACK_B			5			// 일반공격동작2.
#define _MT_MON_SPELL_A				6			// 마법공격동작1.
#define _MT_MON_SPELL_B				7			// 마법공격동작2.
#define _MT_MON_APPEAR				8			// 나타나기동작.
#define _MT_MON_SPECIAL_MTN			9			// 특수동작1.
#define _MT_MON_SKELETON			10			// 해골.


// NPC의 동작 정의.(게임내의 모든 동작을 정의한다.)
// NPC 관련정의.
#define _MAX_NPC_MTN				3			// 최대 동작갯수.
#define _MAX_NPC_FRAME				100			// 다음 NPC로 넘어가는 최대 프레임 갯수.

#define _MT_NPC_STAND				0			// 유휴동작.
#define _MT_NPC_ACT01				1			// 특수동작1.
#define _MT_NPC_ACT02				2			// 특수동작2.



// 마법효과관련정의.
//#define _MAX_EFFECT					41
//#define _MAX_MAGIC					76
//#define _MAX_EXPLOSION				13





/******************************************************************************************************************
	#1. Chat Popup Wnd
*******************************************************************************************************************/
#define _MAX_CHATLINE_POPUP			19

#define _MAX_CHATPOP_BTN			9

#define _BTN_ID_CHATCLOSE			0
#define _BTN_ID_CHATDENY			1
#define _BTN_ID_CHATSHOUT			2
#define _BTN_ID_CHATGROUP			3
#define _BTN_ID_CHATGUILD			4
#define _BTN_ID_CHATALLDENY			5
#define _BTN_ID_DENYGUILD			6
#define _BTN_ID_SCRLUP				7
#define _BTN_ID_SCRLDOWN			8



/******************************************************************************************************************
	#1. Guild Wnd
*******************************************************************************************************************/
#define _MAX_GUILD_BTN				9

#define _BTN_ID_NOTICE				0
#define _BTN_ID_GUILDER				1
#define _BTN_ID_GUILDCHAT			2
#define _BTN_ID_NOTICEREPAIR		3
#define _BTN_ID_GUILDERDEL			4
#define _BTN_ID_GUILDDEL			5
#define _BTN_ID_CHANGEPOS			6
#define _BTN_ID_ALLYDEL				7
#define _BTN_ID_GUILDLOSE			8



/******************************************************************************************************************
	#1. Button Wnd
*******************************************************************************************************************/
#define _BTN_STATE_NORMAL			0
#define _BTN_STATE_FOCUS			1
#define _BTN_STATE_CLICK			2

#define _BTN_TYPE_NOFOCUS			0
#define _BTN_TYPE_FOCUS				1





/******************************************************************************************************************
	#1. Game Procedure
*******************************************************************************************************************/
#define _CLIP_WIDTH					800
#define _CLIP_HEIGHT				600
#define _TIMER_ID					1
// 마법테스트용.
#define _TIMER_MTESTID				2
#define _TIMER_SYSTIME				3


#define _ET_DIGOUTZOMBI				1  //좀비가 땅파고 나온 흔적
#define _ET_MINE					2  //광석이 매장되어 있음
#define _ET_PILESTONES				3  //돌무더기
#define _ET_HOLYCURTAIN				4  //결계
#define _ET_FIRE					5
#define _ET_SCULPEICE				6  //주마왕의 돌깨진 조각
#define _ET_ICEWALL					9  //빙벽
#define _ET_WINDWALL				10 //회풍강막
#define _ET_FIRE_HIGH				11 //지속계

#define _MAX_CELL_OBJ				100

// Day Bright.
#define _DAYSTATE_DUSK				0  // 새벽.
#define _DAYSTATE_DAY				1  // 낮.
#define _DAYSTATE_DAWN				2  // 저녁.
#define _DAYSTATE_NIGHT				3  // 밤.

// Fog Bright.
#define _FOGSTATE_DAY				0  // 낮.
#define _FOGSTATE_NIGHT				1  // 밤.
#define _FOGSTATE_DAWN				2  // 새벽, 저녁.

#define _MAX_STRING_LEN				1024

#define _MAX_DICE					4





/******************************************************************************************************************
	#1. Interface
*******************************************************************************************************************/
#define _BELT_MAX_CELL				6
#define _BELT_CELL_XGAP				40
#define _BELT_CELL_XSTART			279
#define _BELT_CELL_YSTART			432
#define _MAX_BELT_ITEM				6

#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // 투과색.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // 검정색.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // 흰색.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // 빨강.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // 녹색.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // 푸른색
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // 노랑색.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // 주황색

#define _INPUT_EDITWND_XPOS			223
#define _INPUT_EDITWND_YPOS			570
#define _INPUT_EDITWND_WIDTH		354
#define _INPUT_EDITWND_HEIGHT		16

#define _NEW_INPUT_EDITWND_XPOS			185
#define _NEW_INPUT_EDITWND_YPOS			575
#define _NEW_INPUT_LARGEEDITWND_YPOS	534
#define _NEW_INPUT_EDITWND_WIDTH		321
#define _NEW_INPUT_LARGEEDITWND_WIDTH	432
#define _NEW_INPUT_EDITWND_HEIGHT		15

// 메인인터페이스에서 쓰일 윈도우 아이디.
#define _WND_ID_INVENTORY			0			//가방윈도우.
#define _WND_ID_STATUS				1			//캐릭터 정보 보기윈도우(3개).
#define _WND_ID_STORE				2			//상점윈도우.
#define _WND_ID_EXCHANGE			3			//교환윈도우.
#define _WND_ID_GUILD				4			//문원윈도우.
#define _WND_ID_GROUP				6			//그룹윈도우.
#define _WND_ID_USERSTATE			7			//
#define _WND_ID_CHATPOP				8			//
#define _WND_ID_NPCCHAT				9		
#define _WND_ID_MESSAGEBOX			10			// MessageBox
#define _WND_ID_QUEST				11			// 
#define _WND_ID_OPTION				12			// 
#define _WND_ID_HORSE				13			// 
#define _WND_ID_MAGIC				14			// 
#define _WND_ID_NOTICEEDIT			15
#define _WND_ID_BELT				16
#define _WND_ID_SIEGE				18
#define _WND_ID_USERMARKET			19
#define _WND_ID_USERMARKETUP		20
#define _WND_ID_MESSENGER			21
#define _WND_ID_FACEIMGUP			22
#define _WND_ID_UTIL				23
#define _WND_ID_VIEWMINIMAP			24
#define _WND_ID_CHAT				25
#define _WND_ID_SETTING				26
#define _WND_ID_EXIT				27
#define _WND_ID_MAGICSHORTCUT		28
#define _WND_ID_GAMEOUT				100
#define _WND_ID_LOGOUT				101
#define _WND_ID_DROPGOLD			102
#define _WND_ID_GAME				103
#define	_WND_ID_DROPMULTIPLEITEM	104
#define _WND_ID_SELLMULTIPLEITEM	105
#define _WND_ID_SAVEMULTIPLEITEM	106
#define _WND_ID_TAKEBACKMULTIPLEITEM	107
#define _WND_ID_EXCHANGEMULTIPLEITEM	108
#define _WND_ID_GAMEOVER				109
#define _WND_ID_BUYMULTIPLEITEM			110
#define _WND_ID_DIRECT_GAMEOUT			111
#define _WND_ID_CHARGE_BULLET			112
#define _WND_ID_NOTENOUGH				113
#define _WND_ID_SETVALUE				114
#define _WND_ID_WANTTOBUY				115
#define _WND_ID_WANTTOCANCEL			116
#define _WND_ID_WANTTOREGISTRY			117
#define _WND_ID_SENDMONEY				118
#define _WND_ID_DELCHAR					119
#define _WND_ID_SETUTIL					120
#define _WND_ID_SETPRIORITY				121
#define _WND_ID_SETNAME					122
#define _WND_ID_SETPRIORITY2			123
#define _WND_ID_CUTWHISPER				124
#define _WND_ID_DROPITEM				125

// 메인 인터페이스에서 쓰일 윈도우의 이미지 인덱스.
#define _WNDIMGIDX_GAMEOVER			800			//무공설정창
#define _WNDIMGIDX_MAIN				50			//메인인터페이스채팅창
#define _WNDIMGIDX_ITEMSET		    200			//상태창
#define _WNDIMGIDX_USERSTATE		200			//그룹입력창.
#define _WNDIMGIDX_CHATPOP			350			//채팅팝업창.
#define _WNDIMGINDX_MSGBOX1			950
#define _WNDIMGINDX_MSGBOX2			950
#define _WNDIMGIDX_QUEST			700			//퀘스트창.
#define _WNDIMGIDX_HORSE			850			//말창.
#define _WNDIMGIDX_STOREDETAIL		1003		//상점세부리스트.
#define _WNDIMGIDX_GAMEOVER			800			//무공설정창
#define _IMGIDX_BELT				51
#define _WNDIMGIDX_NPCCHAT_TOP		1100		//NPC대화창
#define _WNDIMGIDX_CHAT				150			//채팅


// 새로운 인터페이스 인덱스
#define _NEW_WNDIMGIDX_MAGIC				1490		//무공설정창
#define _NEW_WNDIMGIDX_QUEST				1420		//퀘스트창.
#define _NEW_WNDIMGIDX_HORSE				1400		//말창.
#define _NEW_WNDIMGIDX_EXCHANGE				1390		//교환창
#define _NEW_WNDIMGIDX_GROUP				1360		//그룹창.
#define _NEW_WNDIMGIDX_GUILD				1300		//문원게시판.
#define _NEW_WNDIMGIDX_OPTION				1290		//옵션창.
#define _NEW_WNDIMGIDX_ITEMSET				1280		//상태창
#define _NEW_WNDIMGIDX_STATUS				1281		//상태창 확장
#define _NEW_WNDIMGIDX_STORE				1260		//상점.
#define _NEW_WNDIMGIDX_ITEMDETAIL			1261		//아이템세부리스트.
#define _NEW_WNDIMGIDX_STOREADD				1262		//상점.(하나짜리 물건살때).
#define _NEW_IDX_IMG_NOTICEBOX				1250		//공지창 인덱스
#define _NEW_WNDIMGIDX_INVENTORY			1220		//인벤토리
#define _NEW_WNDIMGIDX_BELT					1210		//벨트창
#define _NEW_WNDIMGIDX_NPCCHAT_TOP			1350		//NPC대화창
#define _NEW_WNDIMGIDX_NPCCHAT_MIDDLE		1351		//NPC대화창
#define _NEW_WNDIMGIDX_NPCCHAT_BOTTOM		1352		//NPC대화창
#define _NEW_WNDIMGIDX_NPCCHAT_TOP_NOFACE	1353		//NPC대화창
#define _NEW_WNDIMGIDX_NPCCHAT_BOTTOM_ARROW	1354		//NPC대화창
#define _NEW_WNDIMGIDX_STAUS_OTHERS			1288		//타인 상태창

// 세번째 인터페이스 인덱스
#define _WNDIMGIDX_GROUP					170			//그룹창.
#define _WNDIMGIDX_STATUS					180			//상태창
#define _WNDIMGIDX_STAUS_OTHERS				200			//타인 상태창
#define _WNDIMGIDX_MESSENGER				210			//메신저
#define _WNDIMGIDX_GUILD					280			//문원게시판.
#define _WNDIMGIDX_OPTION					290			//옵션창.
#define _WNDIMGIDX_SETTING					310			//환경설정창
#define _WNDIMGIDX_BELT						320			//벨트창
#define _WNDIMGIDX_INVENTORY				350			//인벤토리
#define _WNDIMGIDX_EXCHANGE					370			//교환창
#define _WNDIMGIDX_NPCCHAT_TOP_NOFACE		380			//NPC대화창
#define _WNDIMGIDX_NPCCHAT_MIDDLE			381			//NPC대화창
#define _WNDIMGIDX_NPCCHAT_BOTTOM			382			//NPC대화창
#define _WNDIMGIDX_NPCCHAT_BOTTOM_ARROW		383			//NPC대화창
#define _WNDIMGIDX_STORE					390			//상점.
#define _WNDIMGIDX_ITEMDETAIL				391			//아이템세부리스트.
#define _WNDIMGIDX_STOREADD					392			//상점.(하나짜리 물건살때).
#define _WNDIMGIDX_EXIT						410			//상점.(하나짜리 물건살때).
#define _IDX_IMG_NOTICEBOX					660			//공지창 인덱스
#define _WNDIMGIDX_VIEWMINIMAP				670			//미니맵 뷰어
#define _WNDIMGIDX_FACEIMGUP				680			//사진등록
#define _WNDIMGIDX_SIEGE					690			//발석거윈도우
#define _WNDIMGIDX_NOTICEEDIT				284			//공지수정창
#define _WNDIMGIDX_RANKEDIT					284			//직위수정창
#define _WNDIMGIDX_MAGIC					710			//무공설정창
#define _WNDIMGIDX_USERMARKET				760			//유저 아이템 거래 창
#define _WNDIMGIDX_USERMARKETUP				780			//유저 아이템 등록 창
#define _WNDIMGIDX_UTIL						800 		//유틸
#define _WNDIMGIDX_MAGICSHORTCUT			20			//무공단축키창
// 메인인터페이스에서 쓰일 버튼 아이디.
#define _BTN_ID_CHANGE				0
#define _BTN_ID_MINIMAP				1
#define _BTN_ID_MUGONG				2
#define _BTN_ID_EXIT				3
#define _BTN_ID_LOGOUT				4
#define _BTN_ID_GROUP				5
#define _BTN_ID_GUILD				6
#define _BTN_ID_BELT				7
#define _BTN_ID_MAGIC				8
#define _BTN_ID_POPUP				9
#define _BTN_ID_QUEST				10
#define _BTN_ID_OPTION				11
#define _BTN_ID_HELP				12
#define _BTN_ID_HORSE				13
#define _BTN_ID_BAG					14
#define _BTN_ID_CHAR				15

#define _MAX_CHATLINE				15

#define _SYSTEM_CHATLINE			5

#define _CHAT_MODE_NORMAL			0
#define _CHAT_MODE_GROUP			1
#define _CHAT_MODE_GUILD			2

#define _INFO_CHAR					0
#define _INFO_MINIMAP				1

#define _MAX_SAVECHATLINE			80

#define _BELT_STATE_STAY			0
#define _BELT_STATE_UP				1
#define _BELT_STATE_DOWN			2

#define _NEW_BTN_ID_CHANGE				0
#define _NEW_BTN_ID_MINIMAP				1
#define _NEW_BTN_ID_MUGONG				2
#define _NEW_BTN_ID_EXIT				3
#define _NEW_BTN_ID_LOGOUT				4
#define _NEW_BTN_ID_GROUP				5
#define _NEW_BTN_ID_GUILD				6
#define _NEW_BTN_ID_MAGIC				7
#define _NEW_BTN_ID_QUEST				8
#define _NEW_BTN_ID_OPTION				9
#define _NEW_BTN_ID_MESSENGER			10
#define _NEW_BTN_ID_HORSE				11
#define _NEW_BTN_ID_BAG					12
#define _NEW_BTN_ID_CHAR				13
#define _NEW_BTN_ID_LARGECHAT			14
#define	_NEW_BTN_ID_BELT				15
#define _NEW_BTN_ID_CHATDENY			16
#define _NEW_BTN_ID_CHATSHOUT			17
#define _NEW_BTN_ID_CHATGROUP			18
#define _NEW_BTN_ID_CHATGUILD			19
#define _NEW_BTN_ID_CHATALLDENY			20
#define _NEW_BTN_ID_DENYGUILD			21
#define _NEW_BTN_ID_DENYSHOUT			22

#define _NEW_MAX_INTER_BTN				23

#define _3rd_BTN_ID_CHANGE				0
#define _3rd_BTN_ID_MINIMAP				1
#define _3rd_BTN_ID_MUGONG				2
#define _3rd_BTN_ID_QUEST				3
#define _3rd_BTN_ID_OPTION				4
#define _3rd_BTN_ID_BAG					5
#define _3rd_BTN_ID_CHAR				6
#define	_3rd_BTN_ID_BELT				7

#define _MAX_INTER_BTN					8

/******************************************************************************************************************
	#30. ScrollBar
*******************************************************************************************************************/
#define	SCR_TYPE_VERTICAL			0
#define	SCR_TYPE_HORIZONTAL			1


/******************************************************************************************************************
	#1. Inventory Window
*******************************************************************************************************************/
#define _INVEN_MAX_CELL				36
#define _INVEN_CELL_XCNT			6
#define _INVEN_CELL_YCNT			6
#define _INVEN_TOTAL_CELL			600
#define _INVEN_MAX_CELL_YCNT		100
#define _INVEN_CELL_XSTART			25
#define _INVEN_CELL_YSTART			41

#define _NEW_INVEN_CELL_YCNT		8

#define _NEW_INVEN_CELL_XSTART		17
#define _NEW_INVEN_CELL_YSTART		71

#define _MAX_INVEN_BTN				4
#define _MAX_INVEN_ITEM				46

#define _BTN_ID_INVENCLOSE			0
#define _BTN_ID_FUN1				1				
#define _BTN_ID_FUN2				2
#define _BTN_ID_MINIMAPBOOK			3

#define _MAX_TYPE					3

#define _INVEN_TYPE_BAG				0
#define _INVEN_TYPE_REPAIR			1
#define _INVEN_TYPE_SELL			2
#define _INVEN_TYPE_STORAGE			3

#define _PRICE_NONE					0
#define _PRICE_RECEIVING			1
#define _PRICE_RECEIVED				2

/******************************************************************************************************************
	#1. NPC Window
*******************************************************************************************************************/
#define _MAX_NPC_BTN				3

#define _BTN_ID_NPCCLOSE			0
#define _BTN_ID_NPCSCRLDN			1
#define _BTN_ID_NPCSCRLUP			2

/******************************************************************************************************************
	#1. Minimap
*******************************************************************************************************************/
#define _NEW_BLEND_BTN				0
#define _NEW_EXPAND_BTN				1

#define _3rd_BLEND_BTN				0
#define _3rd_EXPAND_BTN				1
#define _3rd_MAPBOOK_BTN			2

/******************************************************************************************************************
	#1. Siege Window
*******************************************************************************************************************/
#define _MAX_SIEGE_BTN				4

#define _BTN_ID_SIEGECLOSE			0
#define	_BTN_ID_ATTACK				1
#define	_BTN_ID_WAIT				2
#define	_BTN_ID_MOVE				3

/******************************************************************************************************************
	#1. UserMarket Window
*******************************************************************************************************************/
#define _MAX_MARKETCELL				13

/******************************************************************************************************************
	# FaceImgUp Window
*******************************************************************************************************************/
#define _CELL_IN_FACEUP				12
/******************************************************************************************************************
	#1. Messenger Window
*******************************************************************************************************************/
#define _CELL_IN_VIEW				7

#define _RECEIVED_BOX				0
#define _READ_BOX					1
#define	_WRITE_BOX					2
#define	_GIFT_BOX					3
#define	_SEND_BOX					4

#define _RECEIVED_MODE				0
#define _SEND_MODE					2

/******************************************************************************************************************
	#1. Exchange Window
*******************************************************************************************************************/
#define _MAX_DEAL_BTN			3

#define _MY_DEAL				0	
#define _YOU_DEAL				1

#define _DEAL_TOTAL_CELL		200
#define _MAX_DEAL_ITEM			12

#define _DEAL_MAX_CELL			30
#define _DEAL_CELL_XCNT			5
#define _DEAL_CELL_YCNT			6
#define _DEAL_MAX_CELL_YCNT		40

#define _LDEAL_CELL_XSTART		21
#define _LDEAL_CELL_YSTART		48
#define _RDEAL_CELL_XSTART		253
#define _RDEAL_CELL_YSTART		48

#define _BTN_ID_DEALCLOSE		0
#define _BTN_ID_DEAL			1
#define _BTN_ID_DEALCHECK		2

#define _NEW_BTN_ID_DEAL		0

#define _NEW_DEAL_MAX_CELL		25
#define _NEW_DEAL_CELL_XCNT		5
#define _NEW_DEAL_CELL_YCNT		5
#define _NEW_DEAL_MAX_CELL_YCNT	40

#define _NEW_LDEAL_CELL_XSTART	23
#define _NEW_LDEAL_CELL_YSTART	64
#define _NEW_RDEAL_CELL_XSTART	263
#define _NEW_RDEAL_CELL_YSTART	64

/******************************************************************************************************************
	#1. Light fog
*******************************************************************************************************************/
#define NUM_CNTX_LIGHTTILE			17
#define NUM_CNTY_LIGHTTILE			18
#define TILE_START_XPOS				-8
#define TILE_START_YPOS				-29

#define TILE_WIDTH					48
#define TILE_HEIGHT					32

#define NUM_LIGHTTILE_INDICES		(NUM_CNTX_LIGHTTILE)*(NUM_CNTY_LIGHTTILE)*3*2
#define NUM_LIGHTTILE_VERTICES		(NUM_CNTX_LIGHTTILE+1)*(NUM_CNTY_LIGHTTILE+1)



/******************************************************************************************************************
	#1. Magic
*******************************************************************************************************************/
#define _MAGIC_ACTIVE				0			// 마법활성상태.
#define _LIGHT_ACTIVE				1			// 마법광원활성상태.
#define _MAGIC_FINISH				2			// 마법소멸.

#define _SKILL_FIREBALL				1			// 화염장.(화)
#define _SKILL_HEALLING				2			// 회복술.
#define _SKILL_ONESWORD				3			// 외수.(무)
#define _SKILL_ILKWANG				4			// 일광.
#define _SKILL_FIREBALL2			5			// 금강화염장.
#define _SKILL_AMYOUNSUL			6			// 암연술.
#define _SKILL_YEDO					7			// 예도.
#define _SKILL_FIREWIND				8			// 화염풍.
#define _SKILL_FIRE					9			// 염사장.
#define _SKILL_SHOOTLIGHTEN			10			// 뢰인장.
#define _SKILL_LIGHTENING			11			// 강격.
#define _SKILL_ERGUM				12			// 어검술.
#define _SKILL_FIRECHARM			13			// 폭살계.
#define _SKILL_HANGMAJINBUB			14			// 항마진법.
#define _SKILL_DEJIWONHO			15			// 대지원호.
#define _SKILL_HOLYSHIELD			16			// 결계.
#define _SKILL_SKELLETON			17			// 백골소환술.
#define _SKILL_CLOAK				18			// 은신.
#define _SKILL_BIGCLOAK				19			// 대은신.
#define _SKILL_TAMMING				20			// 뢰혼격.
#define _SKILL_SPACEMOVE			21			// 아공행법.
#define _SKILL_EARTHFIRE			22			// 지염술.
#define _SKILL_FIREBOOM				23			// 폭열파.
#define _SKILL_LIGHTFLOWER			24			// 뢰설화.
#define _SKILL_BANWOL				25			// 반월.
#define _SKILL_FIRESWORD			26			// 염화결.
#define _SKILL_MOOTEBO				27			// 무태보.
#define _SKILL_SHOWHP				28			// 탐기파연.
#define _SKILL_BIGHEALLING			29			// 대회복.
#define _SKILL_SINSU				30			// 신수소환.
#define _SKILL_SHIELD				31			// 주술의막.
#define _SKILL_KILLUNDEAD			32			// 사자윤회.
#define _SKILL_SNOWWIND				33			// 빙설풍.

#define _SKILL_RANDSWING			34			// 연월참.
#define _SKILL_JUMPSHOT				35			// 맹룡승천세.
#define _SKILL_KICK					36			// 무상각.

#define _SKILL_MOONOK				37			// 월영옥.
#define _SKILL_MOONCHAM				38			// 월영파.
#define _SKILL_ICEBOLT				39			// 빙월장.
#define _SKILL_SUPERICEBOLT			40			// 빙월진천장.
#define _SKILL_MAGICARROW			41			// 비격장.
#define _SKILL_FIREBOOMUP			47			// 폭열파업.(지뢰형폭열파???????).
#define _SKILL_EARTH_SUMMON			48			// 대지소환술.(운석소환???????).
#define _SKILL_ICE					53			// 빙사장.
#define _SKILL_LIGHTWALL			63			// 뢰벽.(비격벽???????).
#define _SKILL_LIGHTFLOWERUP		64			// 뢰설화업.(원거리뢰설화???????).
#define _SKILL_MAGICTRAP			66			// 비격트랩.
#define _SKILL_HANDWIND				67			// 장풍.
#define _SKILL_HURRICANE			72			// 용선풍.
#define _SKILL_HURRICANESHOT		73			// 풍진참
#define _SKILL_HURRICANEBOMB		74			// 격풍
#define _SKILL_REVIVE				77			// 소생술.
#define _SKILL_TRANSFORM			78			// 둔갑술.
#define _SKILL_ANTIMAGIC_FIRE		85			// 항마진법(화).
#define _SKILL_ANTIMAGIC_ICE		86			// 항마진법(빙).
#define _SKILL_ANTIMAGIC_LIGHTENING	87			// 항마진법(뢰).
#define _SKILL_ANTIMAGIC_WIND		88			// 항마진법(풍).
#define _SKILL_MAGICUP				89			// 강마진법.
#define _SKILL_MAGICUP_FIRE			90			// 강마진법(화).
#define _SKILL_MAGICUP_ICE			91			// 강마진법(빙).
#define _SKILL_MAGICUP_LIGHTENING	92			// 강마진법(뢰).
#define _SKILL_MAGICUP_WIND			93			// 강마진법(풍).
#define _SKILL_POWERUP				94			// 맹호강세.
#define _SKILL_WITH_FIRE			95			// 맹호강세(화).
#define _SKILL_WITH_ICE				96			// 맹호강세(빙).
#define _SKILL_WITH_LIGHT			97			// 맹호강세(뢰).
#define _SKILL_WITH_WIND			98			// 맹호강세(풍).
#define _SKILL_WITH_DEF				99			// 맹호강세(방어).
#define _SKILL_WITH_MAGIC			100			// 맹호강세(마법).
#define _SKILL_WITH_ATT				101			// 맹호강세(공격).
#define _SKILL_MAXDEFENCE			102			// 철포삼
#define _SKILL_MANWOL				103			// 회선참
#define _SKILL_SMALLSPACEMOVE		104			// 이형환위.
#define _SKILL_POWERSKELLETON		105			// 진골소환술.
#define _SKILL_MAXOFENCE			106			// 광마결
#define _SKILL_CHANGEPOSITION		107			// 전위보
#define _SKILL_PULL					108			// 격공섭물
#define _SKILL_THUNDERSTORM			111			// 뢰화난무
#define _SKILL_MAXDEFEECEMAGIC		112			// 역혈마공
#define _SKILL_FIREBALL10			113			// 만천화우
#define _SKILL_REMOVEPOISON			120			// 정화술
#define _SKILL_FULLCLOAK			121			// 기환술
#define _SKILL_DOSASHIELD			122			// 선천기공
#define _SKILL_MONSTERUP			123			// 전이술
#define _SKILL_CROSS_ICE			110			// 빙렬파

#define _SKILL_PAWHANGBO			109			// 파황보
#define _SKILL_KANGMAK				114			// 회풍강막
#define _SKILL_MYULSAL				124			// 멸살계

#define _SKILL_TAWOO				125			// 격산타우
#define _SKILL_BANTAN				126			// 반탄강기
#define _SKILL_COPY					127			// 허상분신
#define _SKILL_FREEMOVE				128			// 금강부동
#define _SKILL_HEALX				129			// 양생술

#define _SKILL_BIGMOUNTAIN			130			// 태산압정
#define _SKILL_HYPERSWORD			131			// 쾌도난마
#define _SKILL_POTIONUP				132			// 운기요상
#define _SKILL_1000THUNDER			133			// 천뢰
#define _SKILL_CLOUDTHUNDER			134			// 운중뇌격
#define _SKILL_BIGAM				135			// 대암연술
#define _SKILL_INHALEHP				136			// 흡성대법
#define _SKILL_DOLL					137			// 분열혼

#define _SKILL_BALSACHE				138			// 발사체
#define _SKILL_JIKSUNGYE			139			// 직선계
#define _SKILL_JUMPSHOT_HIGH		143			// 고급맹룡승천세
#define _SKILL_PAWHANGBO_HIGH		144			// 고급파황보
#define _SKILL_SHIELD_HIGH			145			// 고급주술의막
#define _SKILL_MAXDEFEECEMAGIC_HIGH	146			// 고급역혈마공
#define _SKILL_DEJIWONHO_HIGH		147			// 고급대지원호
#define _SKILL_CLOAK_HIGH			148			// 고급은신술
#define _SKILL_MOONCHAM_HIGH		149			// 고급월영파
#define _SKILL_POKBAL				150			// 폭발형
#define _SKILL_JISOKGYE				151			// 지속계
#define _SKILL_RANDSWING_HIGH		152			// 고급연월참






#define _SKILL_ICEWALL				140			// 빙벽
#define _SKILL_BANTAN_HITTED		141			// 반탄강기 반사
#define _SKILL_COPYDIE				142			// 허상죽기
#define _SKILL_CONCENFIREBALL		200			// 집중화염장.


#define _SKILL_ERGUM_HIGH			10012		// 고급어검술
#define _SKILL_MAXDEFENCE_HIGH		10102		// 고급철포삼
#define _SKILL_MANWOL_HIGH			10103		// 고급회선참
#define _SKILL_YEDO_HIGH			10007		// 예도 고급
#define _SKILL_TAMMING_HIGH			10020		// 뢰혼격고급
#define _SKILL_AMYOUNSUL_HIGH		10006		// 암연술고급
#define _SKILL_REVIVE_HIGH			10077		// 소생술고급
#define _SKILL_REMOVEPOISON_HIGH	10120		// 정화술고급




#define _SKILL_SPACEMOVESHOW		320			// 아공행법나타나기.
#define _SKILL_SPACEMOVESHOW2		321			// 아공행법사라나기.
#define _SKILL_SPACEMOVEHIDE2		322			// 아공행법나타나기.
#define _SKILL_PULLSHOW				323			// 격공섭물, 전위보 나타나기.

#define _EVENT_LEFTFIRE1			330			// 잔염1.
#define _EVENT_LEFTFIRE2			331			// 잔염2.
#define _EVENT_LEFTFIRE3			332			// 잔염3.
#define _EVENT_LEFTFIRE4			333			// 잔염4.
#define _EVENT_LEFTFIRE5			334			// 잔염5.
#define _EVENT_DUST					335			// 광캘때 먼지.

#define _SKILL_SHOOTLIGHTEN_ADD		336			// 뢰인장부가효과.
#define _SKILL_REFINEADD			337			// 제련부가효과.

#define _SKILL_STRUCK_FIRE			400			// 무공계열별 타격(화).
#define _SKILL_STRUCK_ICE			401			// 무공계열별 타격(빙).
#define _SKILL_STRUCK_LIGHT			402			// 무공계열별 타격(뢰).
#define _SKILL_STRUCK_WIND			403			// 무공계열별 타격(풍).
#define _SKILL_STRUCK_HOLY			404			// 무공계열별 타격(신성).
#define _SKILL_STRUCK_DARK			405			// 무공계열별 타격(암흑).
#define _SKILL_STRUCK_ILLU			406			// 무공계열별 타격(환영).
#define _SKILL_STRUCK_NONE			407			// 무공계열별 타격(무).

#define _SKILL_GUMGI_FIRE			408			// 무공계열별 검기1(화).
#define _SKILL_GUMGI_ICE			409			// 무공계열별 검기1(빙).
#define _SKILL_GUMGI_LIGHT			410			// 무공계열별 검기1(뢰).
#define _SKILL_GUMGI_WIND			411			// 무공계열별 검기1(풍).
#define _SKILL_GUMGI_HOLY			412			// 무공계열별 검기1(신성).
#define _SKILL_GUMGI_DARK			413			// 무공계열별 검기1(암흑).
#define _SKILL_GUMGI_ILLU			414			// 무공계열별 검기1(환영).
#define _SKILL_GUMGI_NONE			415			// 무공계열별 검기1(무).

#define _SKILL_DOT_1				416			// 표창1.
#define _SKILL_DOT_2				417			// 표창2.
#define _SKILL_DOT_3				418			// 표창3.
#define _SKILL_SNOWDART				419			// 눈싸움.
#define _SKILL_REFINE_S				420			// 제련성공.
#define _SKILL_REFINE_F				421			// 제련실패.
#define _SKILL_LEVELUP				422			// 레벨업.
#define _SKILL_POWERUPGRADE			423			// 레벨업.
/******************************************************************************************************************
	MonMagic
*******************************************************************************************************************/
#define _MONMAGIC_KEPAL				500			// 전격공격.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_EXPLODE			501			// 폭발마법.(돌골렘죽을때, 론공격시)
#define _MONMAGIC_BLACK1			502			// 흑마법사. (마법(시전))
#define _MONMAGIC_BLACK2			503			// 흑마법사. (마법(마법))
#define _MONMAGIC_DIE				504			// 흑마법사, 경갑옷기사, 홍마법사, 신기선보스변신전 죽음.(효과)
#define _MONMAGIC_ANTHEAL			505			// 치유개미힐링(발사마법, 폭발효과.)
#define _MONMAGIC_GREATANT			506			// 거대개미.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_MAGENUMA			508			// 결계.
#define _MONMAGIC_ANT				509			// 병정개미공격.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_WORKANT			510			// 일개미공격.(공격한 캐릭터위에)(마법)
#define _MONMAGIC_RED1				511			// 홍의법사. (마법(시전))
#define _MONMAGIC_RED2				512			// 홍의법사. (마법(마법))
#define _MONMAGIC_COWGHOST			513			// 우면귀. (마법)
#define _MONMAGIC_SINSU				514			// 신수. (마법)
#define _MONMAGIC_ZOMBIE			515			// 좀비. (마법)
#define _MONMAGIC_JUMAWANG			516			// 주마왕. (마법)
#define _MONMAGIC_CHIM				517			// 다크
#define _MONMAGIC_ARROW				518			// 궁수경비
#define _MONMAGIC_MAARROW			519			// 해골궁수
#define _MONMAGIC_DUALAXE			520			// 쌍도끼해골
#define _MONMAGIC_COWFLAME			521			// 화염우면귀
#define _MONMAGIC_BIGGINE_ATT		522			// 촉룡신
#define _MONMAGIC_BIGGINE_CHAR		523			// 촉룡신
#define _MONMAGIC_SANDFISH			524			// 거환수
#define _MONMAGIC_BAODIE			525			// 신기병
#define _MONMAGIC_SINGI_DIE			526			// 신기 죽기
#define _MONMAGIC_HUSU_DIE			527			// 허수아비
#define _MONMAGIC_ZOMBIE_DIE		528			// 좀비
#define _MONMAGIC_SSEGI				529			// 쐐기나방
#define _MONMAGIC_NUMAGUMGI			530			// 옛날 누마왕
#define _MONMAGIC_EXPLODE1			531			// 석장인
#define _MONMAGIC_BOSSATT			532			// 파천황검기
#define _MONMAGIC_BOSSDIE			533			// 파천황죽기
#define _MONMAGIC_OMASKEL_DIE		534			// 해골류죽기
#define _MONMAGIC_GUDEGI			535			// 동굴구더기
#define _MONMAGIC_DUNG				536			// 둥
#define _MONMAGIC_GUMGI				537			// 경비검기
#define _MONMAGIC_LIGHTENING		538			// 몬스터강격.
#define _MONMAGIC_LIGHTFLOWER		539			// 몬스터뢰설화.
#define _MONMAGIC_POKAN				540			// 폭안거미.
#define _MONMAGIC_BIDOK				541			// 비독거미.
#define _MONMAGIC_REDMOON			542			// 적월마.
#define _MONMAGIC_WINDGOD			543			// 풍백.
#define _MONMAGIC_POSUANT			544			// 포수개미.
#define _MONMAGIC_HUMANTREE			545			// 형인수.
#define _MONMAGIC_LIGHTRIGHTATT		546			// 광명우사(공격)6프레임..
#define _MONMAGIC_LIGHTRIGHTDIE		547			// 광명우사(죽기)10프레임..
#define _MONMAGIC_LIGHTLEFTATT		548			// 광명좌사(공격)6프레임..
#define _MONMAGIC_LIGHTLEFTDIE		549			// 광명좌사(죽기)10프레임..
#define _MONMAGIC_LIGHTLEFTMAGIC	550			// 광명좌사(마법공격)6프레임..
#define _MONMAGIC_GUOBLUEATT		551			// 구오좀비(푸른색)(마법공격)6프레임..
#define _MONMAGIC_GUOREDATT			552			// 구오좀비(붉은색)(마법공격)6프레임..
#define _MONMAGIC_ONEZOMBIEDIE		553			// 외팔이좀비(죽기)10프레임..
#define _MONMAGIC_REALUMAATT		554			// 우면본왕(검기공격)10프레임..
#define _MONMAGIC_REALUMAMAGICATT	555			// 우면본왕(마법)20프레임..
#define _MONMAGIC_WEAPONSKELDIE		556			// 창해골, 칼해골, 활해골(죽기)8프레임..
#define _MONMAGIC_SKELCHIEFDIE		557			// 해골장수(죽기)10프레임..
#define _MONMAGIC_SKELBOSSFIRE		558			// 해골진왕(마법-파이어볼)10프레임..
#define _MONMAGIC_SKELBOSS1			559			// 해골진왕..
#define _MONMAGIC_SKELBOSS2			560			// 해골진왕..
#define _MONMAGIC_SKELBOSS3			561			// 해골진왕..
#define _MONMAGIC_SKELBOSS4			562			// 해골진왕..
#define _MONMAGIC_SKELBOSS5			563			// 해골진왕..
#define _MONMAGIC_SKELBOSS6			564			// 해골진왕..
#define _MONMAGIC_SKELBOSS7			565			// 해골진왕..
#define _MONMAGIC_SKELBOSS8			566			// 해골진왕..
#define _MONMAGIC_SKELBOSS9			567			// 해골진왕..
#define _MONMAGIC_SKELBOSS10		568			// 해골진왕..
#define _MONMAGIC_YEJIN_HEAL		569			// 예진(이벤트)치료시전효과.
#define _MONMAGIC_DONKING			570			// 돈왕검기.
#define _MONMAGIC_KINGKING			571			// 왕중왕검기.
#define _MONMAGIC_BLOODSAGAL		572			// 혈사갈전기공격.
#define _MONMAGIC_FLEA_SHOT			573			// 벼룩눈 발사.
#define _MONMAGIC_BYDONKING			574			// 돈왕의 공격에 히트되었을때.
#define _MONMAGIC_KINGKING2			575			// 왕중왕 특수공격.
#define _MONMAGIC_FIREBALL			576			// 반야좌사파이어볼.
#define _MONMAGIC_SAU				577			// 사우천왕이펙트추가.

// 앙코르와트지역추가.
#define _MONMAGIC_SPEAR				578			// 광신도1 창공격.
#define _MONMAGIC_POISON			579			// 광신도2 독공격.
#define _MONMAGIC_ELEP				580			// 거환수 독공격.
#define _MONMAGIC_LION1				581			// 석화돌사자공격.
#define _MONMAGIC_FLION_D			582			// 화염돌사자 죽기.
#define _MONMAGIC_SLION_D			583			// 석화돌사자 죽기.
#define _MONMAGIC_MURYUK_A			584			// 무력신장 공격.
#define _MONMAGIC_MURYUK_S			585			// 무력신장 맞기.
#define _MONMAGIC_MURYUK_D			586			// 무력신장 죽기.
#define _MONMAGIC_MAWANG_A1			587			// 진천마신 검기공격1.
#define _MONMAGIC_MAWANG_MA			588			// 진천마신 마법공격.
#define _MONMAGIC_MAWANG_D			589			// 진천마신 죽기.
#define _MONMAGIC_THROW_STONE		590			// 원후자,원후군 돌던지기.
#define _MONMAGIC_MAWANG_A2			591			// 진천마신 검기공격2.
#define _MONMAGIC_LION2				592			// 화염돌사자공격.

#define _MONMAGIC_SIEGE_SHOOT		593			// 발석거 포 쏘는 것.
#define _MONMAGIC_SIEGE_HITTED		594			// 발석거 포 맞는 것.
#define _MONMAGIC_SIEGECAR_SHOOT	595			// 쇠뇌차 포 쏘는 것.
#define _MONMAGIC_SIEGECAR_HITTED	596			// 쇠뇌차 포 맞는 것.

// 누마공성전
#define _MONMAGIC_NUMAGIBYUNG		597			// 누마기병 공격

#define _MONMAGIC_NUMABUBSA1		598			// 누마사령법사
#define _MONMAGIC_NUMABUBSA2		599			// 누마사령법사
#define _MONMAGIC_NUMABUBSA3		600			// 누마사령법사
#define _MONMAGIC_NUMABUBSA4		601			// 누마사령법사
#define _MONMAGIC_NUMABUBSA5		602			// 누마사령법사
#define _MONMAGIC_NUMABUBSA6		603			// 누마사령법사


#define _MONMAGIC_NUMABUBSA_DIE		604			// 누마사령법사 죽기

#define _MONMAGIC_NUMABODYGUARD_DIE	605			// 누마친위대장 죽기
#define _MONMAGIC_NUMABODYGUARD_A	606			// 누마친위대장 마법공격

#define _NPCEFFECT_THESWORD			607			// 절대검 이펙트

#define	_MONMAGIC_TADANGGA_ATTACK	608			// 타당가 일반공격
#define _MONMAGIC_TADANGGA_MAGIC	609			// 타당가 마법공격
#define _MONMAGIC_TADANGGA_DIE		610			// 타당가 죽기

#define _NPCEFFECT_THESWORD_STAND	611			// 절대검 들고 숨쉬기

#define _MONMAGIC_BARRACK_DIE		612			// 훈련소 죽기
#define _MONMAGIC_GUARD_DIE			613			// 수호자 죽기
#define _MONMAGIC_STATUE_DIE		614			// 신전 죽기

#define _MONMAGIC_SAHYULGUI_A		615			// 사혈괴 손톱
#define _MONMAGIC_DEARYONG_A		616			// 대아룡 공격

#define _MONMAGIC_JICHUN_ATTACK		617			// 지천멸왕 일반공격
#define _MONMAGIC_JICHUN_MAGIC_A	618			// 지천멸왕 마법공격
#define _MONMAGIC_JICHUN_MAGIC_B	619			// 지천멸왕 마법공격2(전체공격)

#define _MONMAGIC_YOUKHYUL_ATTACK	620			// 육혈마룡 일반공격
#define _MONMAGIC_YOUKHYUL_MAGIC	621			// 육혈마룡 마법공격

#define _MONMAGIC_HANBINGMA_MAGIC	622			// 빙혼무장2 마법공격 맞을 때

#define _MONMAGIC_BINGHONGUNG_A		624			// 빙혼궁사1 일반공격

#define _MONMAGIC_BINGBAK_MAGIC_A	625			// 빙백귀녀 마법공격
#define _MONMAGIC_BINGBAK_MAGIC_B	626			// 빙백귀녀 마법공격
#define _MONMAGIC_BINGBAK_SIJUN		627			// 빙백귀녀 시전

#define _MONMAGIC_WHAYOUNG_MAGIC	628			// 화영한테 맞을 때
#define _EFFECT_FIRECRACKER_S		629			// 폭죽 소
#define _EFFECT_FIRECRACKER_M		630			// 폭죽 중
#define _EFFECT_FIRECRACKER_L		631			// 폭죽 대
#define _EFFECT_FIRECRACKER_XL		632			// 폭죽 특대
#define _MONMAGIC_GAMU_B			633			// 가무녀2 공격이펙
#define _MONMAGIC_DAWNQUEEN_MAGIC	634			// 새벽여왕 마법
#define _MONMAGIC_GAMU2_MAGIC		635			// 가무녀2마법
#define _MONMAGIC_GAMU2_MAGIC_SELF	636			// 가무녀2마법자신
#define _MONMAGIC_GAMU_MAGIC_NEAR	637			// 가무녀1 주변 마법
#define _MONMAGIC_GAMU_MAGIC		638			// 가무녀1 전체 마법
#define _MONMAGIC_GAMU_MAGIC_SELF	639			// 가무녀2 전체 자신
#define _MONMAGIC_GUARDGEN_MAGIC	640			// 호위장수 마법
#define _MONMAGIC_GUARDGEN_B		641			// 호위장수 공격이펙
#define _MONMAGIC_DAWNQUEEN_B		642			// 새벽여왕 공격이펙
#define _MONMAGIC_GUARDGEN_DIE		643			// 호위장수 죽기
#define _MONMAGIC_DAWNQUEEN_DIE		644			// 새벽여왕 공격이펙


#define _BLEND_NORMAL				0			// 일반적인그리기.(알파값이 적용될수있다.)
#define _BLEND_LIGHT				1			// 섬광효과형태의 블렌딩.
#define _BLEND_LIGHTINV				2	
#define _BLEND_INVNORMAL			3
#define _BLEND_INVLIGHT				4
#define _BLEND_INVLIGHTINV			5




/******************************************************************************************************************
	#1. Map Handler
*******************************************************************************************************************/

#define _BASETILE_WIDTH				96				// 기본타일 넓이.
#define _BASETILE_HEIGHT			64
	
#define _CELL_WIDTH					48				// 기본셀 넓이, 기본타일은 4개의 셀로 이루어지고 정보는 셀단위로 저장된다.
#define _CELL_HEIGHT				32

#define _VIEW_CELL_X_COUNT			24				// 뷰영역에 필요한 X축의 셀단위 개수.((짜투리 타일제외)좌와위로 3셀, 우와아래로 2셀씩의 여유를 둔다.)
#define _VIEW_CELL_Y_COUNT			26			
#define _VIEW_CELL_Y_COUNT_FOR_OBJ	44

#define _MEMVIEW_CELL_X_COUNT		36
#define _MEMVIEW_CELL_Y_COUNT		36

#define _VIEW_CELL_X_START			-200			// 뷰영역을 그리기 위한 시작 셀 X좌표.
#define _VIEW_CELL_Y_START			-157

#define _VIEW_CELL_X_START_INVEN	-196			// 뷰영역을 그리기 위한 시작 셀 X좌표.
#define _VIEW_CELL_Y_START_INVEN	-157

#define _VIEW_CELL_X_START_STATUS	-186			// 뷰영역을 그리기 위한 시작 셀 X좌표.
#define _VIEW_CELL_Y_START_STATUS	-157

#define _MAX_TILE_FILE				14

// 포그색 관련 속성.
#define _FOG_COLOR_TYPE0			RGB(0, 0, 0);
#define _FOG_COLOR_TYPE1			RGB(100, 10, 10);
#define _FOG_COLOR_TYPE2			RGB(10, 255, 10);
#define _FOG_COLOR_TYPE3			RGB(10, 10, 255);

// 속성 관련 정의.
#define _CAN_WALK					0
#define _CAN_NOTWALK	 			1
#define _CAN_FLY					0
#define _CAN_NOTFLY					1

// 문관련 정의.
#define _DOOR_ISCLOSED				0
#define _DOOR_ISOPEN				1

#define _TILE_ANI_DELAY_1			150
#define _TILE_ANI_DELAY_2			25
#define _TILE_ANI_DELAY_3			50
#define _TILE_ANI_DELAY_4			100
#define _TILE_ANI_DELAY_5			200
#define _TILE_ANI_DELAY_6			250
#define _TILE_ANI_DELAY_7			300
#define _TILE_ANI_DELAY_8			420

// 사운드 관련 정의
#define MAX_VOLUME					0
#define MIN_VOLUME					-10000

// 다중으로 겹치는 아이템 식별자
#define _MULTIPLE_TYPE_ITEM			2


// Config.ini 파일 
#define SECTION_OPTIONS			"Options"
#define KEY_EFFECTSOUND			"EffectSound"
#define KEY_EFFECTSOUNDLEVEL	"EffectSoundLevel"
#define KEY_BGM					"BGM"
#define KEY_BGMLEVEL			"BGMLevel"
#define KEY_AMBIENCE			"Ambience"
#define KEY_AMBIENCELEVEL		"AmbiousLevel"
#define KEY_SHADOWBLEND			"ShadowBlend"
#define KEY_REVERSEPAN			"ReversePan"
#define KEY_ACSHOW				"AcShow"
#define KEY_DCSHOW				"DcShow"
#define KEY_SHOWBLOODNUM		"ShowBloodNum"
#define KEY_DRAWNAME			"DrawName"
#define KEY_INFORMATIONMODE		"InformationMode"
#define KEY_SHOWMON				"ShowMon"
#define KEY_ATTACKUSER			"AttackUser"
#define KEY_MAGICLIGHT			"MagicLight"
#define KEY_SHOWBLOOD			"BloodNum"
#define KEY_SHOWUSERPIC			"UserPic"
#define KEY_AUTOPICKUP			"AutoPickUp"
#define KEY_SHOWDROPITEM		"ShowDropItem"
#define KEY_SHOWHEALTHNUM		"ShowHealthNum"
#define KEY_SHOWHELMET			"ShowHelmet"
#define KEY_SHOWMONEFFECT		"ShowMonEffet"
#define KEY_SHOWDEYING			"ShowDeying"
#define KEY_SHOWHEALTHBAR		"ShowHealthBar"
#define KEY_BELTPOSITIONX		"BeltPositionX"
#define KEY_BELTPOSITIONY		"BeltPositionY"
#define KEY_BELTMODE			"BeltMode"



/******************************************************************************************************************
	#1. Notice Edit Window
*******************************************************************************************************************/
#define _MAX_NOTICE_BTN				2

#define _MAX_NOTICE_EDITLINE		10

#define _BTN_ID_NOTICECLOSE			0
#define _BTN_ID_ACCEPET				1

/******************************************************************************************************************
	# Attack Mode
*******************************************************************************************************************/

#define _ATTACK_ALL					0
#define _ATTACK_PEACH				1
#define _ATTACK_GROUP				2
#define _ATTACK_GUILD				3
#define _ATTACK_VERSUS				4
/******************************************************************************************************************
	#1. Magic Window
*******************************************************************************************************************/
#define _MAX_TYPE_MAGIC				8
#define _MAX_MAGICSLOT				29

#define _MAX_MAGIC_BTN				3

#define _BTN_ID_CLOSE				0
#define _BTN_ID_PREV				1
#define _BTN_ID_NEXT				2

#define _MAGIC_MAX_CELL				29
#define _MAGIC_MAX_KEY				12


/******************************************************************************************************************
	#1. Option Window
*******************************************************************************************************************/
#define _MAX_OPTION_BTN				31

#define _BTN_ID_OPTIONCLOSE			0
#define _BTN_ID_BGMONOFF			1
#define _BTN_ID_SOUNDONOFF			2
#define _NEW_BTN_ID_ANTIPANONOFF	3
#define _BTN_ID_SBLENDONOFF			4
#define	_BTN_ID_BGMVOLUME			5
#define	_BTN_ID_WAVEVOLUME			6
#define _BTN_ID_SHOWMONINMAP		7
#define _BTN_ID_ATTACKUSER			8
#define _BTN_ID_MAGICLIGHT			9
#define _BTN_ID_SHOWBLOODNUM		10
#define _BTN_ID_REVIVAL				11
#define _BTN_ID_CHUNJIHAPIL			12
#define _BTN_ID_EXCHANGEMODE		13
#define _BTN_ID_WHISPERMODE			14
#define _BTN_ID_GUILDWHISPERMODE	16
#define _BTN_ID_GUILDJOINMODE		17
#define _BTN_ID_SHOUTMODE			18
#define _BTN_ID_ATTACKMODE			19
#define _BTN_ID_DRAWUSERPIC			20
#define _BTN_ID_AUTOPICKUP			21
#define _BTN_ID_SHOWDROPITEM		22
#define _BTN_ID_SHOWHEALTHNUM		23
#define _BTN_ID_MONEFFECT			24
#define _BTN_ID_SHOWDEYING			25
#define _BTN_ID_SHOWHELMET			26
#define _BTN_ID_ALLOWGROUP			27
#define _BTN_ID_SHOWHEALTHBAR		28
#define _BTN_ID_CUTSOMEONE			29
#define _BTN_ID_WHOLESHOUTMODE		30

#define _BASIC_SET					0
#define _ALLOW_SET					1
#define	_CHAT_SET					2
#define _VISUAL_SET					3
/******************************************************************************************************************
	#1. Util Window
*******************************************************************************************************************/
#define _SET_ITEM_MODE				0
#define _SET_MAGIC_MODE				1
#define _SET_ETC_MODE				2

/******************************************************************************************************************
	#Belt Window
*******************************************************************************************************************/
#define _VERTICAL_MODE				0
#define _HORIZONTAL_MODE			1

/******************************************************************************************************************
	#1. ViewMinimap Window
*******************************************************************************************************************/
#define _1ST_RATE				1
#define _2ND_RATE				2
#define _HALF_RATE				3
#define _QUATER_RATE			4

#define _MAX_MENU					17

#define _SCRNMAP_WIDTH				512
#define _SCRNMAP_HEIGHT				512

/******************************************************************************************************************
	#1. Horse Window
*******************************************************************************************************************/
#define _MAX_HORSE_BTN				5

#define _BTN_ID_HORSECLOSE			0
#define _BTN_ID_HORSEUP				1
#define _BTN_ID_HORSEDOWN			2
#define _BTN_ID_HORSEHIDE			3
#define _BTN_ID_HORSEENTER			4

/******************************************************************************************************************
	#1. Group Window
*******************************************************************************************************************/
#define _MAX_GROUP_BTN				5

#define _BTN_ID_GROUPCLOSE			0
#define _BTN_ID_GROUPMAKE			1
#define _BTN_ID_GROUPADD			2
#define _BTN_ID_GROUPDEL			3
#define _BTN_ID_GROUPICON			4
/******************************************************************************************************************
	#1. Status Window
*******************************************************************************************************************/
#define _TYPE_EQUIP					0
#define _TYPE_STATUS				1

#define _EQUIP_MAX_CELL				12

#define _MAX_TYPE_WND				2

#define _MAX_STAUTS_BTN				2

#define _BTN_ID_STATUSCLOSE			0
#define _BTN_ID_STATUS				1

#define _BTN_ID_STATUS_X			176
#define _BTN_ID_STATUS_Y			264

#define _EQUIP_CHAR_X				97
#define _EQUIP_CHAR_Y				200

#define _NEW_EQUIP_CHAR_X			88
#define _NEW_EQUIP_CHAR_Y			220
#define _NEW_USERSTATUS_CHAR_X		90
#define _NEW_USERSTATUS_CHAR_Y		225

#define _U_DRESS					0 
#define _U_WEAPON					1 
#define _U_RIGHTHAND				2 
#define _U_NECKLACE					3 
#define _U_HELMET					4 
#define _U_ARMRINGL					5 
#define _U_ARMRINGR					6                
#define _U_RINGL					7 
#define _U_RINGR					8 
#define _U_CHARM					9
#define _U_BOOTS					10
#define _U_ETC						11
#define _U_UNEQUIP					100





/******************************************************************************************************************
	#1. Store Window
*******************************************************************************************************************/
#define _MAX_STORE_BTN				8

#define _MAX_STORE_ITEM				5

#define _MAX_STORE_DETAIL_ITEM		12

#define _TYPE_STORE					0	// 상점.
#define _TYPE_STOREDETAIL			1	// 상점+세부품목.
#define _TYPE_KEEP					2	// 아이템보관.
#define _TYPE_DRUG					3	// 약제조.
#define _TYPE_STOREONEITEM			4	// 상점+하나짜리물건.

#define _TYPE_ADDSTORE				0
#define _TYPE_ADDDRUG				1

#define _BTN_ID_STORECLOSE			0
#define _BTN_ID_STOREOK				1
#define _BTN_ID_DETAILCLOSE			2
#define _BTN_ID_DETAILOK			3
#define _BTN_ID_DETAILLEFT			4
#define _BTN_ID_DETAILRIGHT			5
#define _BTN_ID_STOREADDCLOSE		6
#define _BTN_ID_STOREADDOK			7

#define _NEW_MAX_STORE_ITEM			4


/******************************************************************************************************************
	#1. Client To Server Message
*******************************************************************************************************************/
#define CM_QUERYUSERNAME			80
#define CM_QUERYBAGITEMS			81
#define CM_QUERYUSERSTATE			82	  //타인의 상태 보기
#define CM_CHANGENAME				104

#define CM_GAMEGUARD				800

#define CM_PICKUP					1000
#define CM_DROPITEM					1001
#define	CM_OPENDOOR					1002
#define CM_TAKEONITEM				1003
#define CM_TAKEOFFITEM				1004
#define CM_EAT						1006
#define CM_BUTCH					1007
#define CM_MAGICKEYCHANGE			1008
#define CM_SOFTCLOSE				1009
#define	CM_CLICKNPC					1010	// 이 메시지를 서버로 보내어 해당 MPC의 정보를 받는다.
#define	CM_MERCHANTDLGSELECT		1011	// 사용자가 NPC대화중 Tag가 존재하는 부분을 Click했을경우 보내어진다.
#define	CM_MERCHANTQUERYSELLPRICE	1012	// 팔기 물건을 올려 놓을 경우 가격을 얻는다.  
#define CM_USERSELLITEM				1013	// 팔기 버튼을 눌렸을 경우 (과기: 팔물건만 하나만 보냄, 현재: 팔물건 모두 보냄
#define CM_USERBUYITEM				1014	// 사기 버튼을 눌렸을 경우
#define CM_USERGETDETAILITEM		1015	// 상점 목록중에 Sub Menu가 있는 것을 클릭했을 경우
#define CM_DROPGOLD					1016
#define CM_LOGINNOTICEOK			1018
#define CM_GROUPMODE				1019	// 그룹 // ***************************************
#define CM_CREATEGROUP				1020	// ***************************************
#define CM_ADDGROUPMEMBER			1021	// ***************************************
#define CM_DELGROUPMEMBER			1022	// ***************************************
#define	CM_USERREPAIRITEM			1023	// 수리하다 버튼을 눌렀을 경우
#define	CM_MERCHANTQUERYREPAIRCOST	1024	// 수리할아이템을 올려 놓을 경우 가격을 얻는다.
#define	CM_DEALTRY					1025	// 팔기, 수리
#define	CM_DEALADDITEM				1026
#define	CM_DEALDELITEM				1027
#define	CM_DEALCANCEL				1028
#define	CM_DEALCHGGOLD				1029	//교환하는 돈이 변경됨
#define	CM_DEALEND					1030
#define	CM_USERSTORAGEITEM			1031	// 여관 // 사용자가 맏긴다 버튼(텍스트 버튼 아님)을 눌렀을 경우 보내어진다.
#define	CM_USERTAKEBACKSTORAGEITEM	1032	// 사용자가 찾는다 버튼(텍스트 버튼 아님)을 눌렀을 경우 보내어진다.
#define	CM_WANTMINIMAP				1033
#define CM_USERMAKEDRUGITEM			1034	// 
#define	CM_OPENGUILDDLG				1035	// 문파 // 사용자가 문파창을 열고자 했을 경우 보내어진다.
#define CM_GUILDHOME				1036	// 사용자가 문파창중 HOME 버튼을 눌렀을 경우 보내어진다.
#define	CM_GUILDMEMBERLIST			1037	// 사용자가 문파창중 문원LIST를 보고자 햇을 경우
#define CM_GUILDADDMEMBER			1038	// 사용자가 문원추가를 했을 경우
#define	CM_GUILDDELMEMBER			1039	// 사용자가 문원삭제를 했을 경우
#define	CM_GUILDUPDATENOTICE		1040	// 사용자가 문파공지를 수정 했을 경우
#define	CM_GUILDUPDATERANKINFO		1041	// 사용자가 문원직위를 수정했을 경우
#define CM_GUILDMAKEALLY			1044	// 사용자가 문파동맹을 했을 경우
#define CM_GUILDBREAKALLY			1045	// 사용자가 문파동맹파기를 했을경우
#define CM_QUERYQUESTDIARY			1046	//0629
#define CM_QUERYMONSTERINFO			1047
#define CM_QUERYSUBQUESTDIARY		1048
#define CM_QUESTDIARYDETAIL			1049

#define CM_TRUN						3010
#define CM_WALK						3011
#define CM_SITDOWN					3012
#define CM_RUN						3013
#define CM_HIT						3014
#define CM_HEAVYHIT					3015
#define CM_LONGHIT					3019
#define CM_POWERHIT					3018
#define CM_SPELL					3017	// 보낸후 서버에서 승인이 오면 동작을 한다. 스펠동작이 끝난후 sm_magicfire가 오면 동작을 스탠드로 바꾼다.
#define CM_WIDEHIT					3024
#define CM_FIREHIT					3025
#define CM_SAY						3030
#define CM_RANDHIT					3031
#define CM_BKSHIT					3032
#define CM_MANWOL					3033

#define CM_HIGH_RANDSWINGHIT        3034	//고급연월참

#define	CM_DROPCOUNTITEM			1101 
#define	CM_THROWHIT					1102

#define CM_ATTACKSHOOTER			1120
#define CM_MOVESHOOTER				1121
#define CM_WAITSHOOTER				1122
#define CM_CHARGESHOOTER			1123
#define CM_USEWEARITEM				1124

#define CM_ADDITEMUSERMARKET		1130
#define CM_SEARCHPAGEUSERMARKET		1136
#define CM_NEXTPAGEUSERMARKET		1131
#define CM_PREVPAGEUSERMARKET		1132
#define CM_REFRESHPAGEUSERMARKET	1134
#define CM_BUYITEMUSERMARKET		1133
#define CM_CANCELITEMUSERMARKET		1135

#define CM_REFRESHDHLBOX			1137
#define CM_READDHLMESSAGE			1138
#define CM_DELETEINBOXDHL			1139
#define CM_DELETESENTBOXDHL			1140
#define CM_SENDNEWDHL				1141
#define CM_CANCELSENTDHL			1142

#define CM_ACCPETMAGICCODE			1150
#define CM_UPDATEFACEIMAGE			1151
#define CM_REQUESTFACEIMAGE			1152
#define CM_REQUESTSETXY				1153

/******************************************************************************************************************
	#1. LOGIN PROC
*******************************************************************************************************************/
#define CM_PROTOCOL					2000
#define CM_IDPASSWORD				2001
#define CM_ADDNEWUSER				2002
#define CM_CHANGEPASSWORD			2003
#define CM_UPDATEUSER				2004

#define CM_QUERYCHR					100
#define CM_NEWCHR					101
#define CM_DELCHR					102
#define CM_SELCHR					103
#define CM_SELECTSERVER				104



/******************************************************************************************************************
	#1. Server To Client Message
*******************************************************************************************************************/
#define SM_RUSH						6		// 무태보 밀기.
#define SM_RUSHKUNG             	7 		// 앞으로 전진실패
#define SM_FIREHIT					8
#define SM_BACKSTEP					9

#define SM_TURN						10
#define SM_WALK						11
#define SM_SITDOWN					12
#define SM_RUN						13
#define SM_HIT						14
#define SM_HEAVYHIT					15
#define SM_SPELL					17		// 스펠을 한다.
#define SM_POWERHIT					18
#define SM_LONGHIT					19
#define SM_DIGUP					20

#define SM_DIGDOWN					21
#define SM_FLYAXE					22
#define SM_LIGHTING					23
#define SM_WIDEHIT					24
#define SM_MANWOL					25
#define SM_ALIVE					27
#define SM_HIDE						29
#define SM_DISAPPEAR				30

#define SM_STRUCK					31
#define SM_DEATH					32
#define SM_SKELETON					33		// SM_DEATH와 동일.
#define SM_NOWDEATH					34
#define SM_BACKSTEP2				35
#define SM_RUSH2					36

#define SM_HEAR						40
#define SM_FEATURECHANGED			41
#define SM_USERNAME					42
#define SM_WINEXP					44		
#define SM_LEVELUP					45
#define SM_DAYCHANGING				46
#define SM_POWERUP					47

#define SM_LOGON					50
#define SM_NEWMAP					51
#define SM_ABILITY					52
#define SM_HEALTHSPELLCHANGED		53
#define SM_MAPDESCRIPTION			54

#define SM_GAMEGUARD				80

#define SM_SYSMESSAGE				100
#define SM_GROUPMESSAGE				101
#define SM_CRY						102
#define SM_WHISPER					103
#define SM_GUILDMESSAGE				104
#define SM_EVENTMESSAGE				105

#define SM_ADDITEM					200
#define SM_BAGITEMS					201
#define SM_DELITEM					202
#define SM_UPDATEITEM				203

#define SM_ADDMAGIC					210
#define SM_SENDMYMAGIC				211
#define SM_DELMAGIC					212

#define SM_DROPITEM_SCCESS			600
#define SM_DROPITEM_FAIL			601

#define SM_ITEMSHOW					610
#define SM_ITEMHIDE 				611
#define SM_OPENDOOR_OK				612
#define SM_OPENDOOR_LOCK			613
#define SM_CLOSEDOOR				614
#define SM_TAKEON_OK				615
#define SM_TAKEON_FAIL				616
#define SM_TAKEOFF_OK				619
#define SM_TAKEOFF_FAIL				620

#define SM_SENDUSEITEMS				621
#define SM_WEIGHTCHANGED			622

#define SM_CLEAROBJECT				633
#define SM_CHANGEMAP				634
#define SM_EAT_OK					635
#define SM_EAT_FAIL					636
#define SM_BUTCH					637
#define SM_MAGICFIRE				638		// 마법이 실행된다.
#define SM_MAGIC_LVEXP				640
#define	SM_SOUND					641
#define SM_DURACHANGE				642
#define SM_MERCHANTSAY				643		//
#define	SM_MERCHANTDLGCLOSE			644
#define SM_SENDGOODSLIST			645
#define SM_SENDUSERSELL				646
#define	SM_SENDBUYPRICE				647
#define SM_USERSELLITEM_OK			648
#define SM_USERSELLITEM_FAIL		649

#define	SM_BUYITEM_SUCCESS			650
#define SM_BUYITEM_FAIL				651
#define SM_SENDDETAILGOODSLIST		652
#define	SM_GOLDCHANGED				653
#define SM_CHANGELIGHT				654
#define SM_LAMPCHANGEDURA			655
#define SM_CHANGENAMECOLOR			656
#define SM_CHARSTATUSCHANGE			657
#define SM_SENDNOTICE				658

#define SM_CREATEGROUP_OK			660		// 그룹 // ******************************************************************
#define SM_CREATEGROUP_FAIL			661		// ******************************************************************

#define SM_GROUPADDMEM_OK       	662
#define SM_GROUPDELMEM_OK       	663
#define SM_GROUPADDMEM_FAIL     	664
#define SM_GROUPDELMEM_FAIL     	665

#define SM_GROUPCANCEL				666		// ******************************************************************
#define SM_GROUPMEMBERS				667		// ******************************************************************
#define SM_SENDUSERREPAIR			668
#define SM_USERREPAIRITEM_OK		669

#define SM_USERREPAIRITEM_FAIL		670
#define SM_SENDREPAIRCOST			671
#define	SM_DEALMENU					673	// 교환창
#define	SM_DEALTRY_FAIL				674
#define	SM_DEALADDITEM_OK			675
#define	SM_DEALADDITEM_FAIL			676
#define	SM_DEALDELITEM_OK			677
#define	SM_DEALDELITEM_FAIL			678

#define	SM_DEALCANCEL				681 //도중에 거래 취소됨
#define	SM_DEALREMOTEADDITEM		682 //상대방이 교환 아이템을 추가
#define	SM_DEALREMOTEDELITEM		683 //상대방이 교환 아이템을 뺌
#define	SM_DEALCHGGOLD_OK			684
#define	SM_DEALCHGGOLD_FAIL			685
#define	SM_DEALREMOTECHGGOLD		686
#define	SM_DEALSUCCESS				687

#define SM_SENDUSERSTORAGEITEM		700
#define SM_STORAGE_OK				701
#define SM_STORAGE_FULL				702	//더 보관 못 함.
#define SM_STORAGE_FAIL				703	//보관 에러
#define SM_SAVEITEMLIST				704
#define SM_TAKEBACKSTORAGEITEM_OK	705
#define SM_TAKEBACKSTORAGEITEM_FAIL	706
#define SM_TAKEBACKSTORAGEITEM_FULLBAG	707
#define	SM_AREASTATE				708
#define SM_DELITEMS					709

#define SM_READMINIMAP_OK			710
#define SM_READMINIMAP_FAIL			711
#define SM_SENDUSERMAKEDRUGITEMLIST	712
#define SM_MAKEDRUG_SUCCESS			713
#define SM_MAKEDRUG_FAIL			714

#define SM_CHANGEGUILDNAME			750
#define SM_SENDUSERSTATE			751	// User State
#define SM_SUBABILITY				752
#define	SM_OPENGUILDDLG				753
#define	SM_OPENGUILDDLG_FAIL		754
#define	SM_SENDGUILDHOME			755
#define	SM_SENDGUILDMEMBERLIST		756
#define	SM_GUILDADDMEMBER_OK		757
#define	SM_GUILDADDMEMBER_FAIL		758
#define	SM_GUILDDELMEMBER_OK		759

#define	SM_GUILDDELMEMBER_FAIL		760
#define	SM_GUILDRANKUPDATE_FAIL		761
#define	SM_BUILDGUILD_OK			762
#define	SM_BUILDGUILD_FAIL			763
#define	SM_GUILDMAKEALLY_OK			768
#define	SM_GUILDMAKEALLY_FAIL		769

#define	SM_GUILDBREAKALLY_OK		770
#define	SM_GUILDBREAKALLY_FAIL		771
#define	SM_DLGMSG					772
#define SM_OPENGUILDDLG2			773
#define SM_OPENGUILDDLG3			774
#define SM_SENDGUILDMEMBERLIST2		775
#define SM_SENDGUILDMEMBERLIST3		776

#define SM_SETXY					780

#define SM_SPACEMOVE_HIDE			800  //순간이동 사라짐
#define SM_SPACEMOVE_SHOW			801  //나타남
#define SM_RECONNECT				802
#define SM_GHOST					803
#define SM_SHOWEVENT				804
#define SM_HIDEEVENT				805
#define SM_SPACEMOVE_HIDE2			806  //순간이동 사라짐
#define SM_SPACEMOVE_SHOW2			807  //나타남
#define SM_PULL_SHOW				808

#define SM_SAVEITEMLIST2			820
#define SM_SAVEITEMLIST3			821


#define SM_OPENHEALTH				1100
#define SM_CLOSEHEALTH				1101
#define SM_MONSTERSAY				1501
#define SM_CHANGEFACE				1104
#define	SM_RIDEHORSE				1300
#define SM_QUERYQUESTDIARY			1301
#define SM_ADDQUESTUNIT				1302
#define SM_ADDQUEST					1303
#define SM_QUERYMONSTERINFO			1304
#define SM_OBSERVERMSG				1305
#define SM_RANDSWINGHIT			    1306
#define SM_BACKSWINGHIT				1307
#define SM_BACKKICKHIT				1308
#define SM_STRUCK2                  1309
#define	SM_QUERYSUBQUESTDIARY		1310
#define SM_QUESTDIARYDETAIL			1311

#define SM_GROUPPOS					1312
#define	SM_COUNTERITEMCHANGE		1313
#define SM_USERSELLCOUNTITEM_OK		1314
#define SM_USERSELLCOUNTITEM_FAIL	1315
#define SM_REVIVAL					1316
#define SM_MAGICHIT					1317
#define SM_SVRVERSION				1318		

#define SM_THROWHIT					1319		
#define SM_THROWDOT					1320		
#define SM_MYREVIVAL				1321
#define	SM_WEAPONLEVELUP			1322
#define	SM_SHOWMONSTER				1323
#define SM_UPGRADEWEAPONOK			1324
#define SM_WEAPONPREFIXCHANGED		1325
#define SM_CUSTOMMONACTION			1326
#define SM_PLAYDICE					1200//1318		

#define SM_CHANGEMAGICCODE			1330

#define SM_HIGH_RANDSWINGHIT		1331
#define SM_POWERHIT_HIGH			1332
#define SM_LONGHIT_HIGH				1333
#define SM_MANWOL_HIGH				1334

#define SM_USERGETSHOOTER			1350
#define SM_SHOOTERSTATUSCHANGED		1351
#define SM_SHOTEFFECT				1352
#define SM_LOSESHOOTER				1353
#define SM_USEWEARITEM_FAIL			1354

#define SM_SENDLISTUSERMARKET		1355

#define SM_SENDDHLTITLES			1356
#define SM_READDHLMESSAGE			1357
#define SM_HAVEARRIVEDNEWDHL		1358

#define SM_CMDRESULT				1400
#define SM_SENDCHARSTATUS			1401
#define SM_UPDATEFACERESULT			1402
#define SM_SENDFACEIMAGE			1403

#define SM_MAGICFIRE2				1410

#define SM_BACKKICKUP				1420
#define SM_REFLEXPOWER				1421
#define SM_GUILDPOS					1423
#define SM_FIRECRACKER				1424 

#define SM_MAGICUSETIME				1430

#define SM_NEXTTIME_PASSWORD		1105		//  *로 표시하라는 메세지




/******************************************************************************************************************
	#1. LOGIN PROC
*******************************************************************************************************************/
#define	SM_VERSION_AVAILABLE	500			//
#define	SM_CERTIFICATION_FAIL	501			//  Fail
#define SM_ID_NOTFOUND			502			//	ID 없음
#define	SM_PASSWD_FAIL			503			//	패스워드 틀림
#define	SM_NEWID_SUCCESS		504			//	새아이디 잘 만들어 졌음
#define	SM_NEWID_FAIL			505			//	새아이디 만들기 실패
#define	SM_CHGPASSWD_SUCCESS	506			//	패스워드 바꾸기 성공
#define	SM_CHGPASSWD_FAIL		507			//	패스워드 바꾸기 실패
#define	SM_QUERYCHR				520			//	캐릭리스트
#define	SM_NEWCHR_SUCCESS		521			//	케릭터 생성 성공
#define	SM_NEWCHR_FAIL			522			//	케릭터 생성 실패
#define	SM_DELCHR_SUCCESS		523			//	케릭터 삭제 성공
#define	SM_DELCHR_FAIL			524			//	케릭터 삭제 실패
#define	SM_STARTPLAY			525			//	개임시작
#define	SM_STARTFAIL			526			//	개임시작 실패
#define	SM_QUERYCHR_FAIL		527			//	케릭터 정보 읽어오기 실패
#define	SM_OUTOFCONNECTION		528			//	연결 해제됨
#define	SM_PASSOK_SELECTSERVER	529			//	Password가 맞으므로  서버 Selection으로 넘어감(서버 List및 최근 접속서버 자료)
#define	SM_SELECTSERVER_OK		530			//	서버선택 (접속 서버 IP등의 정보가 들어감)
#define	SM_NEEDUPDATE_ACCOUNT	531			//	계정의 정보를 다시 입력하기 바람 창..
#define	SM_UPDATEID_SUCCESS		532			//	계정정보 갱신 성공
#define	SM_UPDATEID_FAIL		533			//	계정정보 갱신 실패
#define SM_PASSOK_WRONGSSN		534			//  잘못된 주민등록번호.
#define SM_NOT_IN_SERVICE		535			//  서버점검중.
#define SM_CHANGENAME			536			//  이름 바꾸기 - 서버 통합용 (04년 3월)


/******************************************************************************************************************
	Resource Dll string index
*******************************************************************************************************************/
#define _PUNISHMENT_ID_USING             100
#define _PUNISHMENT_ID_THEFT             101
#define _PUNISHMENT_DISTURB_GAME         102
#define _PUNISHMENT_BBS_CURSES           103
#define _PUNISHMENT_CONFIRMED_CURSES     104
#define _PUNISHMENT_USAGE_BUG            105
#define _PUNISHMENT_ASSUMED_GAMEMASTER   106
#define _PUNISHMENT_SPREAD_FALLACY       107
#define _PUNISHMENT_BLOCK_ID			 108
#define _NEW_ACCOUNT_HELP_ID             200
#define _NEW_ACCOUNT_HELP_PWD            201
#define _NEW_ACCOUNT_HELP_REPWD          202
#define _NEW_ACCOUNT_HELP_NAME           203
#define _NEW_ACCOUNT_HELP_SSNO           204
#define _NEW_ACCOUNT_HELP_BIRTH          205
#define _NEW_ACCOUNT_HELP_ZIPCODE        206
#define _NEW_ACCOUNT_HELP_ADDRESS        207
#define _NEW_ACCOUNT_HELP_PHONE          208
#define _NEW_ACCOUNT_HELP_MOBILEPHONE    209
#define _NEW_ACCOUNT_HELP_EMAIL          210
#define _NEW_ACCOUNT_HELP_Q              211
#define _NEW_ACCOUNT_HELP_A              212
#define _NEW_ACCOUNT_WELL_DONE           213
#define _ERROR_STR_LOGIN_1               300
#define _ERROR_STR_LOGIN_2               301
#define _ERROR_STR_LOGIN_3               302
#define _ERROR_STR_LOGIN_4               303
#define _ERROR_STR_LOGIN_5               304
#define _ERROR_STR_NEW_ACCOUNT_1         400
#define _ERROR_STR_NEW_ACCOUNT_2         401
#define _ERROR_STR_NEW_ACCOUNT_3         402
#define _ERROR_STR_NEW_ACCOUNT_4         403
#define _ERROR_STR_NEW_ACCOUNT_5         404
#define _ERROR_STR_NEW_ACCOUNT_6         405
#define _ERROR_STR_NEW_ACCOUNT_7         406
#define _ALRAM_CHARGE                    500
#define _ALRAM_CHARGE_IP                 501
#define _ALRAM_CHARGE_1                  502
#define _ALRAM_CHARGE_2                  503
#define _ALRAM_CHARGE_3                  504
#define _CHANGE_PASSWORD                 600
#define _CHANGE_PASSWORD_1               601
#define _CHANGE_PASSWORD_2               602
#define _CHANGE_PASSWORD_3               603
#define _CHANGE_PASSWORD_4               604
#define _ERROR_STR_SELECT_SERVER_1       700
#define _ERROR_STR_SELECT_SERVER_2       701
#define _ERROR_STR_NEWCHR_1              800
#define _ERROR_STR_NEWCHR_2              801
#define _ERROR_STR_NEWCHR_3              802
#define _DELETE_CHARACTER_1              900
#define _DELETE_CHARACTER_2              901
#define _VERSION_NOT_MATCHED             1000
#define _ERROR_STR_START_GAME_1          1100
#define _ERROR_STR_DELCHR                1101
#define _ERROR_STR_PATCH_1               1102
#define _ERROR_STR_PATCH_2               1103
#define _ERROR_STR_SERVER_CONNECTION     1104
#define _NOTICE_NOT_EXIST_INDEX          1200
#define _NOTICE_LAST_PAGE                1201
#define _FATAL_ERROR_STR                 9000
#define _SERVER_SELECT_TEST              10000




/*******************************************************************************************************
		Login Procedure
*******************************************************************************************************/
#define _MAX_LOGIN_BTN				4

#define _LOGIN_BTN_CONN				0
#define _LOGIN_BTN_REG				1
#define _LOGIN_BTN_CHGPW			2
#define _LOGIN_BTN_QUIT				3

#define LOGIN_WNDID_INPUT			0
#define LOGIN_WNDID_GAMEOUT			1

#define _SVRLIST_SX					40
#define _SVRLIST_SY					80
#define _SVRLIST_GAP_X				20
#define _SVRLIST_GAP_Y				20
#define _SVRBTN_NORMAL				0
#define _SVRBTN_CLICK				1

#define _LOGINPROC_LOGO				0
#define _LOGINPROC_LOGIN			1
#define _LOGINPROC_SVRSEL			2
#define _LOGINPROC_FADE				3

#define _LOGINBACK_LOGO				0
#define _LOGINBACK_LOGIN			1
#define _LOGINBACK_STILL			2

#define _LOGININPUT_ID				0
#define _LOGININPUT_PW				1
#define _LOGININPUT_SETTED			2

#define _LOGINIMG_BACK				0
#define _LOGINIMG_IDPW				2

#define	_LOGIN_SERVER_PORT_DATA		7000
#define _LOGINMSG					".\\Mirmg.dll"
#define _MIR3EI_INI_FILE_NAME		"Mir3.ini"
#define _MIR3EI_TSINI_FILE_NAME		"Mir3Test.ini"
#define _MIR3EI_INI_SECTION			"Initial"
#define _MIR3EI_SRV_SECTION			"Server"
#define _LOGIN_SERVER_NAME			"ServerAddr"
#define _LOGIN_SERVER_PORT			"Param1"
#define _SERVER_COUNT				"ServerCount"
#define _LOGIN_GATE_SERVER_IP		"192.168.0.200"
#define _URL_ACCOUNT				"Param2"
#define _URL_CHANGEPWD				"Param3"
#define _FULLMODE					"Fullmode"
#define _FULLMODE_DATA				"1"

#define	_KIND_IP_FIXED_TIME			1
#define	_KIND_IP_FIXED_MONEY		2
#define	_KIND_PRIVATE_FIXED_TIME	3
#define	_KIND_PRIVATE_FIXED_MONEY	4

/*******************************************************************************************************
		Character Select Procedure
*******************************************************************************************************/
#define _MAX_CHAR						16
#define _MAX_SHOW_CHAR					2
#define _MAX_SPR_KIND					40
#define _CHR_EXPLAIN_WIDTH				430

#define _SELECTED_FST_CHR				0
#define _SELECTED_SND_CHR				1
#define _SELECTED_TRD_CHR				2
#define _SELECTED_4TH_CHR				3
#define _SELECTED_NONE					-1

#define _MAX_CHR_SELECT_BTN				6
#define _MAX_CHR_SELECT_CREATE			0
#define _MAX_CHR_SELECT_DELETE			1
#define _MAX_CHR_SELECT_START			2
#define _MAX_CHR_SELECT_QUIT			3
#define _MAX_CHR_SELECT_NEXT			4
#define _MAX_CHR_SELECT_BEFORE			5

#define _CHR_CHR_CREATE_BTN				5
#define _CHR_CHR_CREATE_WARIOR			0
#define _CHR_CHR_CREATE_MAGICIAN		1
#define _CHR_CHR_CREATE_CLERIC			2
#define _CHR_CHR_CREATE_MAKE			3
#define _CHR_CHR_CREATE_CANCEL			4
#define _CHR_CHR_CREATE_ARCHER			5

#define _CHR_PROC_SELECT				0
#define _CHR_PROC_CREATEIN				1
#define _CHR_PROC_CREATE				2
#define _CHR_PROC_CREATEOUT				3
#define _CHR_PROC_START					4

#define _CHR_PROC_IMG_SELECT			50
#define _CHR_PROC_IMG_CREATE			80
#define _CHR_PROC_IMG_CREATE_STONE		81
#define _CHR_PROC_IMG_CREATE_STONE_S 	82

#define _CHR_MAX_MT						5

#define _CHR_MT_NS						0	
#define _CHR_MT_SM 						1
#define _CHR_MT_SS 						2
#define _CHR_MT_R  						3
#define _CHR_MT_CC 						4





/*********************************************************************
**********************************************************************/
#define _URL_NEW_ACCOUNT		"https://secure.ient.com/mir/signup.php"
#define _URL_CHANGE_PASSWORD	"https://secure.ient.com/mir/signup.php"
//#define _URL_CHANGE_PASSWORD	"http://www.mir2ei.com/service/Modify_pwd"
//http://account.wemade.com/chg_allinfo/main.asp->개인정보변경 바로가기.



#define _SOUND_GLASS_BUTTON		105
#define _SOUND_MONEY			106
#define _SOUND_EAT_DRUG			107
#define _SOUND_CLICK_DRUG		108
#define _SOUND_SPACEMOVE_OUT	109
#define _SOUND_SPACEMOVE_IN		110

#define _SOUND_CLICK_WEAPON		111
#define _SOUND_CLICK_ARMOR		112
#define _SOUND_CLICK_RING		113
#define _SOUND_CLICK_ARMRING	114
#define _SOUND_CLICK_NECK		115
#define _SOUND_CLICK_HELMET		116
#define _SOUND_CLICK_GROBES		117
#define _SOUND_CLICK_ITEM		118

/*********************************************************************
		Info Shop(Kornet)관련.
**********************************************************************/
#define _KORNET_IP				"211.48.62.250"
#define _KORNET_PORT			9000
//#define NO_GAMEGUARD
///////////////    새로운 인터페이스     ////////////////
//#define _NEWINTERFACE
#define _3rdINTERFACE

///////////////        테스트서버용      ////////////////
//#define _TEST_SERVER

#endif // _DEFINE_H























