#include <iostream>

#include "RingbufferLockfree.hpp"

using namespace std;

#define TEST_SIZE 7

int main(void)
{
	RingbufferLockfree rr;
	char input[TEST_SIZE];

	for (int i = 0; i < TEST_SIZE; i++)
	{
		input[i] = i;
	}
	string str;
	char buf[1000] = { 0, };
	while (true)
	{
		memset(buf, 0, sizeof(buf));
		cin >> str;

		if (str == "1")
		{
			cin >> str;
			strcpy_s(buf, str.c_str());
			rr.PutData(buf, str.size());
		}
		else
		{
			size_t size;
			cin >> size;

			rr.GetData(buf, size);
			cout << buf << "\r\n";
		}

	}
	return 0;
}