#ifndef _DEFINE_H
#define _DEFINE_H




/******************************************************************************************************************
	#1. File Names
*******************************************************************************************************************/
#define MESSAGE_DLL_1				".\\Mirmg.dll"
#define MIR2_PATCH_FILE_NAME		".\\Mir2Patch.exe"




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
#define _WM_USER_MSG_INPUTTED		WM_USER + 1005				// ¿¡µðÆ®¹Ú½º ÀÔ·Â¸Þ½ÃÁö. ¸Þ½ÃÁö°¡ Ä¿¸ÇµåÀÏ°æ¿ì wParam°ªÀº TRUE·Î ¼¼ÆÃµÈ´Ù.
#define ID_SOCKCLIENT_EVENT_MSG		WM_USER + 1100				// SOCKETÊÂ¼þ
#define ID_SOCKCLIENT_EVENT_MSG_1	ID_SOCKCLIENT_EVENT_MSG + 1	


/******************************************************************************************************************
	#1. Image Define Message
*******************************************************************************************************************/
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

#define _IMAGE_INTER				70
#define _IMAGE_M_HUMAN				71
#define _IMAGE_M_WEAPON1			72
#define _IMAGE_M_WEAPON2			73
#define _IMAGE_M_WEAPON3			74
#define _IMAGE_M_WEAPON4			75
#define _IMAGE_M_WEAPON5			76
#define _IMAGE_WM_HUMAN				77
#define _IMAGE_WM_WEAPON1			78
#define _IMAGE_WM_WEAPON2			79
#define _IMAGE_WM_WEAPON3			80
#define _IMAGE_WM_WEAPON4			81
#define _IMAGE_WM_WEAPON5			82

#define _IMAGE_M_HAIR				133
#define _IMAGE_M_HELMET1			134
#define _IMAGE_WM_HAIR				135
#define _IMAGE_WM_HELMET1			136
#define _IMAGE_M_HELMET2			146
#define _IMAGE_WM_HELMET2			147

#define _IMAGE_MAGIC				83
#define _IMAGE_ITEM_INVENTORY		84
#define _IMAGE_ITEM_EQUIP			85
#define _IMAGE_ITEM_GROUND			86
#define _IMAGE_MICON				87
#define _IMAGE_PROGUSE				88
#define _IMAGE_HORSE				89

#define _IMAGE_MONSTER1				90
#define _IMAGE_MONSTER2				91
#define _IMAGE_MONSTER3				92
#define _IMAGE_MONSTER4				93
#define _IMAGE_MONSTER5				94
#define _IMAGE_MONSTER6				95
#define _IMAGE_MONSTER7				96
#define _IMAGE_MONSTER8				97
#define _IMAGE_MONSTER9				98
#define _IMAGE_MONSTER10			99
#define _IMAGE_MONSTER11			100
#define _IMAGE_MONSTER12			101
#define _IMAGE_MONSTER13			102
#define _IMAGE_MONSTER14			103
#define _IMAGE_MONSTER15			104
#define _IMAGE_MONSTER16			105
#define _IMAGE_MONSTER17			106
#define _IMAGE_MONSTER18			107
#define _IMAGE_MONSTER19			108
#define _IMAGE_MONSTER20			109

#define _IMAGE_SMONSTER1			110
#define _IMAGE_SMONSTER2			111
#define _IMAGE_SMONSTER3			112
#define _IMAGE_SMONSTER4			113
#define _IMAGE_SMONSTER5			114
#define _IMAGE_SMONSTER6			115
#define _IMAGE_SMONSTER7			116	
#define _IMAGE_SMONSTER8			117
#define _IMAGE_SMONSTER9			118
#define _IMAGE_SMONSTER10			119	
#define _IMAGE_SMONSTER11			120
#define _IMAGE_SMONSTER12			121
#define _IMAGE_SMONSTER13			122
#define _IMAGE_SMONSTER14			123	
#define _IMAGE_SMONSTER15			124
#define _IMAGE_SMONSTER16			125
#define _IMAGE_SMONSTER17			126
#define _IMAGE_SMONSTER18			127	
#define _IMAGE_SMONSTER19			128
#define _IMAGE_SMONSTER20			129

#define _IMAGE_NPC					130
#define _IMAGE_MONMAGIC				131
#define _MAX_MONSTER_IMAGE			132

//ËÀÍöµÄ¹ÖÎï?
#define _IMAGE_D_MONSTER1			137
#define _IMAGE_D_SMONSTER1			138
#define _IMAGE_MAGICEX				139
#define _IMAGE_MONMAGICEX			140
#define _IMAGE_STOREITEM			141
#define _IMAGE_MONMAGICEX2			142
#define _IMAGE_MONSTER54			143
#define _IMAGE_FLAG					144
#define _IMAGE_MONMAGICEX3			145
#define _IMAGE_MonMagicEx4			148
#define _IMAGE_MAGICEX2				149




#define _IMAGE_INTEREX				70	//ÒÑ¾­Ã»ÓÐÕâ¸öÎÄ¼þÁË£¬ÓÃgameinter´úÌæ


#define _MAX_IMAGE					150

#define _TEXTR_FILE_MAGIC			0
#define _TEXTR_FILE_MONMAGIC		1
#define _TEXTR_FILE_MAP				2
#define _TEXTR_FILE_INTER			3

#define _MAX_TEXTR_FILE				4




/******************************************************************************************************************
	#1. Item Define
*******************************************************************************************************************/
#define _ITEM_TYPE_INVENTORY		0
#define _ITEM_TYPE_EQUIP			1
#define _ITEM_TYPE_GROUND			2

#define _INVENTORY_CELL_WIDTH		38
#define _INVENTORY_CELL_HEIGHT		38

#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // Åõ°ú»ö.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // °ËÁ¤»ö.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // Èò»ö.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // »¡°­.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // ³ì»ö.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // Çª¸¥»ö
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // ³ë¶û»ö.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // ÁÖÈ²»ö

#define _USER_NAMECLR1				255	//RGB(255, 255, 255); Èò»ö
#define _USER_NAMECLR2				251	//RGB(255, 255,   0); ³ë¶õ»ö
#define _USER_NAMECLR3				249	//RGB(255,   0,   0); »¡°£»ö
#define _USER_NAMECLR4				125	//RGB(255,   0,   0); ??»ö(°á°è¾È ¸ó½ºÅÍ»ö)
#define _USER_NAMECLR5				47	//RGB(165,  99,  57); °¥»ö
#define _USER_NAMECLR6				180	//RGB(  0,   0, 255); Çª¸¥»ö
#define _USER_NAMECLR7				69	//RGB(239, 107,   0); ÁÖÈ²»ö
#define _USER_NAMECLR8				221	//RGB(  0, 148,   0); ³ì»ö
#define _USER_NAMECLR9				254	//RGB(  0, 255, 255); »ö
#define _USER_NAMECLR10				147	//RGB(140, 214, 239); »ö
#define _USER_NAMECLR11				154	//RGB( 57, 181, 239); »ö
#define _USER_NAMECLR12				229	//RGB(119, 136, 255); »ö
#define _USER_NAMECLR13				168	//RGB(  0, 123, 222); »ö
#define _USER_NAMECLR14				252	//RGB(  0,   0, 255); »ö

#define _CLR_RED					RGB(255, 0, 0)
#define _CLR_BLACK					RGB(0, 0, 0)


/******************************************************************************************************************
	#1. Actor Define
*******************************************************************************************************************/
#define _GENDER_MAN					0
#define _GENDER_WOMAN				1
#define _GENDER_NPC					5//mirµÄ»ã±àÖÐÊý×Ö
#define _GENDER_MON					3//77
#define _MAX_GENDER					4

#define _TARGETRGN_GAPX				10
#define _TARGETRGN_GAPY				8

#define _MAX_HERO_KIND				10
#define _MAX_MON_KIND				255
#define _MAX_NPC_KIND				29

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
#define _MAX_WEAPON					32		

#define _HORSE_NONE					0
#define _MAX_HORSE					4

#define	_MAX_WEAPON_MTN				25
#define	_MAX_WEAPON_FRAME			3000

#define	_START_HORSE_FRAME			2320
#define	_START_HORSE_MTN			29
#define	_MAX_HORSE_FRAME			400

#define _MY_CENTER_XPOS				400
#define _MY_CENTER_YPOS	    		243

#define _MAX_CHAT_LINE				5
#define _CHAT_WIDTH					250
//#define _GAPX_TILE_CHAR_MAP		11
//#define _GAPY_TILE_CHAR_MAP		11 
#define _GAPX_TILE_CHAR_MAP			12
#define _GAPY_TILE_CHAR_MAP			12 
#define _CHAR_CENTER_XPOS			400
#define _CHAR_CENTER_YPOS	    	243

#define _SPEED_WALK					1
#define _SPEED_RUN					2
#define _SPEED_HORSERUN				3

#define _MOTION_LOCKTIME			8000
#define _WARMODE_TIME				5000

#define _JOB_DOSA					2
#define _JOB_SULSA					1
#define _JOB_JUNSA					0

#define _STATE_RED					64690
#define _STATE_GREEN				2016
#define _STATE_BLUE					38079//31
#define _STATE_YELLOW				65504
#define _STATE_FUCHSIA				64511
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
// HeroÀÇ µ¿ÀÛ Á¤ÀÇ.(°ÔÀÓ³»ÀÇ ¸ðµç µ¿ÀÛÀ» Á¤ÀÇÇÑ´Ù.)

#define _MAX_HERO_MTN				33			// ÃÖ´ë µ¿ÀÛ°¹¼ö.
#define _MAX_HERO_FRAME				3000		// ´ÙÀ½ Hero·Î ³Ñ¾î°¡´Â ÃÖ´ë ÇÁ·¹ÀÓ °¹¼ö.
#define	_MAX_HERO_REALFRAME			2640

#define _MT_STAND					0			// À¯ÈÞµ¿ÀÛ.
#define _MT_ARROWATTACK				1			// È°°ø°Ý.
#define _MT_SPELL1					2			// ¸¶¹ý ½ÃÀü1.
#define _MT_SPELL2					3			// ¸¶¹ý °ø°Ý ½ÃÀü2.
#define _MT_HOLD					4			// °ßµð±â.
#define _MT_PUSHBACK				5			// µÚ·Î ¹Ð·Á³ª±â.
#define _MT_PUSHBACKFLY				6			// µÚ·Î ³¯¶ó¼­ ¹Ð·Á³ª±â.
#define _MT_ATTACKMODE				7			// ÀüÅõ¸ðµå.
#define _MT_CUT						8			// °í±â ½ä±â.
#define _MT_ONEVSWING				9			// ÇÑ¼Õ Á¾º£±â.(µ¿ÀÛ 9¹øºÎÅÍ 14¹ø±îÁö¿¡¼­ ¹«±âÀÇ Á¾·ù¿¡ µû¶ó µ¿ÀÛÀÌ Á¤ÇØÁø´Ù.)
#define _MT_TWOVSWING				10			// µÎ¼Õ Á¾º£±â.
#define _MT_ONEHSWING				11			// ÇÑ¼Õ È¾º£±â.
#define _MT_TWOHSWING				12			// µÎ¼Õ È¾º£±â.	
#define _MT_SPEARVSWING				13			// Ã¢ Á¾º£±â.
#define _MT_SPEARHSWING				14			// Ã¢ È¾º£±â.
#define _MT_HITTED					15			// ¸Â±â.
#define _MT_WHEELWIND				16			// µ¹¸é¼­ º£±â.
#define _MT_RANDSWING				17			// ¸¶±¸ º£±â.
#define _MT_BACKDROPKICK			18			// µÚµ¹¾Æ Â÷±â.
#define _MT_DIE						19			// Á×±â.
#define _MT_SPECIALDIE				20			// Æ¢¾î¿Ã¶ó Á×±â.
#define _MT_WALK					21			// °È±â.
#define _MT_RUN						22			// ´Þ¸®±â.
#define _MT_MOODEPO					23			// ¹«ÅÂº¸ ¶Ù±â.
#define _MT_ROLL					24			// ±¸¸£±â.
#define _MT_FISHSTAND				25			// ³¬½Ã¸ðµå À¯ÈÞ.
#define _MT_FISHHAND				26			// ³¬½Ã¸ðµå.
#define _MT_FISHTHROW				27			// ³¬½ÃÁÙ ´øÁö±â.
#define _MT_FISHPULL				28			// ³¬½ÃÁÙ ´ç±â±â.
#define _MT_HORSESTAND				29			// ½Â¸¶¸ðµå À¯ÈÞ.
#define _MT_HORSEWALK				30			// ½Â¸¶¸ðµå °È±â.
#define _MT_HORSERUN				31			// ½Â¸¶¸ðµå ´Þ¸®±â.
#define _MT_HORSEHIT				32			// ½Â¸¶¸ðµå ¸Â±â.

// MonsterÀÇ µ¿ÀÛ Á¤ÀÇ.(°ÔÀÓ³»ÀÇ ¸ðµç µ¿ÀÛÀ» Á¤ÀÇÇÑ´Ù.)
#define _MAX_MON_MTN				10			// ÃÖ´ë µ¿ÀÛ°¹¼ö.
#define _MAX_MON_FRAME				1000		// ´ÙÀ½ Mon·Î ³Ñ¾î°¡´Â ÃÖ´ë ÇÁ·¹ÀÓ °¹¼ö.

#define _MT_MON_STAND				0			// À¯ÈÞµ¿ÀÛ.
#define _MT_MON_WALK				1			// °È±âµ¿ÀÛ.
#define _MT_MON_ATTACK_A			2			// ÀÏ¹Ý°ø°Ýµ¿ÀÛ1.
#define _MT_MON_HITTED				3			// ¸Â±âµ¿ÀÛ.
#define _MT_MON_DIE					4			// Á×±âµ¿ÀÛ.
#define _MT_MON_ATTACK_B			5			// ÀÏ¹Ý°ø°Ýµ¿ÀÛ2.
#define _MT_MON_SPELL_A				6			// ¸¶¹ý°ø°Ýµ¿ÀÛ1.
#define _MT_MON_SPELL_B				7			// ¸¶¹ý°ø°Ýµ¿ÀÛ2.
#define _MT_MON_APPEAR				8			// ³ªÅ¸³ª±âµ¿ÀÛ.
#define _MT_MON_SPECIAL_MTN			9			// Æ¯¼öµ¿ÀÛ1.


// NPCÀÇ µ¿ÀÛ Á¤ÀÇ.(°ÔÀÓ³»ÀÇ ¸ðµç µ¿ÀÛÀ» Á¤ÀÇÇÑ´Ù.)
// NPC °ü·ÃÁ¤ÀÇ.
#define _MAX_NPC_MTN				3			// ÃÖ´ë µ¿ÀÛ°¹¼ö.
#define _MAX_NPC_FRAME				100			// ´ÙÀ½ NPC·Î ³Ñ¾î°¡´Â ÃÖ´ë ÇÁ·¹ÀÓ °¹¼ö.

#define _MT_NPC_STAND				0			// À¯ÈÞµ¿ÀÛ.
#define _MT_NPC_ACT01				1			// Æ¯¼öµ¿ÀÛ1.
#define _MT_NPC_ACT02				2			// Æ¯¼öµ¿ÀÛ2.

// ±âµµ.							0			
// ¹«±â´ëÀåÀåÀÌ.					1			
// ¹æ¾î±¸´ëÀåÀåÀÌ.					2			
// ¿©°üÁ¾¾÷¿ø.						3			
// Ä«¿îÅÍ.							4			
// °æ¸Å¾È³»ÀÚ.						5			
// °í±Þ»ç¼­.						6			
// µµ¼­°ü°æºñ.						7			
// »ç¼­.							8			
// Á¢¼öÃ³.							9			
// ¾àÃÊÇÒ¾Æ¹öÁö.					10			
// ÀÇ·ù»ó.							11			
// ÁÖÁ¡NPC.							12			
// »ç¸·Àü»ç.						13			
// ´ëÀå°£Á¾¾÷¿ø.					14			
// µµ¹ÚÀåÃ¥ÀÓÀÚ.					15			
// ¿¾³¯´ëÀåÀåÀÌ.					16			
// ¿¾³¯¾à¹æ³ëÀÎ.					17			
// ¿¾³¯Ã¥¹æ³ëÀÎ.					18			
// Àâ»óÀÎ.							19			
// ÀâÈ­»ó.							20			
// ÀâÈ­»ó.							21			
// ÀâÈ­»ó.							22			
// Á¡ÀïÀÌ.							23			
// Æ÷¸ñ»ó.							24			
// ¿©°ü¾ÆÁÜ¸¶.						25
// À½½ÄÁ¡ÇÒ¹è.						26
// Á¤À°Á¡ÁÖÀÎ.						27			
// ÇàÁ¤°ü.							28			





// ¸¶¹ýÈ¿°ú°ü·ÃÁ¤ÀÇ.
#define _MAX_EFFECT					33
#define _MAX_MAGIC					52
#define _MAX_EXPLOSION				8





/******************************************************************************************************************
	#1. Chat Popup Wnd
*******************************************************************************************************************/
#define _MAX_CHATLINE_POPUP			19





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
#define _CLIP_HEIGHT				492
#define _TIMER_ID					1

#define _ET_DIGOUTZOMBI				1  //Á»ºñ°¡ ¶¥ÆÄ°í ³ª¿Â ÈçÀû
#define _ET_MINE					2  //±¤¼®ÀÌ ¸ÅÀåµÇ¾î ÀÖÀ½
#define _ET_PILESTONES				3  //µ¹¹«´õ±â
#define _ET_HOLYCURTAIN				4  //°á°è
#define _ET_FIRE					5
#define _ET_SCULPEICE				6  //ÁÖ¸¶¿ÕÀÇ µ¹±úÁø Á¶°¢

#define _MAX_CELL_OBJ				10

// Day Bright.
#define _DAYSTATE_DUSK				0  // »õº®.
#define _DAYSTATE_DAY				1  // ³·.
#define _DAYSTATE_DAWN				2  // Àú³á.
#define _DAYSTATE_NIGHT				3  // ¹ã.

// Fog Bright.
#define _FOGSTATE_DAY				0  // ³·.
#define _FOGSTATE_NIGHT				1  // ¹ã.
#define _FOGSTATE_DAWN				2  // »õº®, Àú³á.





/******************************************************************************************************************
	#1. Interface
*******************************************************************************************************************/
#define _CHAT_COLOR1				0	//RGB(  0,   0,   0); // Åõ°ú»ö.
#define _CHAT_COLOR2				1	//RGB( 10,  10,  10); // °ËÁ¤»ö.
#define _CHAT_COLOR3				2	//RGB(255, 255, 255); // Èò»ö.
#define _CHAT_COLOR4				3	//RGB(255,   0,   0); // »¡°­.
#define _CHAT_COLOR5				4	//RGB(  0, 255,   0); // ³ì»ö.
#define _CHAT_COLOR6				5	//RGB(  0,   0, 255); // Çª¸¥»ö
#define _CHAT_COLOR7				6	//RGB(255, 255,   0); // ³ë¶û»ö.
#define _CHAT_COLOR8				7	//RGB(255, 128,   0); // ÁÖÈ²»ö

#define _INPUT_EDITWND_XPOS			184
#define _INPUT_EDITWND_YPOS			575
#define _INPUT_EDITWND_WIDTH		345
#define _INPUT_EDITWND_HEIGHT		17

// ¸ÞÀÎÀÎÅÍÆäÀÌ½º¿¡¼­ ¾²ÀÏ À©µµ¿ì ¾ÆÀÌµð.
#define _WND_ID_INVENTORY			0			//°¡¹æÀ©µµ¿ì.
#define _WND_ID_STATUS				1			//Ä³¸¯ÅÍ Á¤º¸ º¸±âÀ©µµ¿ì(3°³).
#define _WND_ID_STORE				2			//»óÁ¡À©µµ¿ì.
#define _WND_ID_EXCHANGE			3			//±³È¯À©µµ¿ì.
#define _WND_ID_GUILD				4			//¹®¿øÀ©µµ¿ì.
#define _WND_ID_GUILDMASTER			5			//¹®ÁÖÀ©µµ¿ì.
#define _WND_ID_GROUP				6			//±×·ìÀ©µµ¿ì.
#define _WND_ID_GROUPPOP			7			//
#define _WND_ID_CHATPOP				8			//
#define _WND_ID_NPCCHAT				9		
#define _WND_ID_MESSAGEBOX			10			// MessageBox
#define _WND_ID_QUEST				11			// 
#define _WND_ID_OPTION				12			// 
#define _WND_ID_HORSE				13			// 

// ¸ÞÀÎ ÀÎÅÍÆäÀÌ½º¿¡¼­ ¾²ÀÏ À©µµ¿ìÀÇ ÀÌ¹ÌÁö ÀÎµ¦½º.
#define _WNDIMGIDX_MAIN				1160		//50		Ö÷½çÃæ
#define _WNDIMGIDX_INVENTORY	    1220		//°ü¹ü´°¿Ú
#define _WNDIMGIDX_ITEMSET		    1280		//×´Ì¬£¨½ÇÉ«£©´°¿Ú
#define _WNDIMGIDX_SKILLSET			1620		//skill
#define _WNDIMGIDX_STATUS			1280		//Status
#define _WNDIMGIDX_CHARINFO			1288		//character info,½ÇÉ«ÐÅÏ¢£¬±ðÈË
#define _WNDIMGIDX_STORE			1260			//store
#define _WNDIMGIDX_EXCHANGE			1390		//½»Ò×
#define _WNDIMGIDX_GUILDMASTER		600			//ÐÐ»áÍ·Ä¿£¿.
#define _WNDIMGIDX_GUILD			169			//ÐÐ»á.
#define _WNDIMGIDX_GROUP			1360			//Group.
#define _WNDIMGIDX_GROUPPOP			145			//±×·ìÀÔ·ÂÃ¢.
#define _WNDIMGIDX_CHATPOP			1162			//ÁÄÌì´°¿Ú
#define _WNDIMGINDX_MSGBOX1			254
#define _WNDIMGINDX_MSGBOX2			255
#define _WNDIMGIDX_NPCCHAT			1350		//NPC¶Ô»°´°¿Ú
#define _WNDIMGIDX_QUEST			700			//Äù½ºÆ®Ã¢.
#define _WNDIMGIDX_OPTION			750			//¿É¼ÇÃ¢.
#define _WNDIMGIDX_HORSE			1400			//Âí.
#define _IDX_IMG_NOTICEBOX			1250			//¹«Ô¼´°¿Ú ydq

#define _IDX_IMG_BLANK				1490		//¿Õ°×

#define _IMGIDX_BELT				1210		//belt

// ¸ÞÀÎÀÎÅÍÆäÀÌ½º¿¡¼­ ¾²ÀÏ ¹öÆ° ¾ÆÀÌµð.
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

#define _MAX_INTER_BTN				16
#define _MAX_CHATLINE				5

#define _MAX_SAVECHATLINE			50

#define _BELT_STATE_STAY			0
#define _BELT_STATE_UP				1
#define _BELT_STATE_DOWN			2











/******************************************************************************************************************
	#1. Inventory Window
*******************************************************************************************************************/
#define _INVEN_MAX_CELL				65
#define _BELT_MAX_CELL				6
#define _INVEN_CELL_XCNT			6
#define _INVEN_CELL_YCNT			8
#define _INVEN_MAX_CELL_YCNT		12
#define _INVEN_CELL_XSTART			19
#define _INVEN_CELL_YSTART			60

#define _BELT_CELL_XGAP				42
#define _BELT_CELL_XSTART			18
#define _BELT_CELL_YSTART			14

#define _MAX_INVEN_BTN				1		//2
#define _MAX_INVEN_ITEM				60		//2E
#define _MAX_BELT_ITEM				6

#define _BTN_ID_INVENCLOSE			0
#define _BTN_ID_INVENSCRLUP			1
#define _BTN_ID_INVENSCRLDOWN		2





/******************************************************************************************************************
	#1. Light fog
*******************************************************************************************************************/
#define NUM_CNTX_LIGHTTILE			17
#define NUM_CNTY_LIGHTTILE			21
#define TILE_START_XPOS				-8
#define TILE_START_YPOS				-29

#define TILE_WIDTH					48
#define TILE_HEIGHT					32

#define NUM_LIGHTTILE_INDICES		(NUM_CNTX_LIGHTTILE)*(NUM_CNTY_LIGHTTILE)*3*2
#define NUM_LIGHTTILE_VERTICES		(NUM_CNTX_LIGHTTILE+1)*(NUM_CNTY_LIGHTTILE+1)



/******************************************************************************************************************
	#1. Magic
*******************************************************************************************************************/
#define _MAGIC_ACTIVE				0			// ¸¶¹ýÈ°¼º»óÅÂ.
#define _LIGHT_ACTIVE				1			// ¸¶¹ý±¤¿øÈ°¼º»óÅÂ.
#define _MAGIC_FINISH				2			// ¸¶¹ý¼Ò¸ê.

#define _SKILL_FIREBALL				1			// È­¿°Àå.
#define _SKILL_HEALLING				2			// È¸º¹¼ú.
#define _SKILL_ONESWORD				3			// ¿Ü¼ö.
#define _SKILL_ILKWANG				4			// ÀÏ±¤.
#define _SKILL_FIREBALL2			5			// ±Ý°­È­¿°Àå.
#define _SKILL_AMYOUNSUL			6			// ¾Ï¿¬¼ú.
#define _SKILL_YEDO					7			// ¿¹µµ.
#define _SKILL_FIREWIND				8			// È­¿°Ç³.
#define _SKILL_FIRE					9			// ¿°»çÀå.
#define _SKILL_SHOOTLIGHTEN			10			// ·ÚÀÎÀå.
#define _SKILL_LIGHTENING			11			// °­°Ý.
#define _SKILL_ERGUM				12			// ¾î°Ë¼ú.
#define _SKILL_FIRECHARM			13			// Æø»ì°è.
#define _SKILL_HANGMAJINBUB			14			// Ç×¸¶Áø¹ý.
#define _SKILL_DEJIWONHO			15			// ´ëÁö¿øÈ£.
#define _SKILL_HOLYSHIELD			16			// °á°è.
#define _SKILL_SKELLETON			17			// ¹é°ñ¼ÒÈ¯¼ú.
#define _SKILL_CLOAK				18			// Àº½Å.
#define _SKILL_BIGCLOAK				19			// ´ëÀº½Å.
#define _SKILL_TAMMING				20			// ·ÚÈ¥°Ý.
#define _SKILL_SPACEMOVE			21			// ¾Æ°øÇà¹ý.
#define _SKILL_EARTHFIRE			22			// Áö¿°¼ú.
#define _SKILL_FIREBOOM				23			// Æø¿­ÆÄ.
#define _SKILL_LIGHTFLOWER			24			// ·Ú¼³È­.
#define _SKILL_BANWOL				25			// ¹Ý¿ù.
#define _SKILL_FIRESWORD			26			// ¿°È­°á.
#define _SKILL_MOOTEBO				27			// ¹«ÅÂº¸.
#define _SKILL_SHOWHP				28			// Å½±âÆÄ¿¬.
#define _SKILL_BIGHEALLING			29			// ´ëÈ¸º¹.
#define _SKILL_SINSU				30			// ½Å¼ö¼ÒÈ¯.
#define _SKILL_SHIELD				31			// ÁÖ¼úÀÇ¸·.
#define _SKILL_KILLUNDEAD			32			// »çÀÚÀ±È¸.
#define _SKILL_SNOWWIND				33			// ºù¼³Ç³.

#define _SKILL_JUMPSHOT				33			// Á¡ÇÁÇØ¼­Ä¡±â °Ë±â.
#define _SKILL_RANDSWING			34			// ¸¶±¸ ÈÖµÎ¸£±â.
#define _SKILL_SPACEMOVE2			35			// ¾Æ°øÇà¹ý2.
#define _SKILL_SPACEMOVE3			36			// ¾Æ°øÇà¹ý3.

#define _MONMAGIC_KEPAL				100			// Àü°Ý°ø°Ý.(°ø°ÝÇÑ Ä³¸¯ÅÍÀ§¿¡)(¸¶¹ý)
#define _MONMAGIC_EXPLODE			101			// Æø¹ß¸¶¹ý.(µ¹°ñ·½Á×À»¶§, ·Ð°ø°Ý½Ã)
#define _MONMAGIC_BLACK1			102			// Èæ¸¶¹ý»ç. (¸¶¹ý(½ÃÀü))
#define _MONMAGIC_BLACK2			103			// Èæ¸¶¹ý»ç. (¸¶¹ý(¸¶¹ý))
#define _MONMAGIC_DIE				104			// Èæ¸¶¹ý»ç, °æ°©¿Ê±â»ç, È«¸¶¹ý»ç, ½Å±â¼±º¸½ºº¯½ÅÀü Á×À½.(È¿°ú)
#define _MONMAGIC_ANTHEAL			105			// Ä¡À¯°³¹ÌÈú¸µ(¹ß»ç¸¶¹ý, Æø¹ßÈ¿°ú.)
#define _MONMAGIC_GREATANT			106			// °Å´ë°³¹Ì.(°ø°ÝÇÑ Ä³¸¯ÅÍÀ§¿¡)(¸¶¹ý)
#define _MONMAGIC_MAGENUMA			108			// °á°è.
#define _MONMAGIC_ANT				109			// º´Á¤°³¹Ì°ø°Ý.(°ø°ÝÇÑ Ä³¸¯ÅÍÀ§¿¡)(¸¶¹ý)
#define _MONMAGIC_WORKANT			110			// ÀÏ°³¹Ì°ø°Ý.(°ø°ÝÇÑ Ä³¸¯ÅÍÀ§¿¡)(¸¶¹ý)
#define _MONMAGIC_RED1				111			// È«¸¶¹ý»ç. (¸¶¹ý(½ÃÀü))
#define _MONMAGIC_RED2				112			// È«¸¶¹ý»ç. (¸¶¹ý(¸¶¹ý))
#define _MONMAGIC_COWGHOST			113			// ¿ì¸é±Í. (¸¶¹ý)
#define _MONMAGIC_SINSU				114			// ½Å¼ö. (¸¶¹ý)
#define _MONMAGIC_ZOMBIE			115			// Á»ºñ. (¸¶¹ý)
#define _MONMAGIC_JUMAWANG			116			// ÁÖ¸¶¿Õ. (¸¶¹ý)
#define _MONMAGIC_CHIM				117
#define _MONMAGIC_ARROW				118
#define _MONMAGIC_MAARROW			119
#define _MONMAGIC_DUALAXE			120
#define _MONMAGIC_COWFLAME			121
#define _MONMAGIC_BIGGINE_ATT		122
#define _MONMAGIC_BIGGINE_CHAR		123
#define _MONMAGIC_SANDFISH			124
#define _MONMAGIC_BAODIE			125
#define _MONMAGIC_SINGI_DIE			126
#define _MONMAGIC_HUSU_DIE			127
#define _MONMAGIC_ZOMBIE_DIE		128
#define _MONMAGIC_SSEGI				129
#define _MONMAGIC_NUMAGUMGI			130
#define _MONMAGIC_EXPLODE1			131

#define _BLEND_NORMAL				0			// ÀÏ¹ÝÀûÀÎ±×¸®±â.(¾ËÆÄ°ªÀÌ Àû¿ëµÉ¼öÀÖ´Ù.)
#define _BLEND_LIGHT				1			// ¼¶±¤È¿°úÇüÅÂÀÇ ºí·»µù.
#define _BLEND_LIGHTINV				2	
#define _BLEND_INVNORMAL			3
#define _BLEND_INVLIGHT				4
#define _BLEND_INVLIGHTINV			5




/******************************************************************************************************************
	#1. Map Handler
*******************************************************************************************************************/

#define _BASETILE_WIDTH				96				// ±âº»Å¸ÀÏ ³ÐÀÌ.
#define _BASETILE_HEIGHT			64
	
#define _CELL_WIDTH					48				// ±âº»¼¿ ³ÐÀÌ, ±âº»Å¸ÀÏÀº 4°³ÀÇ ¼¿·Î ÀÌ·ç¾îÁö°í Á¤º¸´Â ¼¿´ÜÀ§·Î ÀúÀåµÈ´Ù.
#define _CELL_HEIGHT				32

#define _VIEW_CELL_X_COUNT			24				// ºä¿µ¿ª¿¡ ÇÊ¿äÇÑ XÃàÀÇ ¼¿´ÜÀ§ °³¼ö.((Â¥Åõ¸® Å¸ÀÏÁ¦¿Ü)ÁÂ¿ÍÀ§·Î 3¼¿, ¿ì¿Í¾Æ·¡·Î 2¼¿¾¿ÀÇ ¿©À¯¸¦ µÐ´Ù.)
#define _VIEW_CELL_Y_COUNT			24			
#define _VIEW_CELL_Y_COUNT_FOR_OBJ	44

#define _VIEW_CELL_X_START			-200			// ºä¿µ¿ªÀ» ±×¸®±â À§ÇÑ ½ÃÀÛ ¼¿ XÁÂÇ¥.
#define _VIEW_CELL_Y_START			-157
#define _MAX_TILE_FILE				69

// Æ÷±×»ö °ü·Ã ¼Ó¼º.
#define _FOG_COLOR_TYPE0			RGB(0, 0, 0);
#define _FOG_COLOR_TYPE1			RGB(100, 10, 10);
#define _FOG_COLOR_TYPE2			RGB(10, 255, 10);
#define _FOG_COLOR_TYPE3			RGB(10, 10, 255);

// ¼Ó¼º °ü·Ã Á¤ÀÇ.
#define _CAN_WALK					0
#define _CAN_NOTWALK	 			1
#define _CAN_FLY					0
#define _CAN_NOTFLY					1

// ¶óÀÌÆ® Å©±â °ü·Ã Á¤ÀÇ.
#define _LIGHT_SIZE_TYPE0			3
#define _LIGHT_SIZE_TYPE1			4
#define _LIGHT_SIZE_TYPE2			5
#define _LIGHT_SIZE_TYPE3			6

// ¶óÀÌÆ® »ö °ü·Ã Á¤ÀÇ.
#define _LIGHT_COLOR_TYPE0			RGB(255, 0, 0);
#define _LIGHT_COLOR_TYPE1			RGB(0, 255, 0);
#define _LIGHT_COLOR_TYPE2			RGB(0, 0, 255);
#define _LIGHT_COLOR_TYPE3			RGB(255, 0, 255);

// ¹®°ü·Ã Á¤ÀÇ.
#define _DOOR_ISCLOSED				0
#define _DOOR_ISOPEN				1

#define _TILE_ANI_DELAY_1			150
#define _TILE_ANI_DELAY_2			200
#define _TILE_ANI_DELAY_3			250
#define _TILE_ANI_DELAY_4			300
#define _TILE_ANI_DELAY_5			350
#define _TILE_ANI_DELAY_6			400
#define _TILE_ANI_DELAY_7			420
#define _TILE_ANI_DELAY_8			450






/******************************************************************************************************************
	#1. Status Window
*******************************************************************************************************************/
#define _TYPE_EQUIP					0
#define _TYPE_STATUS				1
#define _TYPE_SETMAGIC				2

#define _EQUIP_MAX_CELL				11
#define _MAGIC_MAX_CELL				5
#define _MAGIC_MAX_KEY				8

#define _MAX_TYPE_WND				3

#define _MAX_STAUTS_BTN				3

#define _BTN_ID_STATUSCLOSE			0
#define _BTN_ID_STATUS				1
#define _BTN_ID_STATUSMAGIC			2

#define _BTN_ID_STATUS_X			187
#define _BTN_ID_STATUS_Y			266
#define _BTN_ID_STATUSMAGIC_X		224
#define _BTN_ID_STATUSMAGIC_Y		98

#define _EQUIP_CHAR_X				100
#define _EQUIP_CHAR_Y				200

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
#define _U_SHOES					10
#define _U_UNEQUIP					100

#define _MAX_MAGIC_SKILL			32




/******************************************************************************************************************
	#1. Store Window
*******************************************************************************************************************/
#define _STORE_STATE_SELL			0
#define _STORE_STATE_BUY			1






/******************************************************************************************************************
	#1. Client To Server Message
*******************************************************************************************************************/
#define CM_QUERYUSERNAME			80
#define CM_QUERYBAGITEMS			81
#define CM_DROPITEM					1001
#define CM_PICKUP					1000	//¹âÍ¨,¼ñÎï
//#define CM_DROPITEM					1000
//#define CM_PICKUP					1001

#define CM_TAKEONITEM				1003
#define CM_TAKEOFFITEM				1004
#define CM_EAT						1006
#define CM_MAGICKEYCHANGE			1008
#define CM_LOGINNOTICEOK			1018
#define CM_GROUPMODE				1019	// ×éÃüÁî
#define CM_CREATEGROUP				1020	// ×éÃüÁî
#define CM_ADDGROUPMEMBER			1021	// ×éÃüÁî
#define CM_DELGROUPMEMBER			1022	// ×éÃüÁî
#define CM_TRUN						3010	//×ªÉí
#define CM_WALK						3011	//×ß
#define CM_RUN						3013	//ÅÜ
#define CM_HIT						3014	//¹¥»÷
#define CM_FORCEHIT					3015	//Ç¿Á¦¹¥»÷
#define CM_LONGHIT					3019
#define CM_POWERHIT					3018
#define CM_SPELL					3017	//Ê¹ÓÃÄ§Öä Ä§·¨
#define CM_WIDEHIT					3024
#define CM_FIREHIT					3025
#define CM_SAY						3030
#define CM_RIDE						3031

#define CM_BUTCH					1007
#define CM_SITDOWN					3012
#define	CM_CLICKNPC					1010
#define	CM_OPENDOOR					1002


// °øÅë
#define	CM_CLICKNPC					1010	// ÀÌ ¸Þ½ÃÁö¸¦ ¼­¹ö·Î º¸³»¾î ÇØ´ç MPCÀÇ Á¤º¸¸¦ ¹Þ´Â´Ù.
#define	CM_MERCHANTDLGSELECT		1011	// »ç¿ëÀÚ°¡ NPC´ëÈ­Áß Tag°¡ Á¸ÀçÇÏ´Â ºÎºÐÀ» ClickÇßÀ»°æ¿ì º¸³»¾îÁø´Ù.
// ÆÈ±â
#define	CM_MERCHANTQUERYSELLPRICE	1012	// ÆÈ±â ¹°°ÇÀ» ¿Ã·Á ³õÀ» °æ¿ì °¡°ÝÀ» ¾ò´Â´Ù.  
											// º¯°æÇÒ ÇÊ¿ä°¡ ÀÖÀ½ (°ú°Å: ÆÈ¹°°ÇÀÇ °¡°Ý¸¸ Ç¥½Ã, ÇöÀç: ÆÈ¸®´Â ¹°°ÇÀÇ °¢°Ü ¸ðµÎÇ¥½Ã)
#define CM_USERSELLITEM				1013	// ÆÈ±â ¹öÆ°À» ´­·ÈÀ» °æ¿ì (°ú±â: ÆÈ¹°°Ç¸¸ ÇÏ³ª¸¸ º¸³¿, ÇöÀç: ÆÈ¹°°Ç ¸ðµÎ º¸³¿

// »ç±â
#define CM_USERBUYITEM				1014	// »ç±â ¹öÆ°À» ´­·ÈÀ» °æ¿ì
#define CM_USERGETDETAILITEM		1015	// »óÁ¡ ¸ñ·ÏÁß¿¡ Sub Menu°¡ ÀÖ´Â °ÍÀ» Å¬¸¯ÇßÀ» °æ¿ì

// ¼ö¸®
#define	CM_USERREPAIRITEM			1023	// ¼ö¸®ÇÏ´Ù ¹öÆ°À» ´­·¶À» °æ¿ì
#define	CM_MERCHANTQUERYREPAIRCOST	1024	// ¼ö¸®ÇÒ¾ÆÀÌÅÛÀ» ¿Ã·Á ³õÀ» °æ¿ì °¡°ÝÀ» ¾ò´Â´Ù.

// ¾à¹æ
#define CM_USERMAKEDRUGITEM			1034	// 


// ¿©°ü
#define	CM_USERSTORAGEITEM			1031	// »ç¿ëÀÚ°¡ ¸º±ä´Ù ¹öÆ°(ÅØ½ºÆ® ¹öÆ° ¾Æ´Ô)À» ´­·¶À» °æ¿ì º¸³»¾îÁø´Ù.
#define	CM_USERTAKEBACKSTORAGEITEM	1032	// »ç¿ëÀÚ°¡ Ã£´Â´Ù ¹öÆ°(ÅØ½ºÆ® ¹öÆ° ¾Æ´Ô)À» ´­·¶À» °æ¿ì º¸³»¾îÁø´Ù.

// ¹®ÆÄ
#define	CM_OPENGUILDDLG				1035	// »ç¿ëÀÚ°¡ ¹®ÆÄÃ¢À» ¿­°íÀÚ ÇßÀ» °æ¿ì º¸³»¾îÁø´Ù.
#define CM_GUILDHOME				1036	// »ç¿ëÀÚ°¡ ¹®ÆÄÃ¢Áß HOME ¹öÆ°À» ´­·¶À» °æ¿ì º¸³»¾îÁø´Ù.
#define	CM_GUILDMEMBERLIST			1037	// »ç¿ëÀÚ°¡ ¹®ÆÄÃ¢Áß ¹®¿øLIST¸¦ º¸°íÀÚ ÇÞÀ» °æ¿ì
#define CM_GUILDADDMEMBER			1038	// »ç¿ëÀÚ°¡ ¹®¿øÃß°¡¸¦ ÇßÀ» °æ¿ì
#define	CM_GUILDDELMEMBER			1039	// »ç¿ëÀÚ°¡ ¹®¿ø»èÁ¦¸¦ ÇßÀ» °æ¿ì
#define	CM_GUILDUPDATENOTICE		1040	// »ç¿ëÀÚ°¡ ¹®ÆÄ°øÁö¸¦ ¼öÁ¤ ÇßÀ» °æ¿ì
#define	CM_GUILDUPDATERANKINFO		1041	// »ç¿ëÀÚ°¡ ¹®¿øÁ÷À§¸¦ ¼öÁ¤ÇßÀ» °æ¿ì
#define CM_GUILDMAKEALLY			1044	// »ç¿ëÀÚ°¡ ¹®ÆÄµ¿¸ÍÀ» ÇßÀ» °æ¿ì
#define CM_GUILDBREAKALLY			1045	// »ç¿ëÀÚ°¡ ¹®ÆÄµ¿¸ÍÆÄ±â¸¦ ÇßÀ»°æ¿ì

//Ð¡µØÍ¼
#define CM_MINIMAP					1033	//ÇëÇóÐ¡µØÍ¼


/******************************************************************************************************************
	#1. Server To Client Message
*******************************************************************************************************************/
//Í¬²½¶¯×÷ UpdatePacketState()
#define SM_RUSH						6		//³å×².
#define SM_FIREHIT					8		//»ðÇò´ò»÷
#define SM_POWERHIT					18		//Ç¿Á¦´ò»÷
#define SM_BACKSTEP					9		//ºóÍË
#define SM_TURN						10		//×ªÉí
#define SM_WALK						11		//×ß
#define SM_RUN						13		//ÅÜ
#define SM_HIT						14		//´ò»÷
#define SM_SPELL					17		//ÓÃ·û´ò»÷
#define SM_LONGHIT					19		//³¤¾à´ò»÷
#define SM_DIGUP					20		//ÍÚ(ÏòÉÏ)
#define SM_DIGDOWN					21		//ÍÚ(ÏòÏÂ)
#define SM_FLYAXE					22		//·É¸«Í·(÷¼÷Ã½«¾üµÄ¶¯×÷)
#define SM_LIGHTING					23		//ÉÁµç
#define SM_WIDEHIT					24		//´ó·¶Î§´ò»÷
#define SM_DISAPPEAR				30		//ÏûÊ§  ProcessDefaultPacket()
#define SM_STRUCK					31		//±»¹¥»÷
#define SM_DEATH					32		//ËÀÍö
#define SM_NOWDEATH					34		//ËÀÍö
#define SM_FEATURECHANGED			41		//ÍâÃ²¸Ä±ä
#define SM_USERNAME					42		//½ÇÉ«Ãû

#define SM_MAGICFIRE				638		// Ä§·¨»ðÇò?
#define SM_CHANGELIGHT				654		//¹âÏß¸Ä±ä

//OnSocketMessageRecieve()
#define SM_WINEXP					44		//»ñµÃ¾­ÑéÖµ
#define SM_LEVELUP					45		//Éý¼¶ÁË
#define SM_DAYCHANGING				46		//ÌìÁÁ/ºÚ
#define SM_LOGON					50		//ÒÑ¾­µÇÂ½
#define SM_NEWMAP					51		//ÐÂµØÍ¼(µÚÒ»·ùµØÍ¼)
#define SM_ABILITY					52		//¼¼ÄÜ(µÈ¼¶,½ðÇ®,Ñª,Ä§·¨,·ÀÓù...)
#define SM_HEALTHSPELLCHANGED		53		//Ñª/Ä§·¨¸Ä±ä UpdatePacketState()
#define SM_MAPDESCRIPTION			54		//µØÍ¼Ãû

#define SM_HEAR						40		//ÁÄÌìÐÅÏ¢
#define SM_MONSTERSAY				1501	//¹ÖÎï
#define SM_SYSMESSAGE				100		//ÏµÍ³ÏûÏ¢
#define SM_GROUPMESSAGE				101		//×éÏûÏ¢
#define SM_CRY						102		//ÏûÏ¢
#define SM_WHISPER					103		//ÃÜ
#define SM_GUILDMESSAGE				104		//ÐÐ»áÏûÏ¢

#define SM_ADDITEM					200		//Ìí¼ÓÒ»¼þÎïÆ·µ½°ü¹ü
#define SM_BAGITEMS					201		//°ü¹ü
#define SM_ADDMAGIC					210		//ÐÂÔöÄ§·¨¼¼ÄÜ,±£´æÔÚm_xInterface.m_xStatusWnd.m_pstMyMagic,Ó¦¸ÃºÍ¶Ô»°¿ò·ÖÀë
#define SM_SENDMYMAGIC				211		//Ä§·¨(È«²¿)

#define SM_DROPITEM_SCCESS			600		//ÈÓ¶«Î÷³É¹¦
#define SM_DROPITEM_FAIL			601		//ÈÓ¶«Î÷Ê§°Ü
#define SM_ITEMSHOW					610		//ÎïÆ·³öÏÖ,ÐèÒª¼ì²éitem listÖÐÊÇ·ñ´æÔÚ
#define SM_ITEMHIDE 				611		//ÎïÆ·Òþ²Ø,´ÓlistÖÐÉ¾³ý
#define SM_TAKEON_OK				615		//´©´÷³É¹¦
#define SM_TAKEON_FAIL				616		//´©´÷Ê§°Ü
#define SM_DOOROPEN					612		//¿ªÃÅ
#define SM_TAKEOFF_OK				619		//Ð¶ÏÂ³É¹¦
#define SM_TAKEOFF_FAIL				620		//Ð¶ÏÂÊ§°Ü
#define SM_SENDUSEITEMS				621		//ÏÔÊ¾±ðÈËµÄ×°±¸
#define SM_WEIGHTCHANGED			622		//ÖØÁ¿¸Ä±ä
#define SM_CHANGEMAP				634		//¸ü»»µØÍ¼
#define SM_CLEAROBJECT				633		//ÈËÎï,¹ÖÎïÏûÊ§
#define SM_EAT_OK					635		//ºÈÒ©
#define SM_EAT_FAIL					636		//ºÈÒ©Ê§°Ü
#define SM_MAGIC_LVEXP				640		//Ä§·¨Éý¼¶(Ð¡»ðÇò->´ó»ðÇò)
#define SM_DURACHANGE				642		//Item³Ö¾Ã¸Ä±ä
#define SM_GOLDCHANGE				653		//Gold¸Ä±ä

#define SM_CHANGENAMECOLOR			656		//Ãû×ÖÑÕÉ«¸Ä±ä
#define SM_CHARSTATUSCHANGE			657		//×´Ì¬¸Ä±ä UpdatePacketState()
#define SM_SENDNOTICE				658		//µÇÂ½Ê±µÄNotice

#define SM_CREATEGROUP_OK			660		//´´½¨×é³É¹¦
#define SM_CREATEGROUP_FAIL			661		//´´½¨×éÊ§°Ü
#define SM_GROUPCANCEL				666		//È¡Ïû×é
#define SM_GROUPMEMBERS				667		//×éÔ±

#define SM_CHANGEGUILDNAME			750		//ÐÐ»áÃû¸Ä±ä
#define SM_SUBABILITY				752		//¼¼ÄÜ2

#define SM_SHOWEVENT				804
#define SM_HIDEEVENT				805

#define SM_DELITEM					202
#define SM_DELITEMS					203

#define SM_CLOSEHEALTH				1101
#define SM_OPENHEALTH				1100
#define SM_SITDOWN					12
#define SM_BUTCH					637
#define SM_SKELETON					33		// SM_DEATH¿Í µ¿ÀÏ.
#define SM_CHANGEFACE				1104;

#define SM_OPENDOOR_OK				612
#define SM_OPENDOOR_LOCK			613
#define SM_CLOSEDOOR				614

#define SM_MERCHANTSAY				643		//merchant-ÉÌÈË NPC¶Ô»°
#define	SM_MERCHANTDLGCLOSE			644		//¹Ø±ÕNPC¶Ô»°
#define SM_SENDGOODSLIST			645
#define SM_SENDUSERSELL				646
#define	SM_SENDBUYPRICE				647		//send buy price
#define SM_USERSELLITEM_OK			648		//³öÊÛ³É¹¦
#define SM_USERSELLITEM_FAIL		649		//³öÊÛÊ§°Ü
#define	SM_BUYITEM_SUCCESS			650		//Âò³É¹¦
#define SM_BUYITEM_FAIL				651		//ÂòÊ§°Ü
#define SM_SENDDETAILGOODSLIST		652		//ÏêÏ¸goods list
#define	SM_GOLDCHANGED				653		//½ð±Ò¸Ä±ä
#define	SM_OPENGUILDDLG				753		//´ò¿ªÐÐ»á¶Ô»°¿ò
#define	SM_OPENGUILDDLG_FAIL		754		//´ò¿ªÐÐ»á¶Ô»°¿ò-Ê§°Ü
#define	SM_SENDGUILDHOME			755		//
#define	SM_SENDGUILDMEMBERLIST		756		//ÏÔÊ¾ÐÐ»á³ÉÔ±
#define	SM_GUILDADDMEMBER_OK		757		//Ìí¼ÓÐÐ»á³ÉÔ±
#define	SM_GUILDADDMEMBER_FAIL		758		//Ìí¼ÓÐÐ»á
#define	SM_GUILDDELMEMBER_OK		759		//É¾³ýÐÐ»á³ÉÔ±
#define	SM_GUILDDELMEMBER_FAIL		760
#define	SM_GUILDRANKUPDATE_FAIL		761
#define	SM_BUILDGUILD_OK			762
#define	SM_BUILDGUILD_FAIL			763
#define	SM_GUILDMAKEALLY_OK			768
#define	SM_GUILDMAKEALLY_FAIL		769
#define	SM_GUILDBREAKALLY_OK		770
#define	SM_GUILDBREAKALLY_FAIL		771
#define	SM_DLGMSG					772


#define	SM_AREASTATE				708
#define	SM_RIDEHORSE				1300

#define SM_DECODEKEY				1330	//½âÃÜµÄÃÜÔ¿

//Î´¶¨ÒåµÄÏûÏ¢
#define SM_INVENTITEM				1313	//ÎïÆ·¸Ä±ä,Ö¸ºì/À¼/Ëæ»ú¾íµÈ³ÉÀ¦µÄÎïÆ· ,Ôö¼Ó,¼õÉÙ¶¼ÓÐÏûÏ¢
#define SM_639						639
#define SM_709						709		//ËÀºóµÄÏûÏ¢
#define SM_803						803		//°üº¬×ø±êÐÅÏ¢
#define SM_801						801		//
#define SM_807						807		//
#define SM_1104						1104	//
#define SM_1318						1318
#define SM_1323						1323
#define SM_1401						1401


/******************************************************************************************************************
	Resource Dll string index
*******************************************************************************************************************/
#define PUNISHMENT_ID_USING             1
#define PUNISHMENT_ID_THEFT             2
#define PUNISHMENT_DISTURB_GAME         3
#define PUNISHMENT_BBS_CURSES           4
#define PUNISHMENT_CONFIRMED_CURSES     5
#define PUNISHMENT_USAGE_BUG            6
#define PUNISHMENT_ASSUMED_GAMEMASTER   7
#define PUNISHMENT_SPREAD_FALLACY       8
#define NEW_ACCOUNT_HELP_ID             9
#define NEW_ACCOUNT_HELP_PWD            10
#define NEW_ACCOUNT_HELP_REPWD          11
#define NEW_ACCOUNT_HELP_NAME           12
#define NEW_ACCOUNT_HELP_SSNO           13
#define NEW_ACCOUNT_HELP_BIRTH          14
#define NEW_ACCOUNT_HELP_ZIPCODE        15
#define NEW_ACCOUNT_HELP_ADDRESS        16
#define NEW_ACCOUNT_HELP_PHONE          17
#define NEW_ACCOUNT_HELP_MOBILEPHONE    18
#define NEW_ACCOUNT_HELP_EMAIL          19
#define NEW_ACCOUNT_HELP_Q              20
#define NEW_ACCOUNT_HELP_A              21
#define NEW_ACCOUNT_WELL_DONE           22
#define ERROR_STR_LOGIN_1               23
#define ERROR_STR_LOGIN_2               24
#define ERROR_STR_LOGIN_3               25
#define ERROR_STR_LOGIN_4               26
#define ERROR_STR_NEW_ACCOUNT_1         27
#define ERROR_STR_NEW_ACCOUNT_2         28
#define ERROR_STR_NEW_ACCOUNT_3         29
#define ERROR_STR_NEW_ACCOUNT_4         30
#define ERROR_STR_NEW_ACCOUNT_5         31
#define ERROR_STR_NEW_ACCOUNT_6         32
#define ERROR_STR_NEW_ACCOUNT_7         33
#define ALRAM_CHARGE                    34
#define ALRAM_CHARGE_IP                 35
#define ALRAM_CHARGE_1                  36
#define ALRAM_CHARGE_2                  37
#define ALRAM_CHARGE_3                  38
#define CHANGE_PASSWORD                 39
#define CHANGE_PASSWORD_1               40
#define CHANGE_PASSWORD_2               41
#define CHANGE_PASSWORD_3               42
#define CHANGE_PASSWORD_4               43
#define ERROR_STR_SELECT_SERVER_1       44
#define ERROR_STR_SELECT_SERVER_2       45
#define ERROR_STR_NEWCHR_1              200
#define ERROR_STR_NEWCHR_2              201
#define ERROR_STR_NEWCHR_3              202
#define DELETE_CHARACTER_1              203
#define DELETE_CHARACTER_2              204
#define VERSION_NOT_MATCHED             205
#define ERROR_STR_START_GAME_1          206
#define ERROR_STR_DELCHR                207
#define ERROR_STR_PATCH_1               300
#define ERROR_STR_PATCH_2               301
#define ERROR_STR_SERVER_CONNECTION     302
#define NOTICE_NOT_EXIST_INDEX          400
#define NOTICE_LAST_PAGE                401
#define FATAL_ERROR_STR                 9999
#define SERVER_SELECT_TEST              10000
//////////////////////////////////////////////////////////////////////////////////////////////////////



/*******************************************************************************************************
		Login Procedure
*******************************************************************************************************/
#define _LOGIN_SCREEN_WIDTH		640
#define _LOGIN_SCREEN_HEIGHT	480


/******************************************************************************************************************
	#1. Progress States
*******************************************************************************************************************/
#define PRG_CONNECT					 -1
#define PRG_INTRO					 0
#define PRG_LOGIN					 1
#define PRG_NEW_ACCOUNT				 3
#define PRG_PATCH					 4
#define PRG_CHANGE_PASS				 5
#define	PRG_SERVER_SELE				 6
#define PRG_TO_SELECT_CHR			 7
#define	PRG_CHAR_SELE				 8
#define	PRG_CREATE_CHAR				 9
#define PRG_PLAY_GAME				10

#define PRG_SEL_TO_CREA				30
#define PRG_CREA_TO_SEL				31
#define PRG_SEL_TO_GAME				32

#define PRG_PATCH_FILES				77
#define PRG_NEED_ACCOUNT_CHANGE		88
#define PRG_QUIT					99



#endif // _DEFINE_H


