#pragma once
#include "RingBuffer.hpp"
#include <windows.h> 

class RingBufferCSLock : public RingBuffer
{
public:
	RingBufferCSLock()
	{
		::InitializeCriticalSection(&CriticalSection);
	}
	~RingBufferCSLock()
	{
		::DeleteCriticalSection(&CriticalSection);
	}
	void Init()
	{
		::EnterCriticalSection(&CriticalSection);

		RingBuffer::Init();
		::LeaveCriticalSection(&CriticalSection);

	}
	bool IsEmpty()
	{
		bool bResult = false;
		::EnterCriticalSection(&CriticalSection);
		bResult = RingBuffer::IsEmpty();
		::LeaveCriticalSection(&CriticalSection);
		return bResult;
	}
	bool IsFull()
	{
		bool bResult = false;
		::EnterCriticalSection(&CriticalSection);
		bResult = RingBuffer::IsFull();
		::LeaveCriticalSection(&CriticalSection);
		return bResult;
	}
	size_t GetSize()
	{
		size_t szResult = 0;
		::EnterCriticalSection(&CriticalSection);
		szResult = RingBuffer::GetSize();
		::LeaveCriticalSection(&CriticalSection);
		return szResult;
	}

	bool PutData(const void* data, size_t size)
	{
		bool bResult = false;
		::EnterCriticalSection(&CriticalSection);
		bResult = RingBuffer::PutData(data, size);
		::LeaveCriticalSection(&CriticalSection);
		return bResult;
	}
	size_t GetData(void* data, size_t size, rbuf_opt_e clear = rbuf_opt_e::RBUF_CLEAR)
	{
		size_t szResult = 0;
		::EnterCriticalSection(&CriticalSection);
		szResult = RingBuffer::GetData(data, size, clear);
		::LeaveCriticalSection(&CriticalSection);
		return szResult;
	}

	bool DeleteData(size_t size)
	{
		bool bResult = false;
		::EnterCriticalSection(&CriticalSection);
		bResult = RingBuffer::DeleteData(size);
		::LeaveCriticalSection(&CriticalSection);
		return bResult;
	}

	void Flush(rbuf_opt_e clear)
	{
		::EnterCriticalSection(&CriticalSection);

		RingBuffer::Flush(clear);
		::LeaveCriticalSection(&CriticalSection);
	}

	void Clear()
	{
		::EnterCriticalSection(&CriticalSection);
		RingBuffer::Clear();
		::LeaveCriticalSection(&CriticalSection);
	}
	size_t GetMaxSize()
	{
		return RingBuffer::GetMaxSize();
	}
private:
	//TODO
	CRITICAL_SECTION CriticalSection;

};
