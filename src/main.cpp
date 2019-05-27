#include "include/ExpressionEvaluator.h"

constexpr auto exitKeyWord = "exit";

using namespace simpleExpressionEvaluator;

int main()
{
	cout << "Type 'exit' to exit the program." << endl;

	while (true)
	{
		auto evaluator = ExpressionEvaluator();
		string input;

		cout << "Enter an expression>> ";
		getline(cin, input);

		if (!input.empty() && input != exitKeyWord)
		{
			try
			{
				evaluator.evaluate(input);
			}
			catch (const std::exception& e)
			{
				cerr << e.what() << endl;
			}
		}

		if (input == exitKeyWord)
			break;
	}

	return 0;
}