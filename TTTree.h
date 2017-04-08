//2-3树实现（删除节点功能未实现）
#ifndef TTTREE_H
#define TTTREE_H

#include"TTTreeNode.h"

template <typename Key, typename Elem>
class TTTree {
private:
	TTTreeNode<Elem, Key>* root;          //根节点

	//内部函数
	Elem searchHelp(const TTTreeNode<Elem, Key>* subroot, 
		const Key &k)const;
	void insertHelp(TTTreeNode<Elem, Key>* &subroot, 
		TTTreeNode<Elem, Key>* node,
		TTTreeNode<Elem, Key>* &reroot);
	void clearHelp(TTTreeNode<Elem, Key>* subroot);
	void spitNode(TTTreeNode<Elem, Key>* &subroot, 
		TTTreeNode<Elem, Key>* inNode,
		TTTreeNode<Elem, Key>* &outNode);
public:
	//构造函数和析构函数
	TTTree(TTTreeNode<Elem, Key>* r = nullptr) :root(r) {}
	~TTTree() { clear(); }

	//在树中搜索键值为k的元素，并返回对应元素
	bool search(const Key &k, Elem &e)const {
		e = searchHelp(root, k);
		return e != EMPTYELEM;
	}

	//清空树中节点
	void clear() {
		clearHelp(root);
		root = nullptr;
	}
	
	//向树中插入键值为k，值为e的元素
	void insert(Key k, Elem e);
};

//递归实现在树中搜索键值为k的元素
template <typename Key, typename Elem>
Elem TTTree<Key, Elem>::searchHelp(const TTTreeNode<Elem, Key>* subroot, 
	const Key &k)const {
	
	//未找到目标元素，返回空值
	if (subroot == nullptr)
		return EMPTYELEM;

	//目标元素键值小于当前节点左元素键值，在左子树中搜索
	else if (subroot->leftKey() > k)
		return searchHelp(subroot->cleftChild(), k);

	//目标元素为当前节点左元素，返回
	else if (subroot->leftKey() == k)
		return subroot->left();

	//目标元素键值介于当前节点左右元素键值之间，或当前节点未满，在中间子树中搜索
	else if ((!subroot->isfool()) || subroot->rightKey() > k)
		return searchHelp(subroot->ccentreChild(), k);

	//目标元素为当前节点右元素，返回
	else if (subroot->rightKey() == k)
		return subroot->right();

	//目标元素键值大于等于当前节点右元素键值，在右子树中搜索
	else
		return searchHelp(subroot->crightChild(), k);
}

//递归实现在树中插入节点
//node为待插入节点，默认不满且最多只有一个子树
//reroot节点返回分裂出的节点，没有返回不做操作
template <typename Key, typename Elem>
void TTTree<Key, Elem>::insertHelp(TTTreeNode<Elem, Key>* &subroot, 
	TTTreeNode<Elem, Key>* node,
	TTTreeNode<Elem, Key>* &reroot) {

	//当前节点为叶节点
	if (subroot->isLeaf()) {

		//当前节点未满，直接合并节点
		if (!subroot->isfool()) {
			subroot->add(node);
			delete node;
			node = nullptr;
		}

		//当前节点已满，分裂节点，返回上一级
		else
			spitNode(subroot, node, reroot);
		return;
	}

	//当前节点不为叶节点
	//tmp记录下一级插入返回的分裂出的节点
	TTTreeNode<Elem, Key>* tmp = nullptr;

	//插入节点键值小于当前节点左元素键值，插入左子树中
	if (node->leftKey() < subroot->leftKey())
		insertHelp(subroot->leftChild(), node, tmp);

	//插入节点键值介于当前节点左右元素键值之间，或当前节点未满，插入中间子树中
	else if ((!subroot->isfool()) || (node->leftKey() 
		< subroot->rightKey()))
		insertHelp(subroot->centreChild(), node, tmp);

	//插入节点键值大于等于当前节点右元素键值，插入右子树中
	else
		insertHelp(subroot->rightChild(), node, tmp);

	//如果下一级插入存在分裂的节点
	if (tmp != nullptr) {

		//当前节点不满，直接合并节点
		if (!subroot->isfool()) {
			subroot->add(tmp);
			delete tmp;
			tmp = nullptr;
		}

		//否则，分裂节点，返回上一级
		else
			spitNode(subroot, tmp, reroot);
		return;
	}

	return;
}

template <typename Key, typename Elem>
void TTTree<Key, Elem>::insert(Key k, Elem e) {

	//node为待插入节点，tmp接收insertHelp函数返回的分裂节点
	TTTreeNode<Elem, Key>* node = new TTTreeNode<Elem, Key>(k, e, 
		EMPTYKEY, EMPTYELEM);
	TTTreeNode<Elem, Key>* tmp = nullptr;

	//树为空，直接插入根节点
	if (root == nullptr) {
		root = node;
		return;
	}

	insertHelp(root, node, tmp);
	node = nullptr;

	//insertHelp函数存在返回的分裂节点
	//，将返回的节点设置为新的根节点
	//，当前根节点设置为返回节点的左子树
	if (tmp != nullptr) {
		tmp->leftChild() = root;
		root = tmp;
		return;
	}

	return;
}

//递归实现清空树中节点
template <typename Key, typename Elem>
void TTTree<Key, Elem>::clearHelp(TTTreeNode<Elem, Key>* subroot) {
	
	//当前节点为空节点，返回
	if (subroot == nullptr)
		return;

	//否则遍历所有子树后删除当前节点
	if (!subroot->isLeaf()) {
		clearHelp(subroot->rightChild());
		clearHelp(subroot->centreChild());
		clearHelp(subroot->leftChild());
	}
	delete subroot;
	return;
}

//实现将当前节点与inNode节点合并分裂出outNode节点
//，其中inNode节点默认不满且只有一个子树，当前节点默认已满
template <typename Key, typename Elem>
void TTTree<Key, Elem>::spitNode(TTTreeNode<Elem, Key>* &subroot, 
	TTTreeNode<Elem, Key>* inNode,
	TTTreeNode<Elem, Key>* &outNode) {

	//inNode节点的元素键值小于当前节点的左元素键值
	if (inNode->leftKey() < subroot->leftKey()) {
		outNode = new TTTreeNode<Elem, Key>(subroot->leftKey(), 
			subroot->left(), EMPTYKEY, EMPTYELEM,
			nullptr, subroot, nullptr);

		subroot->setLeft(subroot->rightKey(), subroot->right());
		subroot->setRight(EMPTYKEY, EMPTYELEM);

		inNode->leftChild() = subroot->leftChild();
		subroot->leftChild() = subroot->centreChild();
		subroot->centreChild() = subroot->rightChild();
		subroot->rightChild() = nullptr;
		subroot = inNode;
	}

	//inNode节点的元素键值介于当前节点的左右元素键值之间
	else if (inNode->leftKey() < subroot->rightKey()) {
		outNode = new TTTreeNode<Elem, Key>(inNode->leftKey(), 
			inNode->left(), EMPTYKEY, EMPTYELEM,
			nullptr, inNode, nullptr);

		inNode->setLeft(subroot->rightKey(), subroot->right());
		subroot->setRight(EMPTYKEY, EMPTYELEM);

		inNode->leftChild() = inNode->centreChild();
		inNode->centreChild() = subroot->rightChild();
		subroot->rightChild() = nullptr;
	}

	//inNode节点的元素键值大于等于当前节点的右元素键值
	else {
		outNode = new TTTreeNode<Elem, Key>(subroot->rightKey(), 
			subroot->right(), EMPTYKEY, EMPTYELEM,
			nullptr, inNode, nullptr);

		subroot->setRight(EMPTYKEY, EMPTYELEM);

		inNode->leftChild() = subroot->rightChild();
		subroot->rightChild() = nullptr;
	}

	return;
}
#endif // !TTTREE_H