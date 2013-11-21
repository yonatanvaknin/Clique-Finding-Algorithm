/*
#include "Clique_Tester.h"
#include "Graph.h"
#include <ctime>


using namespace std;

int minQ, Clique_Tester::maxQ = 10;
double Clique_Tester::TH = 0.75;
string Clique_Tester::in_file = "test1.csv";
string Clique_Tester::out_file = nullptr;
bool Clique_Tester::Debug = true;
int Clique_Tester::MAX_CLIQUE = 100000;
bool Clique_Tester::Convert = true;
string Clique_Tester::default_args[4] = {"data/test1.csv", "0.8","15","20"};

void Clique_Tester::main(string args[])
{
if (args == nullptr || sizeof(args) / sizeof(args[0]) < 3)
	{
		help();
		args = default_args;
	}
	parse(args);


	long long t0 = clock();
	Graph G(in_file, TH);
	long long t1 = clock();
	std::cout << "Init Graph: " << (t1 - t0) << "  ms or ssc?"<< std::endl;
	//Vector<VertexSet> c1 = G.All_Cliques(maxQ);	
	//	Vector<VertexSet> c2 = G.All_Cliques_DFS(2,maxQ);
	long long t2 = clock();

	//if (out_file == L"")
	//{
		out_file = in_file + "_" + TH + "_" + minQ + "_" + maxQ + ".csv";
	//}
	//G->All_Cliques_DFS(out_file,minQ,maxQ);
	 G.write2file();
	long long t3 = clock();
	std::cout << "Alg3: " << (t3 - t2) << "  ms??" << std::endl;
}


void Clique_Tester::help()
{
	std::cout << "Wrong Parameters! should use: java -jar All_Cliques <input file> <round value> <min clique> <max clique> <output file> <max_cliques> <Graph convert flag>" << std::endl;
	std::cout << "Wrong Parameters! should use: java -jar All_Cliques test1.csv 0.7 5 7 test1_out.txt 10000 true"<< std::endl;
}

void Clique_Tester::parse(string *a)
{
	//try
	//{
		in_file = a[0];
		TH = double(a[1]);
		minQ = int(a[2]);
		maxQ = int(a[3]);
		if (sizeof(a) / sizeof(a[0]) > 4)
		{
			out_file = a[4];
		}
		if (sizeof(a) / sizeof(a[0]) > 5)
		{
			MAX_CLIQUE = int(a[5]);
		}
		if (sizeof(a) / sizeof(a[0]) > 6)
		{
			Convert = bool(a[6]);
		}
	//}
	//catch (std::exception &e)
	//{
	//	e.printStackTrace();
	//	help();
	//}
}
*/

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
        vector<VertexSet> c1 = g.All_Cliques(maxQ);
        clock_t t2 = clock();
        double elap2 = double(t2-t1);
        cout<<"Algo: "<<elap<<" sec";

        g.write2file();
}