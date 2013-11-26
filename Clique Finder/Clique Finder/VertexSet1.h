#pragma once
#include <string>
#include <vector>
using namespace std;

struct VertexSet1{
private:
	vector<int> _set;
public:
	VertexSet1::VertexSet1(){
		_set = vector<int>();
	}
	VertexSet1::VertexSet1(const VertexSet1 &vec){
		_set = vector<int>(vec._set);
	}
	int VertexSet1::size(){ return _set.size(); }
	int  VertexSet1::at(int i) { return _set.at(i); }
	void VertexSet1::add(int i){ _set.push_back(i); }
	string tostring(){
		string ans = "Set: |" + size();
		ans += "| ";
		for (int i = 0; i<size(); i++) ans += at(i) + ", ";
		return ans;
	}

	string  toFile(){
		string ans = " ";
		for (int i = 0; i < size(); i++){
			ans += to_string(at(i));
			ans+=", ";
		}
		return ans;
	}
	//this method computes the intersection between this set and ot set.
	VertexSet1 intersection(VertexSet1 &ot){
		VertexSet1 ans = VertexSet1();
		int i1 = 0, i2 = 0;
		while (i1<this->size() & i2 < ot.size()) {
			int a1 = this->at(i1), a2 = ot.at(i2);
			if (a1 == a2) {
				ans.add(a1); i1++; i2++;
			}
			else if (a1<a2) { i1++; }
			else i2++;
		}
		return ans;
	}
	~VertexSet1(){
	}
};

