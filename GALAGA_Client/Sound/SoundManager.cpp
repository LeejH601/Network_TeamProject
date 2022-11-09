#include "SoundManager.h"
//#include "../Object/ObjectManager.h"

DEFINITION_SINGLE(CSoundManager);

CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
	/*FMOD_Sound_Release(bgmSound_MainMenu);
	FMOD_Sound_Release(bgmSound_stage1);
	FMOD_Sound_Release(bgmSound_stage2);
	FMOD_Sound_Release(bgmSound_stage3);


	FMOD_Sound_Release(effectSound_WraithGood);
	FMOD_Sound_Release(effectSound_Explode1);

	FMOD_System_Release(soundSystem);*/


}

bool CSoundManager::Init()
{
	m_iObjID = m_iObjN++;
	//CObjectManager::GetInst();

	/*FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, 32, FMOD_INIT_NORMAL, NULL);


	FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme1.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_stage1);

	FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme2.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_stage2);

	FMOD_System_CreateSound(soundSystem, "./Sound/Terran_Theme3_(2).mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_stage3);

	FMOD_System_CreateSound(soundSystem, "./Sound/MainMenu_Theme.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_MainMenu);

	FMOD_System_CreateSound(soundSystem, "./Sound/WraithBulletSound.wav",
		FMOD_DEFAULT, 0, &effectSound_WraithGood);

	FMOD_System_CreateSound(soundSystem, "./Sound/Monster_Explde_1.mp3",
		FMOD_DEFAULT, 0, &effectSound_Explode1);

	FMOD_System_CreateSound(soundSystem, "./Sound/YouWin.wav",
		FMOD_LOOP_NORMAL, 0, &bgmSound_StageClear);

	FMOD_System_CreateSound(soundSystem, "./Sound/David Bowie - Starman.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_End);

	FMOD_System_CreateSound(soundSystem, "./Sound/Bossbgm1.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_Boss1);
	FMOD_System_CreateSound(soundSystem, "./Sound/Bossbgm2.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_Boss2);
	FMOD_System_CreateSound(soundSystem, "./Sound/Bossbgm3.mp3",
		FMOD_LOOP_NORMAL, 0, &bgmSound_Boss3);



	for(int i = 0 ; i < 10; ++i)
	FMOD_Channel_SetVolume(m_Explode_Sound_Channel[i], 50.0);


	CSoundManager::GetInst()->playSound(OBJECT_TYPE::OT_NONE,0);*/

	return true;

}

// 종족과 해당스테이지를 인자로 받고 해당하는 사운드  출력
bool CSoundManager::playSound(OBJECT_TYPE obType, int stageNum = 0)
{
	//switch (obType)
	//{
	//case OBJECT_TYPE::OT_NONE:
	//{
	//	//FMOD_System_PlaySound(soundSystem, bgmSound_MainMenu, NULL, 0, &bgmChannel);
	//	FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_MainMenu, false, &bgmChannel);
	//}
	//	break;
	//case OBJECT_TYPE::OT_TERRAN:
	//{
	//	stopSound();
	//
	//	if(stageNum == 1)
	//	//FMOD_System_PlaySound(soundSystem, bgmSound_stage1, NULL, 0, &bgmChannel);
	//		FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_stage1, false, &bgmChannel);
	//	else if (stageNum == 2)
	//	{
	//		//FMOD_System_PlaySound(soundSystem, bgmSound_stage2, NULL, 0, &bgmChannel);
	//		FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_stage2, false, &bgmChannel);
	//		FMOD_Channel_SetVolume(effectChannel, 1.2);
	//		FMOD_Channel_SetVolume(bgmChannel, 0.8);

	//	}
	//	else if (stageNum == 3)
	//	{
	//		//FMOD_System_PlaySound(soundSystem, bgmSound_stage3, NULL, 0, &bgmChannel);
	//		FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_stage3, false, &bgmChannel);
	//		FMOD_Channel_SetVolume(effectChannel, 0.8);
	//		FMOD_Channel_SetVolume(bgmChannel, 1.5);

	//	}
	//	else if (stageNum == 4)
	//	{
	//		//FMOD_System_PlaySound(soundSystem, bgmSound_StageClear, NULL, 0, &bgmChannel);
	//		FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_StageClear, false, &bgmChannel);
	//		FMOD_Channel_SetVolume(effectChannel, 0.8);
	//		FMOD_Channel_SetVolume(bgmChannel, 1.5);

	//	}
	//	else if (stageNum == 0)
	//	{
	//		//FMOD_System_PlaySound(soundSystem, bgmSound_End, NULL, 0, &bgmChannel);
	//		FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_End, false, &bgmChannel);
	//		FMOD_Channel_SetVolume(effectChannel, 0.8);
	//		FMOD_Channel_SetVolume(bgmChannel, 1.5);

	//	}

	//}
	//	break;
	//case OBJECT_TYPE::OT_ZERG:
	//	break;
	//case OBJECT_TYPE::OT_PROTOSS:
	//	break;
	//default:
	//	break;
	//}
	return true;
}

bool CSoundManager::stopSound()
{
	/*FMOD_Channel_Stop(effectChannel);
	FMOD_Channel_Stop(bgmChannel);

	for(int i = 0 ; i < 10 ; ++i)
	FMOD_Channel_Stop(m_Explode_Sound_Channel[i]);
*/


	return true;
}

bool CSoundManager::PlaySound_Bossbgm(int stage)
{
	stopSound();


	//switch (stage)
	//{
	//case 1 :
	//	//FMOD_System_PlaySound(soundSystem, bgmSound_Boss1, NULL, 0, &bgmChannel);
	//	FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_Boss1, false, &bgmChannel);
	//	FMOD_Channel_SetVolume(bgmChannel, 1.5);

	//	break;
	//case 2:
	//	//FMOD_System_PlaySound(soundSystem, bgmSound_Boss2, NULL, 0, &bgmChannel);
	//	FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_Boss2, false, &bgmChannel);
	//	FMOD_Channel_SetVolume(bgmChannel, 1.5);
	//	break;
	//case 3 :
	//	//FMOD_System_PlaySound(soundSystem, bgmSound_Boss3, NULL, 0, &bgmChannel);
	//	FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, bgmSound_Boss3, false, &bgmChannel);
	//	FMOD_Channel_SetVolume(bgmChannel, 1.5);
	//	break;

	//default:
	//	break;
	//}

	return true;
}

bool CSoundManager::playSound_Effect()
{

	////
	////FMOD_System_PlaySound(soundSystem, effectSound_WraithGood, NULL, 0, &effectChannel);
	//FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, effectSound_WraithGood, false, &bgmChannel);
	//
	return true;

}

bool CSoundManager::playSound_Effect_Explode()
{
	//static int Soundidx = 0;
	//
	////FMOD_System_PlaySound(soundSystem, effectSound_Explode1, NULL, 0, &m_Explode_Sound_Channel[Soundidx++]);
	//FMOD_System_PlaySound(soundSystem, FMOD_CHANNEL_FREE, effectSound_Explode1, false, &bgmChannel);
	//
	//if (Soundidx > 9)
	//	Soundidx = 0;


	return true;
}
