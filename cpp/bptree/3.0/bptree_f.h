#ifndef _BPTREE_F_H_
#define _BPTREE_F_H_

/******* offset *********/

/*
 * TODO: < print B+ tree >
 * 在include此文件前加上下面这一行
 * #define _24k_BPTREE_PRINT
 * 可以使用 bptree<index_t, T>::print() 输出B+树
 * 对于 bptree<index_t, T> 中 index_t 与 T 需要支持cout标准输出
 *
 */

#ifndef _GLIBCXX_QUEUE
#include <queue>
#endif

#ifndef _ASSERT_H
#include <assert.h>
#endif

#define __tt(T1, T2)	template <typename T1, typename T2>

//TODO: OFF_NULL 0偏移
// 请确保alloc(size)成功时不返回 OFF_NULL
#define OFF_NULL		(0)

#define BP_NEW(off, T, ...)	(new(getptr(off)) T(__VA_ARGS__)) //在 off 偏移处对 T 类型进行构造
#define BPN(off)		((bp_node*)getptr(off)) //根据偏移获取<临时> bp_node 类型指针

#ifdef _MSC_VER

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#endif //_MSC_VER

#ifndef MAX_T
#define MAX_T	4
#endif

#ifndef MIN_T
#define MIN_T	((MAX_T+1)/2)
#endif

/******** TODO: 修改 alloc(), free(), getptr(), 以使用个性化偏移方式 ***************/
inline ptrdiff_t alloc(size_t size) {return (new char[size])-(char*)NULL;}
inline void free(ptrdiff_t off) {delete[] ((char*)NULL+off);}
inline void* getptr(ptrdiff_t off) {return (void*)((char*)NULL+off);} //根据偏移获取<临时>指针
/************************************************************************************/


namespace _24k{
using namespace std;

class bp_node{	//B+树结点类
  public:
	int		keynum;
	ptrdiff_t	parent;
	ptrdiff_t	key[MAX_T];	//2种类型, 索引(index_t)和真实数据项(T)
	ptrdiff_t	child[MAX_T+1];
	ptrdiff_t	next;

	void clrc();
	bp_node(ptrdiff_t p=OFF_NULL): keynum(0), parent(p), next(OFF_NULL) {clrc();}
};

#ifdef _24k_BPTREE_PRINT

__tt(index_t, T)	// cout << index_t, T
void
bp_node_print(ptrdiff_t node)
{
	int i;

	cout<<'{';
	if (BPN(node)->child[0]) {
		for (i=0; i<BPN(node)->keynum-1; i++)
			cout<<*(index_t*)getptr(BPN(node)->key[i])<<' ';
		if (BPN(node)->keynum)	//or print '\b'
			cout<<*(index_t*)getptr(BPN(node)->key[i]);
	} else {
		for (i=0; i<BPN(node)->keynum-1; i++)
			cout<<*(T*)getptr(BPN(node)->key[i])<<' ';
		if (BPN(node)->keynum)	// '\b'
			cout<<*(T*)getptr(BPN(node)->key[i]);
	}
	cout<<'}';
}

#endif

inline void
bp_node::clrc()
{
	int i;
	for (i=0; i<MAX_T+1; i++)
		child[i] = OFF_NULL;
}

__tt(index_t, T)
class bp_iter{
  public:
	bp_iter& operator = (bp_iter const& it){node=it.node, key=it.key, kind=it.kind; return *this;}
	int operator != (bp_iter const& it)const{return key != it.key;}
	int operator == (bp_iter const& it)const{return key == it.key;}

	bp_iter& operator ++ () {
		if (kind<BPN(node)->keynum-1)
			key = BPN(node)->key[++kind];
		else if (BPN(node)->next) {
			node = BPN(node)->next;
			key = BPN(node)->key[0];
			kind = 0;
		} else
			key = OFF_NULL;
		return *this;
	}

	bp_iter operator ++ (int) {
		bp_iter it = *this;
		++(*this);
		return it;
	}

	T& operator * () {
		return *(T*)getptr(key);
	}

	ptrdiff_t node;
	ptrdiff_t key;
	int kind;
};

/* class bptree */	//具体B+树特性 请参照 baidu.com/s?wd=B%2B%E6%A0%91
__tt(index_t, T)	//索引(index_t)与数据项(T)可以相同: bptree<int,int>, bptree<string(文件名),fstream(文件)>
class bptree{
  public:
	typedef bp_iter<index_t, T> iterator;

	ptrdiff_t find(T const& t);	//返回找到的数据项地址, 没有则返回OFF_NULL
	ptrdiff_t insert(T const& t);	//若调用了set_unique(), 则要插入的数据项已存在时不会插入,而返回已存在数据地址. 其他返回OFF_NULL
	int erase(T const& t);	//删除成功返回1, 不存在则返回0

	T& front() {return *(T*)getptr(min());}
	T& back() {return *(T*)getptr(max());}
	iterator begin();
	iterator& end() {return iter_null;}
	size_t size() {return _size;}

	int isunique(){return unique;}	//若设置了惟一性,返回1, 否则返回0
	void set_unique(){unique=1;}	//设置数据项的惟一性, 不允许"相等"的数据项存在
	void set_nounique(){unique=0;}	//取消数据项的惟一性, 允许"相等"的数据项存在

	// << 构造函数 >>
	bptree(): unique(0), _size(0)
		{iter_null.key=OFF_NULL; _root=alloc(sizeof(bp_node)), BP_NEW(_root, bp_node);}
	~bptree();

	ptrdiff_t min();		//返回最小数据项的地址
	ptrdiff_t max();		//返回最大数据项的地址
	int traverse(int visit(ptrdiff_t));	//自定义visit函数, 从小到大遍历所有数据, 一旦visit返回非0值, 终止并返回该值

#ifdef _24k_BPTREE_PRINT
	void print();
#endif

  private:
	int unique;
	size_t _size;
	ptrdiff_t _root;

	iterator iter_null;
	ptrdiff_t find_t(ptrdiff_t& node, T const& t, int& i);

#ifdef _24k_BPTREE_CHECK
  public:
	bp_node* root() {return BPN(_root);}

	int check_cind(ptrdiff_t node);
	int check_key(ptrdiff_t node);
	int check_child(ptrdiff_t node);
	int check_all(ptrdiff_t node);
	int check();
#endif
};

__tt(index_t, T)
bp_iter<index_t, T>
bptree<index_t, T>::begin()
{
	bp_iter<index_t, T> it;
	ptrdiff_t node = _root;

	while (BPN(node)->child[0])
		node = BPN(node)->child[0];
	it.node = node;
	it.key = BPN(node)->key[0];
	it.kind = 0;
	return it;
}

#ifdef _24k_BPTREE_CHECK
__tt(index_t, T)
int
bptree<index_t, T>::check_cind(ptrdiff_t node)
{
	int i;
	ptrdiff_t node_p;

	assert(node);
	node_p = BPN(node)->parent;
	if (node == _root) {
		assert(!node_p);
		return 0;
	}
	for (i=0; i<BPN(node_p)->keynum; i++)
		if (node == BPN(node_p)->child[i])
			break;
	assert(node == BPN(node_p)->child[i]);
	return 1;
}

__tt(index_t, T)
int
bptree<index_t, T>::check_key(ptrdiff_t node)
{
	int i;

	if (node != _root)
		assert(BPN(node)->keynum >= MIN_T-1);
	for (i=0; i<BPN(node)->keynum; i++)
		assert(BPN(node)->key[i]);
	return BPN(node)->keynum;
}

__tt(index_t, T)
int
bptree<index_t, T>::check_child(ptrdiff_t node)
{
	int i;

//	if (node==_root && !BPN(node)->child[0])
//		return -1;
	if (!BPN(node)->child[0])
		for (i=0; i<=MAX_T; i++)
			assert(!BPN(node)->child[i]);
	else
		for (i=0; i<=BPN(node)->keynum; i++)
			assert(BPN(node)->child[i]), assert(node == BPN(BPN(node)->child[i])->parent);
	return 1;
}

__tt(index_t, T)
int
bptree<index_t, T>::check_all(ptrdiff_t node)
{
	check_cind(node);
	check_key(node);
	check_child(node);
	return 1;
}

__tt(index_t, T)
int
bptree<index_t, T>::check()
{
	int i;
	ptrdiff_t node;
	queue<ptrdiff_t> q;

	q.push(_root);
	while (!q.empty()) {
		node = q.front();
		q.pop();
		check_all(node);
		if (BPN(node)->child[0])
			for (i=0; i<=BPN(node)->keynum; i++)
				q.push(BPN(node)->child[i]);
	}
	return 1;
}

#endif

__tt(index_t, T)
bptree<index_t, T>::~bptree()
{
	int i;
	ptrdiff_t node;
	queue<ptrdiff_t> q;

	q.push(_root);
	while (!q.empty()) {
		node = q.front();
		q.pop();
		if (BPN(node)->child[0]) {
			for (i=0; i<=BPN(node)->keynum; i++)
				q.push(BPN(node)->child[i]);
			for (i=0; i<BPN(node)->keynum; i++)
				free(BPN(node)->key[i]); // delete index_t
		}
		else
			for (i=0; i<BPN(node)->keynum; i++)
				free(BPN(node)->key[i]); // delete T
		free(node);
	}
}

__tt(index_t, T)
inline ptrdiff_t
bptree<index_t, T>::find(T const& t)
{
	int i;
	ptrdiff_t node=_root;
	return find_t(node, t, i);
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::find_t(ptrdiff_t& node, T const& t, int& i)
{
	if (!node)
		node = _root;
	for (;;) {
		if (BPN(node)->child[0]) {
			for (i=0; i<BPN(node)->keynum; i++)
				if (t<=*(index_t*)getptr(BPN(node)->key[i]))			// <=
					break;
			node = BPN(node)->child[i];
		}
		else {
			for (i=0; i<BPN(node)->keynum-1; i++)
				if (t<=*(T*)getptr(BPN(node)->key[i]))			// <=
					break;
			break;
		}
	}
	if (t==*(T*)getptr(BPN(node)->key[i]))
		return BPN(node)->key[i];
	return OFF_NULL;
}

__tt(index_t, T)
int
bptree<index_t, T>::erase(T const& t)
{
	int i, cind, leaf;
	ptrdiff_t node=_root, node_1, node_p;

	{
		ptrdiff_t tp;
		tp = find_t(node, t, i);
		if (!tp)
			return 0;
		free(tp);
	}
	while (++i<BPN(node)->keynum)
		BPN(node)->key[i-1] = BPN(node)->key[i];
	leaf = 1;
	_size--;
	while (--BPN(node)->keynum<MIN_T-1) {
		node_p = BPN(node)->parent;
		if (!node_p) {
			if (BPN(_root)->keynum)
				break;
			_root = BPN(_root)->child[0];
			if (_root)
				BPN(_root)->parent = OFF_NULL;
			else
				_root = alloc(sizeof(bp_node)), BP_NEW(_root, bp_node);
			free(node);
			break;
		}
		for (cind=0; cind<BPN(node_p)->keynum; cind++)
			if (BPN(node_p)->child[cind]==node)
				break;
		if (cind && (BPN(BPN(node_p)->child[cind-1])->keynum>=MIN_T)) {
			i = BPN(node)->keynum;
			node_1 = BPN(node_p)->child[cind-1];
			if (!leaf) {
				BPN(node)->child[i+1] = BPN(node)->child[i];
				while (--i>=0) {
					BPN(node)->key[i+1] = BPN(node)->key[i];
					BPN(node)->child[i+1] = BPN(node)->child[i];
				}
				BPN(node)->key[0] = BPN(node_p)->key[cind-1];
				BPN(node)->child[0] = BPN(node_1)->child[BPN(node_1)->keynum];
				BPN(BPN(node)->child[0])->parent = node;
				BPN(node_p)->key[cind-1] = BPN(node_1)->key[BPN(node_1)->keynum-1];
			}
			else {
				while (--i>=0)
					BPN(node)->key[i+1] = BPN(node)->key[i];
				BPN(node)->key[0] = BPN(node_1)->key[BPN(node_1)->keynum-1];
				*(index_t*)getptr(BPN(node_p)->key[cind-1]) = *(T*)getptr(BPN(node_1)->key[BPN(node_1)->keynum-2]);
			}
			BPN(node)->keynum++, BPN(node_1)->keynum--;
			return 1;
		}
		else if ((cind+1<=BPN(node_p)->keynum) && (BPN(BPN(node_p)->child[cind+1])->keynum>=MIN_T)) {
			node_1 = BPN(node_p)->child[cind+1];
			if (!leaf) {
				BPN(node)->key[BPN(node)->keynum] = BPN(node_p)->key[cind];
				BPN(node_p)->key[cind] = BPN(node_1)->key[0];
				BPN(BPN(node_1)->child[0])->parent = node;
				BPN(node)->child[BPN(node)->keynum+1] = BPN(node_1)->child[0];
				for (i=1; i<BPN(node_1)->keynum; i++) {
					BPN(node_1)->key[i-1] = BPN(node_1)->key[i];
					BPN(node_1)->child[i-1] = BPN(node_1)->child[i];
				}
				BPN(node_1)->child[i-1] = BPN(node_1)->child[i];
			}
			else {
				BPN(node)->key[BPN(node)->keynum] = BPN(node_1)->key[0];
				*(index_t*)getptr(BPN(node_p)->key[cind]) = *(T*)getptr(BPN(node_1)->key[0]);
				for (i=1; i<BPN(node_1)->keynum; i++)
					BPN(node_1)->key[i-1] = BPN(node_1)->key[i];
			}
			BPN(node)->keynum++, BPN(node_1)->keynum--;
			return 1;
		}
		else {
			if (cind+1>BPN(node_p)->keynum) {
				node_1 = node;
				node = BPN(node_p)->child[--cind];
			}
			else
				node_1 = BPN(node_p)->child[cind+1];
			if (!leaf) {
				BPN(node)->key[BPN(node)->keynum] = BPN(node_p)->key[cind];
				BPN(node)->keynum++;
			}
			else
				free(BPN(node_p)->key[cind]);
			while (++cind<BPN(node_p)->keynum) {
				BPN(node_p)->key[cind-1] = BPN(node_p)->key[cind];
				BPN(node_p)->child[cind] = BPN(node_p)->child[cind+1];
			}
			if (!leaf) {
				for (i=0; i<BPN(node_1)->keynum; i++) {
					BPN(node)->key[BPN(node)->keynum+i] = BPN(node_1)->key[i];
					BPN(BPN(node_1)->child[i])->parent = node;
					BPN(node)->child[BPN(node)->keynum+i] = BPN(node_1)->child[i];
				}
				BPN(BPN(node_1)->child[i])->parent = node;
				BPN(node)->child[BPN(node)->keynum+i] = BPN(node_1)->child[i];
			}
			else {
				for (i=0; i<BPN(node_1)->keynum; i++)
					BPN(node)->key[BPN(node)->keynum+i] = BPN(node_1)->key[i];
			}
			BPN(node)->keynum += BPN(node_1)->keynum;
			node = node_p;
			free(node_1);
		}
		leaf ? (leaf=0) : 0;
	}
	return 1;
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::insert(T const& t)
{
	int i, j, leaf;
	ptrdiff_t node=_root, node_1, node_p;

	for (;;)
		if (BPN(node)->child[0]) {
			for (i=0; i<BPN(node)->keynum; i++)
				if (t<=*(index_t*)getptr(BPN(node)->key[i]))
					break;
			node = BPN(node)->child[i];
		}
		else {
			for (i=0; i<BPN(node)->keynum; i++)
				if (t<=*(T*)getptr(BPN(node)->key[i]))
					break;
			break;
		}
	if (unique && (i<BPN(node)->keynum) && (t==*(T*)getptr(BPN(node)->key[i])))
		return BPN(node)->key[i];
	for (j=BPN(node)->keynum; j>i; j--)
		BPN(node)->key[j] = BPN(node)->key[j-1];
	BPN(node)->key[i] = alloc(sizeof(T));//
	BP_NEW(BPN(node)->key[i], T); //构造
	*(T*)getptr(BPN(node)->key[i]) = t; //赋值
	leaf = 1;
	_size++;
	while (++BPN(node)->keynum==MAX_T) {
//split start
		node_1 = alloc(sizeof(bp_node));
		BP_NEW(node_1, bp_node, BPN(node)->parent);
		if (!leaf) {
			for (i=MIN_T; i<MAX_T; i++) {
				BPN(node_1)->key[i-MIN_T] = BPN(node)->key[i];
				BPN(BPN(node)->child[i])->parent = node_1;
				BPN(node_1)->child[i-MIN_T] = BPN(node)->child[i];
			}
			BPN(BPN(node)->child[i])->parent = node_1;
			BPN(node_1)->child[i-MIN_T] = BPN(node)->child[i];
			BPN(node)->keynum = MIN_T-1;
		}
		else {
			for (i=MIN_T; i<MAX_T; i++)
				BPN(node_1)->key[i-MIN_T] = BPN(node)->key[i];
			BPN(node_1)->next = BPN(node)->next;
			BPN(node)->next = node_1;
			BPN(node)->keynum = MIN_T;
		}
		BPN(node_1)->keynum = MAX_T-MIN_T;
//split end
		node_p = BPN(node)->parent;
		if (!node_p) { // node_p == OFF_NULL
			_root = alloc(sizeof(bp_node)), BP_NEW(_root, bp_node);
			BPN(_root)->child[0] = node;
			BPN(node)->parent = _root;
			BPN(node_1)->parent = _root;
			node_p = _root;
		}
		for (i=0; i<BPN(node_p)->keynum; i++)
			if (BPN(node_p)->child[i]==node)
				break;
		for (j=BPN(node_p)->keynum; j>i; j--) {
			BPN(node_p)->key[j] = BPN(node_p)->key[j-1];
			BPN(node_p)->child[j+1] = BPN(node_p)->child[j];
		}
		if (leaf) {
			BPN(node_p)->key[i] = alloc(sizeof(index_t)), BP_NEW(BPN(node_p)->key[i], index_t);//
			*(index_t*)getptr(BPN(node_p)->key[i]) = *(T*)getptr(BPN(node)->key[MIN_T-1]);//提取索引
		}
		else
			BPN(node_p)->key[i] = BPN(node)->key[MIN_T-1];
		BPN(node_p)->child[i+1] = node_1;
		node = node_p;
		leaf ? (leaf=0) : 0;
	}
	return OFF_NULL;
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::min()
{
	ptrdiff_t node = _root;

	while(BPN(node)->child[0])
		node = BPN(node)->child[0];
	return BPN(node)->key[0];
}

__tt(index_t, T)
ptrdiff_t
bptree<index_t, T>::max()
{
	ptrdiff_t node = _root;

	while(BPN(node)->child[0])
		node = BPN(node)->child[BPN(node)->keynum];
	return BPN(node)->key[BPN(node)->keynum-1];
}

__tt(index_t, T)
int
bptree<index_t, T>::traverse(int visit(ptrdiff_t))
{
	int i, ret;
	ptrdiff_t node = _root;

	while (BPN(node)->child[0])
		node = BPN(node)->child[0];
	for (;;) {
		for (i=0; i<BPN(node)->keynum; i++) {
			ret = visit(BPN(node)->key[i]);
			if (ret)
				return ret;
		}
		if (!BPN(node)->next)
			break;
		node = BPN(node)->next;
	}
	return 0;
}

#ifdef _24k_BPTREE_PRINT

__tt(index_t, T)
void
bptree<index_t, T>::print()
{
	const int fl=0x1, fc=0x2, f_lcr=0xf, f_child=0x10;
	int i, line, flag=0;
	ptrdiff_t node=_root;
	queue<ptrdiff_t> q;

	cout<<'{';
	q.push(node);
	q.push(OFF_NULL);
	line = q.size();
	flag |= fl;
	while (!q.empty()) {
		node = q.front();
		q.pop();
		if (line)
			line--;
		else {
			cout<<'\n';
			line = q.size();
			if (! (flag & f_child))
				break;
			else
				flag &= ~f_child;
		}
		if (node) {
			if (flag & fc)
				cout<<' ';
			else
				flag |= fc;
			bp_node_print<index_t, T>(node);
		} else {
			if (flag & fl) {
				cout<<'}'<<' ';
				flag &= ~f_lcr;
			} else {
				cout<<'{';
				flag |= fl;
			}
			continue;
		}
		q.push(OFF_NULL);
		if (BPN(node)->child[0])
			for (i=0; i<=BPN(node)->keynum; i++) {
				q.push(BPN(node)->child[i]);
				flag |= f_child;
			}
		q.push(OFF_NULL);
	}
	cout<<endl;
}

#endif

}//namespace _24k

#undef __tt
#undef OFF_NULL
#undef BP_NEW
#undef BPN

#endif //_BPTREE_F_H_
