#pragma once
#include "../Game.h"


class CSoundManager
{

public:
// 싱글톤으로 관리합니다...
	DECLARE_SINGLE(CSoundManager);

//private:
//	FMOD_SYSTEM			* soundSystem;
//
//	FMOD_SOUND			* bgmSound_stage1;
//	FMOD_SOUND			* bgmSound_stage2;
//	FMOD_SOUND			* bgmSound_stage3;
//
//	FMOD_SOUND			* bgmSound_StageClear;
//	FMOD_SOUND			* bgmSound_MainMenu;
//	FMOD_SOUND			* bgmSound_End;
//
//	FMOD_SOUND			* bgmSound_Boss1;
//	FMOD_SOUND			* bgmSound_Boss2;
//	FMOD_SOUND			* bgmSound_Boss3;
//
//
//	FMOD_CHANNEL		* bgmChannel;
//	
//private:
//
//	FMOD_CHANNEL		* effectChannel;
//	FMOD_SOUND			* effectSound_WraithGood;
//	FMOD_SOUND			* effectSound_Explode1;
//private:
//
//	FMOD_CHANNEL		* m_Explode_Sound_Channel[10];
//
//
//
//
//


public:
	bool Init();

	// 종족과 해당스테이지를 인자로 받고 해당하는 사운드  출력
	bool playSound(OBJECT_TYPE obType, int stageNum);		// 해당 종족의 배경음악을 시작합니다...
	bool stopSound();										// 배경음악을 중지시킵니다..
	bool PlaySound_Bossbgm(int stage);


public:
	bool playSound_Effect();
	bool playSound_Effect_Explode();




};

