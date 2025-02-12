#pragma once
#include "Node.h"

template<typename T>
class Iterator
{
public:
	Iterator<T>();
	Iterator<T>(Node<T>* node);

	T operator*() const;
	//Pre-Increment
	Iterator<T> operator++();
	//Post-Increment
	Iterator<T> operator++(int);
	//Pre-Decrement
	Iterator<T> operator--();
	//Post-Decrement
	Iterator<T> operator--(int);
	const bool operator==(const Iterator<T>& other) const;
	const bool operator!=(const Iterator<T>& other) const;

private:
	Node<T>* m_current;


};

template<typename T>
inline Iterator<T>::Iterator() : m_current(nullptr)
{

};

template<typename T>
inline Iterator<T>::Iterator(Node<T>* node) : m_current(node)
{

};

template<typename T>
inline T Iterator<T>::operator*() const
{
	return m_current->value;
}

//Pre-Increment
template<typename T>
inline Iterator<T> Iterator<T>::operator++()
{
	if (m_current)
	{
		m_current = m_current->next;
		return Iterator<T>(m_current);
	}
	return Iterator<T>(nullptr);
}

//Post-Increment
template<typename T>
inline Iterator<T> Iterator<T>::operator++(int)
{
	if (m_current)
	{
		m_current = m_current->next;
		return Iterator<T>(m_current);
	}
	return Iterator<T>(nullptr);
}

//Pre-Decrement
template<typename T>
inline Iterator<T> Iterator<T>::operator--()
{
	if (m_current)
	{
		m_current = m_current->previous;
		return Iterator<T>(m_current);
	}
	return Iterator<T>(nullptr);
}

//Post-Decrement
template<typename T>
inline Iterator<T> Iterator<T>::operator--(int)
{
	if (m_current)
	{
		m_current = m_current->previous;
		return Iterator<T>(m_current);
	}
	return Iterator<T>(nullptr);
}

template<typename T>
inline const bool Iterator<T>::operator==(const Iterator<T>& other) const
{
	return m_current == other.m_current;
}

template<typename T>
inline const bool Iterator<T>::operator!=(const Iterator<T>& other) const
{
	return m_current != other.m_current;
}
