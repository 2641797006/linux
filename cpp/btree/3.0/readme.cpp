B树3.0

btree<XDE_Table> t;
XDE_Table table, table1, table2;

需要重载以下运算符:{
	table1 < table2;
	table1 <= table2;
	table1 == table2;
	table1 = table2;
}

t.insert(table);
	这将为table分配一块空间,并通过赋值运算符'='将table复制到分配的空间中

unique(唯一性): {
	默认允许相等的table存在
	调用 t.set_unique(); 来设置不允许相等的table存在
	此后t.insert(table)时, 若B树中存在table2与table相等, 则不会将table插入
	而是返回指向B树中table2的指针 (XDE_Table*)
	其他情况insert返回 NULL
}

t.find(table);
	若B树中存在table2==table
		返回指向table2的指针
	否则返回 NULL

t.erase(table);
	若B树中存在table2==table
		delete table2; 返回 1
	否则返回 0


"未写好"但可以实现的功能:
	min() 返回指向最小的table的指针
	max() 返回指向最大的table的指针

	traverse(int visit(XDE_Table*))
		自定义visit函数, 从小到大遍历所有元素, 一但visit函数返回非0值, 则遍历终止, traverse返回visit返回的值

	
