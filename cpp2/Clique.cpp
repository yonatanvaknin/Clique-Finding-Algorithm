#include "Clique.h"

using namespace System;

void Clique::init(Graph ^g)
{
	_graph = g;
}

Clique::Clique(int a, int b)
{
	_clique = gcnew VertexSet();
	_clique->add(a);
	_clique->add(b);
	_Ni = _graph->Ni(a)->intersection(_graph->Ni(b));
}

Clique::Clique(Clique ^ot)
{
	_clique = gcnew VertexSet(ot->_clique);
	_Ni = gcnew VertexSet(ot->_Ni);
}

//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
Clique::Clique(Clique ^ot, int vertex)
{
	this->addVertex(vertex);
}

String ^Clique::toFile()
{
	String ^ans = "";
	for (int i = 0;i < this->_clique->size();i++)
	{
		ans += this->_clique->at(i) + ",";
	}
	return ans;
}

int Clique::size()
{
	return this->_clique->size();
}

VertexSet ^Clique::clique()
{
	return this->_clique;
}

void Clique::addVertex(int vertex)
{
	_clique->add(vertex);
	_Ni = _Ni->intersection(_graph->Ni(vertex));
}

VertexSet ^Clique::commonNi()
{
	return _Ni;
}
