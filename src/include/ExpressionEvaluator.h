#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include "VariableTable.h"

using namespace std;

class ExpressionEvaluator
{
public:
	ExpressionEvaluator();
	void evaluate(string expression);


private:
	string _expression;
	VariableTable _variableTable;
	int _token;
	int _index;

	void getToken();
	void parse();
	void match(char c, string message);
	void error(string message);

	double expr();
	double term();
	double factor();
	double identifier();
	double number();
};