//�б������
#ifndef LIST_H
#define LIST_H

template <typename Elem>
class List {
public:
	virtual void clear() = 0;                          //����б�����
	virtual void insert(const Elem &e) = 0;			   //��ָ��λ�ò���Ԫ��
	virtual void pushBack(const Elem &e) = 0;          //���б�β��׷��Ԫ��
	virtual void remove() = 0;                         //��ָ��λ��ɾ��Ԫ��

	virtual unsigned curPos() = 0;                     //���ص�ǰָ��λ��
	virtual bool setPos(unsigned pos) = 0;             //����ָ����λ��
	virtual void moveToFront() = 0;                    //����ָ��λ������ͷ
	virtual void moveToBack() = 0;                     //����ָ��λ������β
	virtual bool getValue(Elem &e)const = 0;           //��ȡ��ǰָ��λ�õ�Ԫ��
	virtual void prev() = 0;                           //��ָ��λ����ǰ�ƶ�һλ
	virtual void next() = 0;                           //��ָ��λ������ƶ�һλ

	virtual bool isEmpty()const = 0;                   //�ж��б��Ƿ�Ϊ��
	virtual unsigned length()const = 0;                //�����б���
};
#endif // !LIST_H

