#include "stdafx.h"
#include "Graph.h"
// DFS algoritms, and member function allC_seed are not implemented

Graph::Graph(string file, double th){
	this->_file_name = file;
	_TH = th;
	init();
}

void Graph::init(){
	ifstream fr;
	fr.open(this->_file_name);
	string line;
	getline(fr,line);
	// filling the graph
	while (!line.empty()){
		// implementing tokenizer, witch is : ", "
		// optional: getline(fr,line,",") - as "," a delimiter
		int start = 0, end = 0,current = 0,len = 0;
		long double val;
		VertexSet vs;
		char tmp;
		string strVal;
		int size = line.length();
		while (end < size){
			start = current;
			while ((tmp = line.at(current)) != ','){
				current ++;
			} // current points now at ','
			len++;
			end = current;
			current = end + 1;
			strVal = line.substr(start,(end-start));
			val = stold(strVal);
			if (val > _TH){
				vs.add(len); // adding the current length counter
				this->_E_size++;
			}

		}
		getline(fr,line);
		_V.push_back(vs);
	}
}

void Graph::print(){
	cout<<"Graph: |V|="<<_V.size()<<" ,  |E|="<<_E_size;
}



vector<VertexSet> Graph::all_cliques(int q_size){
	vector<VertexSet> ans;
	vector<VertexSet> c0 = this->allEdges();
	ans.insert(ans.end(),c0.begin(),c0.end());
	for (int i = 3; i <= q_size; i++){
		vector<VertexSet> c1 = this->allC(c0);
		ans.insert(ans.end(),c1.begin(),c1.end());
		c0 = c1;
	}
	return ans;
}

vector<VertexSet> Graph::all_cliques(int min_q_size, int max_q_size){
	vector<VertexSet> ans;
	vector<VertexSet> c0 = this->allEdges();
	vector<VertexSet> c1;
	for(size_t i = 0; i < c0.size(); i++){
		VertexSet curr = c0.at(i);
		c1 = this->all_cliques_of_edge(curr, min_q_size, max_q_size);
		ans.insert(ans.end(),c1.begin(),c1.end());
	}
	return ans;
}

vector<VertexSet> Graph::all_cliques_of_edge(VertexSet e, int min_q_size, int max_q_size){
	vector<VertexSet> ans;
	ans.push_back(e);
	size_t i = 0;
	int last_size = e.size();
	while(i < ans.size() && last_size <= max_q_size){
		VertexSet curr = ans.at(i);
		VertexSet inter = this->intersection(curr);
		this->addbiggerCliQ(ans, curr, inter);
		last_size = ans.at(ans.size()-1).size();
		i++;
	}
	size_t start = 0;
	i = 0;
	while (i < ans.size() && start == 0) {
		if (ans.at(i).size() < min_q_size){
			ans.erase(ans.begin());
		}
		else{
			start = 1;
		}
		i++;
	}
	return ans;
}

vector<VertexSet> Graph::allC(vector<VertexSet> c0){
	vector<VertexSet> ans;
	for (size_t i=0; i < c0.size(); i++){
		VertexSet curr = c0.at(i);
		VertexSet inter = this->intersection(curr);
		if (inter.size() > 0){
			addbiggerCliQ(ans, curr, inter);
		}
	}
	return ans;
}

VertexSet Graph::intersection(VertexSet c){
	VertexSet ans = _V.at(c.at(0));
	for (int i = 0; (ans.size() > 0) & (i < c.size()); i++) {
		ans = ans.intersection(_V.at(c.at(i)));
	}
	return ans;
}



VertexSet Graph::Ni(int i){
	VertexSet t;
	return t;
}

vector<VertexSet> Graph::allEdges(){
	vector<VertexSet> ans;
	for (int i=0; i < this->_V.size(); i++){
		VertexSet curr = _V.at(i);
		for (int a=0; i < curr.at(i); a++){ // "triangle" iteration
			VertexSet tmp;
			tmp.add(i);
			tmp.add(curr.at(i));
			ans.push_back(tmp);
		}
	}
	return ans;
}

void Graph::addbiggerCliQ(vector<VertexSet> &ans, VertexSet curr, VertexSet inter){
	int last = curr.at(curr.size() - 1);
	for (int i = 0; i < inter.size(); i++){
		int ind_inter = inter.at(i);
		if (last < ind_inter) {
			VertexSet c = VertexSet(curr);
			c.add(ind_inter);
			ans.push_back(c);
		}
	}
}

vector<VertexSet> Graph::addbiggerCliQ(VertexSet curr, VertexSet inter){
	vector<VertexSet> ans;
	int last = curr.at(curr.size()-1);
	for(int i = 0;i < inter.size(); i++){
		int ind_inter = inter.at(i);
		if (last < ind_inter){
			VertexSet c = VertexSet(curr);
			c.add(ind_inter);
			ans.push_back(c);
		}
	}
	return ans;
}

void Graph::addToSet(vector<VertexSet> ans, vector<Clique> c1){
	for(size_t i = 0; i < c1.size(); i++){
		ans.push_back(c1.at(i).clique());
	}
}

void Graph::write2file(){
	ofstream fw;
	fw.open(this->_file_name+"_DG.txt");
	stringstream ss;
	ss << "ALL_Cliques: of file: "<< _file_name <<",  TH:" << _TH<<"\n";
	string s = ss.str();
	fw.write(s.c_str(),s.size());
	for(size_t i = 0; i < this->_V.size(); i++){
		VertexSet curr = _V.at(i);
		ss.flush();
		ss<<i<<", "<<curr.toFile();
		s = ss.str();
		fw.write(s.c_str(),s.size());
	}
	fw.close();
}