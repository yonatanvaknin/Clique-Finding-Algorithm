#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

/// <summary>
/// Benchmark Results:
/// 
/// Original java version (on standard i3 linux 64  - boaz's laptop:
/// test1_200.csv,0.75,5,8: Graph: 	|V|=200 ,  	|E|=221, 	Init Graph: 117  ms, Alg3: 62  ms, last 1198
/// test1.csv,0.9,5,8: Graph: 		|V|=1728 ,  |E|=483, 	Init Graph: 863  ms, Alg3: 28  ms, last 437
/// test1.csv,0.85,6,10:Graph: 		|V|=1728 ,  |E|=1252, 	Init Graph: 877  ms, Alg3: 235  ms, last 42592 
/// test1.csv,0.8,15,20:Graph: 		|V|=1728 ,  |E|=2407,	Init Graph: 864  ms, Alg3: 516  ms, last 2444
/// </summary>

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
	// public static String[] default_args = {"data/test1_200.csv", "0.75","5","8"};
	//public static String[] default_args = {"data/test1.csv", "0.9","5","8"};
	//public static String[] default_args = {"data/test1.csv", "0.85","6","10"};
	static string default_args[4];

	static void main(string args[]); // test1.csv_DG.txt  0.8 5 7
	static void help();
	static void parse(string a[]);
};
