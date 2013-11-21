#include "VertexSet.h"

VertexSet::VertexSet()
{
	InitializeInstanceFields();
	_set = new int[INIT_SIZE];
	_sp = 0;
}

VertexSet::VertexSet(VertexSet *ot)
{
	InitializeInstanceFields();
	_set = new int[INIT_SIZE];
	_sp = 0;
	for (int i = 0;i < ot->size();i++)
	{
		this->add(ot->at(i));
	}
}

void VertexSet::add(int a)
{
	if (_sp == _set->length)
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

std::wstring VertexSet::toString()
{
	std::wstring ans = std::wstring(L"Set: |") + size() + std::wstring(L"| ");
	for (int i = 0;i < size();i++)
	{
		ans += this->at(i) + std::wstring(L", ");
	}
	return ans;
}

std::wstring VertexSet::toFile()
{
	std::wstring ans = L" ";
	for (int i = 0;i < size();i++)
	{
		ans += this->at(i) + std::wstring(L", ");
	}
	return ans;
}

VertexSet *VertexSet::intersection(VertexSet *ot)
{
	VertexSet *ans = new VertexSet();
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
	int tmp[_sp + INC];
	for (int i = 0;i < _sp;i++)
	{
		tmp[i] = _set[i];
	}
	_set = tmp;
}

void VertexSet::InitializeInstanceFields()
{
	_set = 0;
	_sp = 0;
}
