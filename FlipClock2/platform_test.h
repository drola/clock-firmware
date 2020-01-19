/**
 * ATOMICS
 */
#define ATOMIC_RESTORESTATE
#define ATOMIC_BLOCK(type) for (uint8_t ToDo = 1; ToDo; ToDo = 0)

/**
 * SERIAL PORTS
 */
#define ON_SERIAL_RECEIVED(port) for (uint8_t ToDo = 1; ToDo; ToDo = 0)
#define ON_SERIAL_READY_TO_TRANSMIT(port) for (uint8_t ToDo = 1; ToDo; ToDo = 0)
#define SERIAL_TRANSMIT(port, chr)                                             \
  for (; 0;) {                                                                 \
  }

class SerialMock {
  
}