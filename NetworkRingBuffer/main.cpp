#include <iostream>
#include <thread>
#include <vector>

#define free

#ifdef free
#include "RingbufferLockfree.hpp"
#else
#include "RingbufferLock.hpp"
#endif // free




using namespace std;

#define THREAD_SIZE 5
char arr[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


#ifdef free
RingbufferLockfree rb;
#else
RingbufferLock rb;
#endif // free


void func1()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb.PutData(arr, sizeof(arr));
	}

}

void func2()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb.GetData(arr,10);
	}

}

void func3()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb.GetSize();
	}
}

int main(void)
{
	vector<thread> v;

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	for (int i = 0; i < 2; i++)
	{
		v.emplace_back(func1);
	}
	for (int i = 0; i < 2; i++)
	{
		v.emplace_back(func2);
	}
	for (int i = 0; i < 2; i++)
	{
		v.emplace_back(func3);
	}

	for (auto& t : v)
	{
		if (t.joinable())
			t.join();
	}

	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	std::cout << "Test() �Լ��� �����ϴ� �ɸ� �ð�(��) : " << sec.count() << " seconds" << std::endl;

	return 0;
}