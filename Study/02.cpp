#include <iostream>
#include <iomanip>

#include "h02.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::showpoint;

const size_t MAX{ 80 };

int main()
{
	char buffer[MAX]{};

	cout << endl
		<< "��ӭ����������������̨�汾��"
		<< endl
		<< "��������ʽ����������˳�"
		<< endl;
//	cout.precision(4);
	for (;;)
	{
		cin.getline(buffer, sizeof buffer);
		eatSpaces(buffer);

		if (!buffer[0])
			return 0;

		try
		{
			cout << "\t=" <<std::fixed<< expr(buffer)
				<< endl << endl;
		}
		catch (const char* pEx)
		{
			cerr << pEx << endl;
			cerr << "�������" << endl;
			return 1;
		}
	}
}

