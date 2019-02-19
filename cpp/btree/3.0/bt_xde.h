/*
AddNode(XDE_Table *ptb);
AddNode(XDE_Tree *ptr);
DeleteNode(UINT uid);
GetNode(UINT uid);

XDE_Table, XDE_Tree, WorkGroup
*/

#include "btree.h"
#include <random>

class XDE_Table{};
class XDE_Tree{};
class WorkGroup{};

enum{UT_XTable, UT_XTree, UT_WorkGroup};

class XDE_BTC{
  public:	//先用public, 完成后再考虑改成private
	unsigned int uid;
	unsigned int utype;
	void *p;

	XDE_BTC& operator=(const XDE_BTC& xde)
	{
		uid = xde.uid;
		utype = xde.utype;
		p = xde.p;
		return *this;
	}

	int operator<(const XDE_BTC& xde)const{return uid<xde.uid;}
	int operator>(const XDE_BTC& xde)const{return uid>xde.uid;}
	int operator<=(const XDE_BTC& xde)const{return uid<=xde.uid;}
	int operator>=(const XDE_BTC& xde)const{return uid>=xde.uid;}
	int operator==(const XDE_BTC& xde)const{return uid==xde.uid;}
};

class XDEngine{
  public:
	XDE_BTC* GetNode(unsigned int uid);	//未找到时返回NULL, 成功则返回XDE_BTC类指针
	unsigned int AddNode(XDE_Table *ptb) {return insert(ptb, UT_XTable);}//add成功返回uid
	unsigned int AddNode(XDE_Tree  *ptr) {return insert(ptr, UT_XTree);} //失败返回0
	unsigned int AddNode(WorkGroup *pwg) {return insert(pwg, UT_WorkGroup);}
	int DeleteNode(unsigned int uid);	//删除成功返回1, 不存在则返回0

	XDEngine(){tree.set_unique(); rand.seed(666);} //uid是惟一的, 随机的

  private:
	unsigned int insert(void *p, unsigned int utype);

	XDE_BTC _xde;
	std::default_random_engine rand;
	__tree::btree<XDE_BTC> tree;
};

inline XDE_BTC*
XDEngine::GetNode(unsigned int uid)
{
	_xde.uid = uid;
	return tree.find(_xde);
}

unsigned int
XDEngine::insert(void *p, unsigned int utype)
{
	int i;
	_xde.uid = rand();
	_xde.utype = utype;
	_xde.p = p;
	for (i=0; i<100; i++)
		if (!tree.insert(_xde))
			return _xde.uid;
		else
			_xde.uid = rand();
	return 0;
}

inline int
XDEngine::DeleteNode(unsigned int uid)
{
	_xde.uid = uid;
	return tree.erase(_xde);
}


