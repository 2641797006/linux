#ifndef _MATRIX_H_
#define _MATRIX_H_

#ifndef _GLIBCXX_IOSTREAM
#include <iostream>
#endif

#ifndef _GLIBCXX_CSTDLIB
#include <cstdlib>
#endif

#define __t(T)	template<typename T>

namespace akm{
using namespace std;

__t(T)
class Matrix{
	using uint=uint32_t;
	uint row;
	uint col;
	T *bp;

  public:
	Matrix(int r, int c);
	~Matrix();

	T& operator() (uint r, uint c) const;
	bool rc(Matrix<T> const&) const;
	bool cr(Matrix<T> const&) const;

	void set(T const&);
// for test
	void rand(int);
	void rand(int left, int right);

	Matrix<T>& add(Matrix<T> const&);
	Matrix<T>& sub(Matrix<T> const&);

//	__t(A)
//	friend Matrix<A>& operator+ (Matrix<A> const&, Matrix<A> const&);
	__t(A)
	friend ostream& operator<< (ostream&, Matrix<A> const&);

}; // class Matrix

__t(T)
Matrix<T>&
Matrix<T>::sub(Matrix<T> const& mat)
{
	if ( ! rc(mat) )
		return *this;
	uint i, j;
	for (i=0; i<row; ++i)
		for (j=0; j<col; ++j)
			(*this)(i, j) -= mat(i, j);
	return *this;
}

__t(T)
Matrix<T>&
Matrix<T>::add(Matrix<T> const& mat)
{
	if ( ! rc(mat) )
		return *this;
	uint i, j;
	for (i=0; i<row; ++i)
		for (j=0; j<col; ++j)
			(*this)(i, j) += mat(i, j);
	return *this;
}

__t(T)
T&
Matrix<T>::operator() (uint r, uint c) const
{
	return bp[r*col+c];
}

__t(T)
void
Matrix<T>::rand(int left, int right)
{
	uint i, j, range;
	if (left >= right)
		return;
	range = right - left;
	for (i=0; i<row; ++i)
		for (j=0; j<col; ++j)
			(*this)(i, j) = left + std::rand()%range;
}

__t(T)
void
Matrix<T>::rand(int n)
{
	rand(0, n);
}

__t(T)
void
Matrix<T>::set(T const& t)
{
	uint i, j;
	for (i=0; i<row; ++i)
		for (j=0; j<col; ++j)
			(*this)(i, j) = t;
}

__t(T)
bool
Matrix<T>::rc(Matrix<T> const& mat) const
{
	return row==mat.row && col==mat.col;
}

__t(T)
bool
Matrix<T>::cr(Matrix<T> const& mat) const
{
	return row==mat.col && col==mat.row;
}

__t(A)
ostream&
operator<< (ostream& out, Matrix<A> const& mat)
{
	uint i, j;
	out<<'['<<'\n';
	for (i=0; i<mat.row; ++i) {
		out<<'[';
		out<<mat(i, 0);
		for (j=1; j<mat.col; ++j)
			out<<','<<' '<<mat(i, j);
		out<<']'<<'\n';
	}
	out<<']'<<'\n';
	return out;
}

__t(T)
Matrix<T>::Matrix(int r, int c)
{
	row = r>0 ? r : 1;
	col = c>0 ? c : 1;
	bp = new T[row*col];
}

__t(T)
Matrix<T>::~Matrix()
{
	delete[] bp;
}

} // namespace akm

#undef __t

#endif // _MATRIX_H_

