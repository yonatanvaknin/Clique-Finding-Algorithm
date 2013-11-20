// I decided to merge Graph and Clique headers inside Graph header
// because it can fix our major compiling problem and basically
// clique is also a graph

#include "stdafx.h"

#ifndef GRAPH_H
#define GRAPH_H

#include <sstream>
#include <vector>
#include <fstream>
#include "VertexSet.h"


using namespace std;
class Clique;

class Graph{
	
private:
	string _file_name;
	vector<VertexSet> _V;
	double _TH;
	int _E_size; //initialize
	bool _mat_flag; //initialize
	void init();
	// clique algorithms def//
	void addbiggerCliQ(vector<VertexSet> &ans, VertexSet curr, VertexSet inter);
	vector<VertexSet> addbiggerCliQ(VertexSet curr, VertexSet inter);
	vector<VertexSet> allEdges();
	void addToSet(vector<VertexSet> ans, vector<Clique> c1);
public:
	Graph(){};// default empty constuctor
	Graph(string file, double th);
	VertexSet Ni(int i);
	void print();
	// clique algorithms def//
	vector<VertexSet> all_cliques(int q_size);
	vector<VertexSet> all_cliques(int min_q_size, int max_q_size);
	vector<VertexSet> all_cliques_of_edge(VertexSet e, int min_q_size, int max_q_size);
	vector<VertexSet> allC(vector<VertexSet> c0);
	VertexSet intersection(VertexSet c);
	vector<VertexSet> all_cliques_DFS(int min_size, int max_size);
	vector<VertexSet> all_cliques_DFS(string out_file, int min_size, int max_size);
	vector<Clique> allC_seed(Clique edge, int min_size, int max_size);
	void write2file();
};

class Clique {
private:
	VertexSet _clique;
	VertexSet _Ni;
	static Graph _graph;
public:
	Clique(int a, int b);
	Clique(Clique &ot);
	Clique(Clique ot, int vertex);
	int size();
	VertexSet clique();
	void addVertex(int vertex);
	VertexSet commonNi();
	string toFile();
	static void init(Graph &g){_graph=g;}
};

#endif