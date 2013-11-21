#include "Clique_Tester.h"
#include "Graph.h"

int minQ, Clique_Tester::maxQ = 10;
double Clique_Tester::TH = 0.75;
std::wstring Clique_Tester::in_file = L"test1.csv";
std::wstring Clique_Tester::out_file = nullptr;
bool Clique_Tester::Debug = true;
int Clique_Tester::MAX_CLIQUE = 100000;
bool Clique_Tester::Convert = true;
std::wstring Clique_Tester::default_args[4] = {L"data/test1.csv", L"0.8",L"15",L"20"};

void Clique_Tester::main(std::wstring args[])
{
	if (args == nullptr || sizeof(args) / sizeof(args[0]) < 3)
	{
		help();
		args = default_args;
	}
	parse(args);
	long long t0 = (Date()).getTime();
	Graph *G = new Graph(in_file, TH);
	long long t1 = (Date()).getTime();
	std::cout << std::wstring(L"Init Graph: ") << (t1 - t0) << std::wstring(L"  ms") << std::endl;
	//Vector<VertexSet> c1 = G.All_Cliques(maxQ);	
	//	Vector<VertexSet> c2 = G.All_Cliques_DFS(2,maxQ);
	long long t2 = (Date()).getTime();
	if (out_file == L"")
	{
		out_file = in_file + std::wstring(L"_") + TH + std::wstring(L"_") + minQ + std::wstring(L"_") + maxQ + std::wstring(L".csv");
	}
	G->All_Cliques_DFS(out_file,minQ,maxQ);
	long long t3 = (Date()).getTime();
	std::cout << std::wstring(L"Alg3: ") << (t3 - t2) << std::wstring(L"  ms") << std::endl;
}

void Clique_Tester::help()
{
	std::cout << std::wstring(L"***Wrong Parameters! should use: java -jar All_Cliques <input file> <round value> <min clique> <max clique> <output file> <max_cliques> <Graph convert flag>") << std::endl;
	std::cout << std::wstring(L"Wrong Parameters! should use: java -jar All_Cliques test1.csv 0.7 5 7 test1_out.txt 10000 true") << std::endl;
}

void Clique_Tester::parse(std::wstring a[])
{
	try
	{
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
	}
	catch (std::exception &e)
	{
		e.printStackTrace();
		help();
	}
}
