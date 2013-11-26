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
	Tokenize(const string &str, const string &sep);// - ������ ������� ������ Tokenize ��� ����� �� ����� ������� str �������� ����� ����� ���/������ ������/� sep.
	Tokenize(const string &str);// - ������ ������� ������  Tokenize  ��� ����� �� ����� ������� str �������� ����� ����� ������ ��� ����.
	string nextToken();// - ����� �� ������ �� �� ������� ���� �� �� ������ �������� ������ ��� ����� ��������.
	bool hasMoreToken();// - ����� �� ������ true �� ������ ��� �� ������� ���� ������ �� ��� ������ ()nextToken.
	int countTokens();// - ����� �� ������ ���� ������� �� �� ������ �������� ������ ��� ����� ��������.
	string elementAt(int);
};
