//2-3树节点实现
#ifndef TTTREENODE_H
#define TTTREENODE_H

extern int EMPTYKEY;
extern int EMPTYELEM;

template <typename Key, typename Elem>
class TTTreeNode {
private:
	Elem left_elem;           //左元素值
	Elem right_elem;          //右元素值
	Key left_key;             //左元素键值
	Key right_key;            //右元素键值

	//指向子节点的指针
	TTTreeNode* left_child;
	TTTreeNode* centre_child;          
	TTTreeNode* right_child;   

public:
	//构造函数
	TTTreeNode(const Key &lk, const Elem &le, const Key &rk, const Elem &re,
		TTTreeNode* l = nullptr, TTTreeNode* c = nullptr, 
		TTTreeNode* r = nullptr):left_key(lk), left_elem(le), 
		right_key(rk), right_elem(re), left_child(l), 
		centre_child(c), right_child(r) {}

	//返回对应的键值和值
	Key leftKey()const { return left_key; }
	Key rightKey()const { return right_key; }
	Elem left()const { return left_elem; }
	Elem right()const { return right_elem; }

	//获取对应的节点指针
	TTTreeNode* &leftChild() { return left_child; }
	TTTreeNode* cleftChild()const { return left_child; }

	TTTreeNode* &centreChild() { return centre_child; }
	TTTreeNode* ccentreChild()const { return centre_child; }

	TTTreeNode* &rightChild() { return right_child; }
	TTTreeNode* crightChild()const { return right_child; }

	//设置对应元素的属性
	void setLeft(const Key &k, const Elem &e) {
		left_key = k;
		left_elem = e;
	}

	void setRight(const Key &k, const Elem &e) {
		right_key = k;
		right_elem = e;
	}

	//设置对应节点的指针
	void setLeftChild(TTTreeNode* lc) { left_child = lc; }
	void setCentreChild(TTTreeNode* cc) { centre_child = cc; }
	void setRightChild(TTTreeNode* rc) { right_child = rc; }

	//判断该节点是否已满
	bool isfool()const {
		return right_key != EMPTYKEY && right_elem != EMPTYELEM &&
			left_key != EMPTYKEY && left_elem != EMPTYELEM;
	}

	//判断该节点是否为叶节点
	bool isLeaf()const { 
		return right_child == nullptr && centre_child == nullptr && 
			left_child == nullptr;
	}

	//与另一个节点合并，默认
	//两节点都未满且传入节点只有一个子节点
	void add(TTTreeNode* node);
};

template<typename Key, typename Elem>
void TTTreeNode<Key, Elem>::add(TTTreeNode* node) {

	//现节点的键值大于传入节点的键值
	//，则将传入节点的元素作为现节点的
	//左元素，现节点元素右移
	if (node->leftKey() < left_key) {
		setRight(left_key, left_elem);
		right_child = centre_child;
		centre_child = node->centreChild();
		setLeft(node->leftKey(), node->left());
	}

	//否则将传入节点的元素作为现节点的右元素
	else {
		setRight(node->leftKey(), node->left());
		right_child = node->centreChild();
	}

	return;
}
#endif // !TTTREENODE_H

