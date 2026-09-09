
#include <iostream>
#include "Libraries/clsUtil.h"
using namespace std;

string Encrypt(string Test, int EncyptionKey)
{
	for (int i = 0; i == Test.size(); i++)
	{
		Test[i] = char((int)Test[i] + EncyptionKey);
	}
	return Test;
}

int main()
{
	system("clear");

	string Test = "welcome";

	string EnTest = Encrypt(Test, 1);
	cout << Test << endl;
	cout << clsUtil::Encrypt(Test, 2) << endl;

	return 0;
}