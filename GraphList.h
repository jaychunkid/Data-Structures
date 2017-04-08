//图的链表数组实现
#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include"Graph.h"
#include"LinkedList.h"

class GraphList:public Graph {

	//内部类实现连边类
	struct Edge {
		unsigned label;
		int weight;

		Edge(unsigned l = 0, int w = 0) :label(l), weight(w) {}
	};

	LinkedList<Edge>** list;       //链表数组
	unsigned vertex, edge;         //图的节点数和连边数
	int* mark;                     //各节点的标记
	bool is_directed;              //是否为有向图的标记

public:
	//构造函数，默认为无向图
	GraphList(unsigned v, bool d = false) :vertex(v), edge(0), is_directed(d) {
		list = new LinkedList<Edge>*[vertex];
		for (unsigned i = 0; i < vertex; ++i)
			list[i] = new LinkedList<Edge>();
		mark = new int[vertex]();
	}

	//析构函数
	~GraphList() {
		for (unsigned i = 0; i < vertex; ++i)
			delete list[i];
		delete[]list;
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
	
	unsigned inDegree(unsigned v)const {
		//对于无向图，对应链表长度即为节点入度
		if (!is_directed)
			return list[v]->length();

		//对于有向图，遍历所有链表计算入度
		unsigned count = 0;
		for (unsigned i = 0; i < vertex; ++i)
			if (hasEdge(i, v))
				++count;
		return count;
	}
	
	//对应链表长度即为节点出度
	unsigned outDegree(unsigned v)const { return list[v]->length(); }

	bool isDirected()const { return is_directed; }
	
	unsigned first(unsigned v)const {
		
		//该节点为孤立点，返回节点数
		if (list[v]->isEmpty())
			return vertex;
		
		//返回对应链表的头元素（连边）指向节点
		list[v]->moveToFront();
		Edge tmp;
		list[v]->getValue(tmp);
		return tmp.label;
	}

	unsigned next(unsigned v1, unsigned v2)const {
		
		//节点为孤立点，返回节点数
		if (list[v1]->isEmpty())
			return vertex;
		
		Edge tmp;

		//记录链表内栅栏是否到达链表尾
		bool isntEnd = list[v1]->getValue(tmp);

		//链表栅栏到达链表尾，或者
		//链表栅栏指向的连边节点编号小于v2
		if (!isntEnd || tmp.label < v2) {

			//链表栅栏指向链表尾，则将其移至表头
			if (!isntEnd)
				list[v1]->moveToFront();

			//从前向后遍历链表
			while (list[v1]->curPos() < list[v1]->length()) {
				list[v1]->getValue(tmp);

				//栅栏指向与v2的连边，停止遍历
				if (tmp.label == v2)
					break;

				//链表中不存在与v2的连边，返回节点数
				if (tmp.label > v2)
					return vertex;

				list[v1]->next();
			}

			//遍历完链表仍未找到与v2的连边，返回节点数
			return vertex;
		}

		//链表栅栏指向连边节点编号大于v2
		else if (tmp.label > v2) {

			//从后向前遍历链表
			for (int i = list[v1]->curPos(); i >= 0; --i) {
				list[v1]->getValue(tmp);

				//栅栏指向与v2的连边，停止遍历
				if (tmp.label == v2)
					break;

				//链表中不存在与v2的连边，返回节点数
				if (tmp.label < 2)
					return vertex;

				list[v1]->prev();
			}

			//遍历完链表仍未找到与v2的连边，返回节点数
			return vertex;
		}

		//获取链表中与v2连边的下一连边
		list[v1]->next();

		//若存在下一连边，返回连边指向节点的编号
		//，否则返回节点数
		if (list[v1]->getValue(tmp))
			return tmp.label;
		else return vertex;
	}

	void setEdge(unsigned v1, unsigned v2, int weight = 1) {
		Edge e(v2, weight);

		//判断节点连边是否已存在，并定位栅栏
		if (hasEdge(v1, v2)) {

			//删除对应连边，重新添加新连边
			list[v1]->remove();
			list[v1]->insert(e);

			//对于无向图，在另一节点对应的链表中重设反向连边
			if (!is_directed) {
				Edge e2(v1, weight);
				hasEdge(v2, v1);          //定位栅栏
				list[v2]->remove();
				list[v2]->insert(e2);
			}
		}

		else {
			//连边不存在，直接插入新连边
			list[v1]->insert(e);

			//对于无向图，在另一节点对应的链表中插入反向连边
			if (!is_directed) {
				Edge e2(v1, weight);
				hasEdge(v2, v1);
				list[v2]->insert(e2);
			}

			//连边数加一
			++edge;
		}
	}

	void delEdge(unsigned v1, unsigned v2) {

		//判断连边是否存在，并定位栅栏
		if (hasEdge(v1, v2)) {
			list[v1]->remove();

			//对于无向图，删除另一节点对应链表中的反向连边
			if (!is_directed) {
				hasEdge(v2, v1);
				list[v2]->remove();
			}
		}
	}

	//hasEdge函数判断节点v1到v2间是否有连边
	//，如果有则对应链表栅栏指向节点为v2的连边
	//，否则指向第一个大于v2节点的连边（无连边则指向链表头）
	bool hasEdge(unsigned v1, unsigned v2)const {
		Edge tmp(vertex, 0);

		//栅栏当前指向连边节点为v2
		if (list[v1]->getValue(tmp) && tmp.label == v2)
			return true;

		//栅栏当前指向连边节点编号小于v2
		else if (list[v1]->curPos() != list[v1]->length() && tmp.label < v2) {

			//从前向后遍历链表
			for (; list[v1]->curPos() < list[v1]->length();
				list[v1]->next()) {
				list[v1]->getValue(tmp);
				if (tmp.label == v2)
					return true;
				if (tmp.label > v2)
					break;
			}
		}

		//栅栏当前指向连边节点编号大于v2
		//，或栅栏指向链表尾
		else {
			//从后向前遍历链表
			for (int i = list[v1]->curPos(); i >= 0; --i) {
				list[v1]->getValue(tmp);
				if (tmp.label == v2)
					return true;
				if (tmp.label < v2) {
					list[v1]->next();
					break;
				}
				list[v1]->prev();
			}
		}

		//未找到指向节点v2的连边
		return false;
	}

	//清除所有连边
	void clearEdge() {

		//对所有链表调用clear函数
		for (unsigned i = 0; i < vertex; ++i)
			list[i]->clear();
		edge = 0;
	}

	int weight(unsigned v1, unsigned v2)const {
		//找不到对应连边，返回-1
		if (!hasEdge(v1, v2))
			return UNCONNECTED;

		Edge tmp;
		list[v1]->getValue(tmp);
		return tmp.weight;
	}
};
#endif // !GRAPHLIST_H

