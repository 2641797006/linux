#include <iostream>
#include <set>
#include "matrix.h"
using namespace std;
using namespace akm;

int main()
{
	srand(time(NULL));

	Matrix<int> mat(4,6), mat2(4, 6);
	mat.rand(10);
	cout<<mat<<endl;
	mat2.rand(-9, 1);
	cout<<mat2<<endl;
	cout<<mat.sub(mat2)<<endl;
}

