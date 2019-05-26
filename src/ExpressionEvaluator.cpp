#include "include/ExpressionEvaluator.h"

ExpressionEvaluator::ExpressionEvaluator()
{
	_variableTable = VariableTable();
	_index = -1;
}

void ExpressionEvaluator::evaluate(string expression)
{
	_expression = expression;
	getToken();
	parse();
}

void ExpressionEvaluator::error(string message)
{
	cout << "\nParse error : " << message << endl;
	exit(EXIT_FAILURE);
}

void ExpressionEvaluator::getToken()
{
	_index++;
	while (isspace(_expression[_index]) != 0)
		_index++;
	_token = _expression[_index];
}

void ExpressionEvaluator::match(char c, string message)
{
	if (_token == c)
		getToken();
	else
		error(message);
}

void ExpressionEvaluator::parse()
{
	/* parse -> expr '\n' */
	
	auto result = expr();
	if (_token == '\0')
		cout << "The result is : " << result << endl << endl;
	else
		error("Tokens after end of expression.");
}

double ExpressionEvaluator::expr()
{
	/* expr -> term  { '+' term | '-' term } */

	auto result = term();
	while ((_token == '+') || (_token == '-'))
	{
		if (_token == '+')
		{
			match('+', "+ expected!");
			result += term();
		}
		else
		{
			match('-', "- expected!");
			result -= term();
		}
	}
	return result;
}

double ExpressionEvaluator::term()
{
	/* term -> factor { '*' factor | '/' factor }*/

	auto result = factor();
	while ((_token == '*') || (_token == '/'))
	{
		if (_token == '*')
		{
			match('*', "* expected!");
			result *= factor();
		}
		else
		{
			match('/', "/ expected!");
			auto n = factor();
			if (n != 0)
				result = result / n;
			else
				cout <<  "\nError : Divison by 0!" << endl;
		}
	}
	return result;
}

double ExpressionEvaluator::factor()
{
	/* factor -> '(' expr ')' | number | variable */
	
	double result;
	if (_token == '(')
	{
		match('(', "( expected!");
		result = expr();
		match(')', ") expected!");
	}
	else if (isalpha(_token))
	{
		result = identifier();
	}
	else
	{
		result = number();
	}
	return result;
}

double ExpressionEvaluator::identifier()
{
	/* identifier -> alphabet { alphabet | digit } */

	int j = 0;
	string variable;

	while (isalnum(_token))
	{
		variable += _token;
		j++;
		getToken();
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

double ExpressionEvaluator::number()
{
	/* number -> digit { digit } */

	int j = 0;
	string number;

	while (isdigit(_token) || _token == '.')
	{
		number += _token;
		j++;
		getToken();
	}
	auto value = stod(number);
	return value;
}
