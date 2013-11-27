#include "VertexSet.h"
#include "Split.h"
#include <fstream>
#include <algorithm>

class Graph
{
private:
	string _file_name;
	vector<VertexSet> _V;
	double _TH; // the threshold value
	int _E_size ;
	bool _mat_flag;
	void init();
	vector<VertexSet> allEdges();
	void addToSet(vector<VertexSet> ans, vector<Clique> C1);
public:
	Graph(string file, double th);
	~Graph();
	VertexSet Ni(int i);
	void print();
	vector<VertexSet> All_Cliques_DFS(int min_size, int max_size);
	void All_Cliques_DFS(string out_file, int min_size, int max_size);
	vector<Clique> allC_seed(Clique& edge, int min_size, int max_size);
	void write2file();
};

Graph::Graph(string file, double th)
{
	this->_file_name = file;
	this->_TH = th;
	this->_E_size = 0;
	this->_mat_flag = true;
	init();
}

Graph::~Graph()
{
}

void Graph::init()
{
	ifstream ifs;
	ifs.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		ifs.open(_file_name);
	}
	catch (ifstream::failure e)
	{
		cerr << "Exception opening file: " << _file_name << endl;
	}
	try
	{
		string s;
		getline(ifs, s);
		vector<string> st; // string tokenizer
		splitString(st, s, ",", split::no_empties);
		int len = st.size();
		int line = 0;

		string ll = "0%   20%   40%   60%   80%   100%";
		int ll_len = ll.length();
		int t = max(1, len / ll_len);
		//if (Clique_Tester.Debug)
		if (true)
		{
			cout << "Reading a corrolation matrix of size: " << len << "*" << len << " this may take a while" << endl;
			cout << ll << endl;
		}
		_mat_flag = true;
		if (s.at(0) == 'A')
		{
			//if (Clique_Tester.Debug)
			if (true)
			{
				cout << "Assumes compact representation! two line header!!!" << endl;
				cout << "Header Line1: " << s << endl;
				getline(ifs, s);
				cout << "Header Line2: " << s << endl;
				getline(ifs, s);
				splitString(st, s, ",", split::no_empties);;
				_mat_flag = false;
			}
		}

		while (!s.empty())
		{

			//if (Clique_Tester.Debug)
			if (true)
			{
				if (line % t == 0)
				{
					cout << ".";
				}
			}
			VertexSet vs;
			if (_mat_flag)
			{
				for (int i = 0; i < len; i++)
				{
					float v = stof(st.at(i));
					if ((v > _TH) & (line < i))
					{
						vs.add(i);
						_E_size++;
					}
				}
			}
			else
			{
				int i = 0;
				while (!st.empty())
				{
					int ind = stoi(st.at(i++));
					// bug fixed as for Ronens format.
					if (line < ind)
					{
						vs.add(ind);
					}
				}
			}
			_V.push_back(vs);
			line++;
			getline(ifs, s);
			if (!s.empty())
			{
				splitString(st, s, ",", split::no_empties);
			}
		}
		//if (_mat_flag & Clique_Tester.Convert)
		if (_mat_flag & true)
		{
			write2file();
		}
		//if (Clique_Tester.Debug)
		if (true)
		{
			cout << "" << endl;
			cout << "done reading the graph! ";
			print();
		}

		ifs.close();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

VertexSet Graph::Ni(int i)
{
	VertexSet ans = _V.at(i);
	return  ans;
}

void Graph::print()
{
	cout << "Graph: |V|=" << _V.size() << " ,  |E|=" << _E_size << endl;
}

vector<VertexSet> Graph::allEdges()
{
	vector<VertexSet> ans;
	for (int i = 0; i < _V.size(); i++)
	{
		VertexSet curr = _V.at(i);
		for (int a = 0; a < curr.size(); a++)
		{
			if (i < curr.at(a))
			{
				VertexSet tmp;
				tmp.add(i) ; 
				tmp.add(curr.at(a));
				ans.push_back(tmp);
			}
		}
	}
	return ans;
}

vector<VertexSet> Graph::All_Cliques_DFS(int min_size, int max_size)
{
	Clique::init(*this);
	vector<VertexSet> ans;
	vector<VertexSet> C0 = allEdges();
	int len = C0.size();
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		VertexSet curr_edge = C0.at(i);
		Clique edge = Clique(curr_edge.at(0),curr_edge.at(1));
		vector<Clique> C1 = allC_seed(edge, min_size, max_size);
		count += C1.size();
		addToSet(ans, C1);
	}
	return ans;
}

void Graph::All_Cliques_DFS(string out_file, int min_size, int max_size)
{
	Clique::init(*this);
	vector<VertexSet> C0 = allEdges();
	int len = C0.size();
	cout << "|E|= " << len;
	int count = 0;

	ofstream ofs;
	ofs.exceptions(ofstream::failbit | ofstream::badbit);
	try {
		ofs.open(_file_name);
	}
	catch (ofstream::failure e)
	{
		cerr << "Exception opening file: " << _file_name << endl;
	}
	string ll = "0%   20%   40%   60%   80%   100%";
	int ll_len = ll.length();
	int t = max(1, len / ll_len);
	//if (Clique_Tester.Debug)
	if (true)
	{
		cout << "Computing all cliques of size[" << min_size << "," << max_size << "] based on " << len << " edges graph, this may take a while" << endl;
		cout << ll << endl;
	}
	ofs << "All Cliques: file [min max] TH," << _file_name << "," << min_size << ", " + max_size << ", " << _TH << "\n";
	ofs << "index, edge, clique size, c0, c1, c2, c3, c4,  c5, c6, c7, c8, c9" << "\n";
	for (int i = 0; i < len; i++)
	{

		VertexSet curr_edge = C0.at(i);
		Clique edge(curr_edge.at(0), curr_edge.at(1));
		vector<Clique> C1 = allC_seed(edge, min_size, max_size);

		for (int b = 0; b < C1.size(); b++) {
			Clique c = C1.at(b);
			if (c.size() >= min_size)
			{
				ofs << count << ", " << i + "," << c.size() << ", " << c.toFile() << "\n";
				count++;
			}
		}
		/*if (count > Clique_Tester.MAX_CLIQUE)
		{
		ofs << "ERROR: too many cliques! - cutting off at " << Clique_Tester.MAX_CLIQUE << " for larger files change the default Clique_Tester.MAX_CLIQUE param" << "\n";
		i = len;
		}*/
		if (count > 100000)
		{
			ofs << "ERROR: too many cliques! - cutting off at " << 100000 << " for larger files change the default Clique_Tester.MAX_CLIQUE param" << "\n";
			i = len;
		}
		if (i % t == 0)
		{
			cout << ".";
		}
	} // for
	cout << endl;
	try
	{
		ofs.close();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void Graph::addToSet(vector<VertexSet> ans, vector<Clique> C1)
{
	for (int i = 0; i < C1.size(); i++)
	{
		ans.push_back(C1.at(i).clique());
	}
}

vector<Clique> Graph::allC_seed(Clique& edge, int min_size, int max_size)
{
	vector<Clique> ans;
	ans.push_back(edge);
	int i = 0;
	while (ans.size() > i)
	{
		Clique curr = ans.at(i);
		if (curr.size() < max_size)
		{
			VertexSet Ni = curr.commonNi();
			for (int a = 0; a < Ni.size(); a++)
			{
				Clique c = Clique(curr, Ni.at(a));
				ans.push_back(c);
			}
		}
		else
		{
			i = ans.size();
		}
		i++;
	}
	return ans;
}

void Graph::write2file()
{
	ofstream ofs;
	ofs.exceptions(ofstream::failbit | ofstream::badbit);
	try
	{
		ofs.open(_file_name);
	}
	catch (ofstream::failure e)
	{
		cerr << "Exception opening file: " << _file_name << endl;
	}
	ofs << "ALL_Cliques: of file: " << _file_name << ",  TH:" << _TH << "\n";
	ofs << "" << "\n";
	for (int i = 0; i < _V.size(); i++)
	{
		VertexSet curr = _V.at(i);
		ofs << i << ", " << curr.toFile() << "\n";
	}
	try
	{
		ofs.close();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}