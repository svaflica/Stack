// Stack3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "header.h"

using namespace std;

int main()
{
	try {
		const char* ariph = "(5+6)^2*1";
		const char* ariph2 = "5-6^(2*3)+8/2";

		std::cout << equationSolution(ariph2);

		return 0;
	}
	catch (const char* error)
	{
		cout << error;

		return -1;
	}
}
