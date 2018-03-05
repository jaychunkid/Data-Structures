//栈实现
#ifndef STACK_H
#define STACK_H

#include"ArrayList.h"

template <typename Elem>
class Stack {
	List<Elem>* stack;
public:
	Stack() { stack = new ArrayList<Elem>(); }           //构造函数
	~Stack() { delete stack; }                           //析构函数
	
	void pop() {                                         //弹出栈顶的元素
		stack->moveToBack();
		stack->prev();
		stack->remove();
	}
	
	bool top(Elem &e)const {                             //返回栈顶的元素
		if (stack->isEmpty())
			return false;

		stack->moveToBack();
		stack->prev();
		stack->getValue(e);
		return true;
	}

	void push(const Elem &e) { stack->pushBack(e); }     //将元素压入栈
	bool isEmpty()const { return stack->isEmpty(); }     //判断栈是否为空
};
#endif // !STACK_H

