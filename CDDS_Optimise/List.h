#pragma once
#include "Node.h"
#include "Iterator.h"
#include <initializer_list>

template<typename T>
class List
{
public:
	//constructor
	List<T>();
	List<T>(std::initializer_list<T> list);

	// MAKE Copy constructor
	List(const List&) = default;

	// MAKE Copy assignment operator
	List& operator=(const List&) = default;

	//deconstructor
	~List<T>();

	void pushFront(const T& value);
	void pushBack(const T& value);

	T popFront();
	T popBack();
	bool insert(const T& value, int index);
	int remove(const T& value);
	T first();
	T last();
	Iterator<T> begin() const;
	Iterator<T> end() const;
	void destroy();
	int getLength() const;

private:
	Node<T>* m_head;
	Node<T>* m_tail;
	int m_length;

};

template<typename T>
inline List<T>::List() :
	m_head(nullptr),
	m_tail(nullptr),
	m_length(0)
{
}

template<typename T>
inline List<T>::List(std::initializer_list<T> list) : m_length(0), m_head(nullptr), m_tail(nullptr)
{
	if (list.size() <= 0)
		return;


	for (T item : list)
	{
		pushBack(item);
	}
}

template<typename T>
inline List<T>::~List()
{
	destroy();

	delete m_head;
	m_head = nullptr;

	delete m_tail;
	m_tail = nullptr;

}

template<typename T>
inline void List<T>::pushFront(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_length++;
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}

	m_head->previous = newNode;
	newNode->next = m_head;
	m_head = newNode;
}

template<typename T>
inline void List<T>::pushBack(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	m_length++;
	if (!m_tail)
	{
		m_head = newNode;
		m_tail = newNode;
		return;
	}

	m_tail->next = newNode;
	newNode->previous = m_tail;
	m_tail = newNode;
}

template<typename T>
inline T List<T>::popFront()
{
	if (!m_tail)
		return T();

	T value = m_head->value;

	if (!m_head->next)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
	}
	else
	{
		m_head = m_head->next;
		delete m_head->previous;
		m_head->previous = nullptr;
		m_length--;
	}

	return value;
}

template<typename T>
inline T List<T>::popBack()
{
	if (!m_tail)
		return T();

	T value = m_tail->value;

	if (!m_tail->previous)
	{
		delete m_tail;
		m_tail = nullptr;
		m_head = nullptr;
		m_length = 0;
	}
	else
	{
		m_tail = m_tail->previous;
		delete m_tail->next;
		m_tail->next = nullptr;
		m_length--;
	}

	return value;
}

template<typename T>
inline bool List<T>::insert(const T& value, int index)
{
	if (index < 0 || index > m_length) // Get rid of: index > (=)  m_length ----------------------------------------------------------------------------------------------------------
		return false;

	if (!m_tail || index == 0)
	{
		pushFront(value);
		return true;
	}

	if (index == m_length)// Get rid of: m_length (- 1) ----------------------------------------------------------------------------------------------------------
	{
		pushBack(value);
		return true;
	}

	Node<T>* node = m_head;
	for (int i = 0; i < index; i++)
	{
		if (node->next == nullptr)
			return false;

		node = node->next;
	}

	Node<T>* newNode = new Node<T>(value);
	newNode->previous = node->previous;
	newNode->next = node;
	node->previous = newNode;
	newNode->previous->next = newNode;
	m_length++;
	return true;
}

template<typename T>
inline int List<T>::remove(const T& value)
{
	//If m_tail is null then list is empty
	if (!m_tail)
		return 0;

	int count = 0;

	////If m_head's next is null
	//if (!m_head->next)
	//	return false;

	////If m_tail is equal to the value
	//if (m_tail->value == value)
	//{
	//	popBack();
	//	remove(value);
	//	return true;
	//}

	////If the list is only the head and tail
	//if (m_length <= 2)
	//	return false;

	//Iterate and remove
	Node<T>* node = m_head;
	while (node && m_tail && node != m_tail->next)
	{
		if (node->value == value)
		{
			if (node != m_head)
			{
				node->previous->next = node->next;
			}
			//If m_head is equal to the value
			else
			{
				popFront();
				node = m_head;
				count++;
				//If removed head theres no need to check tail so run next iteration of while loop
				continue;
			}

			if (node != m_tail)
			{
				node->next->previous = node->previous;
				Node<T>* temp = node;
				node = node->next;
				delete temp;

				m_length--;
				count++;
			}
			//If m_tail is equal to the value
			else
			{
				popBack();
				node = m_tail;
				count++;
			}
		}
		else
		{
			node = node->next;
		}
	}
	return count;
}

template<typename T>
inline T List<T>::first()
{
	if (!m_head)
		return T();
	return m_head->value;
}

template<typename T>
inline T List<T>::last()
{
	if (!m_tail)
		return T();
	return m_tail->value;
}

template<typename T>
inline Iterator<T> List<T>::begin() const
{
	if (!m_head)
		return Iterator<T>();
	return Iterator<T>(m_head);
}

template<typename T>
inline Iterator<T> List<T>::end() const
{
	if (!m_tail)
		return Iterator<T>();
	return Iterator<T>(m_tail->next);
}

template<typename T>
inline void List<T>::destroy()
{
	if (!m_tail)
		return;

	for (int i = 0; i < m_length; i++)
	{
		popBack();
	}

	m_head = nullptr;
	m_tail = nullptr;
	m_length = 0;
}

template<typename T>
inline int List<T>::getLength() const
{
	return m_length;
}