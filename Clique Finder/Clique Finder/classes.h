#pragma once
#include "VertexSet1.h"
#include <iostream>
#include <fstream>
#include "Tokenize.h"
class  Graph;




class Clique {
private:
	VertexSet1 _clique;
	VertexSet1 _Ni;
	static Graph _graph;
public:
	static void init(Graph &g);
	/**
	* start a clique with an edge: represented by the indeses a,b
	* @param a: vertex index
	* @param b: vertex index
	*/
	Clique(int a, int b);
	Clique(const Clique &ot);
	Clique(Clique ot, int vertex);
	string toFile();
	int size();
	VertexSet1 clique();
	void addVertex(int vertex);
	VertexSet1 commonNi();
	Clique::~Clique();
};


/**
* this class represents an undirected 0/1 sparse Graph
* @author Boaz
*
*/
class Graph {
private:
	string _file_name;
	vector <VertexSet1> _V;
	double _TH; // the threshold value
	int _E_size = 0;
	bool _mat_flag = true;
public:
	Graph();
	Graph(string file, double th);
	Graph(const Graph &g);
	void operator =(Graph &g);
	vector<Clique> Graph::allC_seed(Clique edge, int min_size, int max_size);
	void Graph::write2file();
	vector<VertexSet1>  Graph::All_Cliques_DFS(int min_size, int max_size);
	void Graph::All_Cliques_DFS(string out_file, int min_size, int max_size);
	VertexSet1 Graph::Ni(int i);
	void Graph::print();
private:
	void Graph::init();
	vector<VertexSet1> Graph::allEdges();
	void Graph::addToSet(vector<VertexSet1> ans, vector<Clique> C1);

};
