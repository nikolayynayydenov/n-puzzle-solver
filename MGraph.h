#pragma once

#include "./ElemLink.h"
#include "./LList.h"

template <typename T>
class graph
{
public:
	void addTop(const T&);
	void deleteTop(const T&);
	void addRib(const T&, const T&);
	void deleteRib(const T&, const T&);
	bool top(const T&);
	bool rib(const T&, const T&);
	bool empty() const;
	elem_link1<T>* point(const T&);
	LList<T> vertexes();
	void print();
private:
	LList< LList<T> > g;
};

