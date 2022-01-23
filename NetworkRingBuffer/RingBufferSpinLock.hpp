#pragma once
#include "RingBuffer.hpp"
#include "SpinLock.hpp"

class RingBufferSpinLock : public RingBuffer
{
public:
	void Init()
	{
		mSpinLock.Lock();
		RingBuffer::Init();
		mSpinLock.Unlock();
	}
	bool IsEmpty()
	{
		bool bResult = false;
		mSpinLock.Lock();
		bResult = RingBuffer::IsEmpty();
		mSpinLock.Unlock();
		return bResult;
	}
	bool IsFull()
	{
		bool bResult = false;
		mSpinLock.Lock();
		bResult = RingBuffer::IsFull();
		mSpinLock.Unlock();
		return bResult;
	}
	size_t GetSize()
	{
		size_t szResult = 0;
		mSpinLock.Lock();
		szResult = RingBuffer::GetSize();
		mSpinLock.Unlock();
		return szResult;
	}

	bool PutData(const void* data, size_t size)
	{
		bool bResult = false;
		mSpinLock.Lock();
		bResult = RingBuffer::PutData(data, size);
		mSpinLock.Unlock();
		return bResult;
	}
	size_t GetData(void* data, size_t size, rbuf_opt_e clear = rbuf_opt_e::RBUF_CLEAR)
	{
		size_t szResult = 0;
		mSpinLock.Lock();
		szResult = RingBuffer::GetData(data, size, clear);
		mSpinLock.Unlock();
		return szResult;
	}

	bool DeleteData(size_t size)
	{
		bool bResult = false;
		mSpinLock.Lock();
		bResult = RingBuffer::DeleteData(size);
		mSpinLock.Unlock();
		return bResult;
	}

	void Flush(rbuf_opt_e clear)
	{
		mSpinLock.Lock();
		RingBuffer::Flush(clear);
		mSpinLock.Unlock();
	}

	void Clear()
	{
		mSpinLock.Lock();
		RingBuffer::Clear();
		mSpinLock.Unlock();
	}
	size_t GetMaxSize()
	{
		return RingBuffer::GetMaxSize();
	}

private:
	//TODO
	//1. atomic_flag 변수를 통한 lock 프리구조 해보기 + lock guard 까지
	//2. windows interlock 구조로 해보기
	SpinLock mSpinLock;
};
