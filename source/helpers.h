#pragma once
#include <assert.h>
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

uint64_t get_usecs() {
  struct timeval st;
  gettimeofday(&st, NULL);
  return st.tv_sec * 1000000 + st.tv_usec;
}

uint16_t *get_random_data(uint64_t size) {
#ifdef SEED
  srand(SEED);
#else
  srand(0);
#endif
  uint16_t *data = (uint16_t *)memalign(32, size * sizeof(*data) + 32);
  for (uint64_t i = 0; i < size; i++) {
    data[i] = rand();
  }
  return data;
}

static inline int *get_random_ints(uint64_t size) {
#ifdef SEED
  srand(SEED);
#else
  srand(0);
#endif
  int *data = (int *)memalign(32, size * sizeof(*data) + 32);
  for (uint64_t i = 0; i < size; i++) {
    data[i] = rand() % 0xFFFF;
  }
  return data;
}

uint16_t load16(const void *loc) {
  uint16_t data;
  memcpy(&data, loc, sizeof(data));
  return data;
}

uint64_t load64(const void *loc) {
  uint64_t data;
  memcpy(&data, loc, sizeof(data));
  return data;
}

uint64_t Encode(uint8_t *loc, uint64_t difference) {
  loc[0] = difference & 0x7FU;
  uint64_t num_bytes = difference > 0;
  difference >>= 7;
  while (difference) {
    loc[num_bytes - 1] |= 0x80U;
    loc[num_bytes] = difference & 0x7FU;
    num_bytes += 1;
    difference >>= 7;
  }
  return num_bytes;
}

uint64_t random_element_uniform_size_distribution() {
  uint64_t size = rand() % 6;
  uint64_t element = 1;
  for (uint64_t i = 0; i < size; i++) {
    element <<= 8;
    element |= (rand() & 0xFFU);
  }
  return element;
}

uint8_t *generate_encoded_data(uint64_t elements_to_generate) {
#ifdef SEED
  srand(SEED);
#else
  srand(0);
#endif
  uint8_t *data =
      (uint8_t *)memalign(32, elements_to_generate * sizeof(uint64_t));
  uint8_t *loc = data;
  uint64_t sum = 0;
  uint64_t last_element = 0;
  for (uint64_t i = 0; i < elements_to_generate; i++) {
    uint64_t difference = random_element_uniform_size_distribution();
    uint64_t element = last_element + difference;
    assert(element > last_element);
    uint64_t size_written = Encode(loc, difference);
    loc += size_written;
    sum += element;
    last_element = element;
  }
  printf("wrote %lu bytes, the sum of all the elements was %lu\n", loc - data,
         sum);
  return data;
}
