//列表的数组实现
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include"List.h"

template <typename Elem>
class ArrayList:public List<Elem> {
	Elem* list = nullptr;
	unsigned fence = 0;              //栅栏指向位置
	unsigned max_size = 10;          //默认初始最大数组长度为10
	unsigned size = 0;               //列表长度

	//内部方法实现数组长度拓展
	void expend() {
		max_size *= 10;                                 //在现有的空间基础上扩大十倍
		Elem* tmp = list;
		list = new Elem[max_size]();
		for (unsigned i = 0; i < size; ++i)
			list[i] = tmp[i];
		delete[]tmp;
		return;
	}

public:
	ArrayList() { list = new Elem[max_size](); }        //构造函数
	~ArrayList() { delete[]list; }                      //析构函数

	void clear() { fence = size = 0; }

	void pushBack(const Elem &e) {                      
		
		//数组空间不足，拓展数组长度
		if (size == max_size - 1)
			expend();

		list[size++] = e;
	}

	//向fence所指向的位置插入元素
	void insert(const Elem &e) {                        
		if (size >= max_size - 1)
			expend();

		//如果fence不指向表尾，则将fence指向位置及之后的元素向后移动一个位置
		if (fence != size)
			for (unsigned i = size - 1; i >= fence; --i)
				list[i + 1] = list[i];

		//fence指向原处于该位置的元素
		list[fence++] = e;
		++size;
		return;
	}

	//删除fence所指向位置的元素
	void remove() {                                     
		if (fence < size) {

			//将fence指向位置及之后的元素向前移动一个位置
			for (unsigned i = fence; i < size; ++i)
				list[i] = list[i + 1];

			--size;
		}
		return;
	}

	unsigned curPos() { return fence; }                 

	bool setPos(unsigned pos) {                          
		
		//设置的位置越过了表尾，操作失败
		if (pos > size)
			return false;

		fence = pos;
		return true;
	}

	void moveToFront() { fence = 0; }                   
	void moveToBack() { fence = size; }                

	bool getValue(Elem &e)const {                       
		
		//栅栏指向位置越过了表尾，操作失败
		if (fence >= size)
			return false;

		e = list[fence];
		return true;
	}

	void prev() {

		//如果栅栏已指向表头，不做任何操作
		if (fence > 0)
			--fence;
	}

	void next() {  

		//如果栅栏已指向表尾，不做任何操作
		if (fence < size)
			++fence;
	}

	bool isEmpty()const { return !size; }              
	unsigned length()const { return size; }            
};
#endif // !ARRAYLIST_H

