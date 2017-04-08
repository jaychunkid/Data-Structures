//队列实现
#ifndef QUEUE_H
#define QUEUE_H

#include"LinkedList.h"

template <typename Elem>
class Queue {
	List<Elem>* queue;
public:
	Queue() { queue = new LinkedList<Elem>(); }          //构造函数
	~Queue() { delete queue; }                           //析构函数
	
	void pop() {                                         //弹出队列的首元素
		queue->moveToFront();
		queue->remove();
	}

	bool front(Elem &e)const {				             //返回队列的头元素
		queue->moveToFront();
		if (queue->getValue(e))
			return true;
		else return false;
	}

	bool back(Elem &e)const {                            //返回队列的尾元素
		if (queue->isEmpty())
			return false;

		queue->moveToBack();
		queue->prev();
		queue->getValue(e);
		return true;
	}

	void push(const Elem &e) { queue->pushBack(e); }     //向队列尾部追加元素
	bool isEmpty()const { return queue->isEmpty(); }     //判断队列是否为空
};
#endif // !QUEUE_H

