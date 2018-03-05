//关于图
#ifndef GRAPH_H
#define GRAPH_H

//图的抽象类
class Graph {
public:
	virtual unsigned n()const = 0;          //返回图的节点个数
	virtual unsigned e()const = 0;          //返回图的连边个数

	//实现对图中节点的标记
	virtual int getMark(unsigned v)const = 0;
	virtual void setMark(unsigned v, int m) = 0;
	virtual void clearMark() = 0;

	//获取节点的出度与入度
	virtual unsigned inDegree(unsigned v)const = 0;
	virtual unsigned outDegree(unsigned v)const = 0;

	//判断图是否为有向图
	virtual bool isDirected()const = 0;

	//遍历某一节点连接的节点
	virtual unsigned first(unsigned v)const = 0;
	virtual unsigned next(unsigned v1, unsigned v2)const = 0;

	//设置、删除、清空节点的连边
	virtual void setEdge(unsigned v1, unsigned v2, int weight = 1) = 0;
	virtual void delEdge(unsigned v1, unsigned v2) = 0;
	virtual void clearEdge() = 0;

	//判断节点间是否连接
	virtual bool hasEdge(unsigned v1, unsigned v2)const = 0;

	//返回节点间连边权值
	virtual int weight(unsigned v1, unsigned v2)const = 0;

	//对节点的各种标记
	constexpr static int UNCONNECTED = -1;
	constexpr static int UNVISITED = 0;
	constexpr static int VTSITED = 1;
	constexpr static bool DIRECTED = true;
	constexpr static bool UNDIRECTED = false;
};

//图的遍历
void BFS(Graph*, unsigned);
void DFS(Graph*, unsigned);
void TopSort(Graph*);

//所有节点对的最短路径问题
void FloydWarshall(Graph*, int**);

//单源最短路径问题
void Dijkstra(Graph*, int*, unsigned);

//最小生成树问题
void Prim(Graph*, int*, unsigned);
#endif // !GRAPH_H



