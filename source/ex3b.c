#include "helpers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <immintrin.h>

typedef struct decode_return {
    uint64_t difference;
    uint64_t old_size;
} decode_return;

static uint64_t extract_masks[] = {
    0x000000000000007FUL, 0x0000000000007F7FUL, 0x00000000007F7F7FUL,
    0x000000007F7F7F7FUL, 0x0000007F7F7F7F7FUL, 0x00007F7F7F7F7F7FUL, 0x007F7F7F7F7F7F7FUL};


decode_return Decode(const uint8_t *loc) {
  decode_return ret;
  // once again special case the first byte
  if ((*loc & 0x80UL) == 0) {
    ret.old_size = *loc > 0;
    ret.difference = *loc;
    return ret;
  }
  // load the next 64 bits of data which is big enough to always contain the next compressed integer
  uint64_t chunks = load64(loc);

  // extract the top bit from each byte
  uint64_t mask = _pext_u64(chunks, 0x8080808080808080UL);

  // find the first bit that is 0 which corresponds to how long the compressed integer is
  int32_t index = __tzcnt_u64(~mask);

  // extract the data bits 
  uint64_t difference = _pext_u64(chunks, extract_masks[index]);
  ret.difference = difference;
  ret.old_size = index+1;

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