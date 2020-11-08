#include <iostream>
#include "MGraph.h"
#include "LList.h"

using namespace std;

template <typename T>
void graph<T>::addTop(const T& a)
{ // създаване на линеен списък, съдържащ елемента a
	LList<T> l;
	l.toEnd(a);
	// включване на върха a към графа
	g.toEnd(l);
}

template <typename T>
void graph<T>::deleteTop(const T& a)
{
	// обхождане на графа с цел изтриване на всички
	// ребра от произволен връх до върха a
	g.iterStart();
	elem_link1<LList<T> >* p = g.iter(), * r;
	while (p)
	{
		p->inf.iterStart();
		elem_link1<T>* q = p->inf.iter();
		if (rib(q->inf, a)) deleteRib(q->inf, a);
		p = p->link;
	}

	// изтриване на линейния списък, представящ
	// върха a и неговите наследници
	g.iterStart();
	elem_link1<T>* q;
	do
	{
		r = g.iter();
		r->inf.iterStart();
		q = r->inf.iter();
	} while (q->inf != a); // a е връх на графа
	LList<T> x;
	g.deleteElem(r, x);
}

template <typename T>
void graph<T>::addRib(const T& a, const T& b)
{
	g.iterStart();
	elem_link1<LList<T> >* p;
	elem_link1<T>* q;
	do
	{
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	} while (q->inf != a);
	p->inf.toEnd(b);
}

template <typename T>
void graph<T>::deleteRib(const T& a, const T& b)
{
	g.iterStart();
	elem_link1<LList<T> >* p;
	elem_link1<T>* q;
	do
	{
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	} while (q->inf != a);
	q = q->link;
	// намиране на указател към наследника b на върха a
	while (q->inf != b) q = q->link;
	T x; p->inf.deleteElem(q, x);
}

template <typename T>
bool graph<T>::top(const T& a)
{
	if (g.empty()) return false;
	g.iterStart();
	elem_link1<LList<T> >* p = g.iter();
	elem_link1<T>* q;
	do
	{
		p->inf.iterStart();
		q = p->inf.iter();
		p = p->link;
	} while (q->inf != a && p);
	return q->inf == a;
}

template <typename T>
bool graph<T>::rib(const T& a, const T& b)
{
	elem_link1<T>* p = point(a);
	p = p->link;
	while (p && p->inf != b) p = p->link;
	return p != NULL;
}

template <typename T>
bool graph<T>::empty() const
{
	return g.empty();
}

template <typename T>
elem_link1<T>* graph<T>::point(const T& a)
{
	g.iterStart();
	elem_link1<LList<T> >* p;
	elem_link1<T>* q;
	do
	{
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	} while (q->inf != a);
	return q;
}

template <typename T>
LList<T> graph<T>::vertexes()
{
	LList<T> l;
	g.iterStart();
	elem_link1<LList<T> >* p = g.iter();
	while (p)
	{
		p->inf.iterStart();
		elem_link1<T>* q = p->inf.iter();
		l.toEnd(q->inf);
		p = p->link;
	}
	return l;
}

template <typename T>
void graph<T>::print()
{
	g.iterStart();
	elem_link1<LList<T> >* p = g.iter();
	while (p)
	{
		p->inf.print();
		p = p->link;
	}
	cout << endl;
}