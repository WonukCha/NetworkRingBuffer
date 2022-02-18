# NetworkRingBuffer

스레드 6개 진행 시

Debug
RingBuffer 함수를 수행하는 걸린 시간(초) : 0.0527009 seconds
RingBufferMutexLock 함수를 수행하는 걸린 시간(초) : 0.93886 seconds
RingBufferLockAtomic 함수를 수행하는 걸린 시간(초) : 1.52229 seconds
RingbufferMutexSpinLock 함수를 수행하는 걸린 시간(초) : 1.59633 seconds
RingBufferIterlockSpinLock 함수를 수행하는 걸린 시간(초) : 0.320812 seconds
RingBufferCSLock 함수를 수행하는 걸린 시간(초) : 0.517823 seconds

Release
RingBuffer 함수를 수행하는 걸린 시간(초) : 0.0369111 seconds
RingBufferMutexLock 함수를 수행하는 걸린 시간(초) : 0.210128 seconds
RingBufferLockAtomic 함수를 수행하는 걸린 시간(초) : 0.682452 seconds
RingbufferMutexSpinLock 함수를 수행하는 걸린 시간(초) : 1.04574 seconds
RingBufferIterlockSpinLock 함수를 수행하는 걸린 시간(초) : 0.304341 seconds
RingBufferCSLock 함수를 수행하는 걸린 시간(초) : 0.451035 seconds