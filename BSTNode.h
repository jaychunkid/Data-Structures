//�����������ڵ�ʵ��
#ifndef BSTNODE_H
#define BSTNODE_H

template <typename Key, typename Elem>
class BSTNode {
	Key key;                       //�ڵ�Ԫ�صļ�ֵ
	Elem elem;                     //�ڵ�Ԫ�ص�ֵ
	BSTNode* left_child;           //ָ��������
	BSTNode* right_child;          //ָ��������

public:
	//���캯��
	BSTNode() {}     
	BSTNode(const Key &k, const Elem &e, 
		BSTNode* lc = nullptr, BSTNode* rc = nullptr) 
		:key(k), elem(e), left_child(lc), right_child(rc) {}

	//��ȡ�ڵ�����
	Key getKey()const { return key; }
	Elem getElem()const { return elem; }
	BSTNode* leftChild()const { return left_child; }
	BSTNode* rightChild()const { return right_child; }

	//���ýڵ�����
	void setElem(Key k, Elem e) { key = k; elem = e; }
	void setLeft(BSTNode* lc) { left_child = lc; }  
	void setRight(BSTNode* rc) { right_child = rc; }

	//�жϽڵ��Ƿ�ΪҶ�ڵ�
	bool isLeaf()const { return left_child == nullptr
		&&right_child == nullptr; }
};

#endif // !BSTNODE_H
