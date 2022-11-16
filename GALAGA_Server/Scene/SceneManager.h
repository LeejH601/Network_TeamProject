#pragma once
#include "../Include/Game.h"
#include "../Object/Object.h"
class CSceneManager : public CObject
{
private:
	friend class CPlayer;


public:
	// �̱������� ����
	DECLARE_SINGLE(CSceneManager);

private:
	class CScene* m_Scene_Begin;		// ���� ����
	class CScene* m_Scene_Stage1;		// STAGE 1
	class CScene* m_Scene_stage2;		// STAGE 2 
	class CScene* m_Scene_stage3;		// STAGE 3
	class CScene* m_Scene_End;			// ���� �� 

	class CScene* m_Scene_StageClear;	// ���� �߰� ��ȯ 
	class CScene* m_Scene_End1;
	class CScene* m_Scene_End2;
	class CScene* m_Scene_End3;

	int m_StageClearCount = 0;
	int NextStageNum = 0;
private:
	list<class CMonster*> m_MonsterList; // ������ ���� ����

private:
	class CPlayer* m_Player1;
	class CPlayer* m_Player2;
public:
	bool Init();
public:
	virtual void Update(float fDeltaTime);
	virtual void LateUpdate(float fDeltaTime);

	void Collision(float fDeltaTime);

	CPlayer* GetPlayer1();
	CPlayer* GetPlayer2();

	list<CMonster*>* GetMonsterList() {
		return &m_MonsterList;
	}

	// ���� ���� List �� ���� �����մϴ�. 
	void DeleteAllMonster()
	{
		m_MonsterList.clear();
	}

	void DeleteMonster(CMonster* it)
	{
		m_MonsterList.remove(it);
	}

	virtual bool HandleMessage(const Telegram& telegram);
};

