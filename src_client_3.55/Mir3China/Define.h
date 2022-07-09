#ifndef _DEFINE_H
#define _DEFINE_H




/******************************************************************************************************************
	#1. File Names
*******************************************************************************************************************/
#define MIR2_PATCH_FILE_NAME		".\\Mir3Patch.exe"
#define MIR2_TS_PATCH_FILE_NAME		".\\Mir3TestPatch.exe"
#define MIR2_PATCH_DAT_NAME			".\\~Mir3Patch.dat"



/******************************************************************************************************************
	#1. Procedeure Define
*******************************************************************************************************************/
#define _LOGIN_PROC					0
#define _SVR_SEL_PROC				1
#define _CHAR_SEL_PROC				2
#define _GAME_PROC					3
#define _SELLOGIN_PROC				4




/******************************************************************************************************************
	#1. Mouse Wheel Define
*******************************************************************************************************************/
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL				WM_MOUSELAST+1 
#endif





/******************************************************************************************************************
	#1. User Define Message
*******************************************************************************************************************/
#define _WM_USER_MSG_INPUTTED		WM_USER + 1005				// ø°µ∆Æπ⁄Ω∫ ¿‘∑¬∏ﬁΩ√¡ˆ. ∏ﬁΩ√¡ˆ∞° ƒø∏«µÂ¿œ∞ÊøÏ wParam∞™¿∫ TRUE∑Œ ºº∆√µ»¥Ÿ.
#define _WM_MSGBOX_RETURN			WM_USER + 1006				// 
#define _WM_USER_MSG_CTRLNUM		WM_USER + 1007				// 
#define _WM_USER_MSG_ALTNUM			WM_USER + 1008				// 
#define ID_SOCKCLIENT_EVENT_MSG		WM_USER + 1000				// º“ƒœ¿Ã∫•∆Æ∏ﬁΩ√¡ˆ.

/******************************************************************************************************************
	#1. Nprotect Message
*******************************************************************************************************************/
#define WM_NPROTECT_EXIT_TWO		WM_USER + 10001


/******************************************************************************************************************
	#1. Image Define Message
*******************************************************************************************************************/
// ±‚∫ª∏ µ•¿Ã≈∏.
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
// «™∏•¡ˆø™∏ µ•¿Ã≈∏.
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
// ªÁ∏∑¡ˆø™∏ µ•¿Ã≈∏.
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
// ¡§±€¡ˆø™∏ µ•¿Ã≈∏.
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
// º≥ø¯¡ˆø™∏ µ•¿Ã≈∏.
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

#define _IMAGE_M_ARMOREFT			160 // Ω≈±‘¿«∫π ¿Ã∆Â∆Æ 2006.07.03
#define _IMAGE_WM_ARMOREFT			161
#define _IMAGE_MARKETEX				162	// ø¯∫∏ªÛ¡° æ∆¿Ã≈€ ¿ÃπÃ¡ˆ

#define _MAX_MONSTER_IMAGE			20

#define _MAX_IMAGE					163

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

#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // ≈ı∞˙ªˆ.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // ∞À¡§ªˆ.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // »Úªˆ.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // ª°∞≠.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // ≥Ïªˆ.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // «™∏•ªˆ
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // ≥Î∂˚ªˆ.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // ¡÷»≤ªˆ

#define _USER_NAMECLR1				255	//RGB(255, 255, 255); »Úªˆ
#define _USER_NAMECLR2				251	//RGB(255, 255,   0); ≥Î∂ıªˆ
#define _USER_NAMECLR3				249	//RGB(255,   0,   0); ª°∞£ªˆ
#define _USER_NAMECLR4				125	//RGB(255,   0,   0); ??ªˆ(∞·∞Ëæ» ∏ÛΩ∫≈Õªˆ)
#define _USER_NAMECLR5				47	//RGB(165,  99,  57); ∞•ªˆ
#define _USER_NAMECLR6				180	//RGB(  0,   0, 255); «™∏•ªˆ
#define _USER_NAMECLR7				69	//RGB(239, 107,   0); ¡÷»≤ªˆ
#define _USER_NAMECLR8				221	//RGB(  0, 148,   0); ≥Ïªˆ
#define _USER_NAMECLR9				254	//RGB(  0, 255, 255); ªˆ
#define _USER_NAMECLR10				147	//RGB(140, 214, 239); ªˆ
#define _USER_NAMECLR11				154	//RGB( 57, 181, 239); ªˆ
#define _USER_NAMECLR12				229	//RGB(119, 136, 255); ªˆ
#define _USER_NAMECLR13				168	//RGB(  0, 123, 222); ªˆ
#define _USER_NAMECLR14				252	//RGB(  0,   0, 255); ªˆ




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

//#define _MAX_HERO_KIND				9
#define _MAX_HERO_KIND				11
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
#define _STATE_DARKBLUE				490
#define _STATE_GRAY					0
#define _STATE_ABLEND				1
#define _STATE_SHIELDUSE			2
#define _STATE_NOTUSED				0XFFFF

#define _RUN_MINHEALTH				10

#define _DIG_NORMAL					0
#define _DIG_UP						1
#define _DIG_DOWN					2
#define _DIG_DOWNDEL				3


/******************************************************************************************************************
	#1. Sprite Define
*******************************************************************************************************************/
// Hero¿« µø¿€ ¡§¿«.(∞‘¿”≥ª¿« ∏µÁ µø¿€¿ª ¡§¿««—¥Ÿ.)

#define _MAX_HERO_MTN				33			// √÷¥Î µø¿€∞πºˆ.
#define _MAX_HERO_FRAME				3000		// ¥Ÿ¿Ω Hero∑Œ ≥—æÓ∞°¥¬ √÷¥Î «¡∑π¿” ∞πºˆ.
#define	_MAX_HERO_REALFRAME			2640

#define _MT_STAND					0			// ¿Ø»ﬁµø¿€.
#define _MT_ARROWATTACK				1			// »∞∞¯∞›.
#define _MT_SPELL1					2			// ∏∂π˝ Ω√¿¸1.
#define _MT_SPELL2					3			// ∏∂π˝ ∞¯∞› Ω√¿¸2.
#define _MT_HOLD					4			// ∞ﬂµ±‚.
#define _MT_PUSHBACK				5			// µ⁄∑Œ π–∑¡≥™±‚.
#define _MT_PUSHBACKFLY				6			// µ⁄∑Œ ≥Ø∂Ûº≠ π–∑¡≥™±‚.
#define _MT_ATTACKMODE				7			// ¿¸≈ı∏µÂ.
#define _MT_CUT						8			// ∞Ì±‚ Ω‰±‚.
#define _MT_ONEVSWING				9			// «—º’ ¡æ∫£±‚.(µø¿€ 9π¯∫Œ≈Õ 14π¯±Ó¡ˆø°º≠ π´±‚¿« ¡æ∑˘ø° µ˚∂Û µø¿€¿Ã ¡§«ÿ¡¯¥Ÿ.)
#define _MT_TWOVSWING				10			// µŒº’ ¡æ∫£±‚.
#define _MT_ONEHSWING				11			// «—º’ »æ∫£±‚.
#define _MT_TWOHSWING				12			// µŒº’ »æ∫£±‚.	
#define _MT_SPEARVSWING				13			// √¢ ¡æ∫£±‚.
#define _MT_SPEARHSWING				14			// √¢ »æ∫£±‚.
#define _MT_HITTED					15			// ∏¬±‚.
#define _MT_WHEELWIND				16			// µπ∏Èº≠ ∫£±‚.
#define _MT_RANDSWING				17			// ∏∂±∏ ∫£±‚.
#define _MT_BACKDROPKICK			18			// µ⁄µπæ∆ ¬˜±‚.
#define _MT_DIE						19			// ¡◊±‚.
#define _MT_SPECIALDIE				20			// ∆¢æÓø√∂Û ¡◊±‚.
#define _MT_WALK					21			// ∞»±‚.
#define _MT_RUN						22			// ¥ﬁ∏Æ±‚.
#define _MT_MOODEPO					23			// π´≈¬∫∏ ∂Ÿ±‚.
#define _MT_ROLL					24			// ±∏∏£±‚.
#define _MT_FISHSTAND				25			// ≥¨Ω√∏µÂ ¿Ø»ﬁ.
#define _MT_FISHHAND				26			// ≥¨Ω√∏µÂ.
#define _MT_FISHTHROW				27			// ≥¨Ω√¡Ÿ ¥¯¡ˆ±‚.
#define _MT_FISHPULL				28			// ≥¨Ω√¡Ÿ ¥Á±‚±‚.
#define _MT_HORSESTAND				29			// Ω¬∏∂∏µÂ ¿Ø»ﬁ.
#define _MT_HORSEWALK				30			// Ω¬∏∂∏µÂ ∞»±‚.
#define _MT_HORSERUN				31			// Ω¬∏∂∏µÂ ¥ﬁ∏Æ±‚.
#define _MT_HORSEHIT				32			// Ω¬∏∂∏µÂ ∏¬±‚.

// Monster¿« µø¿€ ¡§¿«.(∞‘¿”≥ª¿« ∏µÁ µø¿€¿ª ¡§¿««—¥Ÿ.)
#define _MAX_MON_MTN				11			// √÷¥Î µø¿€∞πºˆ.
#define _MAX_MON_FRAME				1000		// ¥Ÿ¿Ω Mon∑Œ ≥—æÓ∞°¥¬ √÷¥Î «¡∑π¿” ∞πºˆ.

#define _MT_MON_STAND				0			// ¿Ø»ﬁµø¿€.
#define _MT_MON_WALK				1			// ∞»±‚µø¿€.
#define _MT_MON_ATTACK_A			2			// ¿œπ›∞¯∞›µø¿€1.
#define _MT_MON_HITTED				3			// ∏¬±‚µø¿€.
#define _MT_MON_DIE					4			// ¡◊±‚µø¿€.
#define _MT_MON_ATTACK_B			5			// ¿œπ›∞¯∞›µø¿€2.
#define _MT_MON_SPELL_A				6			// ∏∂π˝∞¯∞›µø¿€1.
#define _MT_MON_SPELL_B				7			// ∏∂π˝∞¯∞›µø¿€2.
#define _MT_MON_APPEAR				8			// ≥™≈∏≥™±‚µø¿€.
#define _MT_MON_SPECIAL_MTN			9			// ∆Øºˆµø¿€1.
#define _MT_MON_SKELETON			10			// «ÿ∞Ò.


// NPC¿« µø¿€ ¡§¿«.(∞‘¿”≥ª¿« ∏µÁ µø¿€¿ª ¡§¿««—¥Ÿ.)
// NPC ∞¸∑√¡§¿«.
#define _MAX_NPC_MTN				3			// √÷¥Î µø¿€∞πºˆ.
#define _MAX_NPC_FRAME				100			// ¥Ÿ¿Ω NPC∑Œ ≥—æÓ∞°¥¬ √÷¥Î «¡∑π¿” ∞πºˆ.

#define _MT_NPC_STAND				0			// ¿Ø»ﬁµø¿€.
#define _MT_NPC_ACT01				1			// ∆Øºˆµø¿€1.
#define _MT_NPC_ACT02				2			// ∆Øºˆµø¿€2.



// ∏∂π˝»ø∞˙∞¸∑√¡§¿«.
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
// ∏∂π˝≈◊Ω∫∆ÆøÎ.
#define _TIMER_MTESTID				2
#define _TIMER_SYSTIME				3


#define _ET_DIGOUTZOMBI				1  //¡ª∫Ò∞° ∂•∆ƒ∞Ì ≥™ø¬ »Á¿˚
#define _ET_MINE					2  //±§ºÆ¿Ã ∏≈¿Âµ«æÓ ¿÷¿Ω
#define _ET_PILESTONES				3  //µππ´¥ı±‚
#define _ET_HOLYCURTAIN				4  //∞·∞Ë
#define _ET_FIRE					5
#define _ET_SCULPEICE				6  //¡÷∏∂ø’¿« µπ±˙¡¯ ¡∂∞¢
#define _ET_ICEWALL					9  //∫˘∫Æ
#define _ET_WINDWALL				10 //»∏«≥∞≠∏∑
#define _ET_FIRE_HIGH				11 //¡ˆº”∞Ë

#define _MAX_CELL_OBJ				100

// Day Bright.
#define _DAYSTATE_DUSK				0  // ªı∫Æ.
#define _DAYSTATE_DAY				1  // ≥∑.
#define _DAYSTATE_DAWN				2  // ¿˙≥·.
#define _DAYSTATE_NIGHT				3  // π„.

// Fog Bright.
#define _FOGSTATE_DAY				0  // ≥∑.
#define _FOGSTATE_EVENING			1  // ¿˙≥·.
#define _FOGSTATE_NIGHT				2  // π„.
#define _FOGSTATE_DAWN				3  // ªı∫Æ


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

#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // ≈ı∞˙ªˆ.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // ∞À¡§ªˆ.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // »Úªˆ.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // ª°∞≠.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // ≥Ïªˆ.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // «™∏•ªˆ
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // ≥Î∂˚ªˆ.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // ¡÷»≤ªˆ

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

// ∏ﬁ¿Œ¿Œ≈Õ∆‰¿ÃΩ∫ø°º≠ æ≤¿œ ¿©µµøÏ æ∆¿Ãµ.
#define _WND_ID_INVENTORY			0			//∞°πÊ¿©µµøÏ.
#define _WND_ID_STATUS				1			//ƒ≥∏Ø≈Õ ¡§∫∏ ∫∏±‚¿©µµøÏ(3∞≥).
#define _WND_ID_STORE				2			//ªÛ¡°¿©µµøÏ.
#define _WND_ID_EXCHANGE			3			//±≥»Ø¿©µµøÏ.
#define _WND_ID_GUILD				4			//πÆø¯¿©µµøÏ.
#define _WND_ID_GROUP				6			//±◊∑Ï¿©µµøÏ.
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
#define _WND_ID_SETUTILHP				126
#define _WND_ID_SETUTILSCROLL			127
#define _WND_ID_SETUTILMP				128

// ø¯∫∏ªÛ¡°
#define _WND_ID_MARKETEX				129
#define _WND_ID_WANTTOBUY_MARKETEX		130
#define _WND_ID_WANTTOCANCEL_MARKETEX	131
#define	_WND_ID_WANTTOPRESENT_MARKETEX	132

// √ﬂ∞° ∞°πÊ
#define _WND_ID_INVENTORYEX				133

// ∏ﬁ¿Œ ¿Œ≈Õ∆‰¿ÃΩ∫ø°º≠ æ≤¿œ ¿©µµøÏ¿« ¿ÃπÃ¡ˆ ¿Œµ¶Ω∫.
#define _WNDIMGIDX_GAMEOVER			800			//π´∞¯º≥¡§√¢
#define _WNDIMGIDX_MAIN				50			//∏ﬁ¿Œ¿Œ≈Õ∆‰¿ÃΩ∫√§∆√√¢
#define _WNDIMGIDX_ITEMSET		    200			//ªÛ≈¬√¢
#define _WNDIMGIDX_USERSTATE		200			//±◊∑Ï¿‘∑¬√¢.
#define _WNDIMGIDX_CHATPOP			350			//√§∆√∆Àæ˜√¢.
#define _WNDIMGINDX_MSGBOX1			950
#define _WNDIMGINDX_MSGBOX2			950
#define _WNDIMGIDX_QUEST			700			//ƒ˘Ω∫∆Æ√¢.
#define _WNDIMGIDX_HORSE			850			//∏ª√¢.
#define _WNDIMGIDX_STOREDETAIL		1003		//ªÛ¡°ºº∫Œ∏ÆΩ∫∆Æ.
#define _WNDIMGIDX_GAMEOVER			800			//π´∞¯º≥¡§√¢
#define _IMGIDX_BELT				51
#define _WNDIMGIDX_NPCCHAT_TOP		1100		//NPC¥Î»≠√¢
#define _WNDIMGIDX_CHAT				150			//√§∆√


// ªı∑ŒøÓ ¿Œ≈Õ∆‰¿ÃΩ∫ ¿Œµ¶Ω∫
#define _NEW_WNDIMGIDX_MAGIC				1490		//π´∞¯º≥¡§√¢
#define _NEW_WNDIMGIDX_QUEST				1420		//ƒ˘Ω∫∆Æ√¢.
#define _NEW_WNDIMGIDX_HORSE				1400		//∏ª√¢.
#define _NEW_WNDIMGIDX_EXCHANGE				1390		//±≥»Ø√¢
#define _NEW_WNDIMGIDX_GROUP				1360		//±◊∑Ï√¢.
#define _NEW_WNDIMGIDX_NOTICEEDIT			1326		//∞¯¡ˆºˆ¡§√¢
#define _NEW_WNDIMGIDX_RANKEDIT				1326		//¡˜¿ßºˆ¡§√¢
#define _NEW_WNDIMGIDX_GUILD				1300		//πÆø¯∞‘Ω√∆«.
#define _NEW_WNDIMGIDX_OPTION				1290		//ø…º«√¢.
#define _NEW_WNDIMGIDX_ITEMSET				1280		//ªÛ≈¬√¢
#define _NEW_WNDIMGIDX_STATUS				1281		//ªÛ≈¬√¢ »Æ¿Â
#define _NEW_WNDIMGIDX_STORE				1260		//ªÛ¡°.
#define _NEW_WNDIMGIDX_ITEMDETAIL			1261		//æ∆¿Ã≈€ºº∫Œ∏ÆΩ∫∆Æ.
#define _NEW_WNDIMGIDX_STOREADD				1262		//ªÛ¡°.(«œ≥™¬•∏Æ π∞∞«ªÏ∂ß).
#define _NEW_IDX_IMG_NOTICEBOX				1250		//∞¯¡ˆ√¢ ¿Œµ¶Ω∫
#define _NEW_WNDIMGIDX_INVENTORY			1220		//¿Œ∫•≈‰∏Æ
#define _NEW_WNDIMGIDX_BELT					1210		//∫ß∆Æ√¢
#define _NEW_WNDIMGIDX_NPCCHAT_TOP			1350		//NPC¥Î»≠√¢
#define _NEW_WNDIMGIDX_NPCCHAT_MIDDLE		1351		//NPC¥Î»≠√¢
#define _NEW_WNDIMGIDX_NPCCHAT_BOTTOM		1352		//NPC¥Î»≠√¢
#define _NEW_WNDIMGIDX_NPCCHAT_TOP_NOFACE	1353		//NPC¥Î»≠√¢
#define _NEW_WNDIMGIDX_NPCCHAT_BOTTOM_ARROW	1354		//NPC¥Î»≠√¢
#define _NEW_WNDIMGIDX_STAUS_OTHERS			1288		//≈∏¿Œ ªÛ≈¬√¢

// ººπ¯¬∞ ¿Œ≈Õ∆‰¿ÃΩ∫ ¿Œµ¶Ω∫
#define _WNDIMGIDX_GROUP					170			//±◊∑Ï√¢.
#define _WNDIMGIDX_STATUS					180			//ªÛ≈¬√¢
#define _WNDIMGIDX_STAUS_OTHERS				200			//≈∏¿Œ ªÛ≈¬√¢
#define _WNDIMGIDX_MESSENGER				210			//∏ﬁΩ≈¿˙
#define _WNDIMGIDX_GUILD					280			//πÆø¯∞‘Ω√∆«.
#define _WNDIMGIDX_OPTION					290			//ø…º«√¢.
#define _WNDIMGIDX_SETTING					310			//»Ø∞Êº≥¡§√¢
#define _WNDIMGIDX_BELT						320			//∫ß∆Æ√¢
#define _WNDIMGIDX_INVENTORY				350			//¿Œ∫•≈‰∏Æ
#define _WNDIMGIDX_EXCHANGE					370			//±≥»Ø√¢
#define _WNDIMGIDX_NPCCHAT_TOP_NOFACE		380			//NPC¥Î»≠√¢
#define _WNDIMGIDX_NPCCHAT_MIDDLE			381			//NPC¥Î»≠√¢
#define _WNDIMGIDX_NPCCHAT_BOTTOM			382			//NPC¥Î»≠√¢
#define _WNDIMGIDX_NPCCHAT_BOTTOM_ARROW		383			//NPC¥Î»≠√¢
#define _WNDIMGIDX_STORE					390			//ªÛ¡°.
#define _WNDIMGIDX_ITEMDETAIL				391			//æ∆¿Ã≈€ºº∫Œ∏ÆΩ∫∆Æ.
#define _WNDIMGIDX_STOREADD					392			//ªÛ¡°.(«œ≥™¬•∏Æ π∞∞«ªÏ∂ß).
#define _WNDIMGIDX_EXIT						410			//ªÛ¡°.(«œ≥™¬•∏Æ π∞∞«ªÏ∂ß).
#define _IDX_IMG_NOTICEBOX					660			//∞¯¡ˆ√¢ ¿Œµ¶Ω∫
#define _WNDIMGIDX_VIEWMINIMAP				670			//πÃ¥œ∏  ∫‰æÓ
#define _WNDIMGIDX_FACEIMGUP				680			//ªÁ¡¯µÓ∑œ
#define _WNDIMGIDX_SIEGE					690			//πﬂºÆ∞≈¿©µµøÏ
#define _WNDIMGIDX_NOTICEEDIT				284			//∞¯¡ˆºˆ¡§√¢
#define _WNDIMGIDX_RANKEDIT					284			//¡˜¿ßºˆ¡§√¢
#define _WNDIMGIDX_MAGIC					710			//π´∞¯º≥¡§√¢
#define _WNDIMGIDX_USERMARKET				760			//¿Ø¿˙ æ∆¿Ã≈€ ∞≈∑° √¢
#define _WNDIMGIDX_USERMARKETUP				780			//¿Ø¿˙ æ∆¿Ã≈€ µÓ∑œ √¢
#define _WNDIMGIDX_UTIL						800 		//¿Ø∆ø
#define _WNDIMGIDX_MAGICSHORTCUT			20			//πÃ¥œ∏  ∫‰æÓ


// ∏ﬁ¿Œ¿Œ≈Õ∆‰¿ÃΩ∫ø°º≠ æ≤¿œ πˆ∆∞ æ∆¿Ãµ.
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

// √ﬂ∞° ∞°πÊ
#define _MAX_INVENEX_ITEM			50

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
#define _MAGIC_ACTIVE				0			// ∏∂π˝»∞º∫ªÛ≈¬.
#define _LIGHT_ACTIVE				1			// ∏∂π˝±§ø¯»∞º∫ªÛ≈¬.
#define _MAGIC_FINISH				2			// ∏∂π˝º“∏Í.

#define _SKILL_FIREBALL				1			// »≠ø∞¿Â.(»≠)
#define _SKILL_HEALLING				2			// »∏∫πº˙.
#define _SKILL_ONESWORD				3			// ø‹ºˆ.(π´)
#define _SKILL_ILKWANG				4			// ¿œ±§.
#define _SKILL_FIREBALL2			5			// ±›∞≠»≠ø∞¿Â.
#define _SKILL_AMYOUNSUL			6			// æœø¨º˙.
#define _SKILL_YEDO					7			// øπµµ.
#define _SKILL_FIREWIND				8			// »≠ø∞«≥.
#define _SKILL_FIRE					9			// ø∞ªÁ¿Â.
#define _SKILL_SHOOTLIGHTEN			10			// ∑⁄¿Œ¿Â.
#define _SKILL_LIGHTENING			11			// ∞≠∞›.
#define _SKILL_ERGUM				12			// æÓ∞Àº˙.
#define _SKILL_FIRECHARM			13			// ∆¯ªÏ∞Ë.
#define _SKILL_HANGMAJINBUB			14			// «◊∏∂¡¯π˝.
#define _SKILL_DEJIWONHO			15			// ¥Î¡ˆø¯»£.
#define _SKILL_HOLYSHIELD			16			// ∞·∞Ë.
#define _SKILL_SKELLETON			17			// πÈ∞Òº“»Øº˙.
#define _SKILL_CLOAK				18			// ¿∫Ω≈.
#define _SKILL_BIGCLOAK				19			// ¥Î¿∫Ω≈.
#define _SKILL_TAMMING				20			// ∑⁄»•∞›.
#define _SKILL_SPACEMOVE			21			// æ∆∞¯«‡π˝.
#define _SKILL_EARTHFIRE			22			// ¡ˆø∞º˙.
#define _SKILL_FIREBOOM				23			// ∆¯ø≠∆ƒ.
#define _SKILL_LIGHTFLOWER			24			// ∑⁄º≥»≠.
#define _SKILL_BANWOL				25			// π›ø˘.
#define _SKILL_FIRESWORD			26			// ø∞»≠∞·.
#define _SKILL_MOOTEBO				27			// π´≈¬∫∏.
#define _SKILL_SHOWHP				28			// ≈Ω±‚∆ƒø¨.
#define _SKILL_BIGHEALLING			29			// ¥Î»∏∫π.
#define _SKILL_SINSU				30			// Ω≈ºˆº“»Ø.
#define _SKILL_SHIELD				31			// ¡÷º˙¿«∏∑.
#define _SKILL_KILLUNDEAD			32			// ªÁ¿⁄¿±»∏.
#define _SKILL_SNOWWIND				33			// ∫˘º≥«≥.

#define _SKILL_RANDSWING			34			// ø¨ø˘¬¸.
#define _SKILL_JUMPSHOT				35			// ∏Õ∑ÊΩ¬√µºº.
#define _SKILL_KICK					36			// π´ªÛ∞¢.

#define _SKILL_MOONOK				37			// ø˘øµø¡.
#define _SKILL_MOONCHAM				38			// ø˘øµ∆ƒ.
#define _SKILL_ICEBOLT				39			// ∫˘ø˘¿Â.
#define _SKILL_SUPERICEBOLT			40			// ∫˘ø˘¡¯√µ¿Â.
#define _SKILL_MAGICARROW			41			// ∫Ò∞›¿Â.
#define _SKILL_FIREBOOMUP			47			// ∆¯ø≠∆ƒæ˜.(¡ˆ∑⁄«¸∆¯ø≠∆ƒ???????).
#define _SKILL_EARTH_SUMMON			48			// ¥Î¡ˆº“»Øº˙.(øÓºÆº“»Ø???????).
#define _SKILL_ICE					53			// ∫˘ªÁ¿Â.
#define _SKILL_LIGHTWALL			63			// ∑⁄∫Æ.(∫Ò∞›∫Æ???????).
#define _SKILL_LIGHTFLOWERUP		64			// ∑⁄º≥»≠æ˜.(ø¯∞≈∏Æ∑⁄º≥»≠???????).
#define _SKILL_MAGICTRAP			66			// ∫Ò∞›∆Æ∑¶.
#define _SKILL_HANDWIND				67			// ¿Â«≥.
#define _SKILL_HURRICANE			72			// øÎº±«≥.
#define _SKILL_HURRICANESHOT		73			// «≥¡¯¬¸
#define _SKILL_HURRICANEBOMB		74			// ∞›«≥
#define _SKILL_REVIVE				77			// º“ª˝º˙.
#define _SKILL_TRANSFORM			78			// µ–∞©º˙.
#define _SKILL_ANTIMAGIC_FIRE		85			// «◊∏∂¡¯π˝(»≠).
#define _SKILL_ANTIMAGIC_ICE		86			// «◊∏∂¡¯π˝(∫˘).
#define _SKILL_ANTIMAGIC_LIGHTENING	87			// «◊∏∂¡¯π˝(∑⁄).
#define _SKILL_ANTIMAGIC_WIND		88			// «◊∏∂¡¯π˝(«≥).
#define _SKILL_MAGICUP				89			// ∞≠∏∂¡¯π˝.
#define _SKILL_MAGICUP_FIRE			90			// ∞≠∏∂¡¯π˝(»≠).
#define _SKILL_MAGICUP_ICE			91			// ∞≠∏∂¡¯π˝(∫˘).
#define _SKILL_MAGICUP_LIGHTENING	92			// ∞≠∏∂¡¯π˝(∑⁄).
#define _SKILL_MAGICUP_WIND			93			// ∞≠∏∂¡¯π˝(«≥).
#define _SKILL_POWERUP				94			// ∏Õ»£∞≠ºº.
#define _SKILL_WITH_FIRE			95			// ∏Õ»£∞≠ºº(»≠).
#define _SKILL_WITH_ICE				96			// ∏Õ»£∞≠ºº(∫˘).
#define _SKILL_WITH_LIGHT			97			// ∏Õ»£∞≠ºº(∑⁄).
#define _SKILL_WITH_WIND			98			// ∏Õ»£∞≠ºº(«≥).
#define _SKILL_WITH_DEF				99			// ∏Õ»£∞≠ºº(πÊæÓ).
#define _SKILL_WITH_MAGIC			100			// ∏Õ»£∞≠ºº(∏∂π˝).
#define _SKILL_WITH_ATT				101			// ∏Õ»£∞≠ºº(∞¯∞›).
#define _SKILL_MAXDEFENCE			102			// √∂∆˜ªÔ
#define _SKILL_MANWOL				103			// »∏º±¬¸
#define _SKILL_SMALLSPACEMOVE		104			// ¿Ã«¸»Ø¿ß.
#define _SKILL_POWERSKELLETON		105			// ¡¯∞Òº“»Øº˙.
#define _SKILL_MAXOFENCE			106			// ±§∏∂∞·
#define _SKILL_CHANGEPOSITION		107			// ¿¸¿ß∫∏
#define _SKILL_PULL					108			// ∞›∞¯º∑π∞
#define _SKILL_THUNDERSTORM			111			// ∑⁄»≠≥≠π´
#define _SKILL_MAXDEFEECEMAGIC		112			// ø™«˜∏∂∞¯
#define _SKILL_FIREBALL10			113			// ∏∏√µ»≠øÏ
#define _SKILL_REMOVEPOISON			120			// ¡§»≠º˙
#define _SKILL_FULLCLOAK			121			// ±‚»Øº˙
#define _SKILL_DOSASHIELD			122			// º±√µ±‚∞¯
#define _SKILL_MONSTERUP			123			// ¿¸¿Ãº˙
#define _SKILL_CROSS_ICE			110			// ∫˘∑ƒ∆ƒ

#define _SKILL_PAWHANGBO			109			// ∆ƒ»≤∫∏
#define _SKILL_KANGMAK				114			// »∏«≥∞≠∏∑
#define _SKILL_MYULSAL				124			// ∏ÍªÏ∞Ë
#define _SKILL_TAWOO				125			// ∞›ªÍ≈∏øÏ
#define _SKILL_BANTAN				126			// π›≈∫∞≠±‚
#define _SKILL_COPY					127			// «„ªÛ∫–Ω≈
#define _SKILL_FREEMOVE				128			// ±›∞≠∫Œµø
#define _SKILL_HEALX				129			// æÁª˝º˙
#define _SKILL_BIGMOUNTAIN			130			// ≈¬ªÍæ–¡§
#define _SKILL_HYPERSWORD			131			// ƒËµµ≥≠∏∂
#define _SKILL_POTIONUP				132			// øÓ±‚ø‰ªÛ
#define _SKILL_1000THUNDER			133			// √µ∑⁄
#define _SKILL_CLOUDTHUNDER			134			// øÓ¡ﬂ≥˙∞›
#define _SKILL_BIGAM				135			// ¥Îæœø¨º˙
#define _SKILL_INHALEHP				136			// »Ìº∫¥Îπ˝
#define _SKILL_DOLL					137			// ∫–ø≠»•

#define _SKILL_BALSACHE				138			// πﬂªÁ√º
#define _SKILL_JIKSUNGYE			139			// ¡˜º±∞Ë
#define _SKILL_JUMPSHOT_HIGH		143			// ∞Ì±ﬁ∏Õ∑ÊΩ¬√µºº
#define _SKILL_PAWHANGBO_HIGH		144			// ∞Ì±ﬁ∆ƒ»≤∫∏
#define _SKILL_SHIELD_HIGH			145			// ∞Ì±ﬁ¡÷º˙¿«∏∑
#define _SKILL_MAXDEFEECEMAGIC_HIGH	146			// ∞Ì±ﬁø™«˜∏∂∞¯
#define _SKILL_DEJIWONHO_HIGH		147			// ∞Ì±ﬁ¥Î¡ˆø¯»£
#define _SKILL_CLOAK_HIGH			148			// ∞Ì±ﬁ¿∫Ω≈º˙
#define _SKILL_MOONCHAM_HIGH		149			// ∞Ì±ﬁø˘øµ∆ƒ
#define _SKILL_POKBAL				150			// ∆¯πﬂ«¸
#define _SKILL_JISOKGYE				151			// ¡ˆº”∞Ë
#define _SKILL_RANDSWING_HIGH		152			// ∞Ì±ﬁø¨ø˘¬¸




#define _SKILL_ICEWALL				140			// ∫˘∫Æ
#define _SKILL_BANTAN_HITTED		141			// π›≈∫∞≠±‚ π›ªÁ
#define _SKILL_COPYDIE				142			// «„ªÛ¡◊±‚
#define _SKILL_CONCENFIREBALL		200			// ¡˝¡ﬂ»≠ø∞¿Â.


#define _SKILL_ERGUM_HIGH			10012		// ∞Ì±ﬁæÓ∞Àº˙
#define _SKILL_MAXDEFENCE_HIGH		10102		// ∞Ì±ﬁ√∂∆˜ªÔ
#define _SKILL_MANWOL_HIGH			10103		// ∞Ì±ﬁ»∏º±¬¸
#define _SKILL_YEDO_HIGH			10007		// øπµµ ∞Ì±ﬁ
#define _SKILL_TAMMING_HIGH			10020		// ∑⁄»•∞›∞Ì±ﬁ
#define _SKILL_AMYOUNSUL_HIGH		10006		// æœø¨º˙∞Ì±ﬁ
#define _SKILL_REVIVE_HIGH			10077		// º“ª˝º˙∞Ì±ﬁ
#define _SKILL_REMOVEPOISON_HIGH	10120		// ¡§»≠º˙∞Ì±ﬁ





#define _SKILL_SPACEMOVESHOW		320			// æ∆∞¯«‡π˝≥™≈∏≥™±‚.
#define _SKILL_SPACEMOVESHOW2		321			// æ∆∞¯«‡π˝ªÁ∂Û≥™±‚.
#define _SKILL_SPACEMOVEHIDE2		322			// æ∆∞¯«‡π˝≥™≈∏≥™±‚.
#define _SKILL_PULLSHOW				323			// ∞›∞¯º∑π∞, ¿¸¿ß∫∏ ≥™≈∏≥™±‚.

#define _EVENT_LEFTFIRE1			330			// ¿‹ø∞1.
#define _EVENT_LEFTFIRE2			331			// ¿‹ø∞2.
#define _EVENT_LEFTFIRE3			332			// ¿‹ø∞3.
#define _EVENT_LEFTFIRE4			333			// ¿‹ø∞4.
#define _EVENT_LEFTFIRE5			334			// ¿‹ø∞5.
#define _EVENT_DUST					335			// ±§ƒ∂∂ß ∏’¡ˆ.

#define _SKILL_SHOOTLIGHTEN_ADD		336			// ∑⁄¿Œ¿Â∫Œ∞°»ø∞˙.
#define _SKILL_REFINEADD			337			// ¡¶∑√∫Œ∞°»ø∞˙.

#define _SKILL_STRUCK_FIRE			400			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(»≠).
#define _SKILL_STRUCK_ICE			401			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(∫˘).
#define _SKILL_STRUCK_LIGHT			402			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(∑⁄).
#define _SKILL_STRUCK_WIND			403			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(«≥).
#define _SKILL_STRUCK_HOLY			404			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(Ω≈º∫).
#define _SKILL_STRUCK_DARK			405			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(æœ»Ê).
#define _SKILL_STRUCK_ILLU			406			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(»Øøµ).
#define _SKILL_STRUCK_NONE			407			// π´∞¯∞Ëø≠∫∞ ≈∏∞›(π´).

#define _SKILL_GUMGI_FIRE			408			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(»≠).
#define _SKILL_GUMGI_ICE			409			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(∫˘).
#define _SKILL_GUMGI_LIGHT			410			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(∑⁄).
#define _SKILL_GUMGI_WIND			411			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(«≥).
#define _SKILL_GUMGI_HOLY			412			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(Ω≈º∫).
#define _SKILL_GUMGI_DARK			413			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(æœ»Ê).
#define _SKILL_GUMGI_ILLU			414			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(»Øøµ).
#define _SKILL_GUMGI_NONE			415			// π´∞¯∞Ëø≠∫∞ ∞À±‚1(π´).

#define _SKILL_DOT_1				416			// «•√¢1.
#define _SKILL_DOT_2				417			// «•√¢2.
#define _SKILL_DOT_3				418			// «•√¢3.
#define _SKILL_SNOWDART				419			// ¥´ΩŒøÚ.
#define _SKILL_REFINE_S				420			// ¡¶∑√º∫∞¯.
#define _SKILL_REFINE_F				421			// ¡¶∑√Ω«∆–.
#define _SKILL_LEVELUP				422			// ∑π∫ßæ˜.
#define _SKILL_POWERUPGRADE			423			// ∑π∫ßæ˜.
/******************************************************************************************************************
	MonMagic
*******************************************************************************************************************/
#define _MONMAGIC_KEPAL				500			// ¿¸∞›∞¯∞›.(∞¯∞›«— ƒ≥∏Ø≈Õ¿ßø°)(∏∂π˝)
#define _MONMAGIC_EXPLODE			501			// ∆¯πﬂ∏∂π˝.(µπ∞Ò∑Ω¡◊¿ª∂ß, ∑–∞¯∞›Ω√)
#define _MONMAGIC_BLACK1			502			// »Ê∏∂π˝ªÁ. (∏∂π˝(Ω√¿¸))
#define _MONMAGIC_BLACK2			503			// »Ê∏∂π˝ªÁ. (∏∂π˝(∏∂π˝))
#define _MONMAGIC_DIE				504			// »Ê∏∂π˝ªÁ, ∞Ê∞©ø ±‚ªÁ, »´∏∂π˝ªÁ, Ω≈±‚º±∫∏Ω∫∫ØΩ≈¿¸ ¡◊¿Ω.(»ø∞˙)
#define _MONMAGIC_ANTHEAL			505			// ƒ°¿Ø∞≥πÃ»˙∏µ(πﬂªÁ∏∂π˝, ∆¯πﬂ»ø∞˙.)
#define _MONMAGIC_GREATANT			506			// ∞≈¥Î∞≥πÃ.(∞¯∞›«— ƒ≥∏Ø≈Õ¿ßø°)(∏∂π˝)
#define _MONMAGIC_MAGENUMA			508			// ∞·∞Ë.
#define _MONMAGIC_ANT				509			// ∫¥¡§∞≥πÃ∞¯∞›.(∞¯∞›«— ƒ≥∏Ø≈Õ¿ßø°)(∏∂π˝)
#define _MONMAGIC_WORKANT			510			// ¿œ∞≥πÃ∞¯∞›.(∞¯∞›«— ƒ≥∏Ø≈Õ¿ßø°)(∏∂π˝)
#define _MONMAGIC_RED1				511			// »´¿«π˝ªÁ. (∏∂π˝(Ω√¿¸))
#define _MONMAGIC_RED2				512			// »´¿«π˝ªÁ. (∏∂π˝(∏∂π˝))
#define _MONMAGIC_COWGHOST			513			// øÏ∏È±Õ. (∏∂π˝)
#define _MONMAGIC_SINSU				514			// Ω≈ºˆ. (∏∂π˝)
#define _MONMAGIC_ZOMBIE			515			// ¡ª∫Ò. (∏∂π˝)
#define _MONMAGIC_JUMAWANG			516			// ¡÷∏∂ø’. (∏∂π˝)
#define _MONMAGIC_CHIM				517			// ¥Ÿ≈©
#define _MONMAGIC_ARROW				518			// ±√ºˆ∞Ê∫Ò
#define _MONMAGIC_MAARROW			519			// «ÿ∞Ò±√ºˆ
#define _MONMAGIC_DUALAXE			520			// Ω÷µµ≥¢«ÿ∞Ò
#define _MONMAGIC_COWFLAME			521			// »≠ø∞øÏ∏È±Õ
#define _MONMAGIC_BIGGINE_ATT		522			// √À∑ÊΩ≈
#define _MONMAGIC_BIGGINE_CHAR		523			// √À∑ÊΩ≈
#define _MONMAGIC_SANDFISH			524			// ∞≈»Øºˆ
#define _MONMAGIC_BAODIE			525			// Ω≈±‚∫¥
#define _MONMAGIC_SINGI_DIE			526			// Ω≈±‚ ¡◊±‚
#define _MONMAGIC_HUSU_DIE			527			// «„ºˆæ∆∫Ò
#define _MONMAGIC_ZOMBIE_DIE		528			// ¡ª∫Ò
#define _MONMAGIC_SSEGI				529			// Ω˚±‚≥™πÊ
#define _MONMAGIC_NUMAGUMGI			530			// øæ≥Ø ¥©∏∂ø’
#define _MONMAGIC_EXPLODE1			531			// ºÆ¿Â¿Œ
#define _MONMAGIC_BOSSATT			532			// ∆ƒ√µ»≤∞À±‚
#define _MONMAGIC_BOSSDIE			533			// ∆ƒ√µ»≤¡◊±‚
#define _MONMAGIC_OMASKEL_DIE		534			// «ÿ∞Ò∑˘¡◊±‚
#define _MONMAGIC_GUDEGI			535			// µø±º±∏¥ı±‚
#define _MONMAGIC_DUNG				536			// µ’
#define _MONMAGIC_GUMGI				537			// ∞Ê∫Ò∞À±‚
#define _MONMAGIC_LIGHTENING		538			// ∏ÛΩ∫≈Õ∞≠∞›.
#define _MONMAGIC_LIGHTFLOWER		539			// ∏ÛΩ∫≈Õ∑⁄º≥»≠.
#define _MONMAGIC_POKAN				540			// ∆¯æ»∞≈πÃ.
#define _MONMAGIC_BIDOK				541			// ∫Òµ∂∞≈πÃ.
#define _MONMAGIC_REDMOON			542			// ¿˚ø˘∏∂.
#define _MONMAGIC_WINDGOD			543			// «≥πÈ.
#define _MONMAGIC_POSUANT			544			// ∆˜ºˆ∞≥πÃ.
#define _MONMAGIC_HUMANTREE			545			// «¸¿Œºˆ.
#define _MONMAGIC_LIGHTRIGHTATT		546			// ±§∏ÌøÏªÁ(∞¯∞›)6«¡∑π¿”..
#define _MONMAGIC_LIGHTRIGHTDIE		547			// ±§∏ÌøÏªÁ(¡◊±‚)10«¡∑π¿”..
#define _MONMAGIC_LIGHTLEFTATT		548			// ±§∏Ì¡¬ªÁ(∞¯∞›)6«¡∑π¿”..
#define _MONMAGIC_LIGHTLEFTDIE		549			// ±§∏Ì¡¬ªÁ(¡◊±‚)10«¡∑π¿”..
#define _MONMAGIC_LIGHTLEFTMAGIC	550			// ±§∏Ì¡¬ªÁ(∏∂π˝∞¯∞›)6«¡∑π¿”..
#define _MONMAGIC_GUOBLUEATT		551			// ±∏ø¿¡ª∫Ò(«™∏•ªˆ)(∏∂π˝∞¯∞›)6«¡∑π¿”..
#define _MONMAGIC_GUOREDATT			552			// ±∏ø¿¡ª∫Ò(∫”¿∫ªˆ)(∏∂π˝∞¯∞›)6«¡∑π¿”..
#define _MONMAGIC_ONEZOMBIEDIE		553			// ø‹∆»¿Ã¡ª∫Ò(¡◊±‚)10«¡∑π¿”..
#define _MONMAGIC_REALUMAATT		554			// øÏ∏È∫ªø’(∞À±‚∞¯∞›)10«¡∑π¿”..
#define _MONMAGIC_REALUMAMAGICATT	555			// øÏ∏È∫ªø’(∏∂π˝)20«¡∑π¿”..
#define _MONMAGIC_WEAPONSKELDIE		556			// √¢«ÿ∞Ò, ƒÆ«ÿ∞Ò, »∞«ÿ∞Ò(¡◊±‚)8«¡∑π¿”..
#define _MONMAGIC_SKELCHIEFDIE		557			// «ÿ∞Ò¿Âºˆ(¡◊±‚)10«¡∑π¿”..
#define _MONMAGIC_SKELBOSSFIRE		558			// «ÿ∞Ò¡¯ø’(∏∂π˝-∆ƒ¿ÃæÓ∫º)10«¡∑π¿”..
#define _MONMAGIC_SKELBOSS1			559			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS2			560			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS3			561			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS4			562			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS5			563			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS6			564			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS7			565			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS8			566			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS9			567			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_SKELBOSS10		568			// «ÿ∞Ò¡¯ø’..
#define _MONMAGIC_YEJIN_HEAL		569			// øπ¡¯(¿Ã∫•∆Æ)ƒ°∑·Ω√¿¸»ø∞˙.
#define _MONMAGIC_DONKING			570			// µ∑ø’∞À±‚.
#define _MONMAGIC_KINGKING			571			// ø’¡ﬂø’∞À±‚.
#define _MONMAGIC_BLOODSAGAL		572			// «˜ªÁ∞•¿¸±‚∞¯∞›.
#define _MONMAGIC_FLEA_SHOT			573			// ∫≠∑Ë¥´ πﬂªÁ.
#define _MONMAGIC_BYDONKING			574			// µ∑ø’¿« ∞¯∞›ø° »˜∆Æµ«æ˙¿ª∂ß.
#define _MONMAGIC_KINGKING2			575			// ø’¡ﬂø’ ∆Øºˆ∞¯∞›.
#define _MONMAGIC_FIREBALL			576			// π›æﬂ¡¬ªÁ∆ƒ¿ÃæÓ∫º.
#define _MONMAGIC_SAU				577			// ªÁøÏ√µø’¿Ã∆Â∆Æ√ﬂ∞°.

// æ”ƒ⁄∏£øÕ∆Æ¡ˆø™√ﬂ∞°.
#define _MONMAGIC_SPEAR				578			// ±§Ω≈µµ1 √¢∞¯∞›.
#define _MONMAGIC_POISON			579			// ±§Ω≈µµ2 µ∂∞¯∞›.
#define _MONMAGIC_ELEP				580			// ∞≈»Øºˆ µ∂∞¯∞›.
#define _MONMAGIC_LION1				581			// ºÆ»≠µπªÁ¿⁄∞¯∞›.
#define _MONMAGIC_FLION_D			582			// »≠ø∞µπªÁ¿⁄ ¡◊±‚.
#define _MONMAGIC_SLION_D			583			// ºÆ»≠µπªÁ¿⁄ ¡◊±‚.
#define _MONMAGIC_MURYUK_A			584			// π´∑¬Ω≈¿Â ∞¯∞›.
#define _MONMAGIC_MURYUK_S			585			// π´∑¬Ω≈¿Â ∏¬±‚.
#define _MONMAGIC_MURYUK_D			586			// π´∑¬Ω≈¿Â ¡◊±‚.
#define _MONMAGIC_MAWANG_A1			587			// ¡¯√µ∏∂Ω≈ ∞À±‚∞¯∞›1.
#define _MONMAGIC_MAWANG_MA			588			// ¡¯√µ∏∂Ω≈ ∏∂π˝∞¯∞›.
#define _MONMAGIC_MAWANG_D			589			// ¡¯√µ∏∂Ω≈ ¡◊±‚.
#define _MONMAGIC_THROW_STONE		590			// ø¯»ƒ¿⁄,ø¯»ƒ±∫ µπ¥¯¡ˆ±‚.
#define _MONMAGIC_MAWANG_A2			591			// ¡¯√µ∏∂Ω≈ ∞À±‚∞¯∞›2.
#define _MONMAGIC_LION2				592			// »≠ø∞µπªÁ¿⁄∞¯∞›.

#define _MONMAGIC_SIEGE_SHOOT		593			// πﬂºÆ∞≈ ∆˜ ΩÓ¥¬ ∞Õ.
#define _MONMAGIC_SIEGE_HITTED		594			// πﬂºÆ∞≈ ∆˜ ∏¬¥¬ ∞Õ.
#define _MONMAGIC_SIEGECAR_SHOOT	595			// ºË≥˙¬˜ ∆˜ ΩÓ¥¬ ∞Õ.
#define _MONMAGIC_SIEGECAR_HITTED	596			// ºË≥˙¬˜ ∆˜ ∏¬¥¬ ∞Õ.

// ¥©∏∂∞¯º∫¿¸
#define _MONMAGIC_NUMAGIBYUNG		597			// ¥©∏∂±‚∫¥ ∞¯∞›

#define _MONMAGIC_NUMABUBSA1		598			// ¥©∏∂ªÁ∑…π˝ªÁ
#define _MONMAGIC_NUMABUBSA2		599			// ¥©∏∂ªÁ∑…π˝ªÁ
#define _MONMAGIC_NUMABUBSA3		600			// ¥©∏∂ªÁ∑…π˝ªÁ
#define _MONMAGIC_NUMABUBSA4		601			// ¥©∏∂ªÁ∑…π˝ªÁ
#define _MONMAGIC_NUMABUBSA5		602			// ¥©∏∂ªÁ∑…π˝ªÁ
#define _MONMAGIC_NUMABUBSA6		603			// ¥©∏∂ªÁ∑…π˝ªÁ


#define _MONMAGIC_NUMABUBSA_DIE		604			// ¥©∏∂ªÁ∑…π˝ªÁ ¡◊±‚

#define _MONMAGIC_NUMABODYGUARD_DIE	605			// ¥©∏∂ƒ£¿ß¥Î¿Â ¡◊±‚
#define _MONMAGIC_NUMABODYGUARD_A	606			// ¥©∏∂ƒ£¿ß¥Î¿Â ∏∂π˝∞¯∞›

#define _NPCEFFECT_THESWORD			607			// ¿˝¥Î∞À ¿Ã∆Â∆Æ

#define	_MONMAGIC_TADANGGA_ATTACK	608			// ≈∏¥Á∞° ¿œπ›∞¯∞›
#define _MONMAGIC_TADANGGA_MAGIC	609			// ≈∏¥Á∞° ∏∂π˝∞¯∞›
#define _MONMAGIC_TADANGGA_DIE		610			// ≈∏¥Á∞° ¡◊±‚

#define _NPCEFFECT_THESWORD_STAND	611			// ¿˝¥Î∞À µÈ∞Ì º˚Ω¨±‚

#define _MONMAGIC_BARRACK_DIE		612			// »∆∑√º“ ¡◊±‚
#define _MONMAGIC_GUARD_DIE			613			// ºˆ»£¿⁄ ¡◊±‚
#define _MONMAGIC_STATUE_DIE		614			// Ω≈¿¸ ¡◊±‚

#define _MONMAGIC_SAHYULGUI_A		615			// ªÁ«˜±´ º’≈È
#define _MONMAGIC_DEARYONG_A		616			// ¥Îæ∆∑Ê ∞¯∞›

#define _MONMAGIC_JICHUN_ATTACK		617			// ¡ˆ√µ∏Íø’ ¿œπ›∞¯∞›
#define _MONMAGIC_JICHUN_MAGIC_A	618			// ¡ˆ√µ∏Íø’ ∏∂π˝∞¯∞›
#define _MONMAGIC_JICHUN_MAGIC_B	619			// ¡ˆ√µ∏Íø’ ∏∂π˝∞¯∞›2(¿¸√º∞¯∞›)

#define _MONMAGIC_YOUKHYUL_ATTACK	620			// ¿∞«˜∏∂∑Ê ¿œπ›∞¯∞›
#define _MONMAGIC_YOUKHYUL_MAGIC	621			// ¿∞«˜∏∂∑Ê ∏∂π˝∞¯∞›

#define _MONMAGIC_HANBINGMA_MAGIC	622			// ∫˘»•π´¿Â2 ∏∂π˝∞¯∞› ∏¬¿ª ∂ß

#define _MONMAGIC_BINGHONGUNG_A		624			// ∫˘»•±√ªÁ1 ¿œπ›∞¯∞›

#define _MONMAGIC_BINGBAK_MAGIC_A	625			// ∫˘πÈ±Õ≥‡ ∏∂π˝∞¯∞›
#define _MONMAGIC_BINGBAK_MAGIC_B	626			// ∫˘πÈ±Õ≥‡ ∏∂π˝∞¯∞›
#define _MONMAGIC_BINGBAK_SIJUN		627			// ∫˘πÈ±Õ≥‡ Ω√¿¸

#define _MONMAGIC_WHAYOUNG_MAGIC	628			// »≠øµ«—≈◊ ∏¬¿ª ∂ß
#define _EFFECT_FIRECRACKER_S		629			// ∆¯¡◊ º“
#define _EFFECT_FIRECRACKER_M		630			// ∆¯¡◊ ¡ﬂ
#define _EFFECT_FIRECRACKER_L		631			// ∆¯¡◊ ¥Î
#define _EFFECT_FIRECRACKER_XL		632			// ∆¯¡◊ ∆Ø¥Î

#define _MONMAGIC_GAMU_B			633			// ∞°π´≥‡2 ∞¯∞›¿Ã∆Â
#define _MONMAGIC_DAWNQUEEN_MAGIC	634			// ªı∫Æø©ø’ ∏∂π˝
#define _MONMAGIC_GAMU2_MAGIC		635			// ∞°π´≥‡2∏∂π˝
#define _MONMAGIC_GAMU2_MAGIC_SELF	636			// ∞°π´≥‡2∏∂π˝¿⁄Ω≈
#define _MONMAGIC_GAMU_MAGIC_NEAR	637			// ∞°π´≥‡1 ¡÷∫Ø ∏∂π˝
#define _MONMAGIC_GAMU_MAGIC		638			// ∞°π´≥‡1 ¿¸√º ∏∂π˝
#define _MONMAGIC_GAMU_MAGIC_SELF	639			// ∞°π´≥‡2 ¿¸√º ¿⁄Ω≈
#define _MONMAGIC_GUARDGEN_MAGIC	640			// »£¿ß¿Âºˆ ∏∂π˝
#define _MONMAGIC_GUARDGEN_B		641			// »£¿ß¿Âºˆ ∞¯∞›¿Ã∆Â
#define _MONMAGIC_DAWNQUEEN_B		642			// ªı∫Æø©ø’ ∞¯∞›¿Ã∆Â
#define _MONMAGIC_GUARDGEN_DIE		643			// »£¿ß¿Âºˆ ¡◊±‚
#define _MONMAGIC_DAWNQUEEN_DIE		644			// ªı∫Æø©ø’ ∞¯∞›¿Ã∆Â


#define _BLEND_NORMAL				0			// ¿œπ›¿˚¿Œ±◊∏Æ±‚.(æÀ∆ƒ∞™¿Ã ¿˚øÎµ…ºˆ¿÷¥Ÿ.)
#define _BLEND_LIGHT				1			// º∂±§»ø∞˙«¸≈¬¿« ∫Ì∑ªµ˘.
#define _BLEND_LIGHTINV				2	
#define _BLEND_INVNORMAL			3
#define _BLEND_INVLIGHT				4
#define _BLEND_INVLIGHTINV			5




/******************************************************************************************************************
	#1. Map Handler
*******************************************************************************************************************/

#define _BASETILE_WIDTH				96				// ±‚∫ª≈∏¿œ ≥–¿Ã.
#define _BASETILE_HEIGHT			64
	
#define _CELL_WIDTH					48				// ±‚∫ªºø ≥–¿Ã, ±‚∫ª≈∏¿œ¿∫ 4∞≥¿« ºø∑Œ ¿Ã∑ÁæÓ¡ˆ∞Ì ¡§∫∏¥¬ ºø¥‹¿ß∑Œ ¿˙¿Âµ»¥Ÿ.
#define _CELL_HEIGHT				32

#define _VIEW_CELL_X_COUNT			24				// ∫‰øµø™ø° « ø‰«— X√‡¿« ºø¥‹¿ß ∞≥ºˆ.((¬•≈ı∏Æ ≈∏¿œ¡¶ø‹)¡¬øÕ¿ß∑Œ 3ºø, øÏøÕæ∆∑°∑Œ 2ºøæø¿« ø©¿Ø∏¶ µ–¥Ÿ.)
#define _VIEW_CELL_Y_COUNT			26			
#define _VIEW_CELL_Y_COUNT_FOR_OBJ	44

#define _MEMVIEW_CELL_X_COUNT		36
#define _MEMVIEW_CELL_Y_COUNT		36

#define _VIEW_CELL_X_START			-200			// ∫‰øµø™¿ª ±◊∏Æ±‚ ¿ß«— Ω√¿€ ºø X¡¬«•.
#define _VIEW_CELL_Y_START			-157

#define _VIEW_CELL_X_START_INVEN	-196			// ∫‰øµø™¿ª ±◊∏Æ±‚ ¿ß«— Ω√¿€ ºø X¡¬«•.
#define _VIEW_CELL_Y_START_INVEN	-157

#define _VIEW_CELL_X_START_STATUS	-186			// ∫‰øµø™¿ª ±◊∏Æ±‚ ¿ß«— Ω√¿€ ºø X¡¬«•.
#define _VIEW_CELL_Y_START_STATUS	-157

#define _MAX_TILE_FILE				14

// ∆˜±◊ªˆ ∞¸∑√ º”º∫.
#define _FOG_COLOR_TYPE0			RGB(0, 0, 0);
#define _FOG_COLOR_TYPE1			RGB(100, 10, 10);
#define _FOG_COLOR_TYPE2			RGB(10, 255, 10);
#define _FOG_COLOR_TYPE3			RGB(10, 10, 255);

// º”º∫ ∞¸∑√ ¡§¿«.
#define _CAN_WALK					0
#define _CAN_NOTWALK	 			1
#define _CAN_FLY					0
#define _CAN_NOTFLY					1

// πÆ∞¸∑√ ¡§¿«.
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

// ªÁøÓµÂ ∞¸∑√ ¡§¿«
#define MAX_VOLUME					0
#define MIN_VOLUME					-10000

// ¥Ÿ¡ﬂ¿∏∑Œ ∞„ƒ°¥¬ æ∆¿Ã≈€ Ωƒ∫∞¿⁄
#define _MULTIPLE_TYPE_ITEM			2


// Config.ini ∆ƒ¿œ 
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
#define _MAX_OPTION_BTN				32

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
#define _BTN_ID_CHANGEWEATHER		31

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
#define _HPSET						1
#define	_SCROLLSET					2
#define _MPSET						3

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

#define _TYPE_STORE					0	// ªÛ¡°.
#define _TYPE_STOREDETAIL			1	// ªÛ¡°+ºº∫Œ«∞∏Ò.
#define _TYPE_KEEP					2	// æ∆¿Ã≈€∫∏∞¸.
#define _TYPE_DRUG					3	// æ‡¡¶¡∂.
#define _TYPE_STOREONEITEM			4	// ªÛ¡°+«œ≥™¬•∏Æπ∞∞«.

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
// ¡ﬂ±π «ˆ¡ˆ

#define CM_QUERYUSERNAME			80
#define CM_QUERYBAGITEMS			81
#define CM_QUERYUSERSTATE			82	  //≈∏¿Œ¿« ªÛ≈¬ ∫∏±‚

// √ﬂ∞° ∞°πÊ 2006.08.11
#define CM_QUERYBAGITEMSEX			83

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
#define	CM_CLICKNPC					1010	// ¿Ã ∏ﬁΩ√¡ˆ∏¶ º≠πˆ∑Œ ∫∏≥ªæÓ «ÿ¥Á MPC¿« ¡§∫∏∏¶ πﬁ¥¬¥Ÿ.
#define	CM_MERCHANTDLGSELECT		1011	// ªÁøÎ¿⁄∞° NPC¥Î»≠¡ﬂ Tag∞° ¡∏¿Á«œ¥¬ ∫Œ∫–¿ª Click«ﬂ¿ª∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_MERCHANTQUERYSELLPRICE	1012	// ∆»±‚ π∞∞«¿ª ø√∑¡ ≥ı¿ª ∞ÊøÏ ∞°∞›¿ª æÚ¥¬¥Ÿ.  
#define CM_USERSELLITEM				1013	// ∆»±‚ πˆ∆∞¿ª ¥≠∑»¿ª ∞ÊøÏ (∞˙±‚: ∆»π∞∞«∏∏ «œ≥™∏∏ ∫∏≥ø, «ˆ¿Á: ∆»π∞∞« ∏µŒ ∫∏≥ø
#define CM_USERBUYITEM				1014	// ªÁ±‚ πˆ∆∞¿ª ¥≠∑»¿ª ∞ÊøÏ
#define CM_USERGETDETAILITEM		1015	// ªÛ¡° ∏Ò∑œ¡ﬂø° Sub Menu∞° ¿÷¥¬ ∞Õ¿ª ≈¨∏Ø«ﬂ¿ª ∞ÊøÏ
#define CM_DROPGOLD					1016
#define CM_LOGINNOTICEOK			1018
#define CM_GROUPMODE				1019	// ±◊∑Ï // ***************************************
#define CM_CREATEGROUP				1020	// ***************************************
#define CM_ADDGROUPMEMBER			1021	// ***************************************
#define CM_DELGROUPMEMBER			1022	// ***************************************
#define	CM_USERREPAIRITEM			1023	// ºˆ∏Æ«œ¥Ÿ πˆ∆∞¿ª ¥≠∑∂¿ª ∞ÊøÏ
#define	CM_MERCHANTQUERYREPAIRCOST	1024	// ºˆ∏Æ«“æ∆¿Ã≈€¿ª ø√∑¡ ≥ı¿ª ∞ÊøÏ ∞°∞›¿ª æÚ¥¬¥Ÿ.
#define	CM_DEALTRY					1025	// ∆»±‚, ºˆ∏Æ
#define	CM_DEALADDITEM				1026
#define	CM_DEALDELITEM				1027
#define	CM_DEALCANCEL				1028
#define	CM_DEALCHGGOLD				1029	//±≥»Ø«œ¥¬ µ∑¿Ã ∫Ø∞Êµ 
#define	CM_DEALEND					1030
#define	CM_USERSTORAGEITEM			1031	// ø©∞¸ // ªÁøÎ¿⁄∞° ∏∫±‰¥Ÿ πˆ∆∞(≈ÿΩ∫∆Æ πˆ∆∞ æ∆¥‘)¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_USERTAKEBACKSTORAGEITEM	1032	// ªÁøÎ¿⁄∞° √£¥¬¥Ÿ πˆ∆∞(≈ÿΩ∫∆Æ πˆ∆∞ æ∆¥‘)¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_WANTMINIMAP				1033
#define CM_USERMAKEDRUGITEM			1034	// 
#define	CM_OPENGUILDDLG				1035	// πÆ∆ƒ // ªÁøÎ¿⁄∞° πÆ∆ƒ√¢¿ª ø≠∞Ì¿⁄ «ﬂ¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define CM_GUILDHOME				1036	// ªÁøÎ¿⁄∞° πÆ∆ƒ√¢¡ﬂ HOME πˆ∆∞¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_GUILDMEMBERLIST			1037	// ªÁøÎ¿⁄∞° πÆ∆ƒ√¢¡ﬂ πÆø¯LIST∏¶ ∫∏∞Ì¿⁄ «ﬁ¿ª ∞ÊøÏ
#define CM_GUILDADDMEMBER			1038	// ªÁøÎ¿⁄∞° πÆø¯√ﬂ∞°∏¶ «ﬂ¿ª ∞ÊøÏ
#define	CM_GUILDDELMEMBER			1039	// ªÁøÎ¿⁄∞° πÆø¯ªË¡¶∏¶ «ﬂ¿ª ∞ÊøÏ
#define	CM_GUILDUPDATENOTICE		1040	// ªÁøÎ¿⁄∞° πÆ∆ƒ∞¯¡ˆ∏¶ ºˆ¡§ «ﬂ¿ª ∞ÊøÏ
#define	CM_GUILDUPDATERANKINFO		1041	// ªÁøÎ¿⁄∞° πÆø¯¡˜¿ß∏¶ ºˆ¡§«ﬂ¿ª ∞ÊøÏ
#define CM_GUILDMAKEALLY			1044	// ªÁøÎ¿⁄∞° πÆ∆ƒµø∏Õ¿ª «ﬂ¿ª ∞ÊøÏ
#define CM_GUILDBREAKALLY			1045	// ªÁøÎ¿⁄∞° πÆ∆ƒµø∏Õ∆ƒ±‚∏¶ «ﬂ¿ª∞ÊøÏ
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
#define CM_SPELL					3017	// ∫∏≥Ω»ƒ º≠πˆø°º≠ Ω¬¿Œ¿Ã ø¿∏È µø¿€¿ª «—¥Ÿ. Ω∫∆Áµø¿€¿Ã ≥°≥≠»ƒ sm_magicfire∞° ø¿∏È µø¿€¿ª Ω∫≈ƒµÂ∑Œ πŸ≤€¥Ÿ.
#define CM_WIDEHIT					3024
#define CM_FIREHIT					3025
#define CM_SAY						3030
#define CM_RANDHIT					3031
#define CM_BKSHIT					3032
#define CM_MANWOL					3033

#define CM_HIGH_RANDSWINGHIT        3034	//∞Ì±ﬁø¨ø˘¬¸

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

//  2006.06.20 - ∆˜¿Œ∆Æ ªÛ¡°
#define CM_RELOADUSERPOINT				1190		// ∆˜¿Œ∆Æ ∑ŒµÂ ø‰√ª
#define CM_ADDITEMUSERPOINTMARKET		1200		// ( ±‚¡∏¿ß≈π : CM_ADDITEMUSERMARKET )
#define CM_NEXTPAGEUSERPOINTMARKET		1201
#define CM_PREVPAGEUSERPOINTMARKET		1202
#define CM_BUYITEMUSERPOINTMARKET		1203
#define CM_REFRESHPAGEUSERPOINTMARKET	1204
#define CM_CANCELITEMUSERPOINTMARKET	1205
#define CM_SEARCHPAGEUSERPOINTMARKET	1206

// 2006.06.26 - ø¯∫∏ªÛ¡°
#define CM_BUYITEM					1211			// æ∆¿Ã≈€ ±∏¿‘ ( Recog = Identity, Param = ∞πºˆ )
#define CM_SENDITEMGIFT				1212			// æ∆¿Ã≈€ ±∏¿‘ »ƒ º±π∞ ∫∏≥ª±‚ ( Recog = Identity, Param = ∞πºˆ, body = szName[ 25 ] / ¿Ã∏ß )

// 2006.08.09 √ﬂ∞° √¢∞Ì
#define	CM_USERSTORAGEITEMEX			1213	// ø©∞¸ // ªÁøÎ¿⁄∞° ∏∫±‰¥Ÿ πˆ∆∞(≈ÿΩ∫∆Æ πˆ∆∞ æ∆¥‘)¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_USERTAKEBACKSTORAGEITEMEX	1214	// ªÁøÎ¿⁄∞° √£¥¬¥Ÿ πˆ∆∞(≈ÿΩ∫∆Æ πˆ∆∞ æ∆¥‘)¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.

// 2006.08.11 √ﬂ∞° ∞°πÊ
#define CM_ITEMMOVEBETWEENBAGS		1215

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

#define CM_HIGHWIDEHIT  3016





/*
// «—±π idx
#define CM_QUERYUSERNAME			80
#define CM_QUERYBAGITEMS			81
#define CM_QUERYUSERSTATE			82	  //≈∏¿Œ¿« ªÛ≈¬ ∫∏±‚

#define CM_PICKUP					1000
#define CM_DROPITEM					1001
#define	CM_OPENDOOR					1002
#define CM_TAKEONITEM				1003
#define CM_TAKEOFFITEM				1004
#define CM_EAT						1006
#define CM_BUTCH					1007
#define CM_MAGICKEYCHANGE			1008
#define CM_SOFTCLOSE				1009
#define	CM_CLICKNPC					1010	// ¿Ã ∏ﬁΩ√¡ˆ∏¶ º≠πˆ∑Œ ∫g∏≥ªæÓ «ÿ¥Á MPC¿« ¡§∫∏∏¶ πﬁ¥¬¥Ÿ.
#define	CM_MERCHANTDLGSELECT		1011	// ªÁøÎ¿⁄∞° NPC¥Î»≠¡ﬂ Tag∞° ¡∏¿Á«œ¥¬ ∫Œ∫–¿ª Click«ﬂ¿ª∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_MERCHANTQUERYSELLPRICE	1012	// ∆»±‚ π∞∞«¿ª ø√∑¡ ≥ı¿ª ∞ÊøÏ ∞°∞›¿ª æÚ¥¬¥Ÿ.  
#define CM_USERSELLITEM				1013	// ∆»±‚ πˆ∆∞¿ª ¥≠∑»¿ª ∞ÊøÏ (∞˙±‚: ∆»π∞∞«∏∏ «œ≥™∏∏ ∫∏≥ø, «ˆ¿Á: ∆»π∞∞« ∏µŒ ∫∏≥ø
#define CM_USERBUYITEM				1014	// ªÁ±‚ πˆ∆∞¿ª ¥≠∑»¿ª ∞ÊøÏ
#define CM_USERGETDETAILITEM		1015	// ªÛ¡° ∏Ò∑œ¡ﬂø° Sub Menu∞° ¿÷¥¬ ∞Õ¿ª ≈¨∏Ø«ﬂ¿ª ∞ÊøÏ
#define CM_DROPGOLD					1016
#define CM_LOGINNOTICEOK			1018
#define CM_GROUPMODE				1019	// ±◊∑Ï // ***************************************
#define CM_CREATEGROUP				1020	// ***************************************
#define CM_ADDGROUPMEMBER			1021	// ***************************************
#define CM_DELGROUPMEMBER			1022	// ***************************************
#define	CM_USERREPAIRITEM			1023	// ºˆ∏Æ«œ¥Ÿ πˆ∆∞¿ª ¥≠∑∂¿ª ∞ÊøÏ
#define	CM_MERCHANTQUERYREPAIRCOST	1024	// ºˆ∏Æ«“æ∆¿Ã≈€¿ª ø√∑¡ ≥ı¿ª ∞ÊøÏ ∞°∞›¿ª æÚ¥¬¥Ÿ.
#define	CM_DEALTRY					1025	// ∆»±‚, ºˆ∏Æ
#define	CM_DEALADDITEM				1026
#define	CM_DEALDELITEM				1027
#define	CM_DEALCANCEL				1028
#define	CM_DEALCHGGOLD				1029	//±≥»Ø«œ¥¬ µ∑¿Ã ∫Ø∞Êµ 
#define	CM_DEALEND					1030
#define	CM_USERSTORAGEITEM			1031	// ø©∞¸ // ªÁøÎ¿⁄∞° ∏∫±‰¥Ÿ πˆ∆∞(≈ÿΩ∫∆Æ πˆ∆∞ æ∆¥‘)¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_USERTAKEBACKSTORAGEITEM	1032	// ªÁøÎ¿⁄∞° √£¥¬¥Ÿ πˆ∆∞(≈ÿΩ∫∆Æ πˆ∆∞ æ∆¥‘)¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_WANTMINIMAP				1033
#define CM_USERMAKEDRUGITEM			1034	// 
#define	CM_OPENGUILDDLG				1035	// πÆ∆ƒ // ªÁøÎ¿⁄∞° πÆ∆ƒ√¢¿ª ø≠∞Ì¿⁄ «ﬂ¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define CM_GUILDHOME				1036	// ªÁøÎ¿⁄∞° πÆ∆ƒ√¢¡ﬂ HOME πˆ∆∞¿ª ¥≠∑∂¿ª ∞ÊøÏ ∫∏≥ªæÓ¡¯¥Ÿ.
#define	CM_GUILDMEMBERLIST			1037	// ªÁøÎ¿⁄∞° πÆ∆ƒ√¢¡ﬂ πÆø¯LIST∏¶ ∫∏∞Ì¿⁄ «ﬁ¿ª ∞ÊøÏ
#define CM_GUILDADDMEMBER			1038	// ªÁøÎ¿⁄∞° πÆø¯√ﬂ∞°∏¶ «ﬂ¿ª ∞ÊøÏ
#define	CM_GUILDDELMEMBER			1039	// ªÁøÎ¿⁄∞° πÆø¯ªË¡¶∏¶ «ﬂ¿ª ∞ÊøÏ
#define	CM_GUILDUPDATENOTICE		1040	// ªÁøÎ¿⁄∞° πÆ∆ƒ∞¯¡ˆ∏¶ ºˆ¡§ «ﬂ¿ª ∞ÊøÏ
#define	CM_GUILDUPDATERANKINFO		1041	// ªÁøÎ¿⁄∞° πÆø¯¡˜¿ß∏¶ ºˆ¡§«ﬂ¿ª ∞ÊøÏ
#define CM_GUILDMAKEALLY			1044	// ªÁøÎ¿⁄∞° πÆ∆ƒµø∏Õ¿ª «ﬂ¿ª ∞ÊøÏ
#define CM_GUILDBREAKALLY			1045	// ªÁøÎ¿⁄∞° πÆ∆ƒµø∏Õ∆ƒ±‚∏¶ «ﬂ¿ª∞ÊøÏ
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
#define CM_SPELL					3017	// ∫∏≥Ω»ƒ º≠πˆø°º≠ Ω¬¿Œ¿Ã ø¿∏È µø¿€¿ª «—¥Ÿ. Ω∫∆Áµø¿€¿Ã ≥°≥≠»ƒ sm_magicfire∞° ø¿∏È µø¿€¿ª Ω∫≈ƒµÂ∑Œ πŸ≤€¥Ÿ.
#define CM_WIDEHIT					3024
#define CM_FIREHIT					3025
#define CM_SAY						3030
#define CM_RANDHIT					3031
#define CM_BKSHIT					3032
#define CM_MANWOL					3033

#define CM_HIGH_RANDSWINGHIT        3034	//∞Ì±ﬁø¨ø˘¬¸

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

#define CM_HIGHWIDEHIT  3016
*/
/******************************************************************************************************************
	#1. LOGIN PROC
*******************************************************************************************************************/
#define CM_PROTOCOL					2000
#define CM_IDPASSWORD				2001
#define CM_ADDNEWUSER				2002
#define CM_CHANGEPASSWORD			2003
#define CM_UPDATEUSER				2004
#define CM_CARDIDPASSWORD			2005	//¡ﬂ±π ¿Œ¡ı≈∞

#define CM_QUERYCHR					100
#define CM_NEWCHR					101
#define CM_DELCHR					102
#define CM_SELCHR					103
#define CM_SELECTSERVER				104



/******************************************************************************************************************
	#1. Server To Client Message
*******************************************************************************************************************/
// ¡ﬂ±π «ˆ¡ˆ

#define SM_RUSH						6		// π´≈¬∫∏ π–±‚.
#define SM_RUSHKUNG             	7 		// æ’¿∏∑Œ ¿¸¡¯Ω«∆–
#define SM_FIREHIT					8
#define SM_BACKSTEP					9

#define SM_TURN						10
#define SM_WALK						11
#define SM_SITDOWN					12
#define SM_RUN						13
#define SM_HIT						14
#define SM_HEAVYHIT					15
#define SM_SPELL					17		// Ω∫∆Á¿ª «—¥Ÿ.
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
#define SM_SKELETON					33		// SM_DEATHøÕ µø¿œ.
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

// √ﬂ∞° ∞°πÊ 2006.08.11
#define SM_ADDITEMEX				204
#define SM_BAGITEMSEX				205

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
#define SM_MAGICFIRE				638		// ∏∂π˝¿Ã Ω««‡µ»¥Ÿ.
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

#define SM_CREATEGROUP_OK			660		// ±◊∑Ï // ******************************************************************
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
#define	SM_DEALMENU					673	// ±≥»Ø√¢
#define	SM_DEALTRY_FAIL				674
#define	SM_DEALADDITEM_OK			675
#define	SM_DEALADDITEM_FAIL			676
#define	SM_DEALDELITEM_OK			677
#define	SM_DEALDELITEM_FAIL			678

#define	SM_DEALCANCEL				681 //µµ¡ﬂø° ∞≈∑° √Îº“µ 
#define	SM_DEALREMOTEADDITEM		682 //ªÛ¥ÎπÊ¿Ã ±≥»Ø æ∆¿Ã≈€¿ª √ﬂ∞°
#define	SM_DEALREMOTEDELITEM		683 //ªÛ¥ÎπÊ¿Ã ±≥»Ø æ∆¿Ã≈€¿ª ª≠
#define	SM_DEALCHGGOLD_OK			684
#define	SM_DEALCHGGOLD_FAIL			685
#define	SM_DEALREMOTECHGGOLD		686
#define	SM_DEALSUCCESS				687

#define SM_SENDUSERSTORAGEITEM		700
#define SM_STORAGE_OK				701
#define SM_STORAGE_FULL				702	//¥ı ∫∏∞¸ ∏¯ «‘.
#define SM_STORAGE_FAIL				703	//∫∏∞¸ ø°∑Ø
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

#define SM_SPACEMOVE_HIDE			800  //º¯∞£¿Ãµø ªÁ∂Û¡¸
#define SM_SPACEMOVE_SHOW			801  //≥™≈∏≥≤
#define SM_RECONNECT				802
#define SM_GHOST					803
#define SM_SHOWEVENT				804
#define SM_HIDEEVENT				805
#define SM_SPACEMOVE_HIDE2			806  //º¯∞£¿Ãµø ªÁ∂Û¡¸
#define SM_SPACEMOVE_SHOW2			807  //≥™≈∏≥≤
#define SM_PULL_SHOW				808

#define SM_SAVEITEMLIST2			820
#define SM_SAVEITEMLIST3			821

// √ﬂ∞° √¢∞Ì
#define SM_SAVEITEMLISTEX			822
#define SM_SAVEITEMLISTEX2			823
#define SM_SAVEITEMLISTEX3			824
#define SM_SENDUSERSTORAGEITEMEX	825

// 2006.08.18 √ﬂ∞° ∞°πÊ
#define SM_ITEMMOVEBETWEENBAGS		1453

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
/*#define SM_POWERHIT_HIGH			1332
#define SM_LONGHIT_HIGH				1333
#define SM_MANWOL_HIGH				1334*/

// »Ø∞Ò ¿Ã»ƒ æÓ∞Àº˙ 4¥‹, 5¥‹¿« ¿Ã∆Â∆Æ∏¶ ¿ß«ÿº≠
#define SM_POWERHIT_HIGH			10018
#define SM_LONGHIT_HIGH				10019
#define SM_MANWOL_HIGH				10025

#define SM_USERGETSHOOTER			1350
#define SM_SHOOTERSTATUSCHANGED		1351
#define SM_SHOTEFFECT				1352
#define SM_LOSESHOOTER				1353
#define SM_USEWEARITEM_FAIL			1354

#define SM_SENDLISTUSERMARKET		1355

// 2006.06.19 - ∆˜¿Œ∆Æ ªÛ¡°
#define SM_POINTCHANGED				1450		// ∆˜¿Œ∆Æ∞™ ¿¸¥ﬁ( GoldøÕ ∏∂¬˘∞°¡ˆ∑Œ Recogø° Point∞™ ¥„æ∆ ∫∏≥Ω¥Ÿ )
#define SM_SENDLISTUSERPOINTMARKET	1452

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

#define SM_NEXTTIME_PASSWORD		1105		//  *∑Œ «•Ω√«œ∂Û¥¬ ∏ﬁºº¡ˆ




// «—±π idx
/*
#define SM_RUSH						6		// π´≈¬∫∏ π–±‚.
#define SM_RUSHKUNG             	7 		// æ’¿∏∑Œ ¿¸¡¯Ω«∆–
#define SM_FIREHIT					8
#define SM_BACKSTEP					9

#define SM_TURN						10
#define SM_WALK						11
#define SM_SITDOWN					12
#define SM_RUN						13
#define SM_HIT						14
#define SM_HEAVYHIT					15
#define SM_SPELL					17		// Ω∫∆Á¿ª «—¥Ÿ.
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
#define SM_SKELETON					33		// SM_DEATHøÕ µø¿œ.
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
#define SM_MAGICFIRE				638		// ∏∂π˝¿Ã Ω««‡µ»¥Ÿ.
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

#define SM_CREATEGROUP_OK			660		// ±◊∑Ï // ******************************************************************
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
#define	SM_DEALMENU					673	// ±≥»Ø√¢
#define	SM_DEALTRY_FAIL				674
#define	SM_DEALADDITEM_OK			675
#define	SM_DEALADDITEM_FAIL			676
#define	SM_DEALDELITEM_OK			677
#define	SM_DEALDELITEM_FAIL			678

#define	SM_DEALCANCEL				681 //µµ¡ﬂø° ∞≈∑° √Îº“µ 
#define	SM_DEALREMOTEADDITEM		682 //ªÛ¥ÎπÊ¿Ã ±≥»Ø æ∆¿Ã≈€¿ª √ﬂ∞°
#define	SM_DEALREMOTEDELITEM		683 //ªÛ¥ÎπÊ¿Ã ±≥»Ø æ∆¿Ã≈€¿ª ª≠
#define	SM_DEALCHGGOLD_OK			684
#define	SM_DEALCHGGOLD_FAIL			685
#define	SM_DEALREMOTECHGGOLD		686
#define	SM_DEALSUCCESS				687

#define SM_SENDUSERSTORAGEITEM		700
#define SM_STORAGE_OK				701
#define SM_STORAGE_FULL				702	//¥ı ∫∏∞¸ ∏¯ «‘.
#define SM_STORAGE_FAIL				703	//∫∏∞¸ ø°∑Ø
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

#define SM_SPACEMOVE_HIDE			800  //º¯∞£¿Ãµø ªÁ∂Û¡¸
#define SM_SPACEMOVE_SHOW			801  //≥™≈∏≥≤
#define SM_RECONNECT				802
#define SM_GHOST					803
#define SM_SHOWEVENT				804
#define SM_HIDEEVENT				805
#define SM_SPACEMOVE_HIDE2			806  //º¯∞£¿Ãµø ªÁ∂Û¡¸
#define SM_SPACEMOVE_SHOW2			807  //≥™≈∏≥≤
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

#define SM_NEXTTIME_PASSWORD		1105		//  *∑Œ «•Ω√«œ∂Û¥¬ ∏ﬁºº¡ˆ

*/


/******************************************************************************************************************
	#1. LOGIN PROC
*******************************************************************************************************************/
#define	SM_VERSION_AVAILABLE	500			//
#define	SM_CERTIFICATION_FAIL	501			//  Fail
#define SM_ID_NOTFOUND			502			//	ID æ¯¿Ω
#define	SM_PASSWD_FAIL			503			//	∆–Ω∫øˆµÂ ∆≤∏≤
#define	SM_NEWID_SUCCESS		504			//	ªıæ∆¿Ãµ ¿ﬂ ∏∏µÈæÓ ¡≥¿Ω
#define	SM_NEWID_FAIL			505			//	ªıæ∆¿Ãµ ∏∏µÈ±‚ Ω«∆–
#define	SM_CHGPASSWD_SUCCESS	506			//	∆–Ω∫øˆµÂ πŸ≤Ÿ±‚ º∫∞¯
#define	SM_CHGPASSWD_FAIL		507			//	∆–Ω∫øˆµÂ πŸ≤Ÿ±‚ Ω«∆–
#define	SM_QUERYCHR				520			//	ƒ≥∏Ø∏ÆΩ∫∆Æ
#define	SM_NEWCHR_SUCCESS		521			//	ƒ…∏Ø≈Õ ª˝º∫ º∫∞¯
#define	SM_NEWCHR_FAIL			522			//	ƒ…∏Ø≈Õ ª˝º∫ Ω«∆–
#define	SM_DELCHR_SUCCESS		523			//	ƒ…∏Ø≈Õ ªË¡¶ º∫∞¯
#define	SM_DELCHR_FAIL			524			//	ƒ…∏Ø≈Õ ªË¡¶ Ω«∆–
#define	SM_STARTPLAY			525			//	∞≥¿”Ω√¿€
#define	SM_STARTFAIL			526			//	∞≥¿”Ω√¿€ Ω«∆–
#define	SM_QUERYCHR_FAIL		527			//	ƒ…∏Ø≈Õ ¡§∫∏ ¿–æÓø¿±‚ Ω«∆–
#define	SM_OUTOFCONNECTION		528			//	ø¨∞· «ÿ¡¶µ 
#define	SM_PASSOK_SELECTSERVER	529			//	Password∞° ∏¬¿∏π«∑Œ  º≠πˆ Selection¿∏∑Œ ≥—æÓ∞®(º≠πˆ Listπ◊ √÷±Ÿ ¡¢º”º≠πˆ ¿⁄∑·)
#define	SM_SELECTSERVER_OK		530			//	º≠πˆº±≈√ (¡¢º” º≠πˆ IPµÓ¿« ¡§∫∏∞° µÈæÓ∞®)
#define	SM_NEEDUPDATE_ACCOUNT	531			//	∞Ë¡§¿« ¡§∫∏∏¶ ¥ŸΩ√ ¿‘∑¬«œ±‚ πŸ∂˜ √¢..
#define	SM_UPDATEID_SUCCESS		532			//	∞Ë¡§¡§∫∏ ∞ªΩ≈ º∫∞¯
#define	SM_UPDATEID_FAIL		533			//	∞Ë¡§¡§∫∏ ∞ªΩ≈ Ω«∆–
#define SM_PASSOK_WRONGSSN		534			//  ¿ﬂ∏¯µ» ¡÷πŒµÓ∑œπ¯»£.
#define SM_NOT_IN_SERVICE		535			//  º≠πˆ¡°∞À¡ﬂ.
#define SM_CARDIDPASSWORD		536			//  ¡ﬂ±π ¿Œ¡ı≈∞


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
#define LOGON_WNDID_CARDKEY			2
#define LOGIN_WNDID_QUIT			3

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
#define _MIRPROFILE_FILENAME		"/Mir3.ini"
#define _MIRPATCHPROFILE_FILENAME	"/Mir3Patch.ini"
#define _MIR3EI_TSINI_FILE_NAME		"Mir3Test.ini"
#define _MIR3EI_INI_SECTION			"Initial"
#define _MIR3EI_SRV_SECTION			"Server"
#define _LOGIN_SERVER_NAME			"ServerAddr"
#define _LOGIN_SERVER_PORT			"Param1"
#define _SERVER_COUNT				"ServerCount"
#define _LOGIN_GATE_SERVER_IP		"192.168.0.200"
#define _URL_ACCOUNT				"Param2"
#define _URL_CHANGEPWD				"Param3"

#define	_KIND_IP_FIXED_TIME			1
#define	_KIND_IP_FIXED_MONEY		2
#define	_KIND_PRIVATE_FIXED_TIME	3
#define	_KIND_PRIVATE_FIXED_MONEY	4

/*******************************************************************************************************
		Character Select Procedure
*******************************************************************************************************/
#define _MAX_CHAR						4
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

#define _CHR_CHR_CREATE_BTN				6
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
#define _URL_NEW_ACCOUNT		"http://account.wemade.com/main01.html"
#define _URL_CHANGE_PASSWORD	"http://account.wemade.com/main03.html"
//#define _URL_CHANGE_PASSWORD	"http://www.mir2ei.com/service/Modify_pwd"
//http://account.wemade.com/chg_allinfo/main.asp->∞≥¿Œ¡§∫∏∫Ø∞Ê πŸ∑Œ∞°±‚.



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
		Info Shop(Kornet)∞¸∑√.
**********************************************************************/
#define _KORNET_IP				"211.48.62.250"
#define _KORNET_PORT			9000

///////////////    ªı∑ŒøÓ ¿Œ≈Õ∆‰¿ÃΩ∫     ////////////////
//#define _NEWINTERFACE
#define _3rdINTERFACE
//#define _TEST_SERVER

#endif // _DEFINE_H























