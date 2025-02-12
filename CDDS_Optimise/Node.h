#pragma once

template<typename T>
struct Node
{
public:
	Node<T>();
	Node<T>(T value);
	~Node<T>() = default;

public:
	T value;
	Node<T>* next;
	Node<T>* previous;
};

template<typename T>
inline Node<T>::Node() : next(nullptr), previous(nullptr)
{

}

template<typename T>
inline Node<T>::Node(T value) : next(nullptr), previous(nullptr), value(value)
{

}