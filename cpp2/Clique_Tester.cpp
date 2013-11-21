#include "Clique_Tester.h"
#include "Graph.h"

using namespace System;

void Clique_Tester::main(array<String^> ^args)
{
	if (args == nullptr || args->Length < 3)
	{
		help();
		args = default_args;
	}
	parse(args);
	Int64 t0 = (DateTime::Now)->Ticks;
	Graph ^G = gcnew Graph(in_file, TH);
	Int64 t1 = (DateTime::Now)->Ticks;
	Console::WriteLine("Init Graph: " + (t1 - t0) + "  ms");
	//Vector<VertexSet> c1 = G.All_Cliques(maxQ);	
	//	Vector<VertexSet> c2 = G.All_Cliques_DFS(2,maxQ);
	Int64 t2 = (DateTime::Now)->Ticks;
	if (out_file == nullptr)
	{
		out_file = in_file + "_" + TH + "_" + minQ + "_" + maxQ + ".csv";
	}
	G->All_Cliques_DFS(out_file,minQ,maxQ);
	Int64 t3 = (DateTime::Now)->Ticks;
	Console::WriteLine("Alg3: " + (t3 - t2) + "  ms");
}

void Clique_Tester::help()
{
	Console::WriteLine("***Wrong Parameters! should use: java -jar All_Cliques <input file> <round value> <min clique> <max clique> <output file> <max_cliques> <Graph convert flag>");
	Console::WriteLine("Wrong Parameters! should use: java -jar All_Cliques test1.csv 0.7 5 7 test1_out.txt 10000 true");
}

void Clique_Tester::parse(array<String^> ^a)
{
	try
	{
		in_file = a[0];
		TH = double(a[1]);
		minQ = int(a[2]);
		maxQ = int(a[3]);
		if (a->Length > 4)
		{
			out_file = a[4];
		}
		if (a->Length > 5)
		{
			MAX_CLIQUE = int(a[5]);
		}
		if (a->Length > 6)
		{
			Convert = bool(a[6]);
		}
	}
	catch (Exception ^e)
	{
		Console::WriteLine(e->ToString());
		Console::Write(e->StackTrace);
		help();
	}
}
