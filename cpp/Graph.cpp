#include "Graph.h"
#include "Clique_Tester.h"

Graph::Graph(const std::wstring &file, double th)
{
   InitializeInstanceFields();
   this->_file_name = file;
   _TH = th;
   _V = std::vector <VertexSet*>();
	init();
}

void Graph::init()
{
	FileReader *fr = nullptr;
	try
	{
		fr = new FileReader(this->_file_name);
	}
	catch (FileNotFoundException e)
	{
		e->printStackTrace();
	}
	BufferedReader *is = new BufferedReader(fr);
	try
	{
		std::wstring s = is->readLine();
		StringTokenizer *st = new StringTokenizer(s,L", ");
		int len = st->countTokens();
		int line = 0;

		std::wstring ll = L"0%   20%   40%   60%   80%   100%";
		int t = std::max(1,len / ll.length());
		if (Clique_Tester::Debug)
		{
			std::cout << std::wstring(L"Reading a corrolation matrix of size: ") << len << std::wstring(L"*") << len << std::wstring(L" this may take a while") << std::endl;
			std::cout << ll << std::endl;
		}
		_mat_flag = true;
//JAVA TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the Java String 'startsWith' method:
		if (s.startsWith(L"A"))
		{
			if (Clique_Tester::Debug)
			{
				std::cout << std::wstring(L"Assumes compact representation! two line haeder!!!") << std::endl;
				std::cout << std::wstring(L"Header Line1: ") << s << std::endl;
				s = is->readLine();
				std::cout << std::wstring(L"Header Line2: ") << s << std::endl;
				s = is->readLine();
				st = new StringTokenizer(s,L", ");
				_mat_flag = false;
			}
		}

		while (s != L"")
		{

			if (Clique_Tester::Debug)
			{
				if (line % t == 0)
				{
					std::cout << std::wstring(L".");
				}
			}
			VertexSet *vs = new VertexSet();
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
			this->_V.push_back(vs);
			line++;
			s = is->readLine();
		if (s != L"")
		{
			st = new StringTokenizer(s,L", ");
		}
		}
		if (this->_mat_flag & Clique_Tester::Convert)
		{
			write2file();
		}
		if (Clique_Tester::Debug)
		{
			std::cout << std::wstring(L"") << std::endl;
			std::cout << std::wstring(L"done reading the graph! ");
			this->print();
		}
	}
	catch (IOException e)
	{
		e->printStackTrace();
	}
}

VertexSet *Graph::Ni(int i)
{
	VertexSet *ans = _V[i];
	return ans;
}

void Graph::print()
{
	std::cout << std::wstring(L"Graph: |V|=") << this->_V.size() << std::wstring(L" ,  |E|=") << _E_size << std::endl;

}

std::vector<VertexSet*> Graph::allEdges()
{
	std::vector<VertexSet*> ans = std::vector<VertexSet*>();
	for (int i = 0;i < _V.size();i++)
	{
		VertexSet *curr = _V[i];
		for (int a = 0;a < curr->size();a++)
		{
			if (i < curr->at(a))
			{
				VertexSet *tmp = new VertexSet();
				tmp->add(i);
				tmp->add(curr->at(a));
				ans.push_back(tmp);
			}
		}

	}
	return ans;
}

std::vector<VertexSet*> Graph::All_Cliques_DFS(int min_size, int max_size)
{
	Clique::init(this);
	std::vector<VertexSet*> ans = std::vector<VertexSet*>();
	<VertexSet*> *C0 = allEdges(); // all edges � all cliques of size 2/
//	ans.addAll(C0);
	int len = C0->size();
	//System.out.println("|E|= "+len);
	int count = 0;
	for (int i = 0;i < len;i++)
	{

		VertexSet *curr_edge = C0::elementAt(i);
		Clique *edge = new Clique(curr_edge->at(0),curr_edge->at(1));
		std::vector<Clique*> C1 = allC_seed(edge, min_size, max_size);
		count += C1.size();
		//System.out.println("alg2 "+i+") edge:["+curr_edge.at(0)+","+curr_edge.at(1)+"]"+C1.size() +"  total: "+count);
		addToSet(ans, C1);
	} // for
	return ans;
}

void Graph::All_Cliques_DFS(const std::wstring &out_file, int min_size, int max_size)
{
	   Clique::init(this);
	   <VertexSet*> *C0 = allEdges(); // all edges � all cliques of size 2/
	   int len = C0->size();
	   std::cout << std::wstring(L"|E|= ") << len << std::endl;
	   int count = 0;

	   FileWriter *fw = nullptr;
	   try
	   {
		   fw = new FileWriter(out_file);
	   }
	   catch (IOException e)
	   {
		   e->printStackTrace();
	   }
	   PrintWriter *os = new PrintWriter(fw);
	   //os.println("A");

	   std::wstring ll = L"0%   20%   40%   60%   80%   100%";
	   int t = std::max(1,len / ll.length());
	   if (Clique_Tester::Debug)
	   {
		   std::cout << std::wstring(L"Computing all cliques of size[") << min_size << std::wstring(L",") << max_size << std::wstring(L"] based on ") << len << std::wstring(L" edges graph, this may take a while") << std::endl;
		   std::cout << ll << std::endl;
	   }
	   os->println(std::wstring(L"All Cliques: file [min max] TH,") + this->_file_name + std::wstring(L",") + min_size + std::wstring(L", ") + max_size + std::wstring(L", ") + this->_TH);
	   os->println(L"index, edge, clique size, c0, c1, c2, c3, c4,  c5, c6, c7, c8, c9");
	   for (int i = 0;i < len;i++)
	   {

		   VertexSet *curr_edge = C0::elementAt(i);
		   Clique *edge = new Clique(curr_edge->at(0),curr_edge->at(1));
		   std::vector<Clique*> C1 = allC_seed(edge, min_size, max_size);


		   for (int b = 0;b < C1.size();b++)
		   {
			   Clique *c = C1[b];
			   if (c->size() >= min_size)
			   {
				   os->println(count + std::wstring(L", ") + i + std::wstring(L",") + c->size() + std::wstring(L", ") + c->toFile());
				   count++;
			   }
		   }
		   if (count > Clique_Tester::MAX_CLIQUE)
		   {
			   os->println(std::wstring(L"ERROR: too many cliques! - cutting off at ") + Clique_Tester::MAX_CLIQUE + std::wstring(L" for larger files change the default Clique_Tester.MAX_CLIQUE param"));
			   i = len;
		   }
		   if (i % t == 0)
		   {
			   std::cout << std::wstring(L".");
		   }
	   } // for
	   std::cout << std::endl;

	   os->close();
	   try
	   {
		   fw->close();
	   }
	   catch (IOException e)
	   {
		   // TODO Auto-generated catch block
		   e->printStackTrace();
	   }

}

void Graph::addToSet(std::vector<VertexSet*> &ans, std::vector<Clique*> &C1)
{
	for (int i = 0;i < C1.size();i++)
	{
		ans.push_back(C1[i]->clique());
	}
}

std::vector<Clique*> Graph::allC_seed(Clique *edge, int min_size, int max_size)
{
	std::vector<Clique*> ans = std::vector<Clique*>();
	ans.push_back(edge);
	int i = 0;
//	int size = 2;
	while (ans.size() > i)
	{
		Clique *curr = ans[i];
		if (curr->size() < max_size)
		{
			VertexSet *Ni = curr->commonNi();
			for (int a = 0;a < Ni->size();a++)
			{
				Clique *c = new Clique(curr,Ni->at(a));
				ans.push_back(c);
			}
		}
		else // speedup trick
		{
			i = ans.size();
		}
		i++;
	}

	return ans;
}

void Graph::write2file()
{
	FileWriter *fw = nullptr;
	try
	{
		fw = new FileWriter(this->_file_name + std::wstring(L"_DG.txt"));
	}
	catch (IOException e)
	{
		e->printStackTrace();
	}
	PrintWriter *os = new PrintWriter(fw);
	os->println(std::wstring(L"ALL_Cliques: of file: ") + _file_name + std::wstring(L",  TH:") + this->_TH);
	os->println(L"");
	for (int i = 0;i < this->_V.size();i++)
	{
		VertexSet *curr = _V[i];
		os->println(i + std::wstring(L", ") + curr->toFile());
	}
	os->close();
	try
	{
		fw->close();
	}
	catch (IOException e)
	{
		e->printStackTrace();
	}
}

void Graph::InitializeInstanceFields()
{
	_TH = 0;
	_E_size = 0;
	_mat_flag = true;
}
