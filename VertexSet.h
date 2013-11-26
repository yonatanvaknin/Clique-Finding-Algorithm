#include <sstream>

#ifndef VERTEXSET_H
#define VERTEXSET_H


using namespace std;

class VertexSet{
	int *_set;
	int _sp;
private:
	void resize();
public:
	const static int INIT_SIZE=20, INC=50;
	VertexSet();
	VertexSet(const VertexSet &ot);
	void add(int a);
	int size();
	int at(int i);
	string toString();
	string toFile();
	VertexSet intersection(VertexSet ot);
};

#endif