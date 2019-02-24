#ifndef _XKERNEL_H_
#define _XKERNEL_H_

#ifndef _BPTREE_H_
#include "bptree.h"
#endif

#include <random>

#ifdef _vxk_class_
class XDE_Table{};
class XDE_Tree{};
class WorkGroup{};
#endif

enum{UT_XTable, UT_XTree, UT_WorkGroup};

class XK_BTC
{
  public:
	unsigned int uid;
	unsigned int utype;
	void *p;

	XK_BTC& operator=(const XK_BTC& xk)
	{
		uid = xk.uid;
		utype = xk.utype;
		p = xk.p;
		return *this;
	}
	int operator<(const XK_BTC& xk)const{return uid<xk.uid;}
	int operator>(const XK_BTC& xk)const{return uid>xk.uid;}
	int operator<=(const XK_BTC& xk)const{return uid<=xk.uid;}
	int operator>=(const XK_BTC& xk)const{return uid>=xk.uid;}
	int operator==(const XK_BTC& xk)const{return uid==xk.uid;}
	operator unsigned int(){return uid;}
	int operator<(const unsigned int i)const{return uid<i;}
	int operator>(const unsigned int i)const{return uid>i;}
	int operator<=(const unsigned int i)const{return uid<=i;}
	int operator>=(const unsigned int i)const{return uid>=i;}
	int operator==(const unsigned int i)const{return uid==i;}
	void operator=(const unsigned int i){uid = i;}
};

class XKernel
{
  public:
	XK_BTC* GetNode(unsigned int uid); //未找到时返回NULL, 成功则返回XK_BTC类指针
	unsigned int AddNode(XDE_Table *ptb){return insert(ptb, UT_XTable);}	//add成功返回uid(1~65535)
	unsigned int AddNode(XDE_Tree  *ptr){return insert(ptr, UT_XTree);}	//失败返回0
	unsigned int AddNode(WorkGroup *pwg){return insert(pwg, UT_WorkGroup);} //uid超过65535时会失败
	int DeleteNode(unsigned int uid);	//删除成功返回1, 不存在则返回0

	XKernel(){ xk_tree.set_unique(); rand.seed(666);}	//uid是惟一的, 随机的(1~65535)
	~XKernel(){};

  private:
	unsigned int insert(void *p, unsigned int utype);

	XK_BTC _btc;
	std::default_random_engine rand;
	__tree::bptree<unsigned int, XK_BTC> xk_tree;
};

inline XK_BTC*
XKernel::GetNode(unsigned int uid)
{
	_btc.uid = uid;
	return xk_tree.find(_btc);
}

unsigned int
XKernel::insert(void *p, unsigned int utype)
{
	int i;
	_btc.uid = rand()%0xffff+1;
	_btc.utype = utype;
	_btc.p = p;
	for (i=0; i<100; i++)
		if (!xk_tree.insert(_btc))
			return _btc.uid;
		else
			_btc.uid = rand()%0xffff+1;
	return 0;
}

inline int
XKernel::DeleteNode(unsigned int uid)
{
	_btc.uid = uid;
	return xk_tree.erase(_btc);
}

#endif
