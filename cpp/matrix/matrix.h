#ifndef _MATRIX_H_
#define _MATRIX_H_

#ifndef _GLIBCXX_IOSTREAM
#include <iostream>
#endif

#ifndef _GLIBCXX_CSTDLIB
#include <cstdlib>
#endif

#ifndef _GLIBCXX_CSTRING
#include <cstring>
#endif

#ifndef _GLIBCXX_INITIALIZER_LIST
#include <initializer_list>
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
	Matrix(Matrix<T> const&);
	Matrix(Matrix<T> &&);
	Matrix(initializer_list<initializer_list<T>>);
	~Matrix();
	Matrix<T>& operator= (Matrix<T> const&);

	T& operator() (uint r, uint c) const;
	bool rc(Matrix<T> const&) const;
	bool cr(Matrix<T> const&) const;

	void set(T const&);

// for test
	void rand(int);
	void rand(int left, int right);

	Matrix<T> operator+ (Matrix<T> const&) const;
	Matrix<T> operator- (Matrix<T> const&) const;
	Matrix<T>& operator+= (Matrix<T> const&);
	Matrix<T>& operator-= (Matrix<T> const&);
	Matrix<T>& operator*= (Matrix<T> const&);

	__t(A)
	friend Matrix<A> operator+ (Matrix<A> const&, Matrix<A> const&);
	__t(A)
	friend Matrix<A> operator- (Matrix<A> const&, Matrix<A> const&);
	__t(A)
	friend Matrix<A> operator* (Matrix<A> const&, Matrix<A> const&);
//	__t(A)
//	friend Matrix<A> operator/ (Matrix<A> const&, Matrix<A> const&);
	__t(A)
	friend ostream& operator<< (ostream&, Matrix<A> const&);

}; // class Matrix

__t(T)
Matrix<T>&
Matrix<T>::operator= (Matrix<T> const& mat)
{
	delete[] bp;
	return *new(this) Matrix<T>(mat);
}

__t(T)
Matrix<T>&
Matrix<T>::operator*= (Matrix<T> const& mat)
{
	return (*this) = (*this) * mat;
}

__t(T)
Matrix<T>::Matrix(initializer_list<initializer_list<T>> il)
{
	row = il.size();
	col = 0;
	for (auto &x : il)
		if (x.size() > col)
			col = x.size();
	bp = new T[row*col];
	uint r=0, c;
	for (auto const& x : il) {
		c=0;
		for (auto const& y : x)
			(*this)(r, c++) = y;
		for (; c<col; ++c)
			(*this)(r, c) = 0;
		++r;
	}
}

__t(A)
Matrix<A>
operator* (Matrix<A> const& m1, Matrix<A> const& m2)
{
	if ( ! m1.cr(m2) )
		return m1;
	Matrix<A> mp(m1.row, m2.col);
	uint i, j, k;
	double product;
	for (i=0; i<mp.row; ++i)
		for (j=0; j<mp.col; ++j) {
			product = 0;
			for (k=0; k<m1.col; ++k)
				product += m1(i, k) * m2(k, j);
			mp(i, j) = product;
		}
	return mp;
}

__t(A)
Matrix<A>
operator- (Matrix<A> const& m1, Matrix<A> const& m2)
{
	Matrix<A> m(m1);
	return m -= m2;
}

__t(A)
Matrix<A>
operator+ (Matrix<A> const& m1, Matrix<A> const& m2)
{
	Matrix<A> m(m1);
	return m += m2;
}

__t(T)
Matrix<T>::Matrix(Matrix<T> && mat)
{
	row = mat.row;
	col = mat.col;
	bp = mat.bp;
	mat.bp = NULL;
}

__t(T)
Matrix<T>::Matrix(Matrix<T> const& mat)
{
	row = mat.row;
	col = mat.col;
	bp = new T[row*col];
	memcpy(bp, mat.bp, row*col*sizeof(T));
}

__t(T)
Matrix<T>&
Matrix<T>::operator-= (Matrix<T> const& mat)
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
Matrix<T>::operator+= (Matrix<T> const& mat)
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
	return col==mat.row;
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

