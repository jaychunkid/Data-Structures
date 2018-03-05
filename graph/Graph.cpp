//ͼ������㷨ʵ��
#include"Graph.h"
#include"Stack.h"
#include"Queue.h"
#include"Heap.h"
#include"GeneralTree.h"
#include<iostream>
using std::cout;

//������ȱ���
void DFS(Graph* g, unsigned v1) {

	//����ʼ�ڵ����ñ�ǣ���ѹ��ջ��
	g->setMark(v1, Graph::VTSITED);
	Stack<unsigned> vertex;
	vertex.push(v1);

	//ջΪ��ʱ��ֹͣ����
	while (!vertex.isEmpty()) {

		//��ȡջ���ڵ�
		vertex.top(v1);
		vertex.pop();

		//�������нڵ�
		for (unsigned v2 = 0; v2 < g->n(); ++v2)

			//���ڵ�v2�뵱ǰ�ڵ�v1��������δ��������
			//������ʡ���ǽڵ�v2������ѹ��ջ��
			//��ͬʱ��v2����Ϊ��ǰ�ڵ㣬���¿�ʼ�������нڵ�
			if (g->hasEdge(v1, v2) && g->getMark(v2) == Graph::UNVISITED) {
				g->setMark(v2, Graph::VTSITED);
				cout << v2 << ' ';
				vertex.push(v2);
				v1 = v2;
				v2 = 0;
			}
	}
}


//������ȱ���
void BFS(Graph* g, unsigned v1) {

	//����ʼ�ڵ����ñ�ǣ������������
	g->setMark(v1, Graph::VTSITED);
	Queue<unsigned> vertex;
	vertex.push(v1);

	//����Ϊ��ʱ��ֹͣ����
	while (!vertex.isEmpty()) {

		//��ȡ����ͷ�ڵ�
		vertex.front(v1);
		vertex.pop();

		//�������нڵ�
		for(unsigned v2=0;v2<g->n();++v2)

			//���ڵ�v2�뵱ǰ�ڵ�v1��������δ������
			//�����ʡ���ǽڵ�v2�������������У���������ʣ��ڵ�
			if (g->hasEdge(v1, v2) && g->getMark(v2) == Graph::UNVISITED) {
				vertex.push(v2);
				g->setMark(v2, Graph::VTSITED);
				cout << v2 << ' ';
			}
	}
}


//��������
//�����¼������ȼ����⣨�����������������ָ��ǰ�ڵ�Ľڵ�󣬲��ܷ��ʵ�ǰ�ڵ㣩
void TopSort(Graph* g) {
	Queue<unsigned> vertex;                //��¼���Ϊ��Ľڵ�
	int* count = new int[g->n()];          //��¼�ڵ�����

	//��¼�ڵ���ȣ��������Ϊ��Ľڵ�������
	for (size_t i = 0; i < g->n(); ++i) {
		count[i] = g->inDegree(i);
		if (count[i] == 0)
			vertex.push(i);
	}

	//������Ϊ��ʱֹͣ����
	while (!vertex.isEmpty()) {

		//��ȡ����ͷ�ڵ㣬���ʲ����
		unsigned v = 0;
		vertex.front(v);
		vertex.pop();
		g->setMark(v, Graph::VTSITED);
		cout << v << ' ';

		//�����ýڵ㷢�����������ߣ���������һ�˵Ľڵ���ȼ�һ
		//�����нڵ���ȼ�Ϊ������������
		for (unsigned i = 0; i < g->n(); ++i)
			if (g->hasEdge(v, i)) {
				--count[i];
				if (count[i] == 0 && g->getMark(i) == Graph::UNVISITED)
					vertex.push(i);
			}
	}
}


//��Դ���·������
//**d���������
void FloydWarshall(Graph* g, int** d) {

	//��ͼgΪ����ͼ
	if (g->isDirected()) {

		//�����бߵ�Ȩֵ��������d
		for (size_t i = 0; i < g->n(); ++i)
			for (size_t j = 0; j < g->n(); ++j) {
				if (i == j) d[i][j] = 0;
				else d[i][j] = g->weight(i, j);
			}

		//������
		for (unsigned n = 0; n < g->n(); ++n)
			for (size_t i = 0; i < g->n(); ++i)
				for (size_t j = 0; j < g->n(); ++j)
					if (i != n&&j != n)
						if (d[n][j] != Graph::UNCONNECTED && d[i][n] 
							!= Graph::UNCONNECTED && (d[i][j] 
								== Graph::UNCONNECTED || d[i][j] > d[i][n] 
								+ d[n][j]))
							d[i][j] = d[n][j] + d[i][n];
		return;
	}

	//��ͼgΪ����ͼ
	for (size_t i = 0; i < g->n(); ++i)
		for (size_t j = i; j < g->n(); ++j) {
			if (i == j) d[i][j] = 0;
			else d[i][j] = d[j][i] = g->weight(i, j);
		}

	for (unsigned n = 0; n < g->n(); ++n)
		for (size_t i = 0; i < g->n() - 1; ++i)
			for (size_t j = i + 1; j < g->n(); ++j)
				if (d[n][j] != Graph::UNCONNECTED 
					&& d[i][n] != Graph::UNCONNECTED
					&& (d[i][j] == Graph::UNCONNECTED 
						|| d[i][j] > d[i][n] + d[n][j]))
					d[i][j] = d[j][i] = d[n][j] + d[i][n];
	return;
}


//��Դ���·������

//ʵ���������ߵ���
struct Edge {
	unsigned v;          //����ָ��Ľڵ���
	int weight;          //���ߵ�Ȩֵ

	//�Ƚ�������������ߵ�Ȩֵ���бȽ�
	bool operator<(const Edge &e)const { return weight < e.weight; }
	bool operator<=(const Edge &e)const { return weight <= e.weight; }
};

//�㷨ʵ��
//*d����Դ�ڵ㵽���ڵ����
//vΪ��ʼ�ڵ�
void Dijkstra(Graph* g, int* d, unsigned v) {

	//��ʼֵ����
	for (size_t i = 0; i < g->n(); ++i)
		d[i] = Graph::UNCONNECTED;
	d[v] = 0;

	//С���ѶԼ�����е����߽��д���
	MinHeap<Edge> heap;

	//������Ҫ�����ڵ�����һ�Σ����һ���ڵ㲻��Ҫ������
	for (size_t i = 1; i < g->n(); ++i) {

		//����ʼ�ڵ���Ϊ�ѷ���
		g->setMark(v, Graph::VTSITED);

		//������������ʼ�ڵ������ߵĽڵ�
		for (unsigned i = g->first(v); i != g->n(); i = g->next(v, i))

			//���ýڵ�δ��������
			if (g->getMark(i) == Graph::UNVISITED) {

				//���ýڵ㵽Դ�ڵ����Ϊ��ֵ
				//���򽫼���õ��ľ��븳ֵ
				if (d[i] == Graph::UNCONNECTED)
					d[i] = g->weight(v, i) + d[v];

				//���򣬶Աȴ����С�Ľ��ֵ
				else {
					int w = g->weight(v, i) + d[v];
					if (w < d[i])
						d[i] = w;
				}

				//�����߼������
				Edge tmp = { i,d[i] };
				heap.insert(tmp);
			}

		for (;;) {

			//�Ӷ��л�ȡȨֵ��С������
			Edge tmp;
			heap.top(tmp);
			heap.pop();

			//������ָ��ڵ�Ϊδ���ʣ���������Ϊ��ʼ�ڵ㣬���¿�ʼѭ��
			if (g->getMark(tmp.v) == Graph::UNVISITED) {
				v = tmp.v;
				break;
			}

			//��Ϊ�գ����ؽ��
			if (heap.isEmpty())
				return;
		}
	}
}


//��С����������
//*d�����������ӽڵ�ıߵ�Ȩֵ
//vΪ��ʼ�ڵ�
void Prim(Graph* g, int* d, unsigned v) {

	//��ʼֵ����
	for (size_t i = 0; i < g->n(); ++i)
		d[i] = Graph::UNCONNECTED;
	d[v] = 0;

	//С���ѶԼ�����е����߽��д���
	MinHeap<Edge> heap;

	//������Ҫ�����ڵ�����һ�Σ����һ���ڵ㲻��Ҫ������
	for (size_t i = 1; i < g->n(); ++i) {

		//����ʼ�ڵ���Ϊ�ѷ���
		g->setMark(v, Graph::VTSITED);

		//������������ʼ�ڵ������ߵĽڵ�
		for (unsigned i = g->first(v); i != g->n(); i = g->next(v, i))

			//���ýڵ�δ��������
			if (g->getMark(i) == Graph::UNVISITED) {

				//���ýڵ���Դ�ڵ㲻��أ���¼�ñ�Ȩֵ
				if (d[i] == Graph::UNCONNECTED)
					d[i] = g->weight(v, i);

				//���򣬼�¼����ֵ�뵱ǰ���ߵ�Ȩֵ�еĽ�Сֵ
				else {
					int w = g->weight(v, i);
					if (w < d[i])
						d[i] = w;
				}

				//�������߼���С������
				Edge tmp = { i,d[i] };
				heap.insert(tmp);
			}

		for (;;) {

			//�Ӷ��л�ȡȨֵ��С������
			Edge tmp;
			heap.top(tmp);
			heap.pop();

			//������ָ��ڵ�Ϊδ���ʣ���������Ϊ��ʼ�ڵ㣬���¿�ʼѭ��
			if (g->getMark(tmp.v) == Graph::UNVISITED) {
				v = tmp.v;
				break;
			}

			//��Ϊ�գ����ؽ��
			if (heap.isEmpty())
				return;
		}
	}
}


