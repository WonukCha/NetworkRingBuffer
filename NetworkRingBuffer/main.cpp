#include <iostream>
#include <thread>
#include <vector>

//#include "RingbufferLockfree.hpp"
//#include "RingbufferLock.hpp"
#include "RingBufferLockAtomic.hpp"


using namespace std;

#define THREAD_SIZE 5
char arr[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};


//RingbufferLockfree rb;
//RingbufferLock rb;
RingBufferLockAtomic rb;




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

	for (int i = 0; i < 1; i++)
	{
		v.emplace_back(func1);
		v.emplace_back(func2);
		v.emplace_back(func3);
	}

	for (auto& t : v)
	{
		if (t.joinable())
			t.join();
	}

	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
	std::cout << "Test() 함수를 수행하는 걸린 시간(초) : " << sec.count() << " seconds" << std::endl;

	return 0;
}