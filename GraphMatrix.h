//ͼ�Ķ�ά����ʵ��
#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include"Graph.h"

class GraphMatrix:public Graph {
	int** matrix;                   //ͼ������Ȩֵ
	unsigned vertex, edge;          //ͼ�Ľڵ�����������
	int *mark;                      //���ڵ�ı��
	bool is_directed;               //�Ƿ�Ϊ����ͼ�ı��

public:
	//���캯����Ĭ��Ϊ����ͼ
	GraphMatrix(unsigned v, bool d = false) :vertex(v), edge(0), is_directed(d) {
		matrix = new int*[vertex];
		for (size_t i = 0; i < vertex; ++i)
			matrix[i] = new int[vertex]();

		//���ڵ��ʼ״̬Ϊδ����
		for (size_t i = 0; i < vertex; ++i)
			for (size_t j = 0; j < vertex; ++j)
				matrix[i][j] = UNCONNECTED;

		//���ڵ��ǳ�ʼ״̬Ϊδ����
		mark = new int[vertex];
		for (size_t i = 0; i < vertex; ++i)
			mark[i] = UNVISITED;
	}

	//��������
	~GraphMatrix() {
		for (size_t i = 0; i < vertex; ++i)
			delete[]matrix[i];
		delete[]matrix;
		delete[]mark;
	}

	unsigned n()const { return vertex; }
	unsigned e()const { return edge; }
	int getMark(unsigned v)const { return mark[v]; }
	void setMark(unsigned v, int m) { mark[v] = m; }

	//��ʼ�����нڵ�ı��
	void clearMark() {
		for (unsigned i = 0; i < vertex; ++i)
			mark[i] = UNVISITED;
	}

	//������Ӧ������ͳ�����
	unsigned inDegree(unsigned v)const {
		unsigned count = 0;
		for (unsigned i = 0; i < vertex; ++i)
			if (matrix[i][v] != UNCONNECTED)
				++count;
		return count;
	}

	//������Ӧ������ͳ�Ƴ���
	unsigned outDegree(unsigned v)const {
		unsigned count = 0;
		for (unsigned i = 0; i < vertex; ++i)
			if (matrix[v][i] != UNCONNECTED)
				++count;
		return count;
	}

	bool isDirected()const { return is_directed; }

	//������Ӧ�����飬����Ŵ�С������Ѱ��һ�����ӽڵ�
	//���ýڵ�Ϊ�����㣬�򷵻ؽڵ���
	unsigned first(unsigned v)const {
		unsigned i = 0;
		for (i = 0; i < vertex; ++i)
			if (matrix[v][i] != UNCONNECTED)
				break;
		return i;
	}
	
	//�ӵ�v1��v2��λ�ã�����Ŵ�С������Ѱ��һ�����ӽڵ�
	unsigned next(unsigned v1, unsigned v2)const {

		//v2λ�ó������鷶Χ������
		//v2��Ϊv1����ͨ�ڵ㣬���ؽڵ���
		if (v2 >= vertex || matrix[v1][v2] == UNCONNECTED)
			return vertex;

		unsigned i = v2 + 1;
		for (; i < vertex; ++i)
			if (matrix[v1][i] != UNCONNECTED)
				break;
		return i;
	}

	//����v1��v2�����ߣ�ȨֵĬ��Ϊ1
	void setEdge(unsigned v1, unsigned v2, int weight = 1) {
		matrix[v1][v2] = weight;

		//������ͼ���෴��������ͬʱ��ֵ
		if (!is_directed)
			matrix[v2][v1] = weight;
		++edge;
	}

	//ɾ��v1��v2������
	void delEdge(unsigned v1, unsigned v2) { 
		matrix[v1][v2] = UNCONNECTED;

		//������ͼ��ͬʱɾ���෴���������
		if (!is_directed)
			matrix[v2][v1] = UNCONNECTED;
		--edge;
	}

	//�����������
	void clearEdge() {
		for (unsigned i = 0; i < vertex; ++i)
			for (unsigned j = 0; j < vertex; ++j)
				matrix[i][j] = UNCONNECTED;
		edge = 0;
	}

	//�ж�������Ƿ�������
	bool hasEdge(unsigned v1, unsigned v2)const { return matrix[v1][v2] 
		!= UNCONNECTED; }

	//�������������Ȩֵ�������߷���-1��
	int weight(unsigned v1, unsigned v2)const { return matrix[v1][v2]; }
};
#endif // !GRAPHMATRIX_H

