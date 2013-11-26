#include "Graph.h"

Graph Clique::_graph;

Clique::Clique(int a, int b){
	_clique.add(a);
	_clique.add(b);
	_Ni = _graph.Ni(a).intersection(_graph.Ni(b));
}

Clique::Clique(Clique &ot){
	_clique =  VertexSet(ot._clique);
	_Ni =  VertexSet(ot._Ni);
}

Clique::Clique(Clique ot, int vertex){
	_clique =  VertexSet(ot._clique);
	_Ni =  VertexSet(ot._Ni);
	this->addVertex(vertex);
}

int Clique::size(){return _clique.size();}

VertexSet Clique::clique(){return this->_clique;}

void Clique::addVertex(int vertex){
	_clique.add(vertex);
	_Ni = _Ni.intersection(_graph.Ni(vertex));
}

VertexSet Clique::commonNi(){return _Ni;}

string Clique::toFile(){
	string s;
	for(int i=0;i<this->_clique.size();i++) {s+=this->_clique.at(i)+",";}
	return s;
}





