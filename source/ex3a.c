#include "helpers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct decode_return {
    uint64_t difference;
    uint64_t old_size;
} decode_return;

decode_return Decode(const uint8_t *loc) {
  // first check the case if we only use 1 byte by checking the top bit of the first byte
  // this is done because we need to special case what happens if we are 0
  decode_return ret;
  if ((*loc & 0x80UL) == 0) {
    ret.old_size = *loc > 0;
    ret.difference = *loc;
    return ret;
  }
  ret.difference = *loc & 0x7FUL;
  ret.old_size = 1;
  uint64_t shift_amount = 7;
  // loop over each byte and shift the bits to the correct position
  do {
    loc += 1;
    ret.difference = ret.difference | ((*loc & 0x7FUL) << shift_amount);
    ret.old_size += 1;
    shift_amount += 7;
  } while (*loc & 0x80UL);
  return ret;
}

uint64_t sum_compressed(const uint8_t *loc) {
  uint64_t sum = 0;
  uint64_t current_element = 0;
  while (1) {
    decode_return dr = Decode(loc);
    if (dr.old_size == 0){
      return sum;
    }
    current_element += dr.difference;
    sum +=current_element;
    loc+=dr.old_size;
  } 
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("specify the number of elements to generate and encode\n");
  }
  uint64_t number_of_elements = atoi(argv[1]);
  printf("generating %lu elements\n", number_of_elements);
  uint8_t *data = generate_encoded_data(number_of_elements);
  uint64_t start = get_usecs();
  uint64_t total = sum_compressed(data);
  uint64_t end = get_usecs();
  printf("took %lu microseconds, and found a sum of %lu\n",
         (end - start), total);
  return 0;
}