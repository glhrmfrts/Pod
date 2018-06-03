//------------------------------------------------
//--- 010 Editor v8.0 Binary Template
//
//      File: BL4.bt
//   Authors: Syroot
//   Version: 0.1.0
//   Purpose: Parse decrypted Pod BL4 (circuit) files.
//  Category: Pod
// File Mask: *.dec.bl4
//  ID Bytes: 
//   History: 
//  0.1.0   2017-10-02  Initial version.

#include "Math.c"
#include "PBDF.c"
#include "BL4_Mesh.c"
#include "BL4_Event.c"
#include "BL4_Macro.c"
#include "BL4_Texture.c"
#include "BL4_Sector.c"
#include "BL4_Visible.c"
#include "BL4_Environment.c"
#include "BL4_Light.c"
#include "BL4_Animation1.c"
#include "BL4_Sound.c";
#include "BL4_Background.c";
#include "BL4_Animation2.c";
#include "BL4_RepairZone.c";
#include "BL4_Designation.c";
#include "BL4_Difficulty.c";
#include "BL4_Competitor.c";

typedef struct // Circuit
{
	PbdfSeekOffset(0);
	uint check; // 3
	uint unused;
	EventList events <bgcolor = 0xCDE6FF>;
	MacroList macros <bgcolor = 0xBDD4EB>;
	PbdfString trackName;
	uint textureLoD[16];
	PbdfString projectName;
	TextureList textureList(256, 256, 2); // RGB565
	SectorList sectorList <bgcolor = 0xCDCDFF>;
	VisibleList visibleList <bgcolor = 0xBDBDEB>;
	EnvironmentList environmentList <bgcolor = 0xEFCDFF>;
	LightSectorList lightSectorList <bgcolor = 0xFFCDEF>;
	Animation1List animation1List <bgcolor = 0xFFCDCD>;
	SoundList soundList <bgcolor = 0xFFD6CD>;
	Background background <bgcolor = 0xFFEFCD>;
	Sky sky <bgcolor = 0xEBDCBD>;
	Animation2List animation2List <bgcolor = 0xEBBDBD>;
	RepairZoneList repairZoneList <bgcolor = 0xFFEFCD>;

	Designation designationForward <bgcolor = 0xEFFFCD>;
	Difficulty diffForward <bgcolor = 0xCDFFCD>;
	DifficultyLevel diffLevelForwardEasy <bgcolor = 0xCDFFCD>;
	PbdfSeekOffset(1);
	DifficultyLevel diffLevelForwardNormal <bgcolor = 0xCDFFCD>;
	PbdfSeekOffset(2);
	DifficultyLevel diffLevelForwardHard <bgcolor = 0xCDFFCD>;

	PbdfSeekOffset(3);
	Designation designationReverse <bgcolor = 0xEFFFCD>;
	Difficulty diffReverse <bgcolor = 0xCDFFCD>;
	DifficultyLevel diffLevelReverseEasy <bgcolor = 0xCDFFCD>;
	PbdfSeekOffset(4);
	DifficultyLevel diffLevelReverseMedium <bgcolor = 0xCDFFCD>;
	PbdfSeekOffset(5);
	DifficultyLevel diffLevelReverseHard <bgcolor = 0xCDFFCD>;

	PbdfSeekOffset(6);
	CompetitorList competitorListEasy <bgcolor = 0xCDFFEF>;
	PbdfSeekOffset(7);
	CompetitorList competitorListNormal <bgcolor = 0xCDFFEF>;
	PbdfSeekOffset(8);
	CompetitorList competitorListHard <bgcolor = 0xCDFFEF>;
} Circuit <bgcolor = 0xCDFFFF>;

LittleEndian();
local uint key = 0x00000000;
local uint blockSize <format = hex> = 0x00004000;
PbdfHeader header;
Circuit circuit <open = true>;
