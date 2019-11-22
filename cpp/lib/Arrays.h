#ifndef _ARRAYS_H_
#define _ARRAYS_H_

#ifndef _ARRAY_H_
#include "Array.h"
#endif

#include <string.h>

#define __t(T)	template <class T>

namespace akm {

class Arrays {
  public:
	__t(T) static
	Array<T> copyOf(Array<T> const& original, int newLength);
	__t(T) static
	Array<T> copyOfRange(Array<T> const& original, int from, int to);
	__t(T) static
	void fill(Array<T>& a, T const& val);
};

__t(T)
Array<T>
Arrays::copyOf(Array<T> const& original, int newLength) {
	Array<T> newArray(newLength);
	int copyLength = min(original.length, newLength);
	for (int i=0; i<copyLength; ++i)
		newArray[i] = original[i];
	if (newArray.length > copyLength)
		memset(&newArray[copyLength], 0, (newArray.length - copyLength)*sizeof(T));
	return newArray;
}

__t(T)
Array<T>
Arrays::copyOfRange(Array<T> const& original, int from, int to) {
	Array<T> newArray(to - from);
	for (int i=0; i<newArray.length; ++i)
		newArray[i] = original[from + i];
	return newArray;
}

__t(T)
void
Arrays::fill(Array<T>& a, T const& val) {
	for (int i=0; i<a.length; ++i)
		a[i] = val;
}

} // namespace akm

#undef __t

#endif // _ARRAYS_H_

