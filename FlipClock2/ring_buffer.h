/*
 * ring_buffer.h
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stdbool.h>
#include <stdint.h>

#define RING_BUFFER_LENGTH 256

template <uint8_t N> class RingBuffer {
  char data[N];
  uint8_t write_position;
  uint8_t read_position;

public:
  RingBuffer();
  bool write(char val);
  char read();
  bool canRead();
};

template <uint8_t N> RingBuffer<N>::RingBuffer() {
  this->read_position = 0;
  this->write_position = 0;
  for (uint8_t i = 0; i < N; i++) {
    this->data[i] = 0;
  }
}
template <uint8_t N> bool RingBuffer<N>::canRead() {
  return this->read_position != this->write_position;
}

template <uint8_t N> char RingBuffer<N>::read() {
  char result = this->data[this->read_position];
  this->read_position = (this->read_position + 1) % N;

  return result;
}

template <uint8_t N> bool RingBuffer<N>::write(char val) {
  if ((this->write_position + 1) % N == this->read_position) {
    return false;
  }
  this->data[this->write_position] = val;
  this->write_position = (this->write_position + 1) % N;

  return true;
}

#endif /* RING_BUFFER_H_ */
