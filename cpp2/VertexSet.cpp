#include "VertexSet.h"

using namespace System;

VertexSet::VertexSet()
{
	_set = gcnew array<int>(INIT_SIZE);
	_sp = 0;
}

VertexSet::VertexSet(VertexSet ^ot)
{
	_set = gcnew array<int>(INIT_SIZE);
	_sp = 0;
	for (int i = 0;i < ot->size();i++)
	{
		this->add(ot->at(i));
	}
}

void VertexSet::add(int a)
{
	if (_sp == _set->Length)
	{
		resize();
	}
	_set[_sp] = a;
	_sp++;
}

int VertexSet::size()
{
	return _sp;
}

int VertexSet::at(int i)
{
	return _set[i];
}

String ^VertexSet::ToString()
{
	String ^ans = "Set: |" + size() + "| ";
	for (int i = 0;i < size();i++)
	{
		ans += this->at(i) + ", ";
	}
	return ans;
}

String ^VertexSet::toFile()
{
	String ^ans = " ";
	for (int i = 0;i < size();i++)
	{
		ans += this->at(i) + ", ";
	}
	return ans;
}

VertexSet ^VertexSet::intersection(VertexSet ^ot)
{
	VertexSet ^ans = gcnew VertexSet();
	int i1 = 0, i2 = 0;
	while (i1 < this->size() & i2 < ot->size())
	{
		int a1 = this->at(i1), a2 = ot->at(i2);
		if (a1 == a2)
		{
			ans->add(a1);
			i1++;
			i2++;
		}
		else if (a1 < a2)
		{
			i1++;
		}
		else
		{
			i2++;
		}
	}
	return ans;
}

void VertexSet::resize()
{
	array<int> ^tmp = gcnew array<int>(_sp + INC);
	for (int i = 0;i < _sp;i++)
	{
		tmp[i] = _set[i];
	}
	_set = tmp;
}
