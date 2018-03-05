//2-3���ڵ�ʵ��
#ifndef TTTREENODE_H
#define TTTREENODE_H

extern int EMPTYKEY;
extern int EMPTYELEM;

template <typename Key, typename Elem>
class TTTreeNode {
private:
	Elem left_elem;           //��Ԫ��ֵ
	Elem right_elem;          //��Ԫ��ֵ
	Key left_key;             //��Ԫ�ؼ�ֵ
	Key right_key;            //��Ԫ�ؼ�ֵ

	//ָ���ӽڵ��ָ��
	TTTreeNode* left_child;
	TTTreeNode* centre_child;          
	TTTreeNode* right_child;   

public:
	//���캯��
	TTTreeNode(const Key &lk, const Elem &le, const Key &rk, const Elem &re,
		TTTreeNode* l = nullptr, TTTreeNode* c = nullptr, 
		TTTreeNode* r = nullptr):left_key(lk), left_elem(le), 
		right_key(rk), right_elem(re), left_child(l), 
		centre_child(c), right_child(r) {}

	//���ض�Ӧ�ļ�ֵ��ֵ
	Key leftKey()const { return left_key; }
	Key rightKey()const { return right_key; }
	Elem left()const { return left_elem; }
	Elem right()const { return right_elem; }

	//��ȡ��Ӧ�Ľڵ�ָ��
	TTTreeNode* &leftChild() { return left_child; }
	TTTreeNode* cleftChild()const { return left_child; }

	TTTreeNode* &centreChild() { return centre_child; }
	TTTreeNode* ccentreChild()const { return centre_child; }

	TTTreeNode* &rightChild() { return right_child; }
	TTTreeNode* crightChild()const { return right_child; }

	//���ö�ӦԪ�ص�����
	void setLeft(const Key &k, const Elem &e) {
		left_key = k;
		left_elem = e;
	}

	void setRight(const Key &k, const Elem &e) {
		right_key = k;
		right_elem = e;
	}

	//���ö�Ӧ�ڵ��ָ��
	void setLeftChild(TTTreeNode* lc) { left_child = lc; }
	void setCentreChild(TTTreeNode* cc) { centre_child = cc; }
	void setRightChild(TTTreeNode* rc) { right_child = rc; }

	//�жϸýڵ��Ƿ�����
	bool isfool()const {
		return right_key != EMPTYKEY && right_elem != EMPTYELEM &&
			left_key != EMPTYKEY && left_elem != EMPTYELEM;
	}

	//�жϸýڵ��Ƿ�ΪҶ�ڵ�
	bool isLeaf()const { 
		return right_child == nullptr && centre_child == nullptr && 
			left_child == nullptr;
	}

	//����һ���ڵ�ϲ���Ĭ��
	//���ڵ㶼δ���Ҵ���ڵ�ֻ��һ���ӽڵ�
	void add(TTTreeNode* node);
};

template<typename Key, typename Elem>
void TTTreeNode<Key, Elem>::add(TTTreeNode* node) {

	//�ֽڵ�ļ�ֵ���ڴ���ڵ�ļ�ֵ
	//���򽫴���ڵ��Ԫ����Ϊ�ֽڵ��
	//��Ԫ�أ��ֽڵ�Ԫ������
	if (node->leftKey() < left_key) {
		setRight(left_key, left_elem);
		right_child = centre_child;
		centre_child = node->centreChild();
		setLeft(node->leftKey(), node->left());
	}

	//���򽫴���ڵ��Ԫ����Ϊ�ֽڵ����Ԫ��
	else {
		setRight(node->leftKey(), node->left());
		right_child = node->centreChild();
	}

	return;
}
#endif // !TTTREENODE_H

