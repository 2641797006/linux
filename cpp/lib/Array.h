#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <cstddef> // NULL
#include <utility> // move
#include <initializer_list>
#include <new> // placement new

#define __t(T)	template <class T>

namespace akm {
using namespace std;

template <class T>
struct Array {
	T *data;
	int length;

	Array(int len=0);
	Array(const T *arr, int len);
	Array(Array const& other);
	Array(Array && other);
	Array(initializer_list<T> init);
	~Array();

	Array& operator= (Array const& other);
	Array& operator= (Array && other);
	Array& operator= (initializer_list<T> init);

	T& operator[] (int pos);
	T const& operator[] (int pos) const;
};

__t(T)
Array<T>::Array(int len) {
	data = new T[len];
	length = len;
}

__t(T)
Array<T>::Array(const T *arr, int len) {
	new(this) Array(len);
	for (int i=0; i<len; ++i)
		data[i] = arr[i];
}

__t(T)
Array<T>::Array(Array const& other) {
	new(this) Array(other.length);
	for (int i=0; i<length; ++i)
		data[i] = other.data[i];
}

__t(T)
Array<T>::Array(Array && other) {
	data = other.data;
	length = other.length;
	other.data = NULL;
	other.length = 0;
}

__t(T)
Array<T>::Array(initializer_list<T> init) {
	new(this) Array(init.size());
	auto it = init.begin();
	for (int i=0; i<length; ++i) {
		data[i] = *it;
		++it;
	}
}

__t(T)
Array<T>::~Array() {
	delete[] data;
	length = 0;
}

__t(T)
Array<T>&
Array<T>::operator= (Array const& other) {
	this->~Array();
	new(this) Array(other);
	return *this;
}

__t(T)
Array<T>&
Array<T>::operator= (Array && other) {
	this->~Array();
	new(this) Array(move(other));
	return *this;
}

__t(T)
Array<T>&
Array<T>::operator= (initializer_list<T> init) {
	this->~Array();
	new(this) Array(init);
	return *this;
}

__t(T)
T&
Array<T>::operator[] (int pos) {
	return data[pos];
}

__t(T)
T const&
Array<T>::operator[] (int pos) const {
	return data[pos];
}

} // namespace akm

#undef __t

#endif

