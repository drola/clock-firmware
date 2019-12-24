#ifndef SERIAL_H_
#define SERIAL_H_

#include "ring_buffer.h"

class Serial {
  RingBuffer<128> txBuffer;
  RingBuffer<128> rxBuffer;

public:
  void rx(char val);
  bool canTx();
  char tx();
  void print(char c);
  void print(const char *str);
  void println(const char *str);
};

#endif // SERIAL_H

//
// How to tie to HW?
// - polling vs interrupts
// - interrupts: more flexibility w baud rates
// - polling: easier to code, no fuss w atomic ops
// Is it possible to design
// a channel which is inherently safe with non atomic ops? lock-free channel?
// write side of the ring buffer separate from read side:
// contention on the 'count' member
// does this help? count = writtenCount - readCount
// would work if overflow protection sacrificed
// next problem: how to handle overflows w writeCount, readCount
// writeCount >= readCount
// if writeCount < readCount: count = N - readCount + writeCount
// if writeCount >= readCount: count = writeCount - readCount = (N - readCount + writeCount) % N

// N = 4
// wc | rc | c
// 0 | 0 | 0
// 1 | 0 | 1
// 2 | 0 | 2
// 3 | 0 | 3
// 4 | 0 | 0 -> impossible case, because wc is mod 4; we actually have 4 valid value in the buffer in this situation... Should the formula be % N+1 ?
// 0 | 0 | 0 


//with MOD N+1 arithmetic
// N = 4
// wc | rc | c
// 0 | 0 | 0
// 1 | 0 | 1
// 2 | 0 | 2
// 3 | 0 | 3
// 4 | 0 | 4
// 0 | 0 | 0

// counters are hard if they're overflowing
// 0 | 0 | 0 -> it's not clear at all whether we're reading valid values
// 0 | 1 | 3
// 0 | 2 | 2
// 0 | 3 | 1
// 0 | 4 | 0

// extra bit on the write count?
// can distinguish between 0 and 4

// 4 | 0 | 
// 4 | 1 | 3
// 4 | 2 | 2
// 4 | 3 | 1
// 4 | 4 | 0

//Discard write on overflow;
//if writePtr < readPtr && writePtr == readPtr - 1 -> discard write

//Reading:
// can read until writePtr==readPtr