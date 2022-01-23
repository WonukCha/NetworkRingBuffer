#include <iostream>
#include <thread>
#include <vector>

#include "Ringbuffer.hpp"
#include "RingbufferLock.hpp"
#include "RingBufferLockAtomic.hpp"
#include "RingbufferLockfree.hpp"
#include "RingBufferSpinLock.hpp"



using namespace std;

#define THREADS_MULTIPLID_BY_3 2
char arr[77777] = {0,};


RingBuffer rb0;
RingbufferLock rb1;
RingBufferLockAtomic rb2;
RingbufferLockfree rb3;
RingBufferSpinLock rb4;

void Rb0PutData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb0.PutData(arr, sizeof(arr));
	}
}

void Rb0GetData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb0.GetData(arr, 10);
	}
}

void Rb0GetSize()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb0.GetSize();
	}
}

void Rb1PutData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb1.PutData(arr, sizeof(arr));
	}
}	

void Rb1GetData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb1.GetData(arr,10);
	}
}

void Rb1GetSize()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb1.GetSize();
	}
}


void Rb2PutData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb2.PutData(arr, sizeof(arr));
	}
}

void Rb2GetData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb2.GetData(arr, 10);
	}
}

void Rb2GetSize()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb2.GetSize();
	}
}



void Rb3PutData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb3.PutData(arr, sizeof(arr));
	}
}

void Rb3GetData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb3.GetData(arr, 10);
	}
}

void Rb3GetSize()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb3.GetSize();
	}
}

void Rb4PutData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb4.PutData(arr, sizeof(arr));
	}
}

void Rb4GetData()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb4.GetData(arr, 10);
	}
}

void Rb4GetSize()
{
	for (int i = 0; i < 1000000; i++)
	{
		rb4.GetSize();
	}
}


int main(void)
{
	{
		vector<thread> v;
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (int i = 0; i < THREADS_MULTIPLID_BY_3; i++)
		{
			v.emplace_back(Rb0PutData);
			v.emplace_back(Rb0GetData);
			v.emplace_back(Rb0GetSize);
		}

		for (auto& t : v)
		{
			if (t.joinable())
				t.join();
		}
		std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
		std::cout << "Ringbuffer 함수를 수행하는 걸린 시간(초) : " << sec.count() << " seconds" << std::endl;
	}

	{
		vector<thread> v;
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (int i = 0; i < THREADS_MULTIPLID_BY_3; i++)
		{
			v.emplace_back(Rb1PutData);
			v.emplace_back(Rb1GetData);
			v.emplace_back(Rb1GetSize);
		}

		for (auto& t : v)
		{
			if (t.joinable())
				t.join();
		}
		std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
		std::cout << "RingbufferLock 함수를 수행하는 걸린 시간(초) : " << sec.count() << " seconds" << std::endl;
	}
	
	{
		vector<thread> v;
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (int i = 0; i < THREADS_MULTIPLID_BY_3; i++)
		{
			v.emplace_back(Rb2PutData);
			v.emplace_back(Rb2GetData);
			v.emplace_back(Rb2GetSize);
		}

		for (auto& t : v)
		{
			if (t.joinable())
				t.join();
		}
		std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
		std::cout << "RingBufferLockAtomic 함수를 수행하는 걸린 시간(초) : " << sec.count() << " seconds" << std::endl;
	}

	{
		vector<thread> v;
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (int i = 0; i < THREADS_MULTIPLID_BY_3; i++)
		{
			v.emplace_back(Rb3PutData);
			v.emplace_back(Rb3GetData);
			v.emplace_back(Rb3GetSize);
		}

		for (auto& t : v)
		{
			if (t.joinable())
				t.join();
		}
		std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
		std::cout << "RingbufferLockfree 함수를 수행하는 걸린 시간(초) : " << sec.count() << " seconds" << std::endl;
	}

	{
		vector<thread> v;
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (int i = 0; i < THREADS_MULTIPLID_BY_3; i++)
		{
			v.emplace_back(Rb4PutData);
			v.emplace_back(Rb4GetData);
			v.emplace_back(Rb4GetSize);
		}

		for (auto& t : v)
		{
			if (t.joinable())
				t.join();
		}
		std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
		std::cout << "RingBufferSpinLock 함수를 수행하는 걸린 시간(초) : " << sec.count() << " seconds" << std::endl;
	}
	return 0;
}