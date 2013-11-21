#include "Graph.h"
#include <sstream>
#include <fstream>

using namespace std;

Graph::Graph(string file, double th)
{
   InitializeInstanceFields();
   this->_file_name = file;
   _TH = th;
   _V = std::vector <VertexSet>();
	init();
}

void Graph::init()
{
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

VertexSet Graph::Ni(int i)
{
	VertexSet ans;
	return ans;
}

void Graph::print()
{
	 cout<<"Graph: |V|="<<_V.size()<<" ,  |E|="<<_E_size;
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
///////////////////////////////////???????????????????/////
/*
std::vector<VertexSet> Graph::All_Cliques_DFS(int min_size, int max_size)
{
	Clique::init(this);
	std::vector<VertexSet> ans = std::vector<VertexSet>();
	<VertexSet> C0 = allEdges(); // all edges � all cliques of size 2/
//	ans.addAll(C0);
	int len = C0->size();
	//System.out.println("|E|= "+len);
	int count = 0;
	for (int i = 0;i < len;i++)
	{

		VertexSet curr_edge = C0::elementAt(i);
		Clique edge = new Clique(curr_edge->at(0),curr_edge->at(1));
		std::vector<Clique> C1 = allC_seed(edge, min_size, max_size);
		count += C1.size();
		//System.out.println("alg2 "+i+") edge:["+curr_edge.at(0)+","+curr_edge.at(1)+"]"+C1.size() +"  total: "+count);
		addToSet(ans, C1);
	} // for
	return ans;
}
/

/////////////////////?????????????
/
void Graph::All_Cliques_DFS(const string &out_file, int min_size, int max_size)
{
	   Clique::init(this);
	   <VertexSet> C0 = allEdges(); // all edges � all cliques of size 2/
	   int len = C0->size();
	   std::cout << string(L"|E|= ") << len << std::endl;
	   int count = 0;

	   FileWriter fw = nullptr;
	   try
	   {
		   fw = new FileWriter(out_file);
	   }
	   catch (IOException e)
	   {
		   e->printStackTrace();
	   }
	   PrintWriter os = new PrintWriter(fw);
	   //os.println("A");

	   string ll = L"0%   20%   40%   60%   80%   100%";
	   int t = std::max(1,len / ll.length());
	   if (Clique_Tester::Debug)
	   {
		   std::cout << string(L"Computing all cliques of size[") << min_size << string(L",") << max_size << string(L"] based on ") << len << string(L" edges graph, this may take a while") << std::endl;
		   std::cout << ll << std::endl;
	   }
	   os->println(string(L"All Cliques: file [min max] TH,") + this->_file_name + string(L",") + min_size + string(L", ") + max_size + string(L", ") + this->_TH);
	   os->println(L"index, edge, clique size, c0, c1, c2, c3, c4,  c5, c6, c7, c8, c9");
	   for (int i = 0;i < len;i++)
	   {

		   VertexSet curr_edge = C0::elementAt(i);
		   Clique edge = new Clique(curr_edge->at(0),curr_edge->at(1));
		   std::vector<Clique> C1 = allC_seed(edge, min_size, max_size);


		   for (int b = 0;b < C1.size();b++)
		   {
			   Clique c = C1[b];
			   if (c->size() >= min_size)
			   {
				   os->println(count + string(L", ") + i + string(L",") + c->size() + string(L", ") + c->toFile());
				   count++;
			   }
		   }
		   if (count > Clique_Tester::MAX_CLIQUE)
		   {
			   os->println(string(L"ERROR: too many cliques! - cutting off at ") + Clique_Tester::MAX_CLIQUE + string(L" for larger files change the default Clique_Tester.MAX_CLIQUE param"));
			   i = len;
		   }
		   if (i % t == 0)
		   {
			   std::cout << string(L".");
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
/
*/
void Graph::addToSet(vector<VertexSet> ans, vector<Clique> c1){
        for(size_t i = 0; i < c1.size(); i++){
                ans.push_back(c1.at(i).clique());
        }
}

std::vector<Clique> Graph::allC_seed(Clique edge, int min_size, int max_size)
{
	std::vector<Clique> ans = std::vector<Clique>();
	ans.push_back(edge);
	int i = 0;
//	int size = 2;
	while (ans.size() > i)
	{
		Clique curr = ans[i];
		if (curr.size() < max_size)
		{
			VertexSet Ni = curr.commonNi();
			for (int a = 0;a < Ni.size();a++)
			{
				Clique c = new Clique(curr,Ni.at(a));
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
	ofstream fw;
        fw.open(this->_file_name+ "_DG.txt");
        stringstream ss;
        ss << "ALL_Cliques: of file: "<< _file_name <<", TH:" << _TH<<"\n";
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

void Graph::InitializeInstanceFields()
{
	_TH = 0;
	_E_size = 0;
	_mat_flag = true;
}
