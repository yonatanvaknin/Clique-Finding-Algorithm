#pragma once

#include "VertexSet.h"
#include "Graph.h"
#include <string>

/// <summary>
/// this class represent a dedicated Clique class which assumes undirected graph and holds 
/// the potential Ni intersection. 
/// @author Boaz
/// 
/// </summary>
class Clique
{
private:
	VertexSet *_clique;
	VertexSet *_Ni;
	static Graph *_graph;
public:
	static void init(Graph *g);
	/// <summary>
	/// start a clique with an edge: represented by the indeses a,b </summary>
	/// <param name="a">: vertex index </param>
	/// <param name="b">: vertex index </param>
	Clique(int a, int b);
	Clique(Clique *ot);
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
	Clique(Clique *ot, int vertex); //this(ot);
	virtual std::wstring toFile();
	virtual int size();
	virtual VertexSet *clique();
	virtual void addVertex(int vertex);
	virtual VertexSet *commonNi();
};
