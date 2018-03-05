//图的二维数组实现
#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include"Graph.h"

class GraphMatrix:public Graph {
	int** matrix;                   //图的连边权值
	unsigned vertex, edge;          //图的节点数和连边数
	int *mark;                      //各节点的标记
	bool is_directed;               //是否为有向图的标记

public:
	//构造函数，默认为无向图
	GraphMatrix(unsigned v, bool d = false) :vertex(v), edge(0), is_directed(d) {
		matrix = new int*[vertex];
		for (size_t i = 0; i < vertex; ++i)
			matrix[i] = new int[vertex]();

		//各节点初始状态为未连接
		for (size_t i = 0; i < vertex; ++i)
			for (size_t j = 0; j < vertex; ++j)
				matrix[i][j] = UNCONNECTED;

		//各节点标记初始状态为未访问
		mark = new int[vertex];
		for (size_t i = 0; i < vertex; ++i)
			mark[i] = UNVISITED;
	}

	//析构函数
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

	//初始化所有节点的标记
	void clearMark() {
		for (unsigned i = 0; i < vertex; ++i)
			mark[i] = UNVISITED;
	}

	//遍历对应列数组统计入度
	unsigned inDegree(unsigned v)const {
		unsigned count = 0;
		for (unsigned i = 0; i < vertex; ++i)
			if (matrix[i][v] != UNCONNECTED)
				++count;
		return count;
	}

	//遍历对应行数组统计出度
	unsigned outDegree(unsigned v)const {
		unsigned count = 0;
		for (unsigned i = 0; i < vertex; ++i)
			if (matrix[v][i] != UNCONNECTED)
				++count;
		return count;
	}

	bool isDirected()const { return is_directed; }

	//遍历对应行数组，按编号从小到达找寻第一个连接节点
	//若该节点为孤立点，则返回节点数
	unsigned first(unsigned v)const {
		unsigned i = 0;
		for (i = 0; i < vertex; ++i)
			if (matrix[v][i] != UNCONNECTED)
				break;
		return i;
	}
	
	//从第v1行v2列位置，按编号从小到大找寻下一个连接节点
	unsigned next(unsigned v1, unsigned v2)const {

		//v2位置超过数组范围，或者
		//v2不为v1的连通节点，返回节点数
		if (v2 >= vertex || matrix[v1][v2] == UNCONNECTED)
			return vertex;

		unsigned i = v2 + 1;
		for (; i < vertex; ++i)
			if (matrix[v1][i] != UNCONNECTED)
				break;
		return i;
	}

	//设置v1到v2的连边，权值默认为1
	void setEdge(unsigned v1, unsigned v2, int weight = 1) {
		matrix[v1][v2] = weight;

		//对无向图，相反方向连边同时赋值
		if (!is_directed)
			matrix[v2][v1] = weight;
		++edge;
	}

	//删除v1到v2的连边
	void delEdge(unsigned v1, unsigned v2) { 
		matrix[v1][v2] = UNCONNECTED;

		//对无向图，同时删除相反方向的连边
		if (!is_directed)
			matrix[v2][v1] = UNCONNECTED;
		--edge;
	}

	//清除所有连边
	void clearEdge() {
		for (unsigned i = 0; i < vertex; ++i)
			for (unsigned j = 0; j < vertex; ++j)
				matrix[i][j] = UNCONNECTED;
		edge = 0;
	}

	//判断两点间是否有连边
	bool hasEdge(unsigned v1, unsigned v2)const { return matrix[v1][v2] 
		!= UNCONNECTED; }

	//返回两点间连边权值（无连边返回-1）
	int weight(unsigned v1, unsigned v2)const { return matrix[v1][v2]; }
};
#endif // !GRAPHMATRIX_H

