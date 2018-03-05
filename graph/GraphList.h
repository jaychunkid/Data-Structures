//ͼ����������ʵ��
#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include"Graph.h"
#include"LinkedList.h"

class GraphList:public Graph {

	//�ڲ���ʵ��������
	struct Edge {
		unsigned label;
		int weight;

		Edge(unsigned l = 0, int w = 0) :label(l), weight(w) {}
	};

	LinkedList<Edge>** list;       //��������
	unsigned vertex, edge;         //ͼ�Ľڵ�����������
	int* mark;                     //���ڵ�ı��
	bool is_directed;              //�Ƿ�Ϊ����ͼ�ı��

public:
	//���캯����Ĭ��Ϊ����ͼ
	GraphList(unsigned v, bool d = false) :vertex(v), edge(0), is_directed(d) {
		list = new LinkedList<Edge>*[vertex];
		for (unsigned i = 0; i < vertex; ++i)
			list[i] = new LinkedList<Edge>();
		mark = new int[vertex]();
	}

	//��������
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

	//��ʼ�����нڵ�ı��
	void clearMark() {
		for (unsigned i = 0; i < vertex; ++i)
			mark[i] = UNVISITED;
	}
	
	unsigned inDegree(unsigned v)const {
		//��������ͼ����Ӧ�����ȼ�Ϊ�ڵ����
		if (!is_directed)
			return list[v]->length();

		//��������ͼ��������������������
		unsigned count = 0;
		for (unsigned i = 0; i < vertex; ++i)
			if (hasEdge(i, v))
				++count;
		return count;
	}
	
	//��Ӧ�����ȼ�Ϊ�ڵ����
	unsigned outDegree(unsigned v)const { return list[v]->length(); }

	bool isDirected()const { return is_directed; }
	
	unsigned first(unsigned v)const {
		
		//�ýڵ�Ϊ�����㣬���ؽڵ���
		if (list[v]->isEmpty())
			return vertex;
		
		//���ض�Ӧ�����ͷԪ�أ����ߣ�ָ��ڵ�
		list[v]->moveToFront();
		Edge tmp;
		list[v]->getValue(tmp);
		return tmp.label;
	}

	unsigned next(unsigned v1, unsigned v2)const {
		
		//�ڵ�Ϊ�����㣬���ؽڵ���
		if (list[v1]->isEmpty())
			return vertex;
		
		Edge tmp;

		//��¼������դ���Ƿ񵽴�����β
		bool isntEnd = list[v1]->getValue(tmp);

		//����դ����������β������
		//����դ��ָ������߽ڵ���С��v2
		if (!isntEnd || tmp.label < v2) {

			//����դ��ָ������β������������ͷ
			if (!isntEnd)
				list[v1]->moveToFront();

			//��ǰ����������
			while (list[v1]->curPos() < list[v1]->length()) {
				list[v1]->getValue(tmp);

				//դ��ָ����v2�����ߣ�ֹͣ����
				if (tmp.label == v2)
					break;

				//�����в�������v2�����ߣ����ؽڵ���
				if (tmp.label > v2)
					return vertex;

				list[v1]->next();
			}

			//������������δ�ҵ���v2�����ߣ����ؽڵ���
			return vertex;
		}

		//����դ��ָ�����߽ڵ��Ŵ���v2
		else if (tmp.label > v2) {

			//�Ӻ���ǰ��������
			for (int i = list[v1]->curPos(); i >= 0; --i) {
				list[v1]->getValue(tmp);

				//դ��ָ����v2�����ߣ�ֹͣ����
				if (tmp.label == v2)
					break;

				//�����в�������v2�����ߣ����ؽڵ���
				if (tmp.label < 2)
					return vertex;

				list[v1]->prev();
			}

			//������������δ�ҵ���v2�����ߣ����ؽڵ���
			return vertex;
		}

		//��ȡ��������v2���ߵ���һ����
		list[v1]->next();

		//��������һ���ߣ���������ָ��ڵ�ı��
		//�����򷵻ؽڵ���
		if (list[v1]->getValue(tmp))
			return tmp.label;
		else return vertex;
	}

	void setEdge(unsigned v1, unsigned v2, int weight = 1) {
		Edge e(v2, weight);

		//�жϽڵ������Ƿ��Ѵ��ڣ�����λդ��
		if (hasEdge(v1, v2)) {

			//ɾ����Ӧ���ߣ��������������
			list[v1]->remove();
			list[v1]->insert(e);

			//��������ͼ������һ�ڵ��Ӧ�����������跴������
			if (!is_directed) {
				Edge e2(v1, weight);
				hasEdge(v2, v1);          //��λդ��
				list[v2]->remove();
				list[v2]->insert(e2);
			}
		}

		else {
			//���߲����ڣ�ֱ�Ӳ���������
			list[v1]->insert(e);

			//��������ͼ������һ�ڵ��Ӧ�������в��뷴������
			if (!is_directed) {
				Edge e2(v1, weight);
				hasEdge(v2, v1);
				list[v2]->insert(e2);
			}

			//��������һ
			++edge;
		}
	}

	void delEdge(unsigned v1, unsigned v2) {

		//�ж������Ƿ���ڣ�����λդ��
		if (hasEdge(v1, v2)) {
			list[v1]->remove();

			//��������ͼ��ɾ����һ�ڵ��Ӧ�����еķ�������
			if (!is_directed) {
				hasEdge(v2, v1);
				list[v2]->remove();
			}
		}
	}

	//hasEdge�����жϽڵ�v1��v2���Ƿ�������
	//����������Ӧ����դ��ָ��ڵ�Ϊv2������
	//������ָ���һ������v2�ڵ�����ߣ���������ָ������ͷ��
	bool hasEdge(unsigned v1, unsigned v2)const {
		Edge tmp(vertex, 0);

		//դ����ǰָ�����߽ڵ�Ϊv2
		if (list[v1]->getValue(tmp) && tmp.label == v2)
			return true;

		//դ����ǰָ�����߽ڵ���С��v2
		else if (list[v1]->curPos() != list[v1]->length() && tmp.label < v2) {

			//��ǰ����������
			for (; list[v1]->curPos() < list[v1]->length();
				list[v1]->next()) {
				list[v1]->getValue(tmp);
				if (tmp.label == v2)
					return true;
				if (tmp.label > v2)
					break;
			}
		}

		//դ����ǰָ�����߽ڵ��Ŵ���v2
		//����դ��ָ������β
		else {
			//�Ӻ���ǰ��������
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

		//δ�ҵ�ָ��ڵ�v2������
		return false;
	}

	//�����������
	void clearEdge() {

		//�������������clear����
		for (unsigned i = 0; i < vertex; ++i)
			list[i]->clear();
		edge = 0;
	}

	int weight(unsigned v1, unsigned v2)const {
		//�Ҳ�����Ӧ���ߣ�����-1
		if (!hasEdge(v1, v2))
			return UNCONNECTED;

		Edge tmp;
		list[v1]->getValue(tmp);
		return tmp.weight;
	}
};
#endif // !GRAPHLIST_H

