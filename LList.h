#pragma once
#include "./ElemLink.h"



template <typename T = int>
class LList
{
public:
	// ��������� �����������
	LList();
	~LList();
	LList(const LList&);
	LList& operator=(const LList&);
	// ������� �������
	bool empty() const;
	void iterStart(elem_link1<T>* = NULL);
	elem_link1<T>* iter();
	void toEnd(const T&);
	void insertAfter(elem_link1<T>*, const T&);
	void insertBefore(elem_link1<T>*, const T&);
	void deleteAfter(elem_link1<T>*, T&);
	void deleteBefore(elem_link1<T>*, T&);
	void deleteElem(elem_link1<T>*, T&);
	void print() const;
	int length() const;
	void concat(const LList&);
	void reverse();
private:
	elem_link1<T>* start, // �������� ��� ��������
		* end, // �������� ��� ����
		* current; // �������� ��� ����� �������
		// ������� �������
	void copyList(const LList&);
	void deleteList();
};