//二叉搜索树节点实现
#ifndef BSTNODE_H
#define BSTNODE_H

template <typename Key, typename Elem>
class BSTNode {
	Key key;                       //节点元素的键值
	Elem elem;                     //节点元素的值
	BSTNode* left_child;           //指向左子树
	BSTNode* right_child;          //指向右子树

public:
	//构造函数
	BSTNode() {}     
	BSTNode(const Key &k, const Elem &e, 
		BSTNode* lc = nullptr, BSTNode* rc = nullptr) 
		:key(k), elem(e), left_child(lc), right_child(rc) {}

	//获取节点属性
	Key getKey()const { return key; }
	Elem getElem()const { return elem; }
	BSTNode* leftChild()const { return left_child; }
	BSTNode* rightChild()const { return right_child; }

	//设置节点属性
	void setElem(Key k, Elem e) { key = k; elem = e; }
	void setLeft(BSTNode* lc) { left_child = lc; }  
	void setRight(BSTNode* rc) { right_child = rc; }

	//判断节点是否为叶节点
	bool isLeaf()const { return left_child == nullptr
		&&right_child == nullptr; }
};

#endif // !BSTNODE_H
