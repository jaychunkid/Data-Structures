//ƽ����ʵ��
#ifndef GENERALTREE_H
#define GENERALTREE_H

//ƽ��������ʵ�֣����洢�ڵ�ֵ��ֻ��¼���Ľṹ��
class GeneralTree {
	int* array_tree;          //ʵ��ƽ���������飨���ڵ㴢������С�ĸ�ֵ���ӽڵ㴢�游�ڵ��±꣩
	unsigned size;            //��¼�ڵ���Ŀ

	//�жϵ�ǰ�ڵ��Ƿ�Ϊ���ڵ�
	bool isRoot(unsigned v) { return array_tree[v] < 0; }

	//Ѱ�ҵ�ǰ�ڵ�ĸ��ڵ�
	//ʹ��·��ѹ���ķ����������ĸ߶�
	unsigned findRoot(unsigned v) {
		if (isRoot(v)) return v;

		else {
			//���ϱ�����ͬʱ�����ڵ�ֱ�����ӵ����ڵ���
			array_tree[v] = findRoot(array_tree[v]);
			return array_tree[v];
		}
	}

public:
	//���캯��
	GeneralTree(unsigned s) :size(s) {    
		array_tree = new int[size]();

		//���нڵ�ĳ�ʼ״̬��Ϊ���ڵ�
		for (size_t i = 0; i < size; ++i)
			array_tree[i] = -1;
	}
	~GeneralTree() { delete[]array_tree; }          //��������

	//�ж������ڵ��Ƿ�����ͬһ����
	bool differ(unsigned v1, unsigned v2) { return findRoot(v1) != findRoot(v2); }

	//���������ڵ����ڵ���
	//ʹ�ü�Ȩ��ϵķ����������ĸ߶�
	void merge(unsigned v1, unsigned v2) {

		//�����ڵ��Ѿ���ͬһ�����У�ֱ�ӷ���
		if (!differ(v1, v2)) return;

		//����С�ĸ��ڵ���Ϊ�ϴ���ڵ���ӽڵ�
		v1 = findRoot(v1);
		v2 = findRoot(v2);
		unsigned bigger = v1, smaller = v2;
		if ((array_tree[v2] < array_tree[v1])
			|| (array_tree[v1] == array_tree[v2] && v2 < v1)) {
			bigger = v2;
			smaller = v1;
		}
		array_tree[bigger] += array_tree[smaller];
		array_tree[smaller] = bigger;
		return;
	}

};
#endif // !GENERALTREE_H

