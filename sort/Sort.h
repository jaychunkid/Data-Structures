//排序方法实现（从小到大排序）
#ifndef SORT_H
#define SORT_H

//交换数组A中p1，p2位置的值
template <typename Elem>
void swap(Elem* A, unsigned p1, unsigned p2) {
	if (p1 == p2) return;
	Elem tmp = A[p2];
	A[p2] = A[p1];
	A[p1] = tmp;
}


//插入排序法
template <typename Elem>
void insertionSort(Elem* A, unsigned size) {

	//从第二个元素开始头到尾遍历数组
	for (size_t i = 1; i < size; ++i)

		//为元素寻找合适的插入位置
		for (size_t j = i; j > 0; --j) {
			if (A[j] < A[j - 1])
				swap(A, j, j - 1);
			else break;
		}
}


//冒泡排序法
template <typename Elem>
void bubbleSort(Elem* A, unsigned size) {

	//至多的排序次数为n-1
	for (size_t i = 0; i < size - 1; ++i) {
		
		//记录一次排序过程中是否发生过位置交换
		bool isSwap = false; 

		//从尾到头遍历数组
		for (size_t j = size - 1; j > i; --j)

			//当前元素小于前一个元素，则交换位置
			if (A[j] < A[j - 1]) {
				swap(A, j, j - 1);
				isSwap = true;
			}

		//排序已经完成，跳出循环
		if (!isSwap) break;
	}
}


//选择排序法
template <typename Elem>
void selectionSort(Elem* A, unsigned size) {

	//从数组第一个位置开始往后选择
	for (size_t i = 0; i < size - 1; ++i) {

		//记录子数组中最小的元素位置
		size_t lowest = i;

		//遍历子数组找寻最小元素
		for (size_t j = i + 1; j < size; ++j)
			if (A[j] < A[lowest])
				lowest = j;

		//将最小元素替换到当前位置上
		if (lowest != i)
			swap(A, i, lowest);
	}
}


//希尔排序法

//实现对间隔为num_sublists的元素进行插入排序
template<typename Elem>
void shellsortHelp(Elem* A, unsigned num_sublists, unsigned size) {
	for (size_t i = num_sublists; i < size; i += num_sublists)
		for (size_t j = i; j > 0; j -= num_sublists) {
			if (A[j] < A[j - num_sublists])
				swap(A, j, j - num_sublists);
			else break;
		}
}

template <typename Elem>
void shellsort(Elem* A, unsigned size) {

	//对数组中元素进行分组
	for (unsigned i = size / 2; i > 2; i /= 2)

		//对每一个分组进行插入排序
		for (unsigned j = 0; j < i; ++j)
			shellsortHelp(&A[j], i, size - j);

	//最后对整个数组进行一次插入排序
	shellsortHelp(A, 1, size);
}


//归并排序法
template <typename Elem>
void mergesortHelp(Elem* A, unsigned front, unsigned back) {

	//子数组长度小于等于1，返回
	if (front >= back - 1) return;

	//将子数组分成两部分，各自排序
	unsigned mid = (front + back) / 2;
	mergesortHelp(A, front, mid);
	mergesortHelp(A, mid, back);

	//将各自排序完成的两部分子数组合并
	Elem* tmp = new Elem[mid - front];
	for (unsigned i = 0; i < mid - front; ++i)
		tmp[i] = A[i + front];
	unsigned i1 = 0, i2 = mid;
	for (unsigned i = front; i < back; ++i) {
		if (i1 == mid - front)
			A[i] = A[i2++];
		else if (i2 == back)
			A[i] = tmp[i1++];
		else if (tmp[i1] < A[i2])
			A[i] = tmp[i1++];
		else A[i] = A[i2++];
	}
	delete[]tmp;
}

template <typename Elem>
void mergesort(Elem* A, unsigned size) {
	mergesortHelp(A, 0, size);
}


//快速排序法

//实现选取快速排序法的中间节点
template <typename Elem>
unsigned setPivot(Elem* A, unsigned front, unsigned back) {

	//对比子数组的首尾节点和中心节点，取大小中间值
	unsigned mid = (front + back) / 2;
	if (A[front] < A[mid]) {
		if (A[mid] < A[back - 1])
			return mid;
		else if (A[front] < A[back - 1])
			return --back;
		else return front;
	}

	else {
		if (A[front] < A[back - 1])
			return front;
		else if (A[mid] < A[back - 1])
			return --back;
		else return mid;
	}
}

//实现将子数组中元素相对back位置元素的大小分成两边
//，并返回中间位置的元素位置
template <typename Elem>
unsigned partion(Elem* A, unsigned front, unsigned back) {
	unsigned p = back;
	do {
		for (; (front < p) && (A[front] < A[p]); ++front);
		for (; (back > front) && (A[p] <= A[back]); --back);
		swap(A, front, back);
	} while (back > front);
	return front;
}

template <typename Elem>
void quicksortHelp(Elem* A, unsigned front, unsigned back) {
	if (front >= back - 1) return;

	//取分割点，并将该点元素放于子数组尾
	unsigned pivot = setPivot(A, front, back);
	swap(A, pivot, back - 1);

	//将子数组中其他元素分成两边
	unsigned p = partion(A, front, back - 1);
	swap(A, p, back - 1);

	//对两边的子数组分别进行排序
	quicksortHelp(A, front, p);
	quicksortHelp(A, p + 1, back);
}

template <typename Elem>
void quicksort(Elem* A, unsigned size) {
	quicksortHelp(A, 0, size);
}
#endif // !SORT_H

