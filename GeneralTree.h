//平凡树实现
#ifndef GENERALTREE_H
#define GENERALTREE_H

//平凡树数组实现（不存储节点值，只记录树的结构）
class GeneralTree {
	int* array_tree;          //实现平凡树的数组（根节点储存树大小的负值，子节点储存父节点下标）
	unsigned size;            //记录节点数目

	//判断当前节点是否为根节点
	bool isRoot(unsigned v) { return array_tree[v] < 0; }

	//寻找当前节点的根节点
	//使用路径压缩的方法降低树的高度
	unsigned findRoot(unsigned v) {
		if (isRoot(v)) return v;

		else {
			//向上遍历的同时，将节点直接连接到根节点上
			array_tree[v] = findRoot(array_tree[v]);
			return array_tree[v];
		}
	}

public:
	//构造函数
	GeneralTree(unsigned s) :size(s) {    
		array_tree = new int[size]();

		//所有节点的初始状态都为根节点
		for (size_t i = 0; i < size; ++i)
			array_tree[i] = -1;
	}
	~GeneralTree() { delete[]array_tree; }          //析构函数

	//判断两个节点是否不属于同一棵树
	bool differ(unsigned v1, unsigned v2) { return findRoot(v1) != findRoot(v2); }

	//连接两个节点所在的树
	//使用加权结合的方法降低树的高度
	void merge(unsigned v1, unsigned v2) {

		//两个节点已经在同一棵树中，直接返回
		if (!differ(v1, v2)) return;

		//将较小的根节点作为较大根节点的子节点
		v1 = findRoot(v1);
		v2 = findRoot(v2);
		unsigned bigger = v1, smaller = v2;
		if ((array_tree[v2] < array_tree[v1])
			|| (array_tree[v1] == array_tree[v2] && v2 < v1)) {
			bigger = v2;
			smaller = v1;
		}
		array_tree[bigger] += array_tree[smaller];
		array_tree[smaller] = bigger;
		return;
	}

};
#endif // !GENERALTREE_H

