#include "include/VariableTable.h"

using namespace simpleExpressionEvaluator;

bool VariableTable::exists(string variableName)
{
	return (_table.find(variableName) != _table.end()) ? true : false;
}

double VariableTable::getVariable(string variableName)
{
	return _table[variableName];
}

void VariableTable::addVariable(string variableName, double value)
{
	_table[variableName] = value;
}
