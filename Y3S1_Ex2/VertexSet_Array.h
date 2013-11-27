//#include <iostream>
//#include <string>
//using namespace std;
//
//class VertexSet
//{
//private:
//	int *_set;
//	int _len;
//	int _sp;
//	void resize();
//public:
//	const static int INIT_SIZE = 20, INC = 50;
//	VertexSet();
//	VertexSet(VertexSet& ot);
//	~VertexSet();
//	void add(int a);
//	int size() { return _sp; };
//	int at(int i) { return _set[i]; };
//	string toString();
//	string toFile();
//	VertexSet intersection(VertexSet& ot);
//};
//
//VertexSet::VertexSet()
//{
//	_set = new int[INIT_SIZE];
//	_len = INIT_SIZE;
//	_sp = 0;
//}
//
//VertexSet::VertexSet(VertexSet& ot)
//{
//	_set = new int[INIT_SIZE];
//	_len = INIT_SIZE;
//	_sp = 0;
//	for (int i = 0; i < ot.size(); i++)
//	{
//		add(ot.at(i));
//	}
//}
//
//VertexSet::~VertexSet()
//{
//	delete[] _set;	
//}
//
//void VertexSet::add(int a)
//{
//	if (_sp == _len)
//	{
//		resize();
//	}
//	_set[_sp] = a;
//	_sp++;
//}
//
//string VertexSet::toString()
//{
//	string ans = "Set: |" + to_string(size()) + "| ";
//	for (int i = 0; i < size(); i++)
//	{
//		ans += to_string(at(i)) + ", ";
//	}
//	return ans;
//}
//
//string VertexSet::toFile()
//{
//	string ans = " ";
//	for (int i = 0 ; i < size() ; i++)
//	{
//		ans += to_string(at(i)) + ", ";
//	}
//	return ans;
//}
//
//VertexSet VertexSet::intersection(VertexSet& ot)
//{
//	VertexSet ans;
//	int i1 = 0, i2 = 0;
//	while (i1 < size() && i2 < ot.size())
//	{
//		int a1 = at(i1), a2 = ot.at(i2);
//		if (a1 == a2)
//		{
//			ans.add(a1);
//			i1++;
//			i2++;
//		}
//		else if (a1 < a2)
//		{
//			i1++;
//		}
//		else 
//		{
//			i2++;
//		}
//	}
//	return ans;
//}
//
//void VertexSet::resize()
//{
//	int *tmp = new int[_sp + INC];
//	for (int i = 0; i < _sp; i++)
//	{
//		tmp[i]= _set[i];
//	}
//	delete[] _set;
//	_set = tmp;
//	_len =_sp + INC;
//}