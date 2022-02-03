#pragma once
#include <Windows.h>
#include <malloc.h>
#include <iostream>

class IterlockSpinLock
{
	//volatile LONG* pValue = 0;
	//SpinLock()
	//{
	//	pValue = (LONG*)_aligned_malloc(sizeof(LONG), MEMORY_ALLOCATION_ALIGNMENT);
	//}
	//~SpinLock()
	//{
	//	_aligned_free((void*)pValue);
	//}

	volatile LONG mValue = 0;
public:
	void Lock()
	{
		while (_InterlockedCompareExchange(&mValue, 0, 1) == 1)
		{
		}
	}
	void Unlock()
	{
		_InterlockedCompareExchange(&mValue, 1, 0);
	}

};