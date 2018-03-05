//2-3��ʵ�֣�ɾ���ڵ㹦��δʵ�֣�
#ifndef TTTREE_H
#define TTTREE_H

#include"TTTreeNode.h"

template <typename Key, typename Elem>
class TTTree {
private:
	TTTreeNode<Elem, Key>* root;          //���ڵ�

	//�ڲ�����
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
	//���캯������������
	TTTree(TTTreeNode<Elem, Key>* r = nullptr) :root(r) {}
	~TTTree() { clear(); }

	//������������ֵΪk��Ԫ�أ������ض�ӦԪ��
	bool search(const Key &k, Elem &e)const {
		e = searchHelp(root, k);
		return e != EMPTYELEM;
	}

	//������нڵ�
	void clear() {
		clearHelp(root);
		root = nullptr;
	}
	
	//�����в����ֵΪk��ֵΪe��Ԫ��
	void insert(Key k, Elem e);
};

//�ݹ�ʵ��������������ֵΪk��Ԫ��
template <typename Key, typename Elem>
Elem TTTree<Key, Elem>::searchHelp(const TTTreeNode<Elem, Key>* subroot, 
	const Key &k)const {
	
	//δ�ҵ�Ŀ��Ԫ�أ����ؿ�ֵ
	if (subroot == nullptr)
		return EMPTYELEM;

	//Ŀ��Ԫ�ؼ�ֵС�ڵ�ǰ�ڵ���Ԫ�ؼ�ֵ����������������
	else if (subroot->leftKey() > k)
		return searchHelp(subroot->cleftChild(), k);

	//Ŀ��Ԫ��Ϊ��ǰ�ڵ���Ԫ�أ�����
	else if (subroot->leftKey() == k)
		return subroot->left();

	//Ŀ��Ԫ�ؼ�ֵ���ڵ�ǰ�ڵ�����Ԫ�ؼ�ֵ֮�䣬��ǰ�ڵ�δ�������м�����������
	else if ((!subroot->isfool()) || subroot->rightKey() > k)
		return searchHelp(subroot->ccentreChild(), k);

	//Ŀ��Ԫ��Ϊ��ǰ�ڵ���Ԫ�أ�����
	else if (subroot->rightKey() == k)
		return subroot->right();

	//Ŀ��Ԫ�ؼ�ֵ���ڵ��ڵ�ǰ�ڵ���Ԫ�ؼ�ֵ����������������
	else
		return searchHelp(subroot->crightChild(), k);
}

//�ݹ�ʵ�������в���ڵ�
//nodeΪ������ڵ㣬Ĭ�ϲ��������ֻ��һ������
//reroot�ڵ㷵�ط��ѳ��Ľڵ㣬û�з��ز�������
template <typename Key, typename Elem>
void TTTree<Key, Elem>::insertHelp(TTTreeNode<Elem, Key>* &subroot, 
	TTTreeNode<Elem, Key>* node,
	TTTreeNode<Elem, Key>* &reroot) {

	//��ǰ�ڵ�ΪҶ�ڵ�
	if (subroot->isLeaf()) {

		//��ǰ�ڵ�δ����ֱ�Ӻϲ��ڵ�
		if (!subroot->isfool()) {
			subroot->add(node);
			delete node;
			node = nullptr;
		}

		//��ǰ�ڵ����������ѽڵ㣬������һ��
		else
			spitNode(subroot, node, reroot);
		return;
	}

	//��ǰ�ڵ㲻ΪҶ�ڵ�
	//tmp��¼��һ�����뷵�صķ��ѳ��Ľڵ�
	TTTreeNode<Elem, Key>* tmp = nullptr;

	//����ڵ��ֵС�ڵ�ǰ�ڵ���Ԫ�ؼ�ֵ��������������
	if (node->leftKey() < subroot->leftKey())
		insertHelp(subroot->leftChild(), node, tmp);

	//����ڵ��ֵ���ڵ�ǰ�ڵ�����Ԫ�ؼ�ֵ֮�䣬��ǰ�ڵ�δ���������м�������
	else if ((!subroot->isfool()) || (node->leftKey() 
		< subroot->rightKey()))
		insertHelp(subroot->centreChild(), node, tmp);

	//����ڵ��ֵ���ڵ��ڵ�ǰ�ڵ���Ԫ�ؼ�ֵ��������������
	else
		insertHelp(subroot->rightChild(), node, tmp);

	//�����һ��������ڷ��ѵĽڵ�
	if (tmp != nullptr) {

		//��ǰ�ڵ㲻����ֱ�Ӻϲ��ڵ�
		if (!subroot->isfool()) {
			subroot->add(tmp);
			delete tmp;
			tmp = nullptr;
		}

		//���򣬷��ѽڵ㣬������һ��
		else
			spitNode(subroot, tmp, reroot);
		return;
	}

	return;
}

template <typename Key, typename Elem>
void TTTree<Key, Elem>::insert(Key k, Elem e) {

	//nodeΪ������ڵ㣬tmp����insertHelp�������صķ��ѽڵ�
	TTTreeNode<Elem, Key>* node = new TTTreeNode<Elem, Key>(k, e, 
		EMPTYKEY, EMPTYELEM);
	TTTreeNode<Elem, Key>* tmp = nullptr;

	//��Ϊ�գ�ֱ�Ӳ�����ڵ�
	if (root == nullptr) {
		root = node;
		return;
	}

	insertHelp(root, node, tmp);
	node = nullptr;

	//insertHelp�������ڷ��صķ��ѽڵ�
	//�������صĽڵ�����Ϊ�µĸ��ڵ�
	//����ǰ���ڵ�����Ϊ���ؽڵ��������
	if (tmp != nullptr) {
		tmp->leftChild() = root;
		root = tmp;
		return;
	}

	return;
}

//�ݹ�ʵ��������нڵ�
template <typename Key, typename Elem>
void TTTree<Key, Elem>::clearHelp(TTTreeNode<Elem, Key>* subroot) {
	
	//��ǰ�ڵ�Ϊ�սڵ㣬����
	if (subroot == nullptr)
		return;

	//�����������������ɾ����ǰ�ڵ�
	if (!subroot->isLeaf()) {
		clearHelp(subroot->rightChild());
		clearHelp(subroot->centreChild());
		clearHelp(subroot->leftChild());
	}
	delete subroot;
	return;
}

//ʵ�ֽ���ǰ�ڵ���inNode�ڵ�ϲ����ѳ�outNode�ڵ�
//������inNode�ڵ�Ĭ�ϲ�����ֻ��һ����������ǰ�ڵ�Ĭ������
template <typename Key, typename Elem>
void TTTree<Key, Elem>::spitNode(TTTreeNode<Elem, Key>* &subroot, 
	TTTreeNode<Elem, Key>* inNode,
	TTTreeNode<Elem, Key>* &outNode) {

	//inNode�ڵ��Ԫ�ؼ�ֵС�ڵ�ǰ�ڵ����Ԫ�ؼ�ֵ
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

	//inNode�ڵ��Ԫ�ؼ�ֵ���ڵ�ǰ�ڵ������Ԫ�ؼ�ֵ֮��
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

	//inNode�ڵ��Ԫ�ؼ�ֵ���ڵ��ڵ�ǰ�ڵ����Ԫ�ؼ�ֵ
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