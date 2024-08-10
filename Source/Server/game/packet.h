// find:
typedef struct SPacketGCStateCheck
{
	[...]
} TPacketGCStateCheck;

// paste below:
#ifdef __MISSION__
enum EMissionConfig
{
	HEADER_GC_MISSION = 59,
	HEADER_CG_MISSION = 79,

	MISSION_CG_SUBHEADER_OPEN = 0,
	MISSION_CG_SUBHEADER_RETURN,
	MISSION_CG_SUBHEADER_RETURN_ALL,

	MISSION_GC_SUBHEADER_SET_DATA = 0,
	MISSION_GC_SUBHEADER_SET_NPC,
	MISSION_GC_SUBHEADER_UPDATE_STATUS,
	MISSION_GC_SUBHEADER_CLOSE,
	MISSION_GC_SUBHEADER_REWARD,

	MISSION_ELIXIR_25 = 76020,
	MISSION_ELIXIR_50 = 76021,
};

typedef struct packet_mission
{
	BYTE	header;
	WORD	size;
	BYTE	subheader;
} TPacketGCMission;

typedef struct packet_client_mission
{
	BYTE	header;
	BYTE	subheader;
} TPacketCGMission;

typedef struct packet_mission_item
{
	DWORD vnum;
	BYTE count;
} TPacketGCMissionItem;

typedef struct packet_mission_affect
{
	DWORD index;
	DWORD value;
} TPacketGCMissionAffect;

typedef struct packet_mission_info
{
	TPacketGCMissionItem required_item;
	BYTE level;
	float chance;
	DWORD time;
	DWORD map_index;
	BYTE mob_count;
	BYTE affect_count;
	BYTE item_count;
} TPacketGCMissionInfo;

typedef struct packet_mission_status
{
	BYTE returned;
	time_t time;
} TPacketGCMissionStatus;
#endif