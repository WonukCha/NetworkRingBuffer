#pragma once
#include "AtomicLockGuard.hpp"

constexpr size_t MAX_BUFFER_SIZE = 4096;
constexpr size_t LAST_BUFFER_INDEX = MAX_BUFFER_SIZE - 1;

// ring buffer options
typedef enum
{
	RBUF_CLEAR,
	RBUF_NO_CLEAR,
} rbuf_opt_e;

// buffer messages
typedef enum
{
	RBUF_EMPTY = -1,
	RBUF_FULL
} rbuf_msg_e;

class RingBufferLockAtomic
{
public:
	void Init()
	{
		mMutex.lock();
		memset(mBuffer, 0, sizeof(mBuffer));
		mHead = 0;
		mTail = 0;
		mSize = 0;
		mMutex.unlock();
	}
	bool IsEmpty()
	{
		bool bResult = false;
		mMutex.lock();
		if (0 == mSize)
			bResult = true;
		mMutex.unlock();
		return bResult;
	}
	bool IsFull()
	{
		bool bResult = false;
		mMutex.lock();
		if (MAX_BUFFER_SIZE == mSize)
			bResult = true;
		mMutex.unlock();
		return bResult;
	}

	size_t GetSize()
	{
		size_t size = 0;
		mMutex.lock();
		size = mSize;
		mMutex.unlock();
		return size;
	}

	bool PutData(const void* data, size_t size)
	{
		mMutex.lock();
		bool bResult = false;
		do
		{
			if (size == 0)
				break;

			if (size > MAX_BUFFER_SIZE)
				break;

			if (size + mSize > MAX_BUFFER_SIZE)
				break;

			char* dataPos = (char*)data;
			unsigned int curHead = mHead;
			unsigned int nextHead = mHead + size;
			bool bOver = false;
			if (nextHead > LAST_BUFFER_INDEX)
			{
				nextHead = nextHead - MAX_BUFFER_SIZE;
				bOver = true;
			}
			if (mHead != mTail)
			{
				if (bOver)
				{
					if ((curHead <= mTail && mTail < MAX_BUFFER_SIZE)
						|| (0 <= mTail && mTail < nextHead))
						break;
				}
				else
				{
					if (curHead <= mTail && mTail < nextHead)
						break;
				}
			}

			if (curHead < nextHead)
			{
				memcpy(&mBuffer[curHead], data, size);
			}
			else
			{
				size_t firstSize = MAX_BUFFER_SIZE - curHead;
				size_t SecondSize = size - firstSize;

				memcpy(&mBuffer[curHead], &dataPos[0], firstSize);
				memcpy(&mBuffer[0], &dataPos[firstSize], SecondSize);
			}

			mHead = nextHead;
			mSize += size;
			bResult = true;
		} while (false);
		mMutex.unlock();

		return bResult;
	}
	bool GetData(void* data, size_t size, rbuf_opt_e clear = RBUF_CLEAR)
	{
		mMutex.lock();

		bool bResult = false;
		do
		{
			if (size == 0)
				break;

			if (size > MAX_BUFFER_SIZE)
				break;

			if (size > mSize)
				break;

			char* dataPos = (char*)data;
			unsigned int curTail = mTail;
			unsigned int nextTail = mTail + size;
			if (nextTail > LAST_BUFFER_INDEX)
			{
				nextTail = nextTail - MAX_BUFFER_SIZE;
			}
			if ((mHead > curTail && mHead < nextTail) || (mHead < curTail && mHead > nextTail))
			{
				break;
			}
			if (curTail < nextTail)
			{
				memcpy(dataPos, &mBuffer[curTail], size);
			}
			else
			{
				size_t firstSize = MAX_BUFFER_SIZE - curTail;
				size_t SecondSize = size - firstSize;

				memcpy(&dataPos[0], &mBuffer[curTail], firstSize);
				memcpy(&dataPos[firstSize], &mBuffer[0], SecondSize);
			}
			mTail = nextTail;
			mSize -= size;
		} while (false);
		mMutex.unlock();
		return bResult;
	}

	void Flush(rbuf_opt_e clear)
	{
		mMutex.lock();

		mSize = 0;
		mHead = 0;
		mTail = 0;

		if (RBUF_CLEAR == clear)
		{
			memset(mBuffer, 0, sizeof(mBuffer));
		}
		mMutex.unlock();
	}

private:
	//TODO
	//1. atomic_flag 변수를 통한 lock 프리구조 해보기 + lock guard 까지
	//2. windows interlock 구조로 해보기
	my_mutex mMutex;
	char mBuffer[MAX_BUFFER_SIZE] = { 0, };
	unsigned int mHead = 0;
	unsigned int mTail = 0;
	size_t mSize = 0;
};
