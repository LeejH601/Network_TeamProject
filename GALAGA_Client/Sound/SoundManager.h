#pragma once
#include "../Include/Game.h"
#include "../Object/Object.h"
class CSoundManager : public CObject
{
public:
	// �̱��� ����
	DECLARE_SINGLE(CSoundManager);

public:
	bool Init();

	// ������ �ش罺�������� ���ڷ� �ް� �ش��ϴ� ����  ���
	bool playSound(OBJECT_TYPE obType, int stageNum);		// �ش� ������ ��������� �����մϴ�...
	bool stopSound();										// ��������� ������ŵ�ϴ�..
	bool PlaySound_Bossbgm(int stage);


public:
	bool playSound_Effect();
	bool playSound_Effect_Explode();


};

