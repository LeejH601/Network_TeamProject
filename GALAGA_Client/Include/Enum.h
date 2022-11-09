#pragma once


// enum class 를 관리하기 위해서 생성되었습니다...

//  종족을 구분하기 위해서 생성되었습니다....
enum class OBJECT_TYPE
{
	OT_NONE,
	OT_TERRAN,
	OT_ZERG,
	OT_PROTOSS
};


// 공격력 입니다... 
enum class BULLET_ATTACK
{
	BA_STAGE1 = 120,
	BA_STAGE2 = 200,
	BT_STAGE3 = 300,

};

// 아이템 타입 입니다.... 
enum class ITEM_TYPE
{
	IT_RANDOM,
	IT_STEAMPACK,
	IT_HPUP,
	IT_INVINVIBILITY,
	IT_POWERUP

};

enum class PLAYER_TYPE
{
	PT_PLAYER,
	PT_MONSTER

};