//����ͼ
#ifndef GRAPH_H
#define GRAPH_H

//ͼ�ĳ�����
class Graph {
public:
	virtual unsigned n()const = 0;          //����ͼ�Ľڵ����
	virtual unsigned e()const = 0;          //����ͼ�����߸���

	//ʵ�ֶ�ͼ�нڵ�ı��
	virtual int getMark(unsigned v)const = 0;
	virtual void setMark(unsigned v, int m) = 0;
	virtual void clearMark() = 0;

	//��ȡ�ڵ�ĳ��������
	virtual unsigned inDegree(unsigned v)const = 0;
	virtual unsigned outDegree(unsigned v)const = 0;

	//�ж�ͼ�Ƿ�Ϊ����ͼ
	virtual bool isDirected()const = 0;

	//����ĳһ�ڵ����ӵĽڵ�
	virtual unsigned first(unsigned v)const = 0;
	virtual unsigned next(unsigned v1, unsigned v2)const = 0;

	//���á�ɾ������սڵ������
	virtual void setEdge(unsigned v1, unsigned v2, int weight = 1) = 0;
	virtual void delEdge(unsigned v1, unsigned v2) = 0;
	virtual void clearEdge() = 0;

	//�жϽڵ���Ƿ�����
	virtual bool hasEdge(unsigned v1, unsigned v2)const = 0;

	//���ؽڵ������Ȩֵ
	virtual int weight(unsigned v1, unsigned v2)const = 0;

	//�Խڵ�ĸ��ֱ��
	constexpr static int UNCONNECTED = -1;
	constexpr static int UNVISITED = 0;
	constexpr static int VTSITED = 1;
	constexpr static bool DIRECTED = true;
	constexpr static bool UNDIRECTED = false;
};

//ͼ�ı���
void BFS(Graph*, unsigned);
void DFS(Graph*, unsigned);
void TopSort(Graph*);

//���нڵ�Ե����·������
void FloydWarshall(Graph*, int**);

//��Դ���·������
void Dijkstra(Graph*, int*, unsigned);

//��С����������
void Prim(Graph*, int*, unsigned);
#endif // !GRAPH_H



