// Main. Assuming args are included via consle

#include "stdafx.h"
#include <ctime>
#include <vector>
#include "Graph.h"
#include "VertexSet.h"
using namespace std;

int _tmain(int argc, char* argv[])
{
	
	char* in_file = "test1.csv";
	double TH = 0.75;
	int minQ = 6;
	int maxQ = 10;
	clock_t t0 = clock();
	Graph g(in_file,TH);
	clock_t t1 = clock();
	double elap = double(t1-t0)/CLOCKS_PER_SEC;
	cout<<"init graph: "<<elap<<" sec";
	vector<VertexSet> c1 = g.all_cliques(maxQ);
	clock_t t2 = clock();
	double elap2 = double(t2-t1);
	cout<<"Algo: "<<elap<<" sec";
	g.write2file();
	system("PAUSE");
}

