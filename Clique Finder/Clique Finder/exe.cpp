#include "Clique_Tester.h"
#include <time.h>

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
	clock_t t1, t2, t3;
	t1= clock();
	Graph G(Clique_Tester::in_file, Clique_Tester::TH); 
	t2 = clock();
	cout << "Init Graph: " << (t2 - t1) << "  ms";
	//Vector<VertexSet1> c1 = G.All_Cliques(maxQ);

	//	Vector<VertexSet1> c2 = G.All_Cliques_DFS(2,maxQ);
	//	System.out.println("Alg2: "+(t2-t1)+"  ms");

	//TO DO : write fun int to string!!
	if (Clique_Tester::out_file == "")
		Clique_Tester::out_file = Clique_Tester::in_file + "_" + to_string(Clique_Tester::TH) + "_" + to_string(Clique_Tester::minQ) + "_" + to_string(Clique_Tester::maxQ) + ".csv";
	G.All_Cliques_DFS(Clique_Tester::out_file, Clique_Tester::minQ, Clique_Tester::maxQ);
	t3 = clock();
	cout << "Alg3: " << (t3 - t2) << "  ms";
	getchar();
	getchar();
	return 1;
}
