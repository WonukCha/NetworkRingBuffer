# NetworkRingBuffer

스레드 6개 진행 시

단위:초	1차	2차	3차	4차	5차
while(atomic_flag)	2.76087	2.24016	2.4435	2.82407	2.34989
mutex	1.57901	1.59718	1.57237	1.58186	1.55151
mutex.trylock	1.92458	2.22589	2.06255	1.84883	1.88331

i7-7660U 2.50GH
