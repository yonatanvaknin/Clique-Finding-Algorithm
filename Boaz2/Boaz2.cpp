// Main. Assuming args are included via consle

#include "stdafx.h"
#include <ctime>
#include <vector>
#include "Graph.h"
#include "VertexSet.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string in_file = (char*)argv[0][0];
	double TH = (double)argv[0][1];
	int minQ = (int)argv[0][2];
	int maxQ = (int)argv[0][3];

	clock_t t0 = clock();
	Graph g(in_file,TH);
	clock_t t1 = clock();
	double elap = double(t0-t1);
	cout<<"init graph: "<<elap<<" sec";
	vector<VertexSet> c1 = g.all_cliques(maxQ);
	clock_t t2 = clock();
	double elap2 = double(t2-t1);
	cout<<"Algo: "<<elap<<" sec";

	g.write2file();
}

