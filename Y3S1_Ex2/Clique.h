#include "Graph.h"

class Clique
{
private:
	VertexSet _clique;
	VertexSet _Ni;
	static Graph _graph;
public:
	static void init(Graph g) { _graph = g; };
	Clique(int a, int b);
	Clique(Clique& ot);
	Clique(Clique& ot, int vertex);
	~Clique();
	string toFile();
	int size() { return _clique.size(); };
	VertexSet clique() { return _clique; };
	void addVertex(int vertex);
	VertexSet commonNi() { return _Ni; };
};

Clique::Clique(int a, int b)
{
	_clique.add(a);
	_clique.add(b);
	_Ni = _graph.Ni(a).intersection(_graph.Ni(b));
}

Clique::Clique(Clique& ot)
{
	_clique = VertexSet(ot._clique);
	_Ni = VertexSet(ot._Ni);
}

Clique::Clique(Clique& ot, int vertex)
{
	Clique(*ot);
	addVertex(vertex);
}

string Clique::toFile()
{
	string ans = "";
	for (int i = 0; i < _clique.size(); i++)
	{
		ans += to_string(_clique.at(i)) + ", ";
	}
	return ans;
}

void Clique::addVertex(int vertex){
	_clique.add(vertex);
	_Ni = _Ni.intersection(_graph.Ni(vertex));
}