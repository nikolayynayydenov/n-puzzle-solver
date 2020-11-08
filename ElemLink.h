#pragma once

template <typename T = int>
struct elem_link1
{
	T inf; // информационна част
	elem_link1<T>* link; // адресна част
};