#include <iostream>
using namespace std;

class xken{
  public:
	void *p;
	int utype;
	int uid;

	operator int(){return uid;}
	int operator<(const xken& xk)const{return uid<xk.uid;}
	int operator>(const xken& xk)const{return uid>xk.uid;}
	int operator<=(const xken& xk)const{return uid<=xk.uid;}
	int operator>=(const xken& xk)const{return uid>=xk.uid;}
	int operator==(const xken& xk)const{return uid==xk.uid;}
	void operator=(const xken& xk){p=xk.p, utype=xk.utype, uid=xk.uid;}

	int operator<(const int i)const{return uid<i;}
	int operator>(const int i)const{return uid>i;}
	int operator<=(const int i)const{return uid<=i;}
	int operator>=(const int i)const{return uid>=i;}
	int operator==(const int i)const{return uid==i;}
	void operator=(const int i){uid=i;}

	friend ostream& operator<<(ostream& out, const xken& xk){return out<<xk.uid;}
};

#define Mindex_t	int
#define MT		xken
#include "bptree_vs.h"
using namespace __tree;

int
main()
{
	int i, j;
	xken xk, xk1;
	bptree<int, xken> T;

	xk.uid=222333, xk1.uid=44455566;
	cout<<xk<<' '<<xk1<<endl;
	for (i=0; i<1000; i++) {
//		cin>>j;
		xk = i;
		T.insert(xk);
	}
	T.print();
	T.check();
	for (i=0; i<10; i++) cout<<'\n';
	for (i=500; i<1500; i++)
		xk=i,T.erase(xk), T.check();
	T.print();
	xk.uid=66;
	cout<<"find 666="<<*T.find(xk)<<endl;
	xk.uid=6666;
	T.find(xk);
	cout<<"find 6666=(p)="<<T.find(xk)<<endl;
	cout<<T.erase(xk)<<endl;
}
