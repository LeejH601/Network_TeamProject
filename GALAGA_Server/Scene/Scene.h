#pragma once

class CScene
{
private:
	CScene();
	~CScene();
private:
	friend class CSceneManager;

private:
	class CItemList* m_ItemList;


private:
	list<class CMonster*>* m_MonsterList; // ������ ���� ����
	class CBulletList* Monster_BulletList;

	class CTractor* m_Tractor = nullptr;
	class Boss* m_boss = nullptr;
	class CPlayer* m_Player;		 // �÷��̾� ���� 

private:
	bool				  m_bEnable;	 // ȭ�� Ȱ��ȭ üũ ���� 

	double		      m_MaxDistance; // ���������� ���� ����Ÿ� ���� 
	double			  m_Distance;	 // ���� �÷��̾ ������ �Ÿ�

private:
	bool				  m_bSlide;		//  ȭ�鿡�� ������ 2�� �̿��� ���� �����̵� �ؾ��� �� ���� üũ
	bool				  m_bEndScene;	 // �ش� ���� ������� �˸��� ����

	int I_MspawnDelay = 2000;			// ���� ���� ���� ���� �����󵵰� �������ϴ�..
	int I_MspawnCount = 0;

	int m_StageNum = 0;
	int TractorCount_Render = 0;
public:
	// ��� �̹��� ,�÷��̾� , ���� ���� 
	bool Init(const WCHAR* imgBackText, class CPlayer* player, long long  MaxDistance, bool enable, int stageNum);

public:
	// list�� �� ���͸� �߰��մϴ�. 
	void AddObject(class CMonster* pMonster);


public:
	int		Update(float fDeltaTime);
	int		LateUpdate(float fDeltaTime);
	void	Collision(float fDeltaTime);




public:
	// Cscene ȭ���� Ȱ��ȭ ���θ� ��ȯ�մϴ�.  
	bool GetEnable()
	{
		return m_bEnable;
	}

	void SetEnable(bool enable)
	{
		m_bEnable = enable;

	}


	int GetCurSceneMaxDistance()
	{
		return m_MaxDistance;

	}
	void UpdateMaxDistance(double distance, CScene* NextScene);


};

