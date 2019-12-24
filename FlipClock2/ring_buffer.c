#include "ring_buffer.h"

void ring_buffer_init(struct RingBuffer *ring_buffer) {
	ring_buffer->read_position = 0;
	ring_buffer->write_position = 0;
	for(uint8_t i = 0; i < RING_BUFFER_LENGTH; i++) {
		ring_buffer->data[i] = 0;
	}
}

void ring_buffer_write(struct RingBuffer *ring_buffer, char data) {
	if(!ring_buffer_can_write(ring_buffer)) {
		return;
	}

	ring_buffer->data[ring_buffer->write_position] = data;
	if(ring_buffer->write_position == RING_BUFFER_LENGTH - 2) {
		ring_buffer->write_position = 0;
	} else {
		ring_buffer->write_position++;
	}
}

char ring_buffer_read(struct RingBuffer *ring_buffer) {
	if(!ring_buffer_can_read(ring_buffer)) {
		return 0;
	}

	char result = ring_buffer->data[ring_buffer->read_position];
	ring_buffer->data[ring_buffer->read_position] = 0;

	if(ring_buffer->read_position == RING_BUFFER_LENGTH -2) {
		ring_buffer->read_position = 0;
		} else {
		ring_buffer->read_position++;
	}

	return result;
}

bool ring_buffer_can_read(struct RingBuffer* ring_buffer) {
	return ring_buffer->data[ring_buffer->read_position] > 0;
}

bool ring_buffer_can_write(struct RingBuffer* ring_buffer) {
	return ring_buffer->data[ring_buffer->write_position] == 0;
}