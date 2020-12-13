#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>

using std::cerr;
using std::endl;
using std::istream;
using std::ostream;

template <class T>
class AList
{
	//data
	T* data;
	int size;
	int space;
	const int INCFAC = 64;

	//private mutators
	void expand();
	void trim();

public:
	//mutators
	void insert(const T& d, int p);
	void append(const T& d);
	void remove(int p);
	void popend();
	void swap(int p, int q);

	//accessors
	T& get(int p) const;
	T& get(int p);
	int getSize() const; //returns the number of elements in the array, not the amount of space allocated
	int capacity() const; //returns the amount of space available in the array
	bool isEmpty() const; //determines if there are no elements in the array

	//overloaded operators
	AList<T>& operator =(const AList<T>& cp);
	AList<T>& operator =(AList<T>&& mv);
	AList<char>& operator  =(const char* s);
	AList<T>& operator +=(const AList<T>& c);

	T& operator [](int p) {
		if (p < 0 || p > size) {
			cerr << "Error: Element Insertion Failed: Invalid array index requested." << endl;
		} else {
			return data[p];
		}
	}
	T& operator [](int p) const {
		if (p < 0 || p > size) {
			cerr << "Error: Element Insertion Failed: Invalid array index requested." << endl;
		} else {
			return data[p];
		}
	}

	bool operator ==(const AList<T>& c);
	bool operator !=(const AList<T>& c);
	bool operator >(const AList<T>& c);
	bool operator <(const AList<T>& c);
	bool operator >=(const AList<T>& c);
	bool operator <=(const AList<T>& c);

	//constructors
	AList(); //construct an empty list
	AList(const AList<T>& cp); //copy-construct
	AList(AList<T>&& mv); //move-construct
	AList(int s); //construct presized array
	AList(const char* s);
	~AList();
};

/* Mutators */

template <class T>
void AList<T>::expand()
{
	T* temp = new T[space + INCFAC];

	for (int i = 0; i < space; i++)
	{ temp[i] = data[i]; }

	delete[] data;
	data = temp;
	space += INCFAC;
}

template <class T>
void AList<T>::trim() {
	T* temp = new T[space - INCFAC];

	for (int i = 0; i < space; i++)
	{ temp[i] = data[i]; }

	delete[] data;
	data = temp;
	space -= INCFAC;
}

template <class T>
void AList<T>::append(const T& d)
{
	if (size == space) expand();

	data[size] = d;
	++size;
}

template <class T>
void AList<T>::insert(const T& d, int p)
{
	if (p < 0 || p > size) cerr << "Error: Element Insertion Failed: Invalid array index requested." << endl;
	else
	{
		data[p] = d;
	}
}

template <class T>
void AList<T>::remove(int p)
{
	for(int i = p; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
	delete &(data[size - 1]);
	--size;

	if (space - size >= INCFAC * 1.5) trim();
}

template <class T>
void AList<T>::popend()
{
	if (size < 1) cerr << "Error: `popend()` Operation Failed: List is empty." << endl;
	else
	{
		delete &(data[size - 1]);
		--size;

		if (space - size >= INCFAC * 1.5) trim();
	}
}

template <class T>
void AList<T>::swap(int p, int q)
{
	T tmp = data[p];
	data[p] = data[q];
	data[q] = tmp;
}

/* Accessors */

template <class T>
T& AList<T>::get(int p) const
{ return data[p]; }

template <class T>
T& AList<T>::get(int p)
{ return data[p]; }

template <class T>
int AList<T>::getSize() const
{ return size; }

template <class T>
int AList<T>::capacity() const
{ return space - size; }

template <class T>
bool AList<T>::isEmpty() const
{ return size == 0; }

/* Overloaded operators */

template <class T>
AList<T>& AList<T>::operator =(const AList<T>& cp)
{
	if(this == &cp) return *this;
	if(data) delete[] data;

	data = new T[cp.getSize()];
	size = cp.getSize();
	space = cp.getSize() + cp.capacity();

	for (int i = 0; i < size; i++) data[i] = cp.get(i);

	return *this;
}

template <class T>
AList<T>& AList<T>::operator =(AList<T>&& mv)
{
	if(this == &mv) return *this;
	if(data) delete[] data;

	data = mv.data;
	size = mv.getSize();
	space = mv.getSize() + mv.capacity();

	return *this;
}

template <>
AList<char>& AList<char>::operator =(const char* s)
{
	for (int i = 0; s[i] != '\0'; i++) ++size;

	data = new char[size];

	for(int i = 0; i < size; i++) data[i] = s[i];

	space = size;
	return *this;
}

template <class T>
AList<T>& AList<T>::operator +=(const AList<T>& c)
{
	T* temp = new T[size + c.getSize()];

	for (int i = 0; i < size; i++) temp[i] = data[i];

	delete[] data;
	data = temp;

	for (int i = 0; i < c.getSize(); i++) data[size + i] = c.get(i);

	return *this;
}

template <class T>
bool AList<T>::operator ==(const AList<T>& c)
{
	bool eq = true;

	if (size != c.getSize()) eq = false;
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] != c.get(i)) eq = false;
		}
	}
	return eq;
}

template <class T>
bool AList<T>::operator !=(const AList<T>& c)
{
	bool eq = true;

	if (size != c.getSize()) eq = false;
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (data[i] != c.get(i)) eq = false;
		}
	}
	return !eq;
}

template <class T>
bool AList<T>::operator >(const AList<T>& c)
{
	bool gtr = true;

	if (size < c.getSize()) gtr = false;
	else {
		for (int i = 0; i < size; i++) {
			if (data[i] <= c.get(i)) {
				gtr = false;
			}
		}
	}
	return gtr;
}

template <class T>
bool AList<T>::operator <(const AList<T>& c) {
	bool les = true;

	if (size > c.getSize()) les = false;
	else {
		for (int i = 0; i < size; i++) {
			if (data[i] >= c.get(i)) {
				les = false;
			}
		}
	}
	return les;
}

template <class T>
bool AList<T>::operator >=(const AList<T>& c)
{ return !(*this < c); }

template <class T>
bool AList<T>::operator <=(const AList<T>& c)
{ return !(*this > c); }

template <class T>
ostream& operator <<(ostream& o, const AList<T>& c)
{
	for (int i = 0; i < c.getSize(); i++) o << c.get(i);

	return o;
}

template <class T>
istream& operator >>(istream& i, AList<T>& c)
{
	c = AList<T>(i.gcount());

	for (int j = 0; j < i.gcount(); j++) i >> c.get(j);

	return i;
}

/* Constructors */

template <class T>
AList<T>::AList()
{
	data = nullptr;
	size = 0;
	space = 0;
}

template <class T>
AList<T>::AList(const AList<T>& cp)
{
	data = new T[cp.getSize()];
	size = cp.getSize();
	space = cp.getSize() + cp.capacity();

	for (int i = 0; i < size; i++) data[i] = cp.get(i);
}

template <class T>
AList<T>::AList(AList<T>&& mv)
{
	data = mv.data;
	size = mv.getSize();
	space = mv.getSize() + mv.capacity();
}

template <class T>
AList<T>::AList(int s)
{
	data = new T[s];
	size = 0;
	space = s;
}

template <>
AList<char>::AList(const char* s)
{
	for (int i = 0; s[i] != '\0'; i++) ++size;

	data = new char[size];
	space = size;

	for(int i = 0; i < size; i++) data[i] = s[i];
}

template <class T>
AList<T>::~AList()
{
	if(data) delete[] data;
	data = nullptr;
}
#endif // ARRAYLIST_H
