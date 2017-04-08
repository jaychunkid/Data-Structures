//列表抽象类
#ifndef LIST_H
#define LIST_H

template <typename Elem>
class List {
public:
	virtual void clear() = 0;                          //清空列表内容
	virtual void insert(const Elem &e) = 0;			   //向指定位置插入元素
	virtual void pushBack(const Elem &e) = 0;          //向列表尾部追加元素
	virtual void remove() = 0;                         //从指定位置删除元素

	virtual unsigned curPos() = 0;                     //返回当前指定位置
	virtual bool setPos(unsigned pos) = 0;             //设置指定的位置
	virtual void moveToFront() = 0;                    //设置指定位置至表头
	virtual void moveToBack() = 0;                     //设置指定位置至表尾
	virtual bool getValue(Elem &e)const = 0;           //获取当前指定位置的元素
	virtual void prev() = 0;                           //将指定位置向前移动一位
	virtual void next() = 0;                           //将指定位置向后移动一位

	virtual bool isEmpty()const = 0;                   //判断列表是否为空
	virtual unsigned length()const = 0;                //返回列表长度
};
#endif // !LIST_H

