#pragma once
#include <mutex>

constexpr size_t MAX_BUFFER_SIZE = 4096000;
constexpr size_t LAST_BUFFER_INDEX = MAX_BUFFER_SIZE - 1;

// ring buffer options
typedef enum
{
	RBUF_CLEAR = 0,
	RBUF_NO_CLEAR,
} rbuf_opt_e;

// buffer messages
typedef enum
{
	RBUF_EMPTY = -1,
	RBUF_FULL
} rbuf_msg_e;

class RingbufferLock
{
public:
	void Init()
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
		memset(mBuffer, 0, sizeof(mBuffer));
		mHead = 0;
		mTail = 0;
		mSize = 0;
	}
	bool IsEmpty()
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
		return 0 == mSize;
	}
	bool IsFull()
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
		return MAX_BUFFER_SIZE == mSize;
	}

	size_t GetSize()
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
		return mSize;
	}

	bool PutData(const void* data, size_t size)
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
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
			unsigned int nextHead = mHead + (unsigned int)size;
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
		return bResult;
	}
	size_t GetData(void* data, size_t size, rbuf_opt_e clear = RBUF_CLEAR)
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
		size_t szResult = 0;
		do
		{
			if (size == 0)
				break;

			if (size > MAX_BUFFER_SIZE)
				break;

			if (size > mSize)
				break;

			char* dataPos = (char*)data;
			unsigned __int64 curTail = mTail;
			unsigned __int64 nextTail = mTail + (unsigned __int64)size;
			unsigned __int64 curEnd = mTail + (unsigned __int64)size - 1;

			if (nextTail > LAST_BUFFER_INDEX)
			{
				nextTail = nextTail - MAX_BUFFER_SIZE;
			}
			if ((mHead > curTail && mHead < nextTail) || (mHead < curTail && mHead > nextTail))
			{
				break;
			}
			if (curTail <= curEnd)
			{
				memcpy(dataPos, &mBuffer[curTail], size);
			}
			else
			{
				size_t firstSize = MAX_BUFFER_SIZE - curTail;
				size_t SecondSize = size - firstSize;

				memcpy(&dataPos[curTail], &mBuffer[curTail], firstSize);
				memcpy(&dataPos[firstSize], &mBuffer[0], SecondSize);
			}
			if (clear == RBUF_CLEAR)
			{
				mTail = nextTail;
				mSize -= size;
			}
			szResult = size;
		} while (false);
		return szResult;
	}

	bool DeleteData(size_t size)
	{
		std::lock_guard<std::mutex> lock_guard(mCS);

		bool bResult = false;
		do
		{
			if (size == 0)
				break;

			if (size >
				MAX_BUFFER_SIZE)
				break;

			if (size > mSize)
				break;

			unsigned int curTail = mTail;
			unsigned int nextTail = mTail + (unsigned int)size;
			if (nextTail > LAST_BUFFER_INDEX)
			{
				nextTail = nextTail - MAX_BUFFER_SIZE;
			}

			mTail = nextTail;
			mSize -= size;

			bResult = true;
		} while (false);
		return bResult;
	}

	void Flush(rbuf_opt_e clear)
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
		mSize = 0;
		mHead = 0;
		mTail = 0;

		if (RBUF_CLEAR == clear)
		{
			memset(mBuffer, 0, sizeof(mBuffer));
		}
	}

	void Clear()
	{
		std::lock_guard<std::mutex> lock_guard(mCS);
		mSize = 0;
		mHead = 0;
		mTail = 0;
	}
	size_t GetMaxSize()
	{
		return MAX_BUFFER_SIZE;
	}

private:
	std::mutex mCS;
	char mBuffer[MAX_BUFFER_SIZE] = { 0, };
	unsigned __int64 mHead = 0;
	unsigned __int64 mTail = 0;
	size_t mSize = 0;
};
