#pragma once
#include "RingBuffer.hpp"
#include <mutex>


class RingbufferLockfree : public RingBuffer
{
public:
	void Init()
	{
		while (!mCS.try_lock()) {};
		RingBuffer::Init();
		mCS.unlock();
	}
	bool IsEmpty()
	{
		bool bResult = false;
		while (!mCS.try_lock()) {};
		bResult = RingBuffer::IsEmpty();
		mCS.unlock();
		return bResult;
	}
	bool IsFull()
	{
		bool bResult = false;
		while (!mCS.try_lock()) {};
		bResult = RingBuffer::IsFull();
		mCS.unlock();
		return bResult;
	}
	size_t GetSize()
	{
		size_t szResult = 0;
		while (!mCS.try_lock()) {};
		szResult = RingBuffer::GetSize();
		mCS.unlock();
		return szResult;
	}

	bool PutData(const void* data, size_t size)
	{
		bool bResult = false;
		while (!mCS.try_lock()) {};
		bResult = RingBuffer::PutData(data, size);
		mCS.unlock();
		return bResult;
	}
	size_t GetData(void* data, size_t size, rbuf_opt_e clear = rbuf_opt_e::RBUF_CLEAR)
	{
		size_t szResult = 0;
		while (!mCS.try_lock()) {};
		szResult = RingBuffer::GetData(data, size, clear);
		mCS.unlock();
		return szResult;
	}

	bool DeleteData(size_t size)
	{
		bool bResult = false;
		while (!mCS.try_lock()) {};
		bResult = RingBuffer::DeleteData(size);
		mCS.unlock();
		return bResult;
	}

	void Flush(rbuf_opt_e clear)
	{
		while (!mCS.try_lock()) {};
		RingBuffer::Flush(clear);
		mCS.unlock();
	}

	void Clear()
	{
		while (!mCS.try_lock()) {};
		RingBuffer::Clear();
		mCS.unlock();
	}
	size_t GetMaxSize()
	{
		return RingBuffer::GetMaxSize();
	}

private:
	//TODO
	//1. atomic_flag 변수를 통한 lock 프리구조 해보기 + lock guard 까지
	//2. windows interlock 구조로 해보기
	std::mutex mCS;
};
