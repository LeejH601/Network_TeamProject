#pragma once

class CItem;
class CScene
{
private:
	CScene();
	~CScene();
private:
	friend class CSceneManager;

private:
	std::list<CItem*> m_ItemList;

private:
	list<class CMonster*>* m_MonsterList; // ������ ���� ����
	class CBulletList* Monster_BulletList;

	class CTractor* m_Tractor = nullptr;
	class Boss* m_boss = nullptr;

	class CPlayer* m_Player1;		 // �÷��̾�1 ���� 
	class CPlayer* m_Player2;		 // �÷��̾�2 ���� 
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
	float fItemSpawn = 500.0f;
public:
	// ��� �̹��� ,�÷��̾� , ���� ���� 
	bool Init(class CPlayer* player1, class CPlayer* player2, long long  MaxDistance, bool enable, int stageNum);

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

	std::list<CItem*>* GetItemList() { return &m_ItemList; };
	void UpdateMaxDistance(double distance);


};

