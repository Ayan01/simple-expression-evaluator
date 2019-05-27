#include "include/ExpressionEvaluator.h"

ExpressionEvaluator::ExpressionEvaluator()
{
	_variableTable = VariableTable();
	_index = -1;
}

void ExpressionEvaluator::evaluate(string expression)
{
	_expression = expression;
	_getToken();
	_parse();
}

void ExpressionEvaluator::_error(string message)
{
	cout << "\nParse error : " << message << endl;
	exit(EXIT_FAILURE);
}

void ExpressionEvaluator::_getToken()
{
	_index++;
	while (isspace(_expression[_index]) != 0)
		_index++;
	_token = _expression[_index];
}

void ExpressionEvaluator::_match(char c, string message)
{
	if (_token == c)
		_getToken();
	else
		_error(message);
}

void ExpressionEvaluator::_parse()
{
	/* parse -> expr '\n' */
	
	auto result = _expr();
	if (_token == '\0')
		cout << "The result is : " << result << endl << endl;
	else
		_error("Tokens after end of expression.");
}

double ExpressionEvaluator::_expr()
{
	/* expr -> term  { '+' term | '-' term } */

	auto result = _term();
	while ((_token == '+') || (_token == '-'))
	{
		if (_token == '+')
		{
			_match('+', "+ expected!");
			result += _term();
		}
		else
		{
			_match('-', "- expected!");
			result -= _term();
		}
	}
	return result;
}

double ExpressionEvaluator::_term()
{
	/* term -> factor { '*' factor | '/' factor }*/

	auto result = _factor();
	while ((_token == '*') || (_token == '/'))
	{
		if (_token == '*')
		{
			_match('*', "* expected!");
			result *= _factor();
		}
		else
		{
			_match('/', "/ expected!");
			auto n = _factor();
			if (n != 0)
				result = result / n;
			else
				cout <<  "\nError : Divison by 0!" << endl;
		}
	}
	return result;
}

double ExpressionEvaluator::_factor()
{
	/* factor -> '(' expr ')' | number | variable */
	
	double result;
	if (_token == '(')
	{
		_match('(', "( expected!");
		result = _expr();
		_match(')', ") expected!");
	}
	else if (isalpha(_token))
	{
		result = _identifier();
	}
	else
	{
		result = _number();
	}
	return result;
}

double ExpressionEvaluator::_identifier()
{
	/* identifier -> alphabet { alphabet | digit } */

	int j = 0;
	string variable;

	while (isalnum(_token))
	{
		variable += _token;
		j++;
		_getToken();
	}
	if (!_variableTable.exists(variable))
	{
		double value;
		cout << "\nVariable token : " << variable;
		cout << endl << "Enter its value : ";
		cin >> value;
		cin.ignore();
		_variableTable.addVariable(variable, value);
	}
	return _variableTable.getVariable(variable);
}

double ExpressionEvaluator::_number()
{
	/* number -> digit { digit } */

	int j = 0;
	string number;

	while (isdigit(_token) || _token == decimalPoint)
	{
		number += _token;
		j++;
		_getToken();
	}
	auto value = stod(number);
	return value;
}
