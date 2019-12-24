#include "serial.h"

bool Serial::canTx() { return this->txBuffer.canRead(); }

char Serial::tx() { return this->txBuffer.read(); }

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
