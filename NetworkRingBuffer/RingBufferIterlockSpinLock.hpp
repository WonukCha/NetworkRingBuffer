#pragma once
#include "RingBuffer.hpp"
#include "IterlockSpinLock.hpp"

class RingBufferIterlockSpinLock : public RingBuffer
{
public:
	void Init()
	{
		mIterlockSpinLock.Lock();
		RingBuffer::Init();
		mIterlockSpinLock.Unlock();
	}
	bool IsEmpty()
	{
		bool bResult = false;
		mIterlockSpinLock.Lock();
		bResult = RingBuffer::IsEmpty();
		mIterlockSpinLock.Unlock();
		return bResult;
	}
	bool IsFull()
	{
		bool bResult = false;
		mIterlockSpinLock.Lock();
		bResult = RingBuffer::IsFull();
		mIterlockSpinLock.Unlock();
		return bResult;
	}
	size_t GetSize()
	{
		size_t szResult = 0;
		mIterlockSpinLock.Lock();
		szResult = RingBuffer::GetSize();
		mIterlockSpinLock.Unlock();
		return szResult;
	}

	bool PutData(const void* data, size_t size)
	{
		bool bResult = false;
		mIterlockSpinLock.Lock();
		bResult = RingBuffer::PutData(data, size);
		mIterlockSpinLock.Unlock();
		return bResult;
	}
	size_t GetData(void* data, size_t size, rbuf_opt_e clear = rbuf_opt_e::RBUF_CLEAR)
	{
		size_t szResult = 0;
		mIterlockSpinLock.Lock();
		szResult = RingBuffer::GetData(data, size, clear);
		mIterlockSpinLock.Unlock();
		return szResult;
	}

	bool DeleteData(size_t size)
	{
		bool bResult = false;
		mIterlockSpinLock.Lock();
		bResult = RingBuffer::DeleteData(size);
		mIterlockSpinLock.Unlock();
		return bResult;
	}

	void Flush(rbuf_opt_e clear)
	{
		mIterlockSpinLock.Lock();
		RingBuffer::Flush(clear);
		mIterlockSpinLock.Unlock();
	}

	void Clear()
	{
		mIterlockSpinLock.Lock();
		RingBuffer::Clear();
		mIterlockSpinLock.Unlock();
	}
	size_t GetMaxSize()
	{
		return RingBuffer::GetMaxSize();
	}

private:
	//TODO
	//1. atomic_flag 변수를 통한 lock 프리구조 해보기 + lock guard 까지
	//2. windows interlock 구조로 해보기
	IterlockSpinLock mIterlockSpinLock;
};
