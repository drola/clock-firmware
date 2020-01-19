#ifndef SERIAL_H_
#define SERIAL_H_

#include "ring_buffer.h"

class Serial {
  RingBuffer<128> txBuffer;
  RingBuffer<128> rxBuffer;

public:
  //API for hardware comms
  void rx(char val);
  bool hasAnythingToTx();
  char tx();

  //High level API
  void print(char c);
  void print(const char *str);
  void println(const char *str);
  bool hasAnythingToRead();
  char read();
};

#endif // SERIAL_H
