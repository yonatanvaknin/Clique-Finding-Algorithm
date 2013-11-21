#pragma once

#include "VertexSet.h"
#include "Clique.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

/// <summary>
/// this class represents an undirected 0/1 sparse Graph 
/// @author Boaz
/// 
/// </summary>
 private ref class Graph
 {
 private:
	 String ^_file_name;
	 List<VertexSet^> ^_V;
	 double _TH; // the threshold value
	 int _E_size;
	 bool _mat_flag;
 internal:
	 Graph(String ^file, double th);

private:
	void init();

public:
	virtual VertexSet ^Ni(int i);
	virtual void print();

	/// <summary>
	///************* Clique Algorithms ***************** </summary>
	/*Vector<VertexSet>  All_Cliques(int Q_size) {
		Vector<VertexSet> ans = new Vector<VertexSet>();
		Vector<VertexSet>C0 = allEdges(); // all edges � all cliques of size 2/
		ans.addAll(C0);
		for(int i=3;i<=Q_size;i++) {
			Vector<VertexSet>C1 = allC(C0);
			ans.addAll(C1);
			C0 = C1;
		} // for
		return ans;
	}
	Vector<VertexSet>  All_Cliques(int min_Q_size, int max_Q_size) {
		Vector<VertexSet> ans = new Vector<VertexSet>();
		Vector<VertexSet> C0 = allEdges(), C1=null; // all edges � all cliques of size 2/
		for(int i=0;i<C0.size();i++) {
			VertexSet curr = C0.elementAt(i);
			C1 = All_Cliques_of_edge(curr, min_Q_size,  max_Q_size);
//			System.out.println("Edge: ["+curr.at(0)+","+curr.at(1)+"]");
			ans.addAll(C1);
		}
		return ans;
	}*/
	/// <summary>
	/// this method retuns all the Cliques of size between [min,max] which contains the subVertexSet e (usually an edge); </summary>
	/// <param name="min_Q_size"> </param>
	/// <param name="max_Q_size">
	/// @return </param>
	/*
	Vector<VertexSet>  All_Cliques_of_edge(VertexSet e, int min_Q_size, int max_Q_size) {
		Vector<VertexSet> ans = new Vector<VertexSet>();
		ans.add(e);
		int i=0;
		int last_size = e.size();
		while(i<ans.size() & last_size <=max_Q_size) {
			VertexSet curr = ans.elementAt(i);
			VertexSet inter = intersection(curr);
			addbiggerCliQ(ans,curr,inter);
			last_size = ans.elementAt(ans.size()-1).size(); 
			i++;
		}
		int start = 0; i=0;
		while(i<ans.size() && start==0) {
			if(ans.elementAt(i).size()<min_Q_size) {ans.remove(0);}
			else start=1;
			i++;
		}
		return ans;
	}
	Vector<VertexSet> allC(Vector<VertexSet> C0) {
		Vector<VertexSet> ans = new Vector<VertexSet>();
		for(int i=0;i<C0.size();i++) {
			VertexSet curr = C0.elementAt(i);
			VertexSet inter = intersection(curr);
			if(inter.size()>0)  
				addbiggerCliQ(ans,curr,inter); // strange clique expqnding function
	}	
		return ans;	
	}
	VertexSet intersection(VertexSet C) {
		VertexSet ans = _V.elementAt(C.at(0));
		for(int i=0;ans.size()>0 & i<C.size();i++) 
			ans = ans.intersection(_V.elementAt(C.at(i)));
		return ans;
	}
	private void addbiggerCliQ(Vector<VertexSet> ans,VertexSet curr ,VertexSet inter) {
		int last = curr.at(curr.size()-1);
		for(int i=0;i<inter.size();i++) {
			int ind_inter = inter.at(i);
			if(last<ind_inter) {
				VertexSet c = new VertexSet(curr);
				c.add(ind_inter);
				ans.add(c);
			}
		}
	}
	private Vector<VertexSet> addbiggerCliQ(VertexSet curr ,VertexSet inter) {
		Vector<VertexSet> ans = new Vector<VertexSet>(inter.size());
		int last = curr.at(curr.size()-1); // last vertex in the current clique (ordered!)
		for(int i=0;i<inter.size();i++) {
			int ind_inter = inter.at(i);
			if(last<ind_inter) {
				VertexSet c = new VertexSet(curr);
				c.add(ind_inter);
				ans.add(c);
			}
		}
		return ans;
	}*/
	/// <summary>
	/// computes all the 2 cliques --> i.e. all the edges 
	/// @return
	/// </summary>
private:
	List<VertexSet^> ^allEdges(); // all edges � all cliques of size 2/
	/// <summary>
	/// This method computes all cliques of size [min,max] or less using a memory efficient DFS like algorithm.
	/// The implementation was written with CUDA in mind - as a based code for a possibly implementation of parallel cernal.
	/// 
	/// </summary>
internal:
	virtual List<VertexSet^> ^All_Cliques_DFS(int min_size, int max_size);
	/// 
	/// <param name="min_size"> </param>
	/// <param name="max_size"> </param>
 public:
	 virtual void All_Cliques_DFS(String ^out_file, int min_size, int max_size);

	/// <summary>
	/// this function simply add the clique (with no added intersection data) to the set of cliques) </summary>
	/// <param name="ans"> </param>
	/// <param name="C1"> </param>
private:
	void addToSet(List<VertexSet^> ^ans, List<Clique^> ^C1);
internal:
	virtual List<Clique^> ^allC_seed(Clique ^edge, int min_size, int max_size);

public:
	virtual void write2file();

private:
	void InitializeInstanceFields();
 };
