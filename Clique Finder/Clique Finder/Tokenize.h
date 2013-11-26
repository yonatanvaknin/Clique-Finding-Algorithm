#include <iostream>
#include <string>

using namespace std;

/////////////     string Tokenizer     ///////////////////////////

class Tokenize {
private:
	string *tokens;
	int count;
	int token;
public:
	Tokenize(const string &str, const string &sep);// - ליצירת אובייקט מטיפוס Tokenize אשר יאפשר את חלוקת המחרוזת str למחרוזות קטנות בהתאם לתו/מחרוזת המפריד/ה sep.
	Tokenize(const string &str);// - ליצירת אובייקט מטיפוס  Tokenize  אשר יאפשר את חלוקת המחרוזת str למחרוזות קטנות כשהתו המפריד הוא רווח.
	string nextToken();// - מתודה זו מחזירה את תת המחרוזת הבאה על פי התווים המפרידים שנקבעו בעת יצירת האובייקט.
	bool hasMoreToken();// - מתודה זו מחזירה true אם קיימות עוד תת מחרוזות שטרם הוחזרו על ידי המתודה ()nextToken.
	int countTokens();// - מתודה זו מחזירה מספר מחרוזות על פי התווים המפרידים שנקבעו בעת יצירת האובייקט.
	string elementAt(int);
};
