#include "classes.h"
Graph Clique::_graph;
void Clique::init(Graph &g) { Clique::_graph.operator=(g); }

Clique::Clique(int a, int b){
	_clique = VertexSet1();
	_clique.add(a);
	_clique.add(b);
	//_Ni = _graph.Ni(a).intersection(_graph.Ni(b));
}
Clique::Clique(const Clique &ot){
	_clique = VertexSet1(ot._clique);
	_Ni = VertexSet1(ot._Ni);
}
Clique::Clique(Clique ot, int vertex){
	ot = Clique(ot);
	addVertex(vertex);
}
string Clique::toFile() {
	string ans = "";
	for (int i = 0; i<this->_clique.size(); i++) { ans += this->_clique.at(i) + ","; }
	return ans;
}
int Clique::size() { return this->_clique.size(); }
VertexSet1 Clique::clique() { return this->_clique; }
void Clique::addVertex(int vertex){
	_clique.add(vertex);
	//	_Ni = _Ni.intersection(_graph.Ni(vertex));
}
VertexSet1 Clique::commonNi() {
	return _Ni;
}
Clique::~Clique(){
	_clique.~VertexSet1();
	//_graph.~Graph();
	_Ni.~VertexSet1();
}