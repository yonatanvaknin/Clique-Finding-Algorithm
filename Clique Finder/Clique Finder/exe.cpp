#include "Clique_Tester.h"

double Clique_Tester::TH;
int  Clique_Tester::minQ, Clique_Tester::maxQ;
string  Clique_Tester::in_file;
string  Clique_Tester::out_file;

int  Clique_Tester::MAX_CLIQUE;



int main(int argc, string argv[]) {  // test1.csv_DG.txt  0.8 5 7
	
	if (!argv || argc<3) {
		Clique_Tester::help();
		Clique_Tester::init();
	}
	else {
		Clique_Tester::parse(argv, argc);
	}
	time_t time = time_t();
	long t0 = time;
	Graph G(Clique_Tester::in_file, Clique_Tester::TH);
	time = time_t();
	long t1 = time;
	cout << "Init Graph: " << (t1 - t0) << "  ms";
	//Vector<VertexSet1> c1 = G.All_Cliques(maxQ);

	//	Vector<VertexSet1> c2 = G.All_Cliques_DFS(2,maxQ);
	time = time_t();
	long t2 = time;
	//	System.out.println("Alg2: "+(t2-t1)+"  ms");

	//TO DO : write fun int to string!!
	if (Clique_Tester::out_file == ""){
		Clique_Tester::out_file = Clique_Tester::in_file + "_";
		Clique_Tester::out_file += Clique_Tester::TH;
		Clique_Tester::out_file += "_" + Clique_Tester::minQ;
		Clique_Tester::out_file += "_" + Clique_Tester::maxQ;
		Clique_Tester::out_file += ".csv";
	}

	G.All_Cliques_DFS(Clique_Tester::out_file, Clique_Tester::minQ, Clique_Tester::maxQ);
	time = time_t();
	long t3 = time;
	cout << "Alg3: " << (t3 - t2) << "  ms";

	return 1;
}
