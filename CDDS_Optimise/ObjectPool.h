#pragma once
#include "List.h"
#include <iostream>

template<typename T>
class ObjectPool
{
public:
	ObjectPool<T>();

	void AddToPool(T& value, int index);
	void SetInactive(T& value);
	void Activate(int index);

	int ActiveListCount();
	int InactiveListCount();

private:
	List<T*> m_activeList;
	List<T*> m_inactiveList;

};

template<typename T>
inline ObjectPool<T>::ObjectPool()
{

}

template<typename T>
inline void ObjectPool<T>::AddToPool(T& value, int index)
{
	m_activeList.insert(&value, index);
}

template<typename T>
inline void ObjectPool<T>::SetInactive(T& value)
{
	m_inactiveList.pushBack(&value);
	m_activeList.remove(&value);
}

template<typename T>
inline void ObjectPool<T>::Activate(int index)
{
	m_activeList.insert(m_inactiveList.popFront(), index);
	
}

template<typename T>
inline int ObjectPool<T>::ActiveListCount()
{
	return m_activeList.getLength();
}

template<typename T>
inline int ObjectPool<T>::InactiveListCount()
{
	return m_inactiveList.getLength();
}

