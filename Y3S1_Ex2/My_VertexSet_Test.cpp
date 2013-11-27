#include "VertexSet.h"
#include "Clique.h"
#include "Split.h"
#include <ctime>

// Test VertexSet (Vector)
void main()
{
	VertexSet vs;
	vs.add(1);
	vs.add(2);
	vs.add(3);
	vs.add(4);
	vs.add(5);
	vs.add(5);
	vs.add(5);
	vs.add(5);
	cout<<"size: "<<vs.size()<<endl;
	cout<<"at(2): "<<vs.at(2)<<endl;
	cout<<"toString: "<<vs.toString()<<endl;
	cout<<"toFile: "<<vs.toFile()<<endl;
	VertexSet vs1(vs);
	cout<<"size: "<<vs1.size()<<endl;
	cout<<"at(2): "<<vs1.at(2)<<endl;
	cout<<"toString: "<<vs1.toString()<<endl;
	cout<<"toFile: "<<vs1.toFile()<<endl;
	VertexSet vs2 = vs.intersection(vs1);
	cout<<"vs and vs1 intersection: "<<vs2.toString()<<endl;
	VertexSet vs3;
	vs3.add(1);
	vs3.add(5);
	VertexSet vs4 = vs3.intersection(vs2);
	cout<<"vs3 and vs2 intersection: "<<vs4.toString()<<endl;

	/*string part;
	while (getline(cin, part, ','))
		cout << part << endl;*/

	string s = "Abc, defg,, Higk,lmnop,,";
	vector<string> fields;
	cout << "\"" << s << "\"\n\n";
	splitString(fields, s, ",", split::empties_ok);
	cout<<fields.size()<<endl;
	/*Clique c(3,4);
	VertexSet vs1 = c.commonNi();*/

}
