//����ʵ��
#ifndef QUEUE_H
#define QUEUE_H

#include"LinkedList.h"

template <typename Elem>
class Queue {
	List<Elem>* queue;
public:
	Queue() { queue = new LinkedList<Elem>(); }          //���캯��
	~Queue() { delete queue; }                           //��������
	
	void pop() {                                         //�������е���Ԫ��
		queue->moveToFront();
		queue->remove();
	}

	bool front(Elem &e)const {				             //���ض��е�ͷԪ��
		queue->moveToFront();
		if (queue->getValue(e))
			return true;
		else return false;
	}

	bool back(Elem &e)const {                            //���ض��е�βԪ��
		if (queue->isEmpty())
			return false;

		queue->moveToBack();
		queue->prev();
		queue->getValue(e);
		return true;
	}

	void push(const Elem &e) { queue->pushBack(e); }     //�����β��׷��Ԫ��
	bool isEmpty()const { return queue->isEmpty(); }     //�ж϶����Ƿ�Ϊ��
};
#endif // !QUEUE_H

