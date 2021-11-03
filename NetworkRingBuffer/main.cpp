#include <iostream>

#include "RingbufferLock.h"

using namespace std;

#define TEST_SIZE 7

int main(void)
{
	RingbufferLock rbl;
	char input[TEST_SIZE];

	for (int i = 0; i < TEST_SIZE; i++)
	{
		input[i] = i;
	}
	while (true)
	{
		rbl.PutData(input, sizeof(input));
	}
	return 0;
}