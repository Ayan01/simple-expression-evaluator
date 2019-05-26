#include <map>
#include <string>

using namespace std;

class VariableTable
{
public:
	bool exists(string variableName);
	double getVariable(string variableName);
	void addVariable(string variableName, double value);


private:
	map<string, double> _table;
};