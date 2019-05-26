#include "include/ExpressionEvaluator.h"

int main()
{
	while (true)
	{
		auto evaluator = ExpressionEvaluator();
		string buf;

		cout << "Enter an expression>> ";
		getline(cin, buf);

		try
		{
			evaluator.evaluate(buf);
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
		}
	}

	return 0;
}