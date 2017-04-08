//图的相关算法实现
#include"Graph.h"
#include"Stack.h"
#include"Queue.h"
#include"Heap.h"
#include"GeneralTree.h"
#include<iostream>
using std::cout;

//深度优先遍历
void DFS(Graph* g, unsigned v1) {

	//对起始节点设置标记，并压入栈中
	g->setMark(v1, Graph::VTSITED);
	Stack<unsigned> vertex;
	vertex.push(v1);

	//栈为空时，停止遍历
	while (!vertex.isEmpty()) {

		//获取栈顶节点
		vertex.top(v1);
		vertex.pop();

		//遍历所有节点
		for (unsigned v2 = 0; v2 < g->n(); ++v2)

			//若节点v2与当前节点v1有连边且未曾被访问
			//，则访问、标记节点v2并将其压入栈中
			//，同时将v2设置为当前节点，重新开始遍历所有节点
			if (g->hasEdge(v1, v2) && g->getMark(v2) == Graph::UNVISITED) {
				g->setMark(v2, Graph::VTSITED);
				cout << v2 << ' ';
				vertex.push(v2);
				v1 = v2;
				v2 = 0;
			}
	}
}


//广度优先遍历
void BFS(Graph* g, unsigned v1) {

	//对起始节点设置标记，并加入队列中
	g->setMark(v1, Graph::VTSITED);
	Queue<unsigned> vertex;
	vertex.push(v1);

	//队列为空时，停止遍历
	while (!vertex.isEmpty()) {

		//获取队列头节点
		vertex.front(v1);
		vertex.pop();

		//遍历所有节点
		for(unsigned v2=0;v2<g->n();++v2)

			//若节点v2与当前节点v1有连边且未被访问
			//，访问、标记节点v2并将其加入队列中，继续遍历剩余节点
			if (g->hasEdge(v1, v2) && g->getMark(v2) == Graph::UNVISITED) {
				vertex.push(v2);
				g->setMark(v2, Graph::VTSITED);
				cout << v2 << ' ';
			}
	}
}


//拓扑排序
//处理事件的优先级问题（必须遍历所有有连边指向当前节点的节点后，才能访问当前节点）
void TopSort(Graph* g) {
	Queue<unsigned> vertex;                //记录入度为零的节点
	int* count = new int[g->n()];          //记录节点的入度

	//记录节点入度，并将入度为零的节点加入队列
	for (size_t i = 0; i < g->n(); ++i) {
		count[i] = g->inDegree(i);
		if (count[i] == 0)
			vertex.push(i);
	}

	//当队列为空时停止遍历
	while (!vertex.isEmpty()) {

		//获取队列头节点，访问并标记
		unsigned v = 0;
		vertex.front(v);
		vertex.pop();
		g->setMark(v, Graph::VTSITED);
		cout << v << ' ';

		//遍历该节点发出的所有连边，对连边另一端的节点入度减一
		//，若有节点入度减为零则将其加入队列
		for (unsigned i = 0; i < g->n(); ++i)
			if (g->hasEdge(v, i)) {
				--count[i];
				if (count[i] == 0 && g->getMark(i) == Graph::UNVISITED)
					vertex.push(i);
			}
	}
}


//单源最短路径问题
//**d储存计算结果
void FloydWarshall(Graph* g, int** d) {

	//若图g为有向图
	if (g->isDirected()) {

		//将现有边的权值填入数组d
		for (size_t i = 0; i < g->n(); ++i)
			for (size_t j = 0; j < g->n(); ++j) {
				if (i == j) d[i][j] = 0;
				else d[i][j] = g->weight(i, j);
			}

		//计算结果
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

	//若图g为无向图
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


//单源最短路径问题

//实现有向连边的类
struct Edge {
	unsigned v;          //连边指向的节点编号
	int weight;          //连边的权值

	//比较运算符，对连边的权值进行比较
	bool operator<(const Edge &e)const { return weight < e.weight; }
	bool operator<=(const Edge &e)const { return weight <= e.weight; }
};

//算法实现
//*d储存源节点到各节点距离
//v为起始节点
void Dijkstra(Graph* g, int* d, unsigned v) {

	//起始值设置
	for (size_t i = 0; i < g->n(); ++i)
		d[i] = Graph::UNCONNECTED;
	d[v] = 0;

	//小顶堆对加入堆中的连边进行处理
	MinHeap<Edge> heap;

	//至多需要遍历节点数减一次（最后一个节点不需要遍历）
	for (size_t i = 1; i < g->n(); ++i) {

		//将起始节点标记为已访问
		g->setMark(v, Graph::VTSITED);

		//遍历所有与起始节点有连边的节点
		for (unsigned i = g->first(v); i != g->n(); i = g->next(v, i))

			//若该节点未曾被访问
			if (g->getMark(i) == Graph::UNVISITED) {

				//若该节点到源节点距离为初值
				//，则将计算得到的距离赋值
				if (d[i] == Graph::UNCONNECTED)
					d[i] = g->weight(v, i) + d[v];

				//否则，对比储存较小的结果值
				else {
					int w = g->weight(v, i) + d[v];
					if (w < d[i])
						d[i] = w;
				}

				//将连边加入堆中
				Edge tmp = { i,d[i] };
				heap.insert(tmp);
			}

		for (;;) {

			//从堆中获取权值最小的连边
			Edge tmp;
			heap.top(tmp);
			heap.pop();

			//若连边指向节点为未访问，将其设置为起始节点，重新开始循环
			if (g->getMark(tmp.v) == Graph::UNVISITED) {
				v = tmp.v;
				break;
			}

			//堆为空，返回结果
			if (heap.isEmpty())
				return;
		}
	}
}


//最小生成树问题
//*d储存树中连接节点的边的权值
//v为起始节点
void Prim(Graph* g, int* d, unsigned v) {

	//起始值设置
	for (size_t i = 0; i < g->n(); ++i)
		d[i] = Graph::UNCONNECTED;
	d[v] = 0;

	//小顶堆对加入堆中的连边进行处理
	MinHeap<Edge> heap;

	//至多需要遍历节点数减一次（最后一个节点不需要遍历）
	for (size_t i = 1; i < g->n(); ++i) {

		//将起始节点标记为已访问
		g->setMark(v, Graph::VTSITED);

		//遍历所有与起始节点有连边的节点
		for (unsigned i = g->first(v); i != g->n(); i = g->next(v, i))

			//若该节点未曾被访问
			if (g->getMark(i) == Graph::UNVISITED) {

				//若该节点与源节点不相关，记录该边权值
				if (d[i] == Graph::UNCONNECTED)
					d[i] = g->weight(v, i);

				//否则，记录现有值与当前连边的权值中的较小值
				else {
					int w = g->weight(v, i);
					if (w < d[i])
						d[i] = w;
				}

				//将该连边加入小顶堆中
				Edge tmp = { i,d[i] };
				heap.insert(tmp);
			}

		for (;;) {

			//从堆中获取权值最小的连边
			Edge tmp;
			heap.top(tmp);
			heap.pop();

			//若连边指向节点为未访问，将其设置为起始节点，重新开始循环
			if (g->getMark(tmp.v) == Graph::UNVISITED) {
				v = tmp.v;
				break;
			}

			//堆为空，返回结果
			if (heap.isEmpty())
				return;
		}
	}
}


