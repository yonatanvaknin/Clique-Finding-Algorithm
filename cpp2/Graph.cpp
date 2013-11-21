#include "Graph.h"
#include "Clique_Tester.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

Graph::Graph(String ^file, double th)
{
   InitializeInstanceFields();
   this->_file_name = file;
   _TH = th;
   _V = gcnew List <VertexSet^>();
	init();
}

void Graph::init()
{
	FileReader ^fr = nullptr;
	try
	{
		fr = gcnew FileReader(this->_file_name);
	}
	catch (FileNotFoundException ^e)
	{
		e->printStackTrace();
	}
	BufferedReader ^is = gcnew BufferedReader(fr);
	try
	{
		String ^s = is->readLine();
		StringTokenizer ^st = gcnew StringTokenizer(s,", ");
		int len = st->countTokens();
		int line = 0;

		String ^ll = "0%   20%   40%   60%   80%   100%";
		int t = Math::Max(1,len / ll->Length);
		if (Clique_Tester::Debug)
		{
			Console::WriteLine("Reading a corrolation matrix of size: " + len + "*" + len + " this may take a while");
			Console::WriteLine(ll);
		}
		_mat_flag = true;
		if (s->StartsWith("A"))
		{
			if (Clique_Tester::Debug)
			{
				Console::WriteLine("Assumes compact representation! two line haeder!!!");
				Console::WriteLine("Header Line1: " + s);
				s = is->readLine();
				Console::WriteLine("Header Line2: " + s);
				s = is->readLine();
				st = gcnew StringTokenizer(s,", ");
				_mat_flag = false;
			}
		}

		while (s != nullptr)
		{

			if (Clique_Tester::Debug)
			{
				if (line % t == 0)
				{
					Console::Write(".");
				}
			}
			VertexSet ^vs = gcnew VertexSet();
			if (_mat_flag)
			{
				for (int i = 0;i < len;i++)
				{
					float v = (double(st->nextToken()));
					if (v > _TH & line < i)
					{
						vs->add(i);
						_E_size++;
					}
				}
			}
			else
			{
				st->nextToken();
				while (st->hasMoreTokens())
				{
					int ind = (int(st->nextToken()));
					// bug fixed as for Ronens format.
					if (line < ind)
					{
						vs->add(ind);
					}
				}
			}
			this->_V->Add(vs);
			line++;
			s = is->readLine();
		if (s != nullptr)
		{
			st = gcnew StringTokenizer(s,", ");
		}
		}
		if (this->_mat_flag & Clique_Tester::Convert)
		{
			write2file();
		}
		if (Clique_Tester::Debug)
		{
			Console::WriteLine("");
			Console::Write("done reading the graph! ");
			this->print();
		}
	}
	catch (IOException ^e)
	{
		e->printStackTrace();
	}
}

VertexSet ^Graph::Ni(int i)
{
	VertexSet ^ans = _V[i];
	return ans;
}

void Graph::print()
{
	Console::WriteLine("Graph: |V|=" + this->_V->Count + " ,  |E|=" + _E_size);

}

List<VertexSet^> ^Graph::allEdges()
{
	List<VertexSet^> ^ans = gcnew List<VertexSet^>();
	for (int i = 0;i < _V->Count;i++)
	{
		VertexSet ^curr = _V[i];
		for (int a = 0;a < curr->size();a++)
		{
			if (i < curr->at(a))
			{
				VertexSet ^tmp = gcnew VertexSet();
				tmp->add(i);
				tmp->add(curr->at(a));
				ans->Add(tmp);
			}
		}

	}
	return ans;
}

List<VertexSet^> ^Graph::All_Cliques_DFS(int min_size, int max_size)
{
	Clique::init(this);
	List<VertexSet^> ^ans = gcnew List<VertexSet^>();
	<VertexSet^> ^C0 = allEdges(); // all edges � all cliques of size 2/
//	ans.addAll(C0);
	int len = C0->size();
	//System.out.println("|E|= "+len);
	int count = 0;
	for (int i = 0;i < len;i++)
	{

		VertexSet ^curr_edge = C0::elementAt(i);
		Clique ^edge = gcnew Clique(curr_edge->at(0),curr_edge->at(1));
		List<Clique^> ^C1 = allC_seed(edge, min_size, max_size);
		count += C1->Count;
		//System.out.println("alg2 "+i+") edge:["+curr_edge.at(0)+","+curr_edge.at(1)+"]"+C1.size() +"  total: "+count);
		addToSet(ans, C1);
	} // for
	return ans;
}

void Graph::All_Cliques_DFS(String ^out_file, int min_size, int max_size)
{
	   Clique::init(this);
	   <VertexSet^> ^C0 = allEdges(); // all edges � all cliques of size 2/
	   int len = C0->size();
	   Console::WriteLine("|E|= " + len);
	   int count = 0;

	   FileWriter ^fw = nullptr;
	   try
	   {
		   fw = gcnew FileWriter(out_file);
	   }
	   catch (IOException ^e)
	   {
		   e->printStackTrace();
	   }
	   PrintWriter ^os = gcnew PrintWriter(fw);
	   //os.println("A");

	   String ^ll = "0%   20%   40%   60%   80%   100%";
	   int t = Math::Max(1,len / ll->Length);
	   if (Clique_Tester::Debug)
	   {
		   Console::WriteLine("Computing all cliques of size[" + min_size + "," + max_size + "] based on " + len + " edges graph, this may take a while");
		   Console::WriteLine(ll);
	   }
	   os->println("All Cliques: file [min max] TH," + this->_file_name + "," + min_size + ", " + max_size + ", " + this->_TH);
	   os->println("index, edge, clique size, c0, c1, c2, c3, c4,  c5, c6, c7, c8, c9");
	   for (int i = 0;i < len;i++)
	   {

		   VertexSet ^curr_edge = C0::elementAt(i);
		   Clique ^edge = gcnew Clique(curr_edge->at(0),curr_edge->at(1));
		   List<Clique^> ^C1 = allC_seed(edge, min_size, max_size);


		   for (int b = 0;b < C1->Count;b++)
		   {
			   Clique ^c = C1[b];
			   if (c->size() >= min_size)
			   {
				   os->println(count + ", " + i + "," + c->size() + ", " + c->toFile());
				   count++;
			   }
		   }
		   if (count > Clique_Tester::MAX_CLIQUE)
		   {
			   os->println("ERROR: too many cliques! - cutting off at " + Clique_Tester::MAX_CLIQUE + " for larger files change the default Clique_Tester.MAX_CLIQUE param");
			   i = len;
		   }
		   if (i % t == 0)
		   {
			   Console::Write(".");
		   }
	   } // for
	   Console::WriteLine();

	   os->close();
	   try
	   {
		   fw->close();
	   }
	   catch (IOException ^e)
	   {
		   // TODO Auto-generated catch block
		   e->printStackTrace();
	   }

}

void Graph::addToSet(List<VertexSet^> ^ans, List<Clique^> ^C1)
{
	for (int i = 0;i < C1->Count;i++)
	{
		ans->Add(C1[i]->clique());
	}
}

List<Clique^> ^Graph::allC_seed(Clique ^edge, int min_size, int max_size)
{
	List<Clique^> ^ans = gcnew List<Clique^>();
	ans->Add(edge);
	int i = 0;
//	int size = 2;
	while (ans->Count > i)
	{
		Clique ^curr = ans[i];
		if (curr->size() < max_size)
		{
			VertexSet ^Ni = curr->commonNi();
			for (int a = 0;a < Ni->size();a++)
			{
				Clique ^c = gcnew Clique(curr,Ni->at(a));
				ans->Add(c);
			}
		}
		else // speedup trick
		{
			i = ans->Count;
		}
		i++;
	}

	return ans;
}

void Graph::write2file()
{
	FileWriter ^fw = nullptr;
	try
	{
		fw = gcnew FileWriter(this->_file_name + "_DG.txt");
	}
	catch (IOException ^e)
	{
		e->printStackTrace();
	}
	PrintWriter ^os = gcnew PrintWriter(fw);
	os->println("ALL_Cliques: of file: " + _file_name + ",  TH:" + this->_TH);
	os->println("");
	for (int i = 0;i < this->_V->Count;i++)
	{
		VertexSet ^curr = _V[i];
		os->println(i + ", " + curr->toFile());
	}
	os->close();
	try
	{
		fw->close();
	}
	catch (IOException ^e)
	{
		e->printStackTrace();
	}
}

void Graph::InitializeInstanceFields()
{
	_mat_flag = true;
}
