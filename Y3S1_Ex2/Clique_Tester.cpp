//#include "Graph.h"
//#include <ctime>
//
//int minQ = 6, maxQ = 10;
//double TH = 0.75;
//string in_file = "test1.csv";
//string out_file;
//bool Debug = true;
//int MAX_CLIQUE = 100000;
//bool Convert = true;
//
//void main()
//{
//	vector<string> args;
//	args.push_back("d:\\test1.csv"); args.push_back("0.8");
//	args.push_back("5"); args.push_back("7");
//	if (args.empty() || args.size() < 3) {
//		help();
//	} else {
//		parse(args);
//	}
//	long t0 = time(0);
//	Graph G(in_file, TH);
//	long t1 = time(0);
//	cout << "Init Graph: " << (t1 - t0) << "  ms" << endl;
//	long t2 = time(0);
//	if (!out_file.empty()) {
//		out_file = in_file + "_" + to_string(TH) + "_" + to_string(minQ) + "_" + to_string(maxQ) + ".csv";
//	}
//	G.All_Cliques_DFS(out_file, minQ, maxQ);
//	long t3 = time(0);
//	cout << "Alg3: " << (t3 - t2) << "  ms" << endl;
//}
//
//void help() {
//	cout << "Wrong Parameters! should use: java -jar All_Cliques <input file> <round value> <min clique> <max clique> <output file> <max_cliques> <Graph convert flag>" << endl;
//	cout << "Wrong Parameters! should use: java -jar All_Cliques test1.csv 0.7 5 7 test1_out.txt 10000 true" << endl;
//}
//
//void parse(vector<string> a)
//{
//	try {
//		in_file = a.at(0);
//		TH = stod(a.at(1));
//		minQ = stoi(a.at(2));
//		maxQ = stoi(a.at(3));
//		if (a.size() > 4) {
//			out_file = a.at(4);
//		}
//		if (a.size() > 5) {
//			MAX_CLIQUE = stoi(a.at(5));
//		}
//		if (a.size() > 6) {
//			if (a.at(6) == "true")
//				Convert = true;
//			else
//				Convert = false;
//		}
//	} catch (const std::exception& e) {
//		cout << e.what() << endl;
//		help();
//	} catch (...) {
//		help();
//	}
//}