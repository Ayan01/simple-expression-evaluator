#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include "VariableTable.h"

constexpr auto decimalPoint = '.';

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

	void _getToken();
	void _parse();
	void _match(char c, string message);
	void _error(string message);

	double _expr();
	double _term();
	double _factor();
	double _identifier();
	double _number();
};