#include "classes.h"
#include "Clique_Tester.h"
#include <fstream>
#include <iostream>
using namespace std;

bool Clique_Tester::Debug;
bool Clique_Tester::Convert;
Graph::Graph(){

}
Graph::Graph(string file, double th){
	_file_name = file;
	_TH = th;
	_V = vector<VertexSet1>();
	init();
}
Graph::Graph(const Graph &g){
	_file_name = g._file_name;
	_TH = g._TH;
	_V = vector<VertexSet1>(g._V);
	init();
}

void Graph::operator=(Graph &g){
	_file_name = g._file_name;
	_TH = g._TH;
	_V = vector<VertexSet1>(g._V);
	init();
}
void Graph::init() {
	
	
	ifstream fr(_file_name);
	string s = "";
	getline(fr, s);
	Tokenize st(s, " ,");
	int len = st.countTokens();
	int line = 0;
	string ll = "0%   20%   40%   60%   80%   100%";
	int t = fmax(1, len / ll.length());
	if (Clique_Tester::Debug)
		cout << "Reading a corrolation matrix of size: " << len << "*" << len << " this may take a while" << "\n" << ll;
	_mat_flag = true;
	if (st.elementAt(0).at(0) == 'A') {
		if (Clique_Tester::Debug){
			cout << "Assumes compact representation! two line haeder!!!";
			cout << "Header Line1: " << s;
			getline(fr, s);
			cout << "Header Line2: " << s;
			getline(fr, s);
			st = Tokenize(s, " ,");
			_mat_flag = false;
		}
	}

	while (s != "") {

		if (Clique_Tester::Debug){
			if (line%t == 0) cout << ".";
		}
		VertexSet1 vs = VertexSet1();
		if (_mat_flag){
			for (int i = 0; i<len; i++) {
				float v = atof(st.nextToken().c_str());
				
				if (v>_TH & line< i) {
					vs.add(i);
					_E_size++;
				}
			}
		}
		else {
			st.nextToken();
			while (st.hasMoreToken()) {
				int ind = atoi(st.nextToken().c_str());
				// bug fixed as for Ronens format.
				if (line<ind) vs.add(ind);
			}
		}
		this->_V.push_back(vs);
		line++;
		getline(fr, s);
		if (s != "")	st = Tokenize(s, ", ");
	}
	// 
	if (this->_mat_flag && Clique_Tester::Convert) { write2file(); }
	if (Clique_Tester::Debug){
		cout << "\ndone reading the graph! ";
		this->print();
	}

	
}

VertexSet1 Graph::Ni(int i) {
	VertexSet1 ans = _V.at(i);
	return  ans;
}
void Graph::print() {
	cout << "Graph: |V|=" << this->_V.size() << " ,  |E|=" << _E_size;

}

vector<VertexSet1> Graph::allEdges() { // all edges – all cliques of size 2/
	vector<VertexSet1> ans = vector<VertexSet1>();
	for (int i = 0; i<_V.size(); i++) {
		VertexSet1 curr = _V.at(i);
		for (int a = 0; a<curr.size(); a++) {
			if (i<curr.at(a)) {
				VertexSet1 tmp = VertexSet1();
				tmp.add(i);
				tmp.add(curr.at(a));
				ans.push_back(tmp);
			}
		}

	}
	return ans;
}
/**
* This method computes all cliques of size [min,max] or less using a memory efficient DFS like algorithm.
* The implementation was written with CUDA in mind - as a based code for a possibly implementation of parallel cernal.
*
*/
vector<VertexSet1>  Graph::All_Cliques_DFS(int min_size, int max_size) {
	Clique::init(*this);
	vector<VertexSet1> ans = vector<VertexSet1>();
	vector<VertexSet1>C0 = allEdges(); // all edges – all cliques of size 2/
	//	ans.addAll(C0);
	int len = C0.size();
	//System.out.println("|E|= "+len);
	int count = 0;
	for (int i = 0; i<len; i++) {

		VertexSet1 curr_edge = C0.at(i);
		Clique edge = Clique(curr_edge.at(0), curr_edge.at(1));
		vector<Clique> C1 = allC_seed(edge, min_size, max_size);
		count += C1.size();
		//System.out.println("alg2 "+i+") edge:["+curr_edge.at(0)+","+curr_edge.at(1)+"]"+C1.size() +"  total: "+count);
		addToSet(ans, C1);
	} // for
	return ans;
}
/**
*
* @param min_size
* @param max_size
*/
void Graph::All_Cliques_DFS(string out_file, int min_size, int max_size) {
	Clique::init(*this);
	vector<VertexSet1>C0 = allEdges(); // all edges – all cliques of size 2/
	int len = C0.size();
	cout << "|E|= " << len;
	int count = 0;
	ofstream fw;
	fw = ofstream(out_file);
	//os.println("A");

	string ll = "0%   20%   40%   60%   80%   100%";
	int t = fmax(1, len / ll.length());
	if (Clique_Tester::Debug){
		cout << "Computing all cliques of size[" << min_size << "," << max_size << "] based on " << len << " edges graph, this may take a while";
		cout << ll;
	}
	fw << "All Cliques: file [min max] TH," << this->_file_name << "," << min_size << ", " << max_size << ", " << this->_TH;
	fw << "index, edge, clique size, c0, c1, c2, c3, c4,  c5, c6, c7, c8, c9";
	for (int i = 0; i<len; i++) {

		VertexSet1 curr_edge = C0.at(i);
		Clique edge = Clique(curr_edge.at(0), curr_edge.at(1));
		vector<Clique> C1 = allC_seed(edge, min_size, max_size);


		for (int b = 0; b<C1.size(); b++) {
			Clique c = C1.at(b);
			if (c.size() >= min_size) {
				fw << count << ", " << i << "," + c.size() << ", " << c.toFile()<<"\n";
				count++;
			}
		}
		if (count > Clique_Tester::MAX_CLIQUE) {
			fw << "ERROR: too many cliques! - cutting off at " << Clique_Tester::MAX_CLIQUE << " for larger files change the default Clique_Tester.MAX_CLIQUE param";
			i = len;
		}
		if (i%t == 0) {
			cout << ".";
		}
		// for
		cout << "\n";
		fw.close();
		// TODO Auto-generated catch block
	}

}

/**
* this function simply add the clique (with no added intersection data) to the set of cliques)
* @param ans
* @param C1
*/
void Graph::addToSet(vector<VertexSet1> ans, vector<Clique> C1) {
	for (int i = 0; i<C1.size(); i++) {
		ans.push_back(C1.at(i).clique());
	}
}
vector<Clique> Graph::allC_seed(Clique edge, int min_size, int max_size) {
	vector<Clique> ans = vector<Clique>();
	ans.push_back(edge);
	int i = 0;
	//	int size = 2;
	while (ans.size()>i) {
		Clique curr = ans.at(i);
		if (curr.size()<max_size) {
			VertexSet1 Ni = curr.commonNi();
			for (int a = 0; a<Ni.size(); a++) {
				Clique c = Clique(curr, Ni.at(a));
				ans.push_back(c);
			}
		}
		else { i = ans.size(); } // speedup trick 
		i++;
	}

	return ans;
}

void Graph::write2file() {
	ofstream fw;
	fw = ofstream(this->_file_name + "_DG.txt");
	fw << "ALL_Cliques: of file: " << _file_name << ",  TH:" << this->_TH << "\n";
	for (int i = 0; i<this->_V.size(); i++) {
		VertexSet1 curr = _V.at(i);
		fw << i << ", " << curr.toFile()<<endl;
	}
	fw.close();
}

