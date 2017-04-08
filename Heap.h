//堆实现
#ifndef HEAP_H
#define HEAP_H

//小顶堆的数组实现
template <typename Elem>
class MinHeap {
	Elem* heap;                     //实现堆的数组
	unsigned maxSize = 10;          //堆的最大容量，默认为10
	unsigned count = 0;             //统计堆中的节点数
	
	//内部函数，返回对应的父、子节点
	unsigned parent(unsigned pos)const { return (pos - 1) / 2; }
	unsigned rightChild(unsigned pos)const { return 2 * pos + 2; }
	unsigned leftChild(unsigned pos)const { return 2 * pos + 1; }

	//判断节点是否为叶节点
	bool isLeaf(unsigned pos)const { return (pos >= count / 2) 
		&& (pos < count); }

	//内部函数，实现数组长度的拓展
	void expend() {
		maxSize *= 10;
		Elem* tmp = heap;
		heap = new Elem[maxSize]();
		for (unsigned i = 0; i < count; ++i)
			heap[i] = tmp[i];
		delete tmp;
	}

	//内部函数，将一个节点重新放置到合适的位置中
	void siftDown(unsigned pos) {

		//从目标节点向下遍历整棵树
		while (!isLeaf(pos)) {
			unsigned rc = rightChild(pos), lc = leftChild(pos);

			//m储存子节点中的较小节点
			unsigned m = lc;
			if (rc < count&&heap[rc] < heap[lc])
				m = rc;

			//当前节点值小于子节点的值，则已到达合适位置，返回
			if (heap[pos] <= heap[m])
				return;

			//否则，交换目标节点与较小子节点的位置，继续向下遍历
			Elem tmp = heap[pos];
			heap[pos] = heap[m];
			heap[m] = tmp;
			pos = m;
		}
	}

public:
	//构造函数与析构函数
	MinHeap() { heap = new Elem[maxSize](); }
	MinHeap(unsigned m) :maxSize(m) { heap = new Elem[maxSize]; }
	~MinHeap() { delete heap; }

	//向堆中插入节点
	void insert(const Elem &e) {

	    //数组空间不足，先拓展数组
		if (count >= maxSize - 1)
			expend();

		//先将插入节点放置在数组的最后位置
		unsigned cur = count++;
		heap[cur] = e;

		//自底向上将节点放置到合适的位置
		while (cur != 0 && heap[cur] < heap[parent(cur)]) {
			Elem tmp = heap[parent(cur)];
			heap[parent(cur)] = heap[cur];
			heap[cur] = tmp;
			cur = parent(cur);
		}
	}

	//获取堆中的顶节点（即最小节点）
	bool top(Elem &e) {
		if (isEmpty())
			return false;

		e = heap[0];
		return true;
	}

	//弹出堆中的顶节点
	void pop() {
		if (isEmpty())
			return;

		//将数组的最后一个节点放置到顶节点位置
		//，再对其执行siftDown函数
		unsigned cur = --count;
		if (cur != 0) {
			heap[0] = heap[cur];
			siftDown(0);
		}
	}

	unsigned size()const { return count; }              //返回堆的大小
	bool isEmpty()const { return count == 0; }          //判断堆是否为空
};

#endif // !HEAP_H

