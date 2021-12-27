#pragma once
#include "AtomicLockGuard.hpp"
#include "RingBuffer.hpp"


class RingBufferLockAtomic : public RingBuffer
{
public:
	void Init()
	{
		mMutex.lock();
		RingBuffer::Init();
		mMutex.unlock();

	}
	bool IsEmpty()
	{
		bool bResult = false;
		mMutex.lock();
		bResult = RingBuffer::IsEmpty();
		mMutex.unlock();
		return bResult;
	}
	bool IsFull()
	{
		bool bResult = false;
		mMutex.lock();
		bResult = RingBuffer::IsFull();
		mMutex.unlock();
		return bResult;
	}
	size_t GetSize()
	{
		size_t szResult = 0;
		mMutex.lock();
		szResult = RingBuffer::GetSize();
		mMutex.unlock();
		return szResult;
	}

	bool PutData(const void* data, size_t size)
	{
		bool bResult = false;
		mMutex.lock();
		bResult = RingBuffer::PutData(data, size);
		mMutex.unlock();
		return bResult;
	}
	size_t GetData(void* data, size_t size, rbuf_opt_e clear = rbuf_opt_e::RBUF_CLEAR)
	{
		size_t szResult = 0;
		mMutex.lock();
		szResult = RingBuffer::GetData(data, size, clear);
		mMutex.unlock();
		return szResult;
	}

	bool DeleteData(size_t size)
	{
		bool bResult = false;
		mMutex.lock();
		bResult = RingBuffer::DeleteData(size);
		mMutex.unlock();
		return bResult;
	}

	void Flush(rbuf_opt_e clear)
	{
		mMutex.lock();
		RingBuffer::Flush(clear);
		mMutex.unlock();
	}

	void Clear()
	{
		mMutex.lock();
		RingBuffer::Clear();
		mMutex.unlock();
	}
	size_t GetMaxSize()
	{
		return RingBuffer::GetMaxSize();
	}
private:
	//TODO
	//1. atomic_flag 변수를 통한 lock 프리구조 해보기 + lock guard 까지
	//2. windows interlock 구조로 해보기
	my_mutex mMutex;

};
