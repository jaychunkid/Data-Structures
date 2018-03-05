//�б������ʵ��
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include"List.h"

//����ڵ���
template<typename Elem>
class LinkedNode {
	Elem elem;                                 //��ǰ�ڵ�Ԫ��
	LinkedNode* prev_node = nullptr;           //ָ��ǰһ���ڵ�
	LinkedNode* next_node = nullptr;           //ָ���һ���ڵ�

public:
	//���캯��
	LinkedNode() {}
	LinkedNode(Elem e) :elem(e) {}

	//��ȡ��ǰ�ڵ�Ԫ��
	Elem value()const { return elem; }

	//��ȡ��һ������һ���ڵ��ָ��
	LinkedNode* prev()const { return prev_node; }
	LinkedNode* next()const { return next_node; }

	//���ýڵ�����
	void setElem(const Elem &e) { elem = e; }
	void setPrev(LinkedNode* p) { prev_node = p; }
	void setNext(LinkedNode* n) { next_node = n; }
};

//������
template <typename Elem>
class LinkedList:public List<Elem> {
	LinkedNode<Elem>* head = nullptr;          //ָ��ͷ�ڵ�
	LinkedNode<Elem>* tail = nullptr;          //ָ��β�ڵ�
	LinkedNode<Elem>* cur = nullptr;           //ָ��դ��λ�õ���һ���ڵ�
	unsigned cur_pos = 0;                      //ָʾդ����ǰλ��
	unsigned size = 0;                         //���г���

public:
	LinkedList() {
		//�����һ��Ԫ�ؽ���ָʾ���ã����洢����
		head = new LinkedNode<Elem>();          
		cur = tail = head;
	}

	~LinkedList() {
		clear();
		delete head;
	}

	void clear() {
		cur = head;

		//�ӱ�β���ͷɾ���ڵ㣬��ɾ����һ���ڵ�
		while (tail != head) {
			LinkedNode<Elem>* tmp = tail;
			tail = tmp->prev();
			delete tmp;
		}
	}

	//��curָ��ָ��ڵ�ĺ󷽲���ڵ�
	void insert(const Elem &e) {
		LinkedNode<Elem>* node = new LinkedNode<Elem>(e);
		node->setPrev(cur);
		node->setNext(cur->next());

		if (cur->next() != nullptr)
			cur->next()->setPrev(node);
		cur->setNext(node);

		//�������λ���ڱ�β������β�ڵ�ָ��
		if (tail == cur)
			tail = node;
		
		//curָ���²���Ľڵ�
		cur = node;
		++cur_pos;
		++size;
	}

	void pushBack(const Elem &e) {
		LinkedNode<Elem>* node = new LinkedNode<Elem>(e);
		node->setPrev(tail);

		tail->setNext(node);
		tail = node;

		++size;
	}

	//ɾ��curָ��ָ��ڵ�ĺ�һ���ڵ�
	void remove() {
		if (cur != tail) {
			LinkedNode<Elem>* tmp = cur->next();

			//���ɾ������β�ڵ㣬����β�ڵ�ָ��
			if (tmp == tail)
				tail = cur;

			//�������ɾ���ڵ����һ���ڵ�
			else
				tmp->next()->setPrev(cur);

			cur->setNext(tmp->next());
			delete tmp;
			--size;
		}
		return;
	}

	unsigned curPos() { return cur_pos; }

	bool setPos(unsigned pos) {
		if (pos > size)
			return false;

		unsigned cp = curPos();
		
		//�Ѿ�ָ��Ŀ��λ�ã�����Ҫ�κβ���
		if (cp == pos) return true;

		//curָ��λ����Ŀ��λ��ǰ������ָ��
		else if (cp < pos)
			for (; cp != pos; ++cp)
				cur = cur->next();

		//curָ��λ����Ŀ��λ�ú�ǰ��ָ��
		else
			for (; cp != pos; --cp)
				cur = cur->prev();

		//����cur_pos��ֵ
		cur_pos = pos;
		return true;
	}

	void moveToFront() { 
		cur = head;
		cur_pos = 0;
	}

	void moveToBack() { 
		cur = tail;
		cur_pos = size;
	}

	bool getValue(Elem &e)const { 
		if (cur == tail)
			return false;

		e = cur->next()->value();
		return true;
	}

	void prev() {

		//���դ����ָ���ͷ�������κβ���
		if (cur != head) {
			cur = cur->prev();
			--cur_pos;
		}
	}

	void next() {

		//���դ����ָ���β�������κβ���
		if (cur != tail) {
			cur = cur->next();
			++cur_pos;
		}
	}

	bool isEmpty()const { return !size; }
	unsigned length()const { return size; }
};
#endif // !LINKEDLIST_H

