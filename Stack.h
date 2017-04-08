//ջʵ��
#ifndef STACK_H
#define STACK_H

#include"ArrayList.h"

template <typename Elem>
class Stack {
	List<Elem>* stack;
public:
	Stack() { stack = new ArrayList<Elem>(); }           //���캯��
	~Stack() { delete stack; }                           //��������
	
	void pop() {                                         //����ջ����Ԫ��
		stack->moveToBack();
		stack->prev();
		stack->remove();
	}
	
	bool top(Elem &e)const {                             //����ջ����Ԫ��
		if (stack->isEmpty())
			return false;

		stack->moveToBack();
		stack->prev();
		stack->getValue(e);
		return true;
	}

	void push(const Elem &e) { stack->pushBack(e); }     //��Ԫ��ѹ��ջ
	bool isEmpty()const { return stack->isEmpty(); }     //�ж�ջ�Ƿ�Ϊ��
};
#endif // !STACK_H

