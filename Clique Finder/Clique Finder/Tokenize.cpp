#include "Tokenize.h"


static int cntSubstring(string st, string sub){
	int count = 0;
	if (st == "") return 0;
	int subl = sub.length(), stl = st.find_last_not_of(sub);
	for (int k = 0; k<stl; k++){
		for (int i = 0; i<subl; i++)
		if (st.at(k) == sub.at(i)){
			//cout<<st.substr(k);
			//cout<<st.substr(k).find_first_not_of(sub);
			k += st.substr(k).find_first_not_of(sub);
			count++;
			break;
		}
	}
	return count;
}

Tokenize::Tokenize(const string &str, const string &sep){// - ליצירת אובייקט מטיפוס Tokenize אשר יאפשר את חלוקת המחרוזת str למחרוזות קטנות בהתאם לתו/מחרוזת המפריד/ה sep.
	count = cntSubstring(str, sep) +1;
	tokens = new string[count];
	int j = 0, sepl = sep.length(), strl = str.find_last_not_of(sep);
	for (int k = 0; k <= strl; k++){
		for (int i = 0; i<sepl; i++)
		if (str.at(k) == sep.at(i)){
			k += str.substr(k).find_first_not_of(sep);
			j++;
			break;
		}
		tokens[j] += str.at(k);
	}
	token = 0;
}
Tokenize::Tokenize(const string &str){// - ליצירת אובייקט מטיפוס  Tokenize  אשר יאפשר את חלוקת המחרוזת str למחרוזות קטנות כשהתו המפריד הוא רווח.
	count = cntSubstring(str, " ") +1;
	tokens = new string[count];
	int j = 0, strl = str.find_last_not_of(" ");
	for (int k = 0; k <= strl; k++){
		if (str.at(k) == ' '){
			k += str.substr(k).find_first_not_of(" ");
			j++;
		}
		tokens[j] += str.at(k);
	}
	token = 0;
}
string Tokenize::nextToken(){// - מתודה זו מחזירה את תת המחרוזת הבאה על פי התווים המפרידים שנקבעו בעת יצירת האובייקט.
	if (this->hasMoreToken())
		return tokens[token++];
}
bool Tokenize::hasMoreToken(){// - מתודה זו מחזירה true אם קיימות עוד תת מחרוזות שטרם הוחזרו על ידי המתודה ()nextToken.
	return token<=count;
}
int Tokenize::countTokens(){
	return count;

}
string Tokenize::elementAt(int i){
	if (i <= count) 
		return tokens[i];
}