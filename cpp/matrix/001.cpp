#include <iostream>
#include <set>
#include "matrix.h"
using namespace std;
using namespace akm;

int main()
{
	srand(time(NULL));

	Matrix<int> m1({
		{4, -1, 2, 1},
		{1, 1, 0, 3},
		{0, 3, 1, 4},
	}),
	m2({
		{1, 2},
		{0, 1},
		{3, 0},
		{-1, 2}
	}),
	m3({
		{1, 2, 3},
		{2, 2, 1},
		{3, 4, 3}
	});
	cout<<m3<<endl;
	cout<<m3.value()<<endl;
}

