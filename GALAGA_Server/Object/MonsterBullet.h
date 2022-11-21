#include "..\Include\Game.h"
#include "Bullet.h"

class CMonsterBullet : public CBullet
{

	virtual bool HandleMessage(const Telegram& telegram);

};