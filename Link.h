#ifndef LINK_H
#define LINK_H

#include <iostream>

using std::cerr;
using std::endl;

template <class T>
class Link
{
	T data;
	Link<T>* prev;
	Link<T>* next;

public:
	//accessors
	T& get() const;
	T& right(int p) const;
	T& left(int p) const;

	//movers
	void goLeft();
	void goRight();

	//mutators
	void set(const T& dt);
	void linkRight(const Link<T>& lk);
	void linkLeft(const Link<T>& lk);

	//overloaded operators
	Link<T>& operator =(const Link<T>& lk);
	Link<T>& operator =(Link<T>&& mv);
	//Link<T>& operator ==(const Link<T>& lk);

	//constructors
	Link();
	Link(const Link<T>& cp);
	Link(Link<T>&& mv);
	Link<T>(const T& dt);
	~Link();
};

/* Accessors */

template <class T>
T& Link<T>::get() const
{
	return data;
}

template <class T>
T& Link<T>::right(int p) const
{
	Link<T>* r = this;

	while(p > 0)
	{
		if(this == nullptr)
		{
			cerr << "Error: Linked List Access Overflow" << endl;
		}
		r = this->prev();
	}
	return r->get();
}

template <class T>
T& Link<T>::left(int p) const
{
	Link<T>* l = this;

	while(p > 0)
	{
		if(this == nullptr)
		{
			cerr << "Error: Linked List Access Underflow" << endl;
		}
		l = this->next();
	}
	return l->get();
}

/* Movers */

template <class T>
void Link<T>::goRight()
{
	this = prev;
}

template <class T>
void Link<T>::goLeft()
{
	this = next;
}

/* Mutators */

template <class T>
void Link<T>::set(const T& dt)
{
	data = dt;
}

template <class T>
void Link<T>::linkRight(const Link<T>& lk)
{
	prev = &lk;
}

template <class T>
void Link<T>::linkLeft(const Link<T>& lk)
{
	next = &lk;
}

/* Assignment Operator */

template <class T>
Link<T>& Link<T>::operator =(const Link<T>& lk)
{
	if(data) delete data;
	data = lk.data;
	prev = lk.prev;
	next = lk.next;
}

template <class T>
Link<T>& Link<T>::operator =(Link<T>&& lk)
{
	if(data) delete data;
	data = lk.data;
	prev = lk.prev;
	next = lk.next;
}

/* Constructors */

template <class T>
Link<T>::Link()
{
	prev = nullptr;
	next = nullptr;
}

template <class T>
Link<T>::Link(const Link<T>& cp)
{
	data = cp.data;
	prev = cp.prev;
	next = cp.next;
}

template <class T>
Link<T>::Link(Link<T>&& mv)
{
	data = mv.data;
	prev = mv.prev;
	next = mv.next;
}

template <class T>
Link<T>::Link(const T& dt)
{
	data = dt;
	prev = nullptr;
	next = nullptr;
}

template <class T>
Link<T>::~Link()
{
	next->prev = prev;
	prev->next = next;
}


#endif	// LINK_H

