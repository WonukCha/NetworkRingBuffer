#include <iostream>

#include "Ringbuffer.h"

using namespace std;

#define TEST_SIZE 7

int main(void)
{
	Ringbuffer rr;
	char input[TEST_SIZE];

	for (int i = 0; i < TEST_SIZE; i++)
	{
		input[i] = i;
	}
	while (true)
	{
		rr.PutData(input, sizeof(input));
	}
	return 0;
}