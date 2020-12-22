#pragma once

enum Offsets {
	SAMP_CHAT_INFO_OFFSET = 0x21A0E4,
	SAMP_CHAT_INPUT_INFO_OFFSET = 0x21A0E8,
	SAMP_KILL_INFO_OFFSET = 0x21A0EC,
	SAMP_INFO_OFFSET = 0x21A0F8,
	SAMP_MISC_INFO = 0x21A10C,
	SAMP_SCOREBOARD_INFO = 0x21A0B4,
	SAMP_COLOR_OFFSET = 0x216378,
	SAMP_DRAWING_DISTANCE = 0xD3DCC,
};

enum Statistics {
	SAMP_DRAWTEXTLABLES = 0x71471,
	SAMP_ONFOOTSENDRATE = 0xEC0A8,
	SAMP_INCARSENDRATE = 0xEC0AC,
	SAMP_AIMSENDRATE = 0xEC0B0,
};

enum Functions {
	SAMP_FUNC_ADDTOCHATWND = 0x64010,
	SAMP_FUNC_SPAWN = 0x3AD0,
	SAMP_FUNC_REQUEST_SPAWN = 0x56A0,
	SAMP_FUNC_DEATH = 0x55E0,
	SAMP_FUNC_SETSPECIALACTION = 0x30C0,
	SAMP_FUNC_SAY = 0x57F0,
	SAMP_FUNC_SENDCMD = 0x65C60,
	SAMP_FUNC_ADDCLIENTCMD = 0x65AD0,
	SAMP_FUNC_NAMECHANGE = 0xB290,
	SAMP_FUNC_RESTARTGAME = 0xA060,
	SAMP_FUNC_ENCRYPT_PORT = 0x1BC20,
	SAMP_FUNC_TOGGLECURSOR = 0x9BD30,
	SAMP_FUNC_CURSORUNLOCKACTORCAM = 0x9BC10,
	SAMP_FUNC_UPDATESCOREBOARDDATA = 0x8A10,
	SAMP_FUNC_CNETGAMEDESTRUCTOR = 0x9380,
	SAMP_FUNC_SENDINTERIOR = 0x5740,
	SAMP_FUNC_DISABLE_SCOREBOARD = 0x6A320
};

enum DialogStyle {
	DIALOG_STYLE_MSGBOX = 0,
	DIALOG_STYLE_INPUT = 1,
	DIALOG_STYLE_LIST = 2,
	DIALOG_STYLE_PASSWORD = 3,
	DIALOG_STYLE_TABLIST = 4,
	DIALOG_STYLE_TABLIST_HEADERS = 5
};

enum Gamestate {
	GAMESTATE_NONE = 0,
	GAMESTATE_WAIT_CONNECT = 9,
	GAMESTATE_DISCONNECTED = 13,
	GAMESTATE_AWAIT_JOIN = 15,
	GAMESTATE_CONNECTED = 14,
	GAMESTATE_RESTARTING = 18
};

enum PlayerState {
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_ONFOOT = 17,
	PLAYER_STATE_PASSENGER = 18,
	PLAYER_STATE_DRIVER = 19,
	PLAYER_STATE_WASTED = 32,
	PLAYER_STATE_SPAWNED = 33
};

enum Limits {
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 1000,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20
};

enum ChatMessageType {
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 2,
	CHAT_TYPE_INFO = 4,
	CHAT_TYPE_DEBUG = 8
};

enum ChatDisplayMode {
	CHAT_WINDOW_MODE_OFF = 0,
	CHAT_WINDOW_MODE_LIGHT = 1,
	CHAT_WINDOW_MODE_FULL = 2
};

enum eSendrateType {
	ONFOOTSENDRATE = 1,
	INCARSENDRATE = 2,
	AIMSENDRATE = 3
};

#pragma pack(push, 1)

struct stSAMPPools {
	struct stActorPool* pActor;
	struct stObjectPool* pObject;
	struct stGangzonePool* pGangzone;
	struct stTextLabelPool* pText3D;
	struct stTextdrawPool* pTextdraw;
	void* pPlayerLabels;
	struct stPlayerPool* pPlayer;
	struct stVehiclePool* pVehicle;
	struct stPickupPool* pPickup;
};

struct  stSAMP {
	void* pUnk0;
	struct stServerInfo* pServerInfo;
	unsigned char									byteSpace[24];
	char									szIP[257];
	char									szHostname[259];
	bool									bNametagStatus; // changes by /nametagstatus
	unsigned int								ulPort;
	unsigned int								ulMapIcons[100];
	int										iLanMode;
	int										iGameState;
	unsigned int								ulConnectTick;
	struct stServerPresets* pSettings;
	void* pRakClientInterface;
	struct stSAMPPools* pPools;
};

struct stServerInfo {
	unsigned int 								ulIP;
	unsigned short 								usPort;
	// ...
};

struct stServerPresets {
	unsigned char									byteCJWalk;
	unsigned char									byteUnk0[4];
	float									fWorldBoundaries[4];
	unsigned char									byteUnk1;
	float									fGravity;
	unsigned char									byteDisableInteriorEnterExits;
	unsigned int								ulVehicleFriendlyFire;
	unsigned char									byteUnk2[4];
	int										iClassesAvailable;
	float									fNameTagsDistance;
	unsigned char									byteUnk3;
	unsigned char									byteWorldTime_Hour;
	unsigned char									byteWorldTime_Minute;
	unsigned char									byteWeather;
	unsigned char									byteNoNametagsBehindWalls;
	unsigned char									bytePlayerMarkersMode;
	unsigned char									byteUnk4[3];
	float									fGlobalChatRadiusLimit;
	unsigned char									byteShowNameTags;
};

struct stTextDrawTransmit {
	union
	{
		unsigned char								byteFlags;
		struct
		{
			unsigned char							byteBox : 1;
			unsigned char							byteLeft : 1;
			unsigned char							byteRight : 1;
			unsigned char							byteCenter : 1;
			unsigned char							byteProportional : 1;
			unsigned char							bytePadding : 3;
		};
	};
	float									fLetterWidth;
	float									fLetterHeight;
	unsigned int								dwLetterColor;
	float									fBoxWidth;
	float									fBoxHeight;
	unsigned int								dwBoxColor;
	unsigned char									byteShadow;
	unsigned char									byteOutline;
	unsigned int								dwBackgroundColor;
	unsigned char									byteStyle;
	unsigned char									byteUNK;
	float									fX;
	float									fY;
	unsigned short								sModel;
	float									fRot[3];
	float									fZoom;
	unsigned short								sColor[2];
};

struct stTextdraw {
	char									szText[800 + 1];
	char									szString[1600 + 2];
	float									fLetterWidth;
	float									fLetterHeight;
	unsigned int								dwLetterColor;
	unsigned char									byte_unk;	// always = 01 (?)
	unsigned char									byteCenter;
	unsigned char									byteBox;
	float									fBoxSizeX;
	float									fBoxSizeY;
	unsigned int								dwBoxColor;
	unsigned char									byteProportional;
	unsigned int								dwShadowColor;
	unsigned char									byteShadowSize;
	unsigned char									byteOutline;
	unsigned char									byteLeft;
	unsigned char									byteRight;
	int										iStyle;		// font style/texture/model
	float									fX;
	float									fY;
	unsigned char									unk[8];
	unsigned int								unsigned long99B;	// -1 by default
	unsigned int								unsigned long99F;	// -1 by default
	unsigned int								index;		// -1 if bad
	unsigned char									byte9A7;	// = 1; 0 by default
	unsigned short								sModel;
	float									fRot[3];
	float									fZoom;
	unsigned short								sColor[2];
	unsigned char									f9BE;
	unsigned char									byte9BF;
	unsigned char									byte9C0;
	unsigned int								unsigned long9C1;
	unsigned int								unsigned long9C5;
	unsigned int								unsigned long9C9;
	unsigned int								unsigned long9CD;
	unsigned char									byte9D1;
	unsigned int								unsigned long9D2;
};

struct  stTextdrawPool {
	int										iIsListed[SAMP_MAX_TEXTDRAWS];
	int										iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw* textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw* playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];

};

struct stPickup {
	int										iModelID;
	int										iType;
	float									fPosition[3];
};

struct  stPickupPool {
	int										iPickupsCount;
	unsigned int								ul_GTA_PickupID[SAMP_MAX_PICKUPS];
	int										iPickupID[SAMP_MAX_PICKUPS];
	int										iTimePickup[SAMP_MAX_PICKUPS];
	unsigned char									unk[SAMP_MAX_PICKUPS * 3];
	struct stPickup							pickup[SAMP_MAX_PICKUPS];

};

struct  stPlayerPool {
	unsigned int								ulMaxPlayerID;
	unsigned short								sLocalPlayerID;
	void* pVTBL_txtHandler;
	union {
		char								szLocalPlayerName[16];
		char* pszLocalPlayerName;
	};
	int										iLocalPlayerNameLen;
	int										iLocalPlayerNameAllocated;
	struct stLocalPlayer* pLocalPlayer;
	int										iLocalPlayerPing;
	int										iLocalPlayerScore;
	struct stRemotePlayer* pRemotePlayer[SAMP_MAX_PLAYERS];
	int										iIsListed[SAMP_MAX_PLAYERS];
	unsigned int								dwPlayerIP[SAMP_MAX_PLAYERS]; // always 0
};

struct stSAMPKeys {
	unsigned char									keys_primaryFire : 1;
	unsigned char									keys_horn__crouch : 1;
	unsigned char									keys_secondaryFire__shoot : 1;
	unsigned char									keys_accel__zoomOut : 1;
	unsigned char									keys_enterExitCar : 1;
	unsigned char									keys_decel__jump : 1;			// on foot: jump or zoom in
	unsigned char									keys_circleRight : 1;
	unsigned char									keys_aim : 1;					// hydra auto aim or on foot aim
	unsigned char									keys_circleLeft : 1;
	unsigned char									keys_landingGear__lookback : 1;
	unsigned char									keys_unknown__walkSlow : 1;
	unsigned char									keys_specialCtrlUp : 1;
	unsigned char									keys_specialCtrlDown : 1;
	unsigned char									keys_specialCtrlLeft : 1;
	unsigned char									keys_specialCtrlRight : 1;
	unsigned char									keys__unused : 1;
};

struct stOnFootData {
	unsigned short								sLeftRightKeys;
	unsigned short								sUpDownKeys;
	union {
		unsigned short							sKeys;
		struct stSAMPKeys					stSampKeys;
	};
	float									fPosition[3];
	float									fQuaternion[4];
	unsigned char									byteHealth;
	unsigned char									byteArmor;
	unsigned char									byteCurrentWeapon;
	unsigned char									byteSpecialAction;
	float									fMoveSpeed[3];
	float									fSurfingOffsets[3];
	unsigned short								sSurfingVehicleID;
	short									sCurrentAnimationID;
	short									sAnimFlags;
};

struct stInCarData {
	unsigned short								sVehicleID;
	unsigned short								sLeftRightKeys;
	unsigned short								sUpDownKeys;
	union {
		unsigned short							sKeys;
		struct stSAMPKeys					stSampKeys;
	};
	float									fQuaternion[4];
	float									fPosition[3];
	float									fMoveSpeed[3];
	float									fVehicleHealth;
	unsigned char									bytePlayerHealth;
	unsigned char									byteArmor;
	unsigned char									byteCurrentWeapon;
	unsigned char									byteSiren;
	unsigned char									byteLandingGearState;
	unsigned short								sTrailerID;
	union {
		unsigned short							HydraThrustAngle[2];	//nearly same value
		float								fTrainSpeed;
	};
};

struct stAimData {
	unsigned char									byteCamMode;
	float									vecAimf1[3];
	float									vecAimPos[3];
	float									fAimZ;
	unsigned char									byteCamExtZoom : 6;		// 0-63 normalized
	unsigned char									byteWeaponState : 2;	// see eWeaponState
	unsigned char									bUnk;
};

struct stTrailerData {
	unsigned short								sTrailerID;
	float									fPosition[3];
	float									fQuaternion[4];
	float									fSpeed[3];
	float									fUnk[2];
	unsigned int								pad;
};

struct stPassengerData {
	unsigned short								sVehicleID;
	unsigned char									byteSeatID;
	unsigned char									byteCurrentWeapon;
	unsigned char									byteHealth;
	unsigned char									byteArmor;
	unsigned short								sLeftRightKeys;
	unsigned short								sUpDownKeys;
	union
	{
		unsigned short							sKeys;
		struct stSAMPKeys					stSampKeys;
	};
	float									fPosition[3];
};

struct stDamageData {
	unsigned short								sVehicleID_lastDamageProcessed;
	int										iBumperDamage;
	int										iDoorDamage;
	unsigned char									byteLightDamage;
	unsigned char									byteWheelDamage;
};

struct stSurfData {
	int										iIsSurfing;
	float									fSurfPosition[3];
	int										iUnk0;
	unsigned short								sSurfingVehicleID;
	unsigned int								ulSurfTick;
	struct stSAMPVehicle* pSurfingVehicle;
	int										iUnk1;
	int										iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};


struct stUnoccupiedData {
	unsigned short									sVehicleID;
	unsigned char									byteSeatID;
	float									fRoll[3];
	float									fDirection[3];
	float									fPosition[3];
	float									fMoveSpeed[3];
	float									fTurnSpeed[3];
	float									fHealth;
};

struct stBulletData {
	unsigned char									byteType;
	unsigned short								sTargetID;
	float									fOrigin[3];
	float									fTarget[3];
	float									fCenter[3];
	unsigned char									byteWeaponID;
};

struct stSpectatorData {
	unsigned short								sLeftRightKeys;
	unsigned short								sUpDownKeys;
	union
	{
		unsigned short							sKeys;
		struct stSAMPKeys					stSampKeys;
	};
	float									fPosition[3];
};

struct stStatsData {
	int										iMoney;
	int										iAmmo;	// ?
};

struct stHeadSync {
	float									fHeadSync[3];
	int										iHeadSyncUpdateTick;
	int										iHeadSyncLookTick;
};

struct  stLocalPlayer {
	struct stSAMPPed* pSAMP_Actor;
	unsigned short								sCurrentAnimID;
	unsigned short								sAnimFlags;
	unsigned int								ulUnk0;
	int										iIsActive;
	int										iIsWasted;
	unsigned short								sCurrentVehicleID;
	unsigned short								sLastVehicleID;
	struct stOnFootData						onFootData;
	struct stPassengerData					passengerData;
	struct stTrailerData					trailerData;
	struct stInCarData						inCarData;
	struct stAimData						aimData;
	unsigned char									byteTeamID;
	int										iSpawnSkin;
	unsigned char									byteUnk1;
	float									fSpawnPos[3];
	float									fSpawnRot;
	int										iSpawnWeapon[3];
	int										iSpawnAmmo[3];
	int										iIsActorAlive;
	int										iSpawnClassLoaded;
	unsigned int								ulSpawnSelectionTick;
	unsigned int								ulSpawnSelectionStart;
	int										iIsSpectating;
	unsigned char									byteTeamID2;
	unsigned short								usUnk2;
	unsigned int								ulSendTick;
	unsigned int								ulSpectateTick;
	unsigned int								ulAimTick;
	unsigned int								ulStatsUpdateTick;
	unsigned int								ulWeapUpdateTick;
	unsigned short								sAimingAtPid;
	unsigned short								usUnk3;
	unsigned char									byteCurrentWeapon;
	unsigned char									byteWeaponInventory[13];
	int										iWeaponAmmo[13];
	int										iPassengerDriveBy;
	unsigned char									byteCurrentInterior;
	int										iIsInRCVehicle;
	unsigned short								sTargetObjectID;
	unsigned short								sTargetVehicleID;
	unsigned short								sTargetPlayerID;
	struct stHeadSync						headSyncData;
	unsigned int								ulHeadSyncTick;
	unsigned char									byteSpace3[260];
	struct stSurfData						surfData;
	int										iClassSelectionOnDeath;
	int										iSpawnClassID;
	int										iRequestToSpawn;
	int										iIsInSpawnScreen;
	unsigned int								ulUnk4;
	unsigned char									byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	unsigned char									byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int										iSpectateID;
	int										iInitiatedSpectating;
	struct stDamageData						vehicleDamageData;

};

struct stRemotePlayerData {
	struct stSAMPPed* pSAMP_Actor;
	struct stSAMPVehicle* pSAMP_Vehicle;
	unsigned char									byteTeamID;
	unsigned char									bytePlayerState;
	unsigned char									byteSeatID;
	unsigned int								ulUnk3;
	int										iPassengerDriveBy;
	void* pUnk0;
	unsigned char									byteUnk1[60];
	float									fSomething[3];
	float									fVehicleRoll[4];
	unsigned int								ulUnk2[3];
	float									fOnFootPos[3];
	float									fOnFootMoveSpeed[3];
	float									fVehiclePosition[3];
	float									fVehicleMoveSpeed[3];
	unsigned short								sPlayerID;
	unsigned short								sVehicleID;
	unsigned int								ulUnk5;
	int										iShowNameTag;
	int										iHasJetPack;
	unsigned char									byteSpecialAction;
	unsigned int								ulUnk4[3];
	struct stOnFootData						onFootData;
	struct stInCarData						inCarData;
	struct stTrailerData					trailerData;
	struct stPassengerData					passengerData;
	struct stAimData						aimData;
	float									fActorArmor;
	float									fActorHealth;
	unsigned int								ulUnk10;
	unsigned char									byteUnk9;
	unsigned int								dwTick;
	unsigned int								dwLastStreamedInTick;	// is 0 when currently streamed in
	unsigned int								ulUnk7;
	int										iAFKState;
	struct stHeadSync						headSyncData;
	int										iGlobalMarkerLoaded;
	int										iGlobalMarkerLocation[3];
	unsigned int								ulGlobalMarker_GTAID;
};

struct stStreamedOutPlayerInfo {
	float									fPlayerPos[SAMP_MAX_PLAYERS][3];
};

struct stRemotePlayer {
	stRemotePlayerData* pPlayerData;
	int										iIsNPC;
	void* pVTBL_txtHandler;
	union
	{
		char								szPlayerName[16];
		char* pszPlayerName;
	};
	int										iNameLen;
	int										iNameAllocated;
	int										iScore;
	int										iPing;
};

template <typename T>

struct stSAMPEntity {
	void* pVTBL;
	unsigned char									byteUnk0[60]; // game CEntity object maybe. always empty.
	T* pGTAEntity;
	unsigned int								ulGTAEntityHandle;
};

struct stSAMPPed {
	int										usingCellPhone;
	unsigned char									byteUnk0[600];
	struct cPed* pGTA_Ped;
	unsigned char									byteUnk1[22];
	unsigned char									byteKeysId;
	unsigned short								ulGTA_UrinateParticle_ID;
	int										DrinkingOrSmoking;
	int										object_in_hand;
	int										drunkLevel;
	unsigned char									byteUnk2[5];
	int										isDancing;
	int										danceStyle;
	int										danceMove;
	unsigned char									byteUnk3[20];
	int										isUrinating;
};

struct  stVehiclePool {
	int										iVehicleCount;
	void* pUnk0;
	unsigned char									byteSpace1[0x112C];
	struct stSAMPVehicle* pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int										iIsListed[SAMP_MAX_VEHICLES];
	struct vehicle_info* pGTA_Vehicle[SAMP_MAX_VEHICLES];
	unsigned char									byteSpace2[SAMP_MAX_VEHICLES * 6];
	unsigned int								ulShit[SAMP_MAX_VEHICLES];
	int										iIsListed2[SAMP_MAX_VEHICLES];
	unsigned int								byteSpace3[SAMP_MAX_VEHICLES * 2];
	float									fSpawnPos[SAMP_MAX_VEHICLES][3];
	int										iInitiated;
};

struct stSAMPVehicle : public stSAMPEntity < struct vehicle_info > {
	unsigned int								bUnk0;
	struct vehicle_info* pGTA_Vehicle;
	unsigned char									byteUnk1[8];
	int										bIsMotorOn;
	int										iIsLightsOn;
	int										iIsLocked;
	unsigned char									byteIsObjective;
	int										iObjectiveBlipCreated;
	unsigned char									byteUnk2[16];
	unsigned char									byteColor[2];
	int										iColorSync;
	int										iColor_something;
};

struct stObject : public stSAMPEntity < struct object_info > {
	unsigned char									byteUnk0[2];
	unsigned int								ulUnk1;
	int										iModel;
	unsigned short								byteUnk2;
	float									fDrawDistance;
	float									fUnk;
	float									fPos[3];
	unsigned char									byteUnk3[68];
	unsigned char									byteUnk4;
	float									fRot[3];
};

struct  stObjectPool {
	int										iObjectCount;
	int										iIsListed[SAMP_MAX_OBJECTS];
	struct stObject* object[SAMP_MAX_OBJECTS];
};

struct stGangzone {
	float									fPosition[4];
	unsigned int								dwColor;
	unsigned int								dwAltColor;
};

struct stGangzonePool {
	struct stGangzone* pGangzone[SAMP_MAX_GANGZONES];
	int										iIsListed[SAMP_MAX_GANGZONES];
};

struct stTextLabel {
	char* pText;
	unsigned int								color;
	float									fPosition[3];
	float									fMaxViewDistance;
	unsigned char									byteShowBehindWalls;
	unsigned short								sAttachedToPlayerID;
	unsigned short								sAttachedToVehicleID;
};

struct  stTextLabelPool {
	struct stTextLabel						textLabel[SAMP_MAX_3DTEXTS];
	int										iIsListed[SAMP_MAX_3DTEXTS];

};

struct stChatEntry {
	unsigned int								SystemTime;
	char									szPrefix[28];
	char									szText[144];
	unsigned char									unknown[64];
	int										iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	unsigned long								clTextColor;
	unsigned long								clPrefixColor;	// or textOnly colour
};

struct stFontRenderer {
	struct ID3DXFont* m_pChatFont;
	struct ID3DXFont* m_pLittleFont;
	struct ID3DXFont* m_pChatShadowFont;
	struct ID3DXFont* m_pLittleShadowFont;
	struct ID3DXFont* m_pCarNumberFont;
	struct ID3DXSprite* m_pTempSprite;
	struct IDirect3DDevice9* m_pD3DDevice;
	char* m_pszTextBuffer;
};

struct  stChatInfo {
	int										pagesize;
	void* pUnk;
	int										iChatWindowMode;
	unsigned char									bTimestamps;
	unsigned int								iLogFileExist;
	char									logFilePathChatLog[MAX_PATH + 1];
	void* pGameUI; // CDXUTDialog
	void* pEditBackground; // CDXUTEditBox
	void* pDXUTScrollBar;
	unsigned long								clTextColor;
	unsigned long								clInfoColor;
	unsigned long								clDebugColor;
	unsigned int								ulChatWindowBottom;
	struct stChatEntry						chatEntry[100];
	stFontRenderer* m_pFontRenderer;
	ID3DXSprite* m_pChatTextSprite;
	ID3DXSprite* m_pSprite;
	IDirect3DDevice9* m_pD3DDevice;
	int										m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	struct ID3DXRenderToSurface* pID3DXRenderToSurface;
	struct IDirect3DTexture9* m_pTexture;
	struct IDirect3DSurface9* pSurface;
	struct D3DDISPLAYMODE* pD3DDisplayMode;
	int										iUnk1[3];
	int										iUnk2; // smth related to drawing in direct mode
	int										m_iRedraw;
	int										m_nPrevScrollBarPosition;
	int										m_iFontSizeY;
	int										m_iTimestampWidth;
};

typedef void(__cdecl* CMDPROC) (char*);

struct stInputInfo {
	void* pD3DDevice;
	void* pDXUTDialog;
	class _CDXUTEditBox* pDXUTEditBox;
	CMDPROC									pCMDs[SAMP_MAX_CLIENTCMDS];
	char									szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int										iCMDCount;
	int										iInputEnabled;
	char									szInputBuffer[129];
	char									szRecallBufffer[10][129];
	char									szCurrentBuffer[129];
	int										iCurrentRecall;
	int										iTotalRecalls;
	CMDPROC									pszDefaultCMD;
};

struct stKillEntry {
	char									szKiller[25];
	char									szVictim[25];
	unsigned long								clKillerColor;
	unsigned long								clVictimColor;
	unsigned char									byteType;
};

struct stKillInfo {
	int										iEnabled;
	struct stKillEntry						killEntry[5];
	int 									iLongestNickLength;
	int 									iOffsetX;
	int 									iOffsetY;

	ID3DXFont* pD3DFont;
	ID3DXFont* pWeaponFont1;
	ID3DXFont* pWeaponFont2;
	struct ID3DXSprite* pSprite;
	IDirect3DDevice9* pD3DDevice;
	int 									iAuxFontInited;
	struct ID3DXFont* pAuxFont1;
	struct ID3DXFont* pAuxFont2;
};

struct  stDialogInfo {
	void* pVTBL;
	int										iTextPoxX;
	int										iTextPoxY;
	int										iTextSizeX;
	int										iTextSizeY;
	int										iBtnOffsetX;
	int										iBtnOffsetY;
	class _CDXUTDialog* pDialog;
	class _CDXUTListBox* pList;
	class _CDXUTEditBox* pEditBox;
	int										iIsActive;
	int										iType;
	unsigned int								DialogID;
	char* pText;
	unsigned int								font;
	unsigned int								font2;
	char									szCaption[64];
	unsigned char									byteUnknown;
	int										bServerside;

};

struct stChatPlayer {
	int										iCreated;
	char									probablyTheText[256];	// text max length = 144
	unsigned int								dwTickCreated;
	unsigned int								dwLiveLength;
	unsigned int								dwColor;
	float									fDrawDistance;
	unsigned int								dwUnknown;
};

struct stMiscInfo {
	struct stAudio {
		int									iSoundState; // 0 - Finished, 1 - Loaded, 2 - Playing
	};
	struct stCamera {
		class CMatrix_Padded* matrix;
	};

	stAudio* pAudio;
	stCamera* pCamera;
	stSAMPPed* pLocalPlayerPed;
	float									fCheckpointPos[3];
	float									fCheckpointExtent[3];
	int										bCheckpointsEnabled;

	unsigned int								dwCheckpointMarker;
	float									fRaceCheckpointPos[3];
	float									fRaceCheckpointNext[3];
	float									m_fRaceCheckpointSize;
	unsigned char									byteRaceType;
	int										bRaceCheckpointsEnabled;
	unsigned int								dwRaceCheckpointMarker;
	unsigned int								dwRaceCheckpointHandle;
	int										iCursorMode;
	unsigned int								ulUnk1;
	int										bClockEnabled;
	unsigned int								ulUnk2;
	int										bHeadMove;
	unsigned int								ulFpsLimit;
	unsigned char									byteUnk3;
	unsigned char									byteVehicleModels[212];
};

struct  stScoreboardInfo {
	int										iIsEnabled;
	int										iPlayersCount;
	float									fTextOffsetX;
	float									fTextOffsetY;
	float									fScalar;
	struct IDirect3DDevice9* pDirectDevice;
	class _CDXUTDialog* pDialog;
	class _CDXUTListBox* pList;
	int										iOffset;		// ?
	int										iIsSorted;		// ?

};

struct stActorPool {
	int										iLastActorID;
	stSAMPEntity<void>* pActor[SAMP_MAX_ACTORS]; // ?
	int										iIsListed[SAMP_MAX_ACTORS];
	struct cPed* pGTAPed[SAMP_MAX_ACTORS];
	unsigned int								ulUnk0[SAMP_MAX_ACTORS];
	unsigned int								ulUnk1[SAMP_MAX_ACTORS];
};

struct stChatBubbleInfo {
	struct stChatPlayer						chatBubble[SAMP_MAX_PLAYERS];
};

#pragma pack(pop)