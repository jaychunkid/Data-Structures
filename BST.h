//二叉搜索树实现
//左子树中的节点键值小于根节点键值
//右子树中的节点键值大于等于根节点键值
#ifndef BST_H
#define BST_H

#include"BSTNode.h"
#include<iostream>
using std::cout;

template <typename Key, typename Elem>
class BST {
	BSTNode<Key, Elem>* root = nullptr;          //树根节点
	unsigned count = 0;                          //统计节点个数

	//内部递归函数
	void clearHelp(BSTNode<Key, Elem>*);
	BSTNode<Key, Elem>* insertHelp(BSTNode<Key, Elem>* subroot, const Key &k, const Elem &e);
	BSTNode<Key, Elem>* searchHelp(BSTNode<Key, Elem>* subroot, const Key &k)const;
	BSTNode<Key, Elem>* removeHelp(BSTNode<Key, Elem>* subroot, const Key &k);
	void printHelp(const BSTNode<Key, Elem>*, unsigned)const;
	BSTNode<Key, Elem>* deleteMin(BSTNode<Key, Elem>* subroot);
	BSTNode<Key, Elem>* getMin(BSTNode<Key, Elem>* subroot);

public:
	//构造函数和析构函数
	BST() {}               
	~BST() { clear(); }   
	
	//清空树中的所有节点
	void clear() {          
		clearHelp(root);
		root = nullptr;
		count = 0;
	}
	
	//向树中插入节点
	void insert(const Key &k, const Elem &e) {  
		root = insertHelp(root, k, e);
		++count;
	}  
	
	//在树中查找对应键值k的节点，返回节点元素的值
	bool search(const Key &k, Elem &e)const {   
		BSTNode<Key, Elem>* tmp = searchHelp(root, k);
		if (tmp == nullptr)
			return false;
		else {
			e = tmp->getElem();
			return true;
		}
	}
	
	//删除树中对应键值k的节点，返回被删除节点元素的值
	bool remove(const Key &k, Elem &e) {
		if (!search(k, e))
			return false;
		else {
			root = removeHelp(root, k);
			--count;
			return true;
		}
	}
	
	//输出树结构
	void print()const {
		printHelp(root, 0);
	}

	//返回树的大小（节点数目）
	unsigned size() { return count; }

	//判断树是否为空
	bool isEmpty()const { return !count; }     
};

//递归函数实现删除整棵树的节点
template <typename Key, typename Elem>
void BST<Key, Elem>::clearHelp(BSTNode<Key, Elem>* subroot) {
	
	//遇到空节点，直接返回
	if (subroot == nullptr)
		return;

	//非空节点，遍历左右子树后删除节点，返回
	else {
		clearHelp(subroot->leftChild());
		clearHelp(subroot->rightChild());
		delete subroot;
		return;
	}
}

//递归函数实现向树中插入节点
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::insertHelp(BSTNode<Key, Elem>* subroot, 
	const Key &k, const Elem &e) {

	//遇到空节点，插入节点后返回
	if (subroot == nullptr)
		return new BSTNode<Key, Elem>(k, e);
	
	//待插入节点键值小于根节点键值，更新节点左子树
	if (k < subroot->getKey())
		subroot->setLeft(insertHelp(subroot->leftChild(), k, e));

	//待插入节点键值大于等于根节点键值，更新节点右子树
	else
		subroot->setRight(insertHelp(subroot->rightChild(), k, e));

	return subroot;          //返回更新后的节点
}

//递归函数实现在树中搜索指定节点
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::searchHelp(BSTNode<Key, Elem>* subroot, const Key &k)const {

	//遇到空节点，指定节点不存在，返回空值
	if (subroot == nullptr)
		return nullptr;

	//待查找节点键值小于根节点键值，查找左子树
	if (k < subroot->getKey())
		return searchHelp(subroot->leftChild(), k);

	//待查找节点键值大于根节点键值，查找右子树
	else if (k > subroot->getKey())
		return searchHelp(subroot->rightChild(), k);

	//根节点为待查找节点，返回
	else
		return subroot;
}

//递归函数实现删除书中的指定节点
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::removeHelp(BSTNode<Key, Elem>* subroot, const Key &k) {

	//待删除节点键值小于根节点键值，更新左子树
	if (k < subroot->getKey()) {
		subroot->setLeft(removeHelp(subroot->leftChild(), k));
		return subroot;
	}

	//待删除节点键值大于根节点键值，更新右子树
	else if (k > subroot->getKey()) {
		subroot->setRight(removeHelp(subroot->rightChild(), k));
		return subroot;
	}

	//找到待删除节点
	else {

		//待删除节点是叶节点，直接删除
		if (subroot->isLeaf()) {
			delete subroot;
			return nullptr;
		}

		BSTNode<Key, Elem>* tmp = nullptr;

		//待删除节点只有右子树，右子树根节点替换待删除节点位置
		if (subroot->leftChild() == nullptr) {
			tmp = subroot->rightChild();
			delete subroot;
			return tmp;
		}

		//待删除节点只有左子树，左子树根节点替换待删除节点位置
		if (subroot->rightChild() == nullptr) {
			tmp = subroot->leftChild();
			delete subroot;
			return tmp;
		}
	
		//待删除节点有左右子树，从右子树中获取最小节点替换待删除节点位置
		tmp = getMin(subroot->rightChild());
		subroot->setRight(deleteMin(subroot->rightChild()));
		subroot->setElem(tmp->getKey(), tmp->getElem());
		delete tmp;

		return subroot;          //返回更新后的根节点
	}
}

//递归实现删除树中的最小节点
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::deleteMin(BSTNode<Key, Elem>* subroot) {

	//根节点为空，返回空值
	if (subroot == nullptr)
		return nullptr;

	//当前节点是最小节点，右子树根节点替代当前节点位置
	if (subroot->leftChild() == nullptr) {
		BSTNode<Key, Elem>* tmp = subroot->rightChild();
		delete subroot;
		return tmp;
	}
	
	//当前节点不是最小节点，更新左子树
	else {
		subroot->setLeft(deleteMin(subroot->leftChild()));
		return subroot;
	}
}

//递归实现获取树中最小的节点
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::getMin(BSTNode<Key, Elem>* subroot) {

	//根节点为空，返回空值
	if (subroot == nullptr)
		return nullptr;

	//当前节点是最小节点，返回节点
	if (subroot->leftChild() == nullptr)
		return subroot;

	//当前节点不是最小节点，在左子树中查找
	else
		return getMin(subroot->leftChild());
}

//递归实现输出树的结构，当前节点的高度为level
template <typename Key, typename Elem>
void BST<Key, Elem>::printHelp(const BSTNode<Key, Elem>* subroot, unsigned level)const {
	
	//遇到空节点，直接返回
	if (subroot == nullptr)
		return;

	//先遍历右子树
	printHelp(subroot->rightChild(), level + 1);

	//根据当前节点的高度使用空格符控制格式
	for (unsigned i = 0; i < level; ++i)
		cout << ' ';

	//输出当前节点键值
	cout << subroot->getKey() << '\n';

	//最后遍历左子树
	printHelp(subroot->leftChild(), level + 1);
	return;
}
#endif // !BST_H

