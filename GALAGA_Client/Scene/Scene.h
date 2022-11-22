#pragma once

class CScene
{
private:
	CScene();
	~CScene();
private:
	friend class CSceneManager;
private:
	list<class CMonster*>* m_MonsterList; // 출현할 몬스터 정보
	list<class CItem*> m_ItemList;
	class CBulletList* Monster_BulletList;

	class CTractor* m_Tractor = nullptr;
	class Boss* m_boss = nullptr;
	class CPlayer* m_Player;		 // 플레이어 정보 

private:
	CImage				  m_BackImage;	 // 배경 이미지
	bool				  m_bEnable;	 // 화면 활성화 체크 변수 

	double		      m_MaxDistance; // 스테이지가 끝날 주행거리 변수 
	double			  m_Distance;	 // 현재 플레이어가 움직인 거리

private:

	POSITION			  m_imgLT;		 // 이미지 파일 원본에서 출력할 이미지의 기준점
	POSITION			  m_imgSize;
	POSITION			  m_imgRenderLT;
	POSITION			 m_imgRenderSize;


	// Screen Slide 
	POSITION			  m_imgLT2;		 // 기준점 2 ( 파일의 끝에 도달할 때 )
	POSITION			  m_imgSize2;
	POSITION			  m_imgRenderLT2;
	POSITION			 m_imgRenderSize2;

	bool				  m_bSlide;		//  화면에서 기준점 2를 이용해 맵을 슬라이드 해야할 때 인지 체크
	bool				  m_bEndScene;	 // 해당 씬이 종료됨을 알리는 변수

	int I_MspawnDelay = 2000;			// 값이 낮을 수록 몬스터 생성빈도가 많아집니다..
	int I_MspawnCount = 0;

	int m_StageNum = 0;
	int TractorCount_Render = 0;

public:

	void imgLT_Move(float fDeltaTime); //출력할 원본 이미지의 기준점을 이동시킵니다. ( 플레이어가 상향키를 눌렀을 때 )
	void imgLT_Move_Auto(float fDeltaTime); // 원본 이미지의 기준점을 이동시킵니다. ( 화면이 자동으로 움직입니다. )


public:
	// 배경 이미지 ,플레이어 , 몬스터 설정 
	bool Init(const WCHAR* imgBackText, class CPlayer* player, long long  MaxDistance, bool enable, int stageNum);

public:
	// list에 들어갈 몬스터 추가
	void AddObject(class CMonster* pMonster);
	void AddItem(int id, ITEM_TYPE type_Item, POSITION pos);

public:
	void	Input(float fDeltaTime, class CScene* NextScene);
	int		Update(float fDeltaTime);
	int		LateUpdate(float fDeltaTime);
	void	Collision(float fDeltaTime);
	void	Render(HDC mainhDC, HDC hDC, float fDeltaTime);
 
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
	void UpdateMaxDistance(double distance, CScene* NextScene);
};

