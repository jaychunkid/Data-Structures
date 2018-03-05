//�б������ʵ��
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include"List.h"

template <typename Elem>
class ArrayList:public List<Elem> {
	Elem* list = nullptr;
	unsigned fence = 0;              //դ��ָ��λ��
	unsigned max_size = 10;          //Ĭ�ϳ�ʼ������鳤��Ϊ10
	unsigned size = 0;               //�б���

	//�ڲ�����ʵ�����鳤����չ
	void expend() {
		max_size *= 10;                                 //�����еĿռ����������ʮ��
		Elem* tmp = list;
		list = new Elem[max_size]();
		for (unsigned i = 0; i < size; ++i)
			list[i] = tmp[i];
		delete[]tmp;
		return;
	}

public:
	ArrayList() { list = new Elem[max_size](); }        //���캯��
	~ArrayList() { delete[]list; }                      //��������

	void clear() { fence = size = 0; }

	void pushBack(const Elem &e) {                      
		
		//����ռ䲻�㣬��չ���鳤��
		if (size == max_size - 1)
			expend();

		list[size++] = e;
	}

	//��fence��ָ���λ�ò���Ԫ��
	void insert(const Elem &e) {                        
		if (size >= max_size - 1)
			expend();

		//���fence��ָ���β����fenceָ��λ�ü�֮���Ԫ������ƶ�һ��λ��
		if (fence != size)
			for (unsigned i = size - 1; i >= fence; --i)
				list[i + 1] = list[i];

		//fenceָ��ԭ���ڸ�λ�õ�Ԫ��
		list[fence++] = e;
		++size;
		return;
	}

	//ɾ��fence��ָ��λ�õ�Ԫ��
	void remove() {                                     
		if (fence < size) {

			//��fenceָ��λ�ü�֮���Ԫ����ǰ�ƶ�һ��λ��
			for (unsigned i = fence; i < size; ++i)
				list[i] = list[i + 1];

			--size;
		}
		return;
	}

	unsigned curPos() { return fence; }                 

	bool setPos(unsigned pos) {                          
		
		//���õ�λ��Խ���˱�β������ʧ��
		if (pos > size)
			return false;

		fence = pos;
		return true;
	}

	void moveToFront() { fence = 0; }                   
	void moveToBack() { fence = size; }                

	bool getValue(Elem &e)const {                       
		
		//դ��ָ��λ��Խ���˱�β������ʧ��
		if (fence >= size)
			return false;

		e = list[fence];
		return true;
	}

	void prev() {

		//���դ����ָ���ͷ�������κβ���
		if (fence > 0)
			--fence;
	}

	void next() {  

		//���դ����ָ���β�������κβ���
		if (fence < size)
			++fence;
	}

	bool isEmpty()const { return !size; }              
	unsigned length()const { return size; }            
};
#endif // !ARRAYLIST_H

