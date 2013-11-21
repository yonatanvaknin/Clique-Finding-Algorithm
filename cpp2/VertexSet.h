#pragma once

using namespace System;

/// <summary>
/// this class represents a simple ORDERD set of vertices. used by Cliques
/// The code was written in C like flavor - no java.util, no abstraction  
/// @author Boaz
/// 
/// </summary>
public ref class VertexSet
{
private:
	array<int> ^_set;
	int _sp;
public:
	literal int INIT_SIZE = 20, INC = 50;

	VertexSet();

	VertexSet(VertexSet ^ot);

	virtual void add(int a);
	virtual int size();
	virtual int at(int i);

	virtual String ^ToString() override;
	virtual String ^toFile();
	/// <summary>
	/// this method computes the intersection between this set and ot set. </summary>
	/// <param name="ot"> - the other set </param>
	virtual VertexSet ^intersection(VertexSet ^ot);

private:
	void resize();

};
