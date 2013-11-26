#include "VertexSet.h"

VertexSet::VertexSet(){
	_set = new int[INIT_SIZE];
	_sp = 0;
}

VertexSet::VertexSet(const VertexSet &ot){
	_set = new int[sizeof(ot._set)];
	_sp = ot._sp;
	for(int i = 0; i < sizeof(_set); i++) _set[i] = ot._set[i];
}

void VertexSet::add(int a){
	if(_sp==sizeof(_set)) resize();
	_set[_sp++] = a;
}

void VertexSet::resize(){
	int *tmp = new int[_sp+INC];
	int i;
	for(i=0;i<_sp;i++) tmp[i]=_set[i];
	_set=tmp;
}

int VertexSet::size(){return _sp;}

int VertexSet::at(int i){return _set[i];}

string VertexSet::toString(){
	string ans = "Set: |"+this->size()+'| ';
		for(int i=0;i<_sp;i++) ans+=this->at(i)+", ";
	return ans;
}

string VertexSet::toFile(){
	stringstream ss;
	string ans;
	for(int i=0;i<_sp;i++){
		ss<<at(i)<<", ";
	}
	ans = ss.str();
	return ans;
}

VertexSet VertexSet::intersection(VertexSet ot){
	VertexSet ans;
	int i=0,j=0;
	while(i<_sp && j < ot.size()) {
		int a1=this->at(i), a2 = ot.at(j);
		if(a1==a2) {
			ans.add(a1); i++; j++;}
		else if(a1<a2) i++;
		else j++;
	}
	return ans;
}






