//���򷽷�ʵ�֣���С��������
#ifndef SORT_H
#define SORT_H

//��������A��p1��p2λ�õ�ֵ
template <typename Elem>
void swap(Elem* A, unsigned p1, unsigned p2) {
	if (p1 == p2) return;
	Elem tmp = A[p2];
	A[p2] = A[p1];
	A[p1] = tmp;
}


//��������
template <typename Elem>
void insertionSort(Elem* A, unsigned size) {

	//�ӵڶ���Ԫ�ؿ�ʼͷ��β��������
	for (size_t i = 1; i < size; ++i)

		//ΪԪ��Ѱ�Һ��ʵĲ���λ��
		for (size_t j = i; j > 0; --j) {
			if (A[j] < A[j - 1])
				swap(A, j, j - 1);
			else break;
		}
}


//ð������
template <typename Elem>
void bubbleSort(Elem* A, unsigned size) {

	//������������Ϊn-1
	for (size_t i = 0; i < size - 1; ++i) {
		
		//��¼һ������������Ƿ�����λ�ý���
		bool isSwap = false; 

		//��β��ͷ��������
		for (size_t j = size - 1; j > i; --j)

			//��ǰԪ��С��ǰһ��Ԫ�أ��򽻻�λ��
			if (A[j] < A[j - 1]) {
				swap(A, j, j - 1);
				isSwap = true;
			}

		//�����Ѿ���ɣ�����ѭ��
		if (!isSwap) break;
	}
}


//ѡ������
template <typename Elem>
void selectionSort(Elem* A, unsigned size) {

	//�������һ��λ�ÿ�ʼ����ѡ��
	for (size_t i = 0; i < size - 1; ++i) {

		//��¼����������С��Ԫ��λ��
		size_t lowest = i;

		//������������Ѱ��СԪ��
		for (size_t j = i + 1; j < size; ++j)
			if (A[j] < A[lowest])
				lowest = j;

		//����СԪ���滻����ǰλ����
		if (lowest != i)
			swap(A, i, lowest);
	}
}


//ϣ������

//ʵ�ֶԼ��Ϊnum_sublists��Ԫ�ؽ��в�������
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

	//��������Ԫ�ؽ��з���
	for (unsigned i = size / 2; i > 2; i /= 2)

		//��ÿһ��������в�������
		for (unsigned j = 0; j < i; ++j)
			shellsortHelp(&A[j], i, size - j);

	//���������������һ�β�������
	shellsortHelp(A, 1, size);
}


//�鲢����
template <typename Elem>
void mergesortHelp(Elem* A, unsigned front, unsigned back) {

	//�����鳤��С�ڵ���1������
	if (front >= back - 1) return;

	//��������ֳ������֣���������
	unsigned mid = (front + back) / 2;
	mergesortHelp(A, front, mid);
	mergesortHelp(A, mid, back);

	//������������ɵ�������������ϲ�
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


//��������

//ʵ��ѡȡ�������򷨵��м�ڵ�
template <typename Elem>
unsigned setPivot(Elem* A, unsigned front, unsigned back) {

	//�Ա����������β�ڵ�����Ľڵ㣬ȡ��С�м�ֵ
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

//ʵ�ֽ���������Ԫ�����backλ��Ԫ�صĴ�С�ֳ�����
//���������м�λ�õ�Ԫ��λ��
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

	//ȡ�ָ�㣬�����õ�Ԫ�ط���������β
	unsigned pivot = setPivot(A, front, back);
	swap(A, pivot, back - 1);

	//��������������Ԫ�طֳ�����
	unsigned p = partion(A, front, back - 1);
	swap(A, p, back - 1);

	//�����ߵ�������ֱ��������
	quicksortHelp(A, front, p);
	quicksortHelp(A, p + 1, back);
}

template <typename Elem>
void quicksort(Elem* A, unsigned size) {
	quicksortHelp(A, 0, size);
}
#endif // !SORT_H

