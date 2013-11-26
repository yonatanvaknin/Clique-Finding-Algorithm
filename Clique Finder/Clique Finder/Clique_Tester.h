#pragma once
#include "classes.h"

class Clique_Tester
{
public:
	static int minQ, maxQ;
	static double TH;
	static string in_file;
	static string out_file;
	static bool Debug;
	static int MAX_CLIQUE;
	static bool Convert;

	static void Clique_Tester::init(){
		minQ = 6, maxQ = 10;
		TH = 0.75;
		in_file = "test1.csv";
		Debug = true;
		MAX_CLIQUE = 100000;
		Convert = true;
	}


	static void help() {
		cout << "Wrong Parameters! should use: java -jar All_Cliques <input file> <round value> <min clique> <max clique> <output file> <max_cliques> <Graph convert flag>";
		cout << "Wrong Parameters! should use: java -jar All_Cliques test1.csv 0.7 5 7 test1_out.txt 10000 true";
	}
	static void parse(string a[], int c){

		in_file = a[0];
		TH = stod(a[1]);
		minQ = stoi(a[2]);
		maxQ = stoi(a[3]);
		if (c>4) out_file = a[4];
		if (c>5) MAX_CLIQUE = stoi(a[5]);
		if (c>6) if (a[6] == "true") Convert = true;
		else Convert = false;
	}

};



