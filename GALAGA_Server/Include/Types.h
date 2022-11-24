
// 구조체를 만들고 관리합니다. 


#pragma once

// 해상도 ( 화면 크기 )
typedef struct _tagResolution
{
	unsigned int iW;
	unsigned int iH;

}RESOLUTION, * PRESOLUTION;

// DeltaTime 으로 실수를 이용해 움직일 수 있게하기 위해 만들어졌습니다. 
typedef struct _tagPosition
{
	// 실수로 잡는이유 : 소수점이 누락되면 나중에 픽셀 차이가 나게된다.
	float x, y;

	_tagPosition() :
		x(0.f), y(0.f)
	{

	}

	_tagPosition(float _x, float _y) :
		x(_x), y(_y)
	{

	}

	// 복사생성자
	_tagPosition(const _tagPosition& pos)
	{
		
		x = pos.x;
		y = pos.y;
	}
	_tagPosition(const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
	}
	//연산자 기능의 재정의
	void operator=(const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator = (const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
	}

	void operator=(float f[2])
	{
		x = f[0];
		y = f[1];
	}
	// 뒤에 const 를 붙여놔야 상수 객체에서 호출이 가능하다.

	// =========================    +     =====================
	_tagPosition operator+(const _tagPosition& pos)const
	{
		_tagPosition tpos;
		tpos.x = x + pos.x;
		tpos.y = y + pos.y;
		return tpos;
	}
	_tagPosition operator+(const POINT& pos)const
	{
		_tagPosition tpos;
		tpos.x = x + pos.x;
		tpos.y = y + pos.y;
		return tpos;
	}
	_tagPosition operator+(float f[2])const
	{
		_tagPosition tpos;
		tpos.x = x + f[0];
		tpos.y = y + f[1];
		return tpos;
	}
	_tagPosition operator+(float f)const
	{
		_tagPosition tpos;
		tpos.x = x + f;
		tpos.y = y + f;
		return tpos;
	}

	void operator += (const _tagPosition& pos)
	{
		x += pos.x;
		y += pos.y;
	}

	// =========================    -    =====================
	_tagPosition operator-(const _tagPosition& pos)const
	{
		_tagPosition tpos;
		tpos.x = x - pos.x;
		tpos.y = y - pos.y;
		return tpos;
	}
	_tagPosition operator-(const POINT& pos)const
	{
		_tagPosition tpos;
		tpos.x = x - pos.x;
		tpos.y = y - pos.y;
		return tpos;
	}
	_tagPosition operator-(float f[2])const
	{
		_tagPosition tpos;
		tpos.x = x - f[0];
		tpos.y = y - f[1];
		return tpos;
	}
	_tagPosition operator-(float f)const
	{
		_tagPosition tpos;
		tpos.x = x - f;
		tpos.y = y - f;
		return tpos;
	}


	// =========================    *    =====================
	_tagPosition operator*(const _tagPosition& pos)const
	{
		_tagPosition tpos;
		tpos.x = x * pos.x;
		tpos.y = y * pos.y;
		return tpos;
	}
	_tagPosition operator*(const POINT& pos)const
	{
		_tagPosition tpos;
		tpos.x = x * pos.x;
		tpos.y = y * pos.y;
		return tpos;
	}
	_tagPosition operator*(float f[2]) const
	{
		_tagPosition tpos;
		tpos.x = x * f[0];
		tpos.y = y * f[1];
		return tpos;
	}
	_tagPosition operator*(float f) const
	{
		_tagPosition tpos;
		tpos.x = x * f;
		tpos.y = y * f;
		return tpos;
	}


	// =========================    /    =====================
	_tagPosition operator/(const _tagPosition& pos)const
	{
		_tagPosition tpos;
		tpos.x = x / pos.x;
		tpos.y = y / pos.y;
		return tpos;
	}
	_tagPosition operator/(const POINT& pos)const
	{
		_tagPosition tpos;
		tpos.x = x / pos.x;
		tpos.y = y / pos.y;
		return tpos;
	}
	_tagPosition operator/(float f[2])const
	{
		_tagPosition tpos;
		tpos.x = x / f[0];
		tpos.y = y / f[1];
		return tpos;
	}
	_tagPosition operator/(float f)const
	{
		_tagPosition tpos;
		tpos.x = x / f;
		tpos.y = y / f;
		return tpos;
	}
}POSITION, * PPOSITION, _SIZE, * _PSIZE;


struct Telegram {
	int Sender;
	int Receiver;
	int Msg;
	LONGLONG DispatchTime;
	void* Extrainfo = nullptr;
};


inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (fabs(t1.DispatchTime - t2.DispatchTime) < 0) &&
		(t1.Sender == t2.Sender) &&
		(t1.Receiver == t2.Receiver) &&
		(t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}

	else
	{
		return  (t1.DispatchTime < t2.DispatchTime);
	}
}


enum class MESSAGE_TYPE {
	Msg_objectCreate,
	Msg_objectMove,
	Msg_playerHit,
	Msg_objectChangeState,
	Msg_playSound,
	Msg_changeScene,
	Msg_clientReady,
	END_Enum,
};


enum class MONSTER_PATTERN {
	PAT_STRAIGHT,
	PAT_STAIRS,
	PAT_RING,
	PAT_UTURN,
	END_ENUM,
	PAT_CROSS,
};