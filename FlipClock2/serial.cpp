#include "serial.h"

bool Serial::hasAnythingToTx() { return this->txBuffer.canRead(); }

char Serial::tx() { return this->txBuffer.read(); }

void Serial::rx(char chr) { this->rxBuffer.write(chr); }

void Serial::print(char c) { this->txBuffer.write(c); }

void Serial::print(const char *str) {
  uint8_t i = 0;
  while (str[i] > 0) {
    this->print(str[i]);
    i++;
  }
}

void Serial::println(const char *str) {
  this->print(str);
  this->print('\n');
}

char Serial::read() { return this->rxBuffer.read(); }

bool Serial::hasAnythingToRead() { return this->rxBuffer.canRead(); }
