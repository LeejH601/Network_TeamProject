#pragma once


// enum class �� �����ϱ� ���ؼ� �����Ǿ����ϴ�...

//  ������ �����ϱ� ���ؼ� �����Ǿ����ϴ�....
enum class TRIBE_TYPE
{
	OT_NONE,
	OT_TERRAN,
	OT_ZERG,
	OT_PROTOSS
};


// ���ݷ� �Դϴ�... 
enum class BULLET_ATTACK
{
	BA_STAGE1 = 120,
	BA_STAGE2 = 200,
	BT_STAGE3 = 300,

};

enum class OBJECT_TYPE
{
	IT_RANDOM = 0,
	IT_STEAMPACK,
	IT_HPUP,
	IT_INVINVIBILITY,
	IT_POWERUP,
	OBJ_Wraith = 10001,
	OBJ_Valkyrie,
	OBJ_Battlecruiser,
	OBJ_Dropship,
	OBJ_Vessel,
	OBJ_Mutalisk = 20001,
	OBJ_Devourer,
	OBJ_Queen,
	OBJ_Scourge,
	OBJ_Scout = 30001,
	OBJ_Corsair,
	OBJ_Carrier,
	OBJ_Arbiter,
	OBJ_BOSS_ONE,
	OBJ_BOSS_TWO,
	OBJ_BOSS_THREE,
	MONSTER_BULLET = 40001,
	PLAYER_BULLET,
	OBJ_PLAYER = 50001,	//Player
	OBJ_ANOTHER_PLAYER	//Another Player
};

enum class PLAYER_TYPE
{
	PT_PLAYER,
	PT_MONSTER

};

enum class SCENE_TYPE
{
	ST_BEGIN,
	ST_STAGE1,
	ST_STAGE2,
	ST_STAGE3,
	ST_CLEAR,
	ST_END,
};

enum class OBJECT_STATE {
	DONDESTORY,
	IDLE,
	DESTORY,
	ERASE
};

enum class SOUND_TYPE {
};