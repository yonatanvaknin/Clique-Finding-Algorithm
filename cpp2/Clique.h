#pragma once

#include "VertexSet.h"
#include "Graph.h"

using namespace System;

/// <summary>
/// this class represent a dedicated Clique class which assumes undirected graph and holds 
/// the potential Ni intersection. 
/// @author Boaz
/// 
/// </summary>
public ref class Clique
{
private:
	VertexSet ^_clique;
	VertexSet ^_Ni;
	static Graph ^_graph = nullptr;
public:
	static void init(Graph ^g);
	/// <summary>
	/// start a clique with an edge: represented by the indeses a,b </summary>
	/// <param name="a">: vertex index </param>
	/// <param name="b">: vertex index </param>
	Clique(int a, int b);
	Clique(Clique ^ot);
//JAVA TO C++ CONVERTER TODO TASK: Calls to same-class constructors are not supported in C++ prior to C++11:
	Clique(Clique ^ot, int vertex); //this(ot);
	virtual String ^toFile();
	virtual int size();
	virtual VertexSet ^clique();
	virtual void addVertex(int vertex);
	virtual VertexSet ^commonNi();
};
