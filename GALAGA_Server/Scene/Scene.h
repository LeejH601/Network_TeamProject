#pragma once

class CItem;
class CBulletList;
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
	list<class CMonster*>* m_MonsterList; // 출현할 몬스터 정보
	CBulletList* Monster_BulletList;

	class CTractor* m_Tractor = nullptr;
	class CBoss* m_boss = nullptr;

	class CPlayer* m_Player1 = NULL;		 // 플레이어1 정보 
	class CPlayer* m_Player2 = NULL;		 // 플레이어2 정보 
private:
	bool				  m_bEnable;	 // 화면 활성화 체크 변수 

	double		      m_MaxDistance; // 스테이지가 끝날 주행거리 변수 
public:
	double			  m_Distance;	 // 현재 플레이어가 움직인 거리
	bool			  m_bEndScene;	 // 해당 씬이 종료됨을 알리는 변수

private:
	bool				  m_bSlide;		//  화면에서 기준점 2를 이용해 맵을 슬라이드 해야할 때 인지 체크

	int I_MspawnDelay = 2000;			// 값이 낮을 수록 몬스터 생성빈도가 많아집니다..
	int I_MspawnCount = 0;

	int m_StageNum = 0;
	int TractorCount_Render = 0;
	float fItemSpawn = 0.5f;

public:
	// 배경 이미지 ,플레이어 , 몬스터 설정 
	bool Init(class CPlayer* player1, class CPlayer* player2, long long  MaxDistance, bool enable, int stageNum);

public:
	// list에 들어갈 몬스터를 추가합니다. 
	void AddObject(class CMonster* pMonster);


public:
	int		Update(float fDeltaTime);
	int		LateUpdate(float fDeltaTime);
	void	Collision(float fDeltaTime);


public:
	// Cscene 화면의 활성화 여부를 반환합니다.  
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
	CBulletList* GetBulletList() { return Monster_BulletList; };

	void UpdateBulletListWithBoss();

	void UpdateMaxDistance(double distance);


};

