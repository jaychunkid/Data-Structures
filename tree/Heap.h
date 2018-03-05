//��ʵ��
#ifndef HEAP_H
#define HEAP_H

//С���ѵ�����ʵ��
template <typename Elem>
class MinHeap {
	Elem* heap;                     //ʵ�ֶѵ�����
	unsigned maxSize = 10;          //�ѵ����������Ĭ��Ϊ10
	unsigned count = 0;             //ͳ�ƶ��еĽڵ���
	
	//�ڲ����������ض�Ӧ�ĸ����ӽڵ�
	unsigned parent(unsigned pos)const { return (pos - 1) / 2; }
	unsigned rightChild(unsigned pos)const { return 2 * pos + 2; }
	unsigned leftChild(unsigned pos)const { return 2 * pos + 1; }

	//�жϽڵ��Ƿ�ΪҶ�ڵ�
	bool isLeaf(unsigned pos)const { return (pos >= count / 2) 
		&& (pos < count); }

	//�ڲ�������ʵ�����鳤�ȵ���չ
	void expend() {
		maxSize *= 10;
		Elem* tmp = heap;
		heap = new Elem[maxSize]();
		for (unsigned i = 0; i < count; ++i)
			heap[i] = tmp[i];
		delete tmp;
	}

	//�ڲ���������һ���ڵ����·��õ����ʵ�λ����
	void siftDown(unsigned pos) {

		//��Ŀ��ڵ����±���������
		while (!isLeaf(pos)) {
			unsigned rc = rightChild(pos), lc = leftChild(pos);

			//m�����ӽڵ��еĽ�С�ڵ�
			unsigned m = lc;
			if (rc < count&&heap[rc] < heap[lc])
				m = rc;

			//��ǰ�ڵ�ֵС���ӽڵ��ֵ�����ѵ������λ�ã�����
			if (heap[pos] <= heap[m])
				return;

			//���򣬽���Ŀ��ڵ����С�ӽڵ��λ�ã��������±���
			Elem tmp = heap[pos];
			heap[pos] = heap[m];
			heap[m] = tmp;
			pos = m;
		}
	}

public:
	//���캯������������
	MinHeap() { heap = new Elem[maxSize](); }
	MinHeap(unsigned m) :maxSize(m) { heap = new Elem[maxSize]; }
	~MinHeap() { delete heap; }

	//����в���ڵ�
	void insert(const Elem &e) {

	    //����ռ䲻�㣬����չ����
		if (count >= maxSize - 1)
			expend();

		//�Ƚ�����ڵ��������������λ��
		unsigned cur = count++;
		heap[cur] = e;

		//�Ե����Ͻ��ڵ���õ����ʵ�λ��
		while (cur != 0 && heap[cur] < heap[parent(cur)]) {
			Elem tmp = heap[parent(cur)];
			heap[parent(cur)] = heap[cur];
			heap[cur] = tmp;
			cur = parent(cur);
		}
	}

	//��ȡ���еĶ��ڵ㣨����С�ڵ㣩
	bool top(Elem &e) {
		if (isEmpty())
			return false;

		e = heap[0];
		return true;
	}

	//�������еĶ��ڵ�
	void pop() {
		if (isEmpty())
			return;

		//����������һ���ڵ���õ����ڵ�λ��
		//���ٶ���ִ��siftDown����
		unsigned cur = --count;
		if (cur != 0) {
			heap[0] = heap[cur];
			siftDown(0);
		}
	}

	unsigned size()const { return count; }              //���ضѵĴ�С
	bool isEmpty()const { return count == 0; }          //�ж϶��Ƿ�Ϊ��
};

#endif // !HEAP_H

