#include "Graph.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
// DFS algoritms, and member function allC_seed are not implemented
using namespace std;

Graph::Graph(char* file, double th){
	this->_file_name = file;
	_TH = th;
	this->_E_size = 0;
	init();
}

void Graph::init(){
	int i=0;
	int token_counter=0;
	int line_counter=0;
	ifstream in;     //delcraing instream
	string oneline;
	in.open("test1.csv");  //open instream
	while(getline(in, oneline))
	{
		line_counter++;
		VertexSet vs;
		size_t begin(0); 
		size_t end;
		do
		{
			token_counter++;
			end = oneline.find_first_of(" ,", begin);
			//outputs file into copy file - not anymore
        string val = oneline.substr(begin, 
                    (end == string::npos ? oneline.size() : end) - begin);
			begin = end+1;
			char * S = new char[val.length() + 1];
			std::strcpy(S,val.c_str());
			float v=atof(S);
			if(v>_TH & line_counter<token_counter) {
				vs.add(i);
				i++;  //legit???
				_E_size++;
			}
			//pointer moves to second token after first scan is over 
		}
		while (end != string::npos);
		_V.push_back(vs);
		token_counter=0;
	}
	in.close();      //closes in file
}


void Graph::print(){
	cout<<"Graph: |V|="<<_V.size()<<" ,  |E|="<<_E_size;
}



vector<VertexSet> Graph::all_cliques(int q_size){
	vector<VertexSet> ans;
	vector<VertexSet> c0 = this->allEdges();
	ans.insert(ans.end(),c0.begin(),c0.end());
	for (int i = 3; i <= q_size; i++){
		cout<<"\npass1\n";
		vector<VertexSet> c1 = this->allC(c0);
		cout<<"\npass2\n";
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
		//crash in intersec
		VertexSet inter = this->intersection(curr);
		if (inter.size() > 0){
			addbiggerCliQ(ans, curr, inter);
		}
	}
	return ans;
}

VertexSet Graph::intersection(VertexSet c){
	VertexSet ans(_V.at(c.at(0)));
	cout<<"ans size"<<ans.size();
	for (int i = 0; (ans.size() > 0) & (i < c.size()); i++) {
		VertexSet tmp(ans.intersection(_V.at(c.at(i))));
		ans = tmp;
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
		for (int a=0; a < curr.size(); a++){ // "triangle" iteration
			if (i < curr.at(a)){
				VertexSet tmp;
				tmp.add(i);
				tmp.add(curr.at(a));
				ans.push_back(tmp);
			}
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
	for(int i = 0; i < this->_V.size(); i++){
		VertexSet curr = _V.at(i);
		ss.str("");
		ss<<i<<", "<<curr.toFile()<<"\n";
		s = ss.str();
		fw.write(s.c_str(),s.size());
	}
	fw.close();
}