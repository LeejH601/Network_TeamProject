#pragma once
#include "../Include/Game.h"

//class Compare {
//public:
//	bool operator()(const CObject* lhs, const CObject* rhs) const {
//		return lhs->GetID() < rhs->GetID();
//	}
//};

class CObject;
class CObjectManager
{
public:
	// ½Ì±ÛÅæ ¼±¾ð
	DECLARE_SINGLE(CObjectManager);
private:
	std::set<CObject*> ObjectSet;
public:
	void RegisterObject(CObject* NewObject);
	CObject* GetObjectFromID(int id);
	void RemoveObject(CObject* pObject);
	void RemoveObject(int id);
};

