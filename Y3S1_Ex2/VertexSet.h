#include <iostream>
#include <string>
#include <vector>
using namespace std;

class VertexSet
{
private:
	vector<int> _set;
public:
	VertexSet();
	VertexSet(VertexSet& ot);
	~VertexSet();
	void add(int a);
	int size() { return _set.size(); };
	int at(int i) { return _set.at(i); };
	string toString();
	string toFile();
	VertexSet intersection(VertexSet& ot);
};

VertexSet::VertexSet()
{
}

VertexSet::VertexSet(VertexSet& ot)
{
	for (int i = 0; i < ot.size(); i++)
	{
		add(ot.at(i));
	}
}

VertexSet::~VertexSet()
{
}

void VertexSet::add(int a)
{
	_set.push_back(a);
}

string VertexSet::toString()
{
	string ans = "Set: |" + to_string(size()) + "| ";
	for (int i = 0; i < size(); i++)
	{
		ans += to_string(at(i)) + ", ";
	}
	return ans;
}

string VertexSet::toFile()
{
	string ans = " ";
	for (int i =0 ; i < size() ; i++)
	{
		ans += to_string(at(i)) + ", ";
	}
	return ans;
}

VertexSet VertexSet::intersection(VertexSet &ot)
{
	VertexSet ans;
	int i1 = 0, i2 = 0;
	while (i1 < size() && i2 < ot.size())
	{
		int a1 = at(i1), a2 = ot.at(i2);
		if (a1 == a2)
		{
			ans.add(a1);
			i1++;
			i2++;
		}
		else if (a1 < a2)
		{
			i1++;
		}
		else 
		{
			i2++;
		}
	}
	return ans;
}