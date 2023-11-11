/*
 * ring_buffer.h
 *
 *  Created on: Sep 14, 2023
 *      Author: hoang
 */
#include "type.h"
#include "stddef.h"
//#include "fl.h"

#ifndef APPS_USER_RING_BUFFER_H_
#define APPS_USER_RING_BUFFER_H_

#define LENGTH_BUFFER		256

/**
 * The type which is used to hold the size
 * and the indicies of the buffer.
 */
typedef unsigned int ring_buffer_size_t;

/**
 * Used as a modulo operator
 * as <tt> a % b = (a & (b âˆ’ 1)) </tt>
 * where \c a is a positive index in the buffer and
 * \c b is the (power of two) size of the buffer.
 */
#define RING_BUFFER_MASK(rb) (rb->buffer_mask)
typedef struct l_data {
	u8 length;
	char arr[LENGTH_BUFFER];
} l_data_t;

typedef l_data_t data_buffer_t;
//struct data_buffer_t{
//
//};

/**
 * Simplifies the use of <tt>struct ring_buffer_t</tt>.
 */
// struct ring_buffer ring_buffer_t;


/**
 * Structure which holds a ring buffer.
 * The buffer contains a buffer array
 * as well as metadata for the ring buffer.
 */
 typedef struct ring_buffer {
  /** Buffer memory. */
  data_buffer_t *buffer;
  /** Buffer mask. */
  ring_buffer_size_t buffer_mask;
  /** Index of tail. */
  ring_buffer_size_t tail_index;
  /** Index of head. */
  ring_buffer_size_t head_index;
}ring_buffer_t;

/**
 * Initializes the ring buffer pointed to by <em>buffer</em>.
 * This function can also be used to empty/reset the buffer.
 * The resulting buffer can contain <em>buf_size-1</em> bytes.
 * @param buffer The ring buffer to initialize.
 * @param buf The buffer allocated for the ringbuffer.
 * @param buf_size The size of the allocated ringbuffer.
 */
void ring_buffer_init(ring_buffer_t *buffer, data_buffer_t *buf, size_t buf_size);

/**
 * Adds a byte to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data The byte to place.
 */
void ring_buffer_queue(ring_buffer_t *buffer, data_buffer_t data);

/**
 * Adds an array of bytes to a ring buffer.
 * @param buffer The buffer in which the data should be placed.
 * @param data A pointer to the array of bytes to place in the queue.
 * @param size The size of the array.
 */
void ring_buffer_queue_arr(ring_buffer_t *buffer, const data_buffer_t *data, ring_buffer_size_t size);

/**
 * Returns the oldest byte in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @return 1 if data was returned; 0 otherwise.
 */
u8 ring_buffer_dequeue(ring_buffer_t *buffer, data_buffer_t *data);

/**
 * Returns the <em>len</em> oldest bytes in a ring buffer.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the array at which the data should be placed.
 * @param len The maximum number of bytes to return.
 * @return The number of bytes returned.
 */
ring_buffer_size_t ring_buffer_dequeue_arr(ring_buffer_t *buffer, data_buffer_t *data, ring_buffer_size_t len);
/**
 * Peeks a ring buffer, i.e. returns an element without removing it.
 * @param buffer The buffer from which the data should be returned.
 * @param data A pointer to the location at which the data should be placed.
 * @param index The index to peek.
 * @return 1 if data was returned; 0 otherwise.
 */
u8 ring_buffer_peek(ring_buffer_t *buffer, data_buffer_t *data, ring_buffer_size_t index);


/**
 * Returns whether a ring buffer is empty.
 * @param buffer The buffer for which it should be returned whether it is empty.
 * @return 1 if empty; 0 otherwise.
 */
inline u8 ring_buffer_is_empty(ring_buffer_t *buffer) {
  return (buffer->head_index == buffer->tail_index);
}

/**
 * Returns whether a ring buffer is full.
 * @param buffer The buffer for which it should be returned whether it is full.
 * @return 1 if full; 0 otherwise.
 */
inline u8 ring_buffer_is_full(ring_buffer_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK(buffer)) == RING_BUFFER_MASK(buffer);
}

/**
 * Returns the number of items in a ring buffer.
 * @param buffer The buffer for which the number of items should be returned.
 * @return The number of items in the ring buffer.
 */
inline ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK(buffer));
}

#endif /* APPS_USER_RING_BUFFER_H_ */
