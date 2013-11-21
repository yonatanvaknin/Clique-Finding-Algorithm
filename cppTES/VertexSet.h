#pragma once

#include <string>

/// <summary>
/// this class represents a simple ORDERD set of vertices. used by Cliques
/// The code was written in C like flavor - no java.util, no abstraction  
/// @author Boaz
/// 
/// </summary>
class VertexSet
{
private:
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: private int[] _set = nullptr;
	int _set;
	int _sp;
public:
	static const int INIT_SIZE = 20, INC = 50;

	VertexSet();

	VertexSet(VertexSet ot);

	virtual void add(int a);
	virtual int size();
	virtual int at(int i);

	virtual std::string toString() override;
	virtual std::string toFile();
	/// <summary>
	/// this method computes the intersection between this set and ot set. </summary>
	/// <param name="ot"> - the other set </param>
	virtual VertexSet intersection(VertexSet ot);

private:
	void resize();


private:
	void InitializeInstanceFields();
};
