//列表的链表实现
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include"List.h"

//链表节点类
template<typename Elem>
class LinkedNode {
	Elem elem;                                 //当前节点元素
	LinkedNode* prev_node = nullptr;           //指向前一个节点
	LinkedNode* next_node = nullptr;           //指向后一个节点

public:
	//构造函数
	LinkedNode() {}
	LinkedNode(Elem e) :elem(e) {}

	//获取当前节点元素
	Elem value()const { return elem; }

	//获取上一个、下一个节点的指针
	LinkedNode* prev()const { return prev_node; }
	LinkedNode* next()const { return next_node; }

	//设置节点属性
	void setElem(const Elem &e) { elem = e; }
	void setPrev(LinkedNode* p) { prev_node = p; }
	void setNext(LinkedNode* n) { next_node = n; }
};

//链表类
template <typename Elem>
class LinkedList:public List<Elem> {
	LinkedNode<Elem>* head = nullptr;          //指向头节点
	LinkedNode<Elem>* tail = nullptr;          //指向尾节点
	LinkedNode<Elem>* cur = nullptr;           //指向栅栏位置的上一个节点
	unsigned cur_pos = 0;                      //指示栅栏当前位置
	unsigned size = 0;                         //队列长度

public:
	LinkedList() {
		//链表第一个元素仅作指示作用，不存储数据
		head = new LinkedNode<Elem>();          
		cur = tail = head;
	}

	~LinkedList() {
		clear();
		delete head;
	}

	void clear() {
		cur = head;

		//从表尾向表头删除节点，不删除第一个节点
		while (tail != head) {
			LinkedNode<Elem>* tmp = tail;
			tail = tmp->prev();
			delete tmp;
		}
	}

	//向cur指针指向节点的后方插入节点
	void insert(const Elem &e) {
		LinkedNode<Elem>* node = new LinkedNode<Elem>(e);
		node->setPrev(cur);
		node->setNext(cur->next());

		if (cur->next() != nullptr)
			cur->next()->setPrev(node);
		cur->setNext(node);

		//如果插入位置在表尾，更新尾节点指针
		if (tail == cur)
			tail = node;
		
		//cur指向新插入的节点
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

	//删除cur指针指向节点的后一个节点
	void remove() {
		if (cur != tail) {
			LinkedNode<Elem>* tmp = cur->next();

			//如果删除的是尾节点，更新尾节点指针
			if (tmp == tail)
				tail = cur;

			//否则更新删除节点的下一个节点
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
		
		//已经指向目标位置，不需要任何操作
		if (cp == pos) return true;

		//cur指针位置在目标位置前，后移指针
		else if (cp < pos)
			for (; cp != pos; ++cp)
				cur = cur->next();

		//cur指针位置在目标位置后，前移指针
		else
			for (; cp != pos; --cp)
				cur = cur->prev();

		//更新cur_pos的值
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

		//如果栅栏已指向表头，不做任何操作
		if (cur != head) {
			cur = cur->prev();
			--cur_pos;
		}
	}

	void next() {

		//如果栅栏已指向表尾，不做任何操作
		if (cur != tail) {
			cur = cur->next();
			++cur_pos;
		}
	}

	bool isEmpty()const { return !size; }
	unsigned length()const { return size; }
};
#endif // !LINKEDLIST_H

