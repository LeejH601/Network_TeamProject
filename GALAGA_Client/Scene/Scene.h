#pragma once

class CScene
{
private:
	CScene();
	~CScene();
private:
	friend class CSceneManager;
private:
	list<class CMonster*>* m_MonsterList;
	list<class CItem*> m_ItemList;
	class CBulletList* Monster_BulletList;

	class CTractor* m_Tractor = nullptr;
	class CBoss* m_boss = nullptr;
	class CPlayer* m_MainPlayer;
	class CPlayer* m_AnotherPlayer;
private:
	CImage				m_BackImage;
	bool				m_bEnable;

	double				m_MaxDistance;
	double				m_Distance;

private:
	POSITION			m_imgLT;
	POSITION			m_imgSize;
	POSITION			m_imgRenderLT;
	POSITION			m_imgRenderSize;

	// Screen Slide 
	POSITION			m_imgLT2;
	POSITION			m_imgSize2;
	POSITION			m_imgRenderLT2;
	POSITION			m_imgRenderSize2;

	bool				m_bSlide;
	bool				m_bEndScene;

	int					I_MspawnDelay = 2000;
	int					I_MspawnCount = 0;

	int					m_StageNum = 0;
	int					TractorCount_Render = 0;

public:

	void imgLT_Move(float fDeltaTime);
	void imgLT_Move_Auto(float fDeltaTime);









	void Set_MainPlayer(CPlayer* pPlayer);
	void Set_AnotherPlayer(CPlayer* pPlayer);
public:
	bool Init(const WCHAR* imgBackText, class CPlayer* mainplayer, class CPlayer* anotherplayer, long long  MaxDistance, bool enable, int stageNum);

public:
	void AddObject(int id, OBJECT_TYPE type_Item, POSITION pos);
public:
	void	Input(float fDeltaTime, class CScene* NextScene);
	int		Update(float fDeltaTime);
	int		LateUpdate(float fDeltaTime);
	void	Collision(float fDeltaTime);
	void	Render(HDC mainhDC, HDC hDC, float fDeltaTime);

public:
	// CScene ȭ�� Ȱ��ȭ ���� ��ȯ
	bool	GetEnable() { return m_bEnable; }
	void	SetEnable(bool enable) { m_bEnable = enable; }
	int		GetCurSceneMaxDistance() { return m_MaxDistance; }
	void	UpdateMaxDistance(double distance, CScene* NextScene);

};

