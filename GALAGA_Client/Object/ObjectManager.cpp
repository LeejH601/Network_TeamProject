#include "ObjectManager.h"
#include "Object.h"

DEFINITION_SINGLE(CObjectManager);

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
}

void CObjectManager::RegisterObject(CObject* NewObject)
{
	ObjectSet.insert(NewObject);
}

CObject* CObjectManager::GetObjectFromID(int id)
{
	CObject dummyObject;
	dummyObject.SetID(id);
	auto it = ObjectSet.find(&dummyObject);

	if (it != ObjectSet.end())
		return *it;

	return nullptr;
}

void CObjectManager::RemoveObject(CObject* pObject)
{
	ObjectSet.erase(pObject);
}

void CObjectManager::RemoveObject(int id)
{
	CObject* pObject = GetObjectFromID(id);
	if (!pObject)
		RemoveObject(pObject);
}
