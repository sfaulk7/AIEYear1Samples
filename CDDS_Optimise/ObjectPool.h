#pragma once
#include "List.h"

template<typename T>
class ObjectPool
{
public:
	ObjectPool<T>();

	void AddToPool(T& value, int index);
	void SetInactive(T& value);
	void Activate(int index);
	int GetInactiveLength();

	List<T*> ActiveList;
	List<T*> InactiveList;

};

template<typename T>
inline ObjectPool<T>::ObjectPool()
{

}

template<typename T>
inline void ObjectPool<T>::AddToPool(T& value, int index)
{
	ActiveList.insert(&value, index);
}

template<typename T>
inline void ObjectPool<T>::SetInactive(T& value)
{
	InactiveList.pushBack(&value);
	ActiveList.remove(&value);
}

template<typename T>
inline void ObjectPool<T>::Activate(int index)
{
	ActiveList.insert(InactiveList.popFront(), index);
	
}

template<typename T>
inline int ObjectPool<T>::GetInactiveLength()
{
	return InactiveList.getLength();
}
