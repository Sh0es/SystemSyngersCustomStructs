#ifndef PTR_H
#define PTR_H

#include <iostream>

using std::cin;
using std::cout;

template <class T>
class Ptr
{
	T* data;

public:

	Ptr<T>& operator =(const Ptr<T>& pp);
	Ptr<T>& operator =(Ptr<T>&& mm);
	T& operator *();
	Ptr<T>& operator &(const T& dt);

	//constructors
	Ptr();
	Ptr(const Ptr<T>& cp);
	Ptr(Ptr<T>&& mv);
	Ptr(const T& dt);
	~Ptr();
};

template <class T>
Ptr<T>& Ptr<T>::operator =(const Ptr<T>& pp)
{
	if (this == &pp) return *this;
	*data = *pp;
	return *this;
}

template <class T>
Ptr<T>& Ptr<T>::operator =(Ptr<T>&& mm)
{
	if (this != &mm)
	{
		delete data;
		data = &mm;
	}
	return *this;
}

template <class T>
Ptr<T>& Ptr<T>::operator &(const T& dt)
{
	return Ptr<T>(dt);
}

template <class T>
T& Ptr<T>::operator *()
{
	return *data;
}

template <class T>
Ptr<T>::Ptr()
{
	data = new T;
}

template <class T>
Ptr<T>::Ptr(const Ptr<T>& cp)
{
	*data = *cp;
	return *this;
}

template <class T>
Ptr<T>::Ptr(Ptr<T>&& mv)
{
	data = &mv;
	return *this;
}

template<class T>
Ptr<T>::Ptr(const T& dt)
{
	data = dt;
}

template <class T>
Ptr<T>::~Ptr()
{
	delete data;
	data = nullptr;
}

#endif	// PTR_H
