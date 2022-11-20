#include "..\Include\Game.h"
#include "Object.h"

class CBullet : public CObject
{

	virtual bool HandleMessage(const Telegram& telegram);

	bool	GetEnable();
	void	SetEnableFalse();

private:
	bool	m_bEnable = false;
};