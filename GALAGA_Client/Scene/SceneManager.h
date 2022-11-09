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

	CImage images[31];
	WCHAR m_img_Text[20][50];


private:

	list<class CMonster*> m_MonsterList; // ������ ���� ����

private:
	class CPlayer* m_Player;

public:
	bool Init();
public:
	virtual void Input(float fDeltaTime);
	virtual void Update(float fDeltaTime);
	virtual void LateUpdate(float fDeltaTime);
	virtual void Render(HDC mainhDC, HDC hDC, float fDeltaTime);

	void Collision(float fDeltaTime);

	CPlayer* GetPlayer();

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

public:


	CImage* GetCimage(const WCHAR* imgText)
	{
		for (int i = 0; i < 19; i++)
		{
			if (wcscmp(imgText, m_img_Text[i]) == 0)
			{
				return &images[i];
				break;

			}
		}
		return nullptr;
	}

};
