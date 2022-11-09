#pragma once
#include "../Include/Game.h"
#include "../Object/Object.h"
class CSoundManager : public CObject
{
public:
	// 싱글톤 선언
	DECLARE_SINGLE(CSoundManager);

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

