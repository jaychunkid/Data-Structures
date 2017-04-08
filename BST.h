//����������ʵ��
//�������еĽڵ��ֵС�ڸ��ڵ��ֵ
//�������еĽڵ��ֵ���ڵ��ڸ��ڵ��ֵ
#ifndef BST_H
#define BST_H

#include"BSTNode.h"
#include<iostream>
using std::cout;

template <typename Key, typename Elem>
class BST {
	BSTNode<Key, Elem>* root = nullptr;          //�����ڵ�
	unsigned count = 0;                          //ͳ�ƽڵ����

	//�ڲ��ݹ麯��
	void clearHelp(BSTNode<Key, Elem>*);
	BSTNode<Key, Elem>* insertHelp(BSTNode<Key, Elem>* subroot, const Key &k, const Elem &e);
	BSTNode<Key, Elem>* searchHelp(BSTNode<Key, Elem>* subroot, const Key &k)const;
	BSTNode<Key, Elem>* removeHelp(BSTNode<Key, Elem>* subroot, const Key &k);
	void printHelp(const BSTNode<Key, Elem>*, unsigned)const;
	BSTNode<Key, Elem>* deleteMin(BSTNode<Key, Elem>* subroot);
	BSTNode<Key, Elem>* getMin(BSTNode<Key, Elem>* subroot);

public:
	//���캯������������
	BST() {}               
	~BST() { clear(); }   
	
	//������е����нڵ�
	void clear() {          
		clearHelp(root);
		root = nullptr;
		count = 0;
	}
	
	//�����в���ڵ�
	void insert(const Key &k, const Elem &e) {  
		root = insertHelp(root, k, e);
		++count;
	}  
	
	//�����в��Ҷ�Ӧ��ֵk�Ľڵ㣬���ؽڵ�Ԫ�ص�ֵ
	bool search(const Key &k, Elem &e)const {   
		BSTNode<Key, Elem>* tmp = searchHelp(root, k);
		if (tmp == nullptr)
			return false;
		else {
			e = tmp->getElem();
			return true;
		}
	}
	
	//ɾ�����ж�Ӧ��ֵk�Ľڵ㣬���ر�ɾ���ڵ�Ԫ�ص�ֵ
	bool remove(const Key &k, Elem &e) {
		if (!search(k, e))
			return false;
		else {
			root = removeHelp(root, k);
			--count;
			return true;
		}
	}
	
	//������ṹ
	void print()const {
		printHelp(root, 0);
	}

	//�������Ĵ�С���ڵ���Ŀ��
	unsigned size() { return count; }

	//�ж����Ƿ�Ϊ��
	bool isEmpty()const { return !count; }     
};

//�ݹ麯��ʵ��ɾ���������Ľڵ�
template <typename Key, typename Elem>
void BST<Key, Elem>::clearHelp(BSTNode<Key, Elem>* subroot) {
	
	//�����սڵ㣬ֱ�ӷ���
	if (subroot == nullptr)
		return;

	//�ǿսڵ㣬��������������ɾ���ڵ㣬����
	else {
		clearHelp(subroot->leftChild());
		clearHelp(subroot->rightChild());
		delete subroot;
		return;
	}
}

//�ݹ麯��ʵ�������в���ڵ�
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::insertHelp(BSTNode<Key, Elem>* subroot, 
	const Key &k, const Elem &e) {

	//�����սڵ㣬����ڵ�󷵻�
	if (subroot == nullptr)
		return new BSTNode<Key, Elem>(k, e);
	
	//������ڵ��ֵС�ڸ��ڵ��ֵ�����½ڵ�������
	if (k < subroot->getKey())
		subroot->setLeft(insertHelp(subroot->leftChild(), k, e));

	//������ڵ��ֵ���ڵ��ڸ��ڵ��ֵ�����½ڵ�������
	else
		subroot->setRight(insertHelp(subroot->rightChild(), k, e));

	return subroot;          //���ظ��º�Ľڵ�
}

//�ݹ麯��ʵ������������ָ���ڵ�
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::searchHelp(BSTNode<Key, Elem>* subroot, const Key &k)const {

	//�����սڵ㣬ָ���ڵ㲻���ڣ����ؿ�ֵ
	if (subroot == nullptr)
		return nullptr;

	//�����ҽڵ��ֵС�ڸ��ڵ��ֵ������������
	if (k < subroot->getKey())
		return searchHelp(subroot->leftChild(), k);

	//�����ҽڵ��ֵ���ڸ��ڵ��ֵ������������
	else if (k > subroot->getKey())
		return searchHelp(subroot->rightChild(), k);

	//���ڵ�Ϊ�����ҽڵ㣬����
	else
		return subroot;
}

//�ݹ麯��ʵ��ɾ�����е�ָ���ڵ�
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::removeHelp(BSTNode<Key, Elem>* subroot, const Key &k) {

	//��ɾ���ڵ��ֵС�ڸ��ڵ��ֵ������������
	if (k < subroot->getKey()) {
		subroot->setLeft(removeHelp(subroot->leftChild(), k));
		return subroot;
	}

	//��ɾ���ڵ��ֵ���ڸ��ڵ��ֵ������������
	else if (k > subroot->getKey()) {
		subroot->setRight(removeHelp(subroot->rightChild(), k));
		return subroot;
	}

	//�ҵ���ɾ���ڵ�
	else {

		//��ɾ���ڵ���Ҷ�ڵ㣬ֱ��ɾ��
		if (subroot->isLeaf()) {
			delete subroot;
			return nullptr;
		}

		BSTNode<Key, Elem>* tmp = nullptr;

		//��ɾ���ڵ�ֻ�������������������ڵ��滻��ɾ���ڵ�λ��
		if (subroot->leftChild() == nullptr) {
			tmp = subroot->rightChild();
			delete subroot;
			return tmp;
		}

		//��ɾ���ڵ�ֻ�������������������ڵ��滻��ɾ���ڵ�λ��
		if (subroot->rightChild() == nullptr) {
			tmp = subroot->leftChild();
			delete subroot;
			return tmp;
		}
	
		//��ɾ���ڵ����������������������л�ȡ��С�ڵ��滻��ɾ���ڵ�λ��
		tmp = getMin(subroot->rightChild());
		subroot->setRight(deleteMin(subroot->rightChild()));
		subroot->setElem(tmp->getKey(), tmp->getElem());
		delete tmp;

		return subroot;          //���ظ��º�ĸ��ڵ�
	}
}

//�ݹ�ʵ��ɾ�����е���С�ڵ�
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::deleteMin(BSTNode<Key, Elem>* subroot) {

	//���ڵ�Ϊ�գ����ؿ�ֵ
	if (subroot == nullptr)
		return nullptr;

	//��ǰ�ڵ�����С�ڵ㣬���������ڵ������ǰ�ڵ�λ��
	if (subroot->leftChild() == nullptr) {
		BSTNode<Key, Elem>* tmp = subroot->rightChild();
		delete subroot;
		return tmp;
	}
	
	//��ǰ�ڵ㲻����С�ڵ㣬����������
	else {
		subroot->setLeft(deleteMin(subroot->leftChild()));
		return subroot;
	}
}

//�ݹ�ʵ�ֻ�ȡ������С�Ľڵ�
template <typename Key, typename Elem>
BSTNode<Key, Elem>* BST<Key, Elem>::getMin(BSTNode<Key, Elem>* subroot) {

	//���ڵ�Ϊ�գ����ؿ�ֵ
	if (subroot == nullptr)
		return nullptr;

	//��ǰ�ڵ�����С�ڵ㣬���ؽڵ�
	if (subroot->leftChild() == nullptr)
		return subroot;

	//��ǰ�ڵ㲻����С�ڵ㣬���������в���
	else
		return getMin(subroot->leftChild());
}

//�ݹ�ʵ��������Ľṹ����ǰ�ڵ�ĸ߶�Ϊlevel
template <typename Key, typename Elem>
void BST<Key, Elem>::printHelp(const BSTNode<Key, Elem>* subroot, unsigned level)const {
	
	//�����սڵ㣬ֱ�ӷ���
	if (subroot == nullptr)
		return;

	//�ȱ���������
	printHelp(subroot->rightChild(), level + 1);

	//���ݵ�ǰ�ڵ�ĸ߶�ʹ�ÿո�����Ƹ�ʽ
	for (unsigned i = 0; i < level; ++i)
		cout << ' ';

	//�����ǰ�ڵ��ֵ
	cout << subroot->getKey() << '\n';

	//������������
	printHelp(subroot->leftChild(), level + 1);
	return;
}
#endif // !BST_H

