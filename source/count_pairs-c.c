#include "helpers.h"
#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long __attribute__((noinline))
count_pairs(unsigned char *data, unsigned long size, unsigned char target) {
  unsigned long total = 0;
  unsigned short check = target | (target << 8U);
  __m256i compare = _mm256_set1_epi16(target);
  for (uint64_t i = 0; i < size * 2; i += 32) {
    uint32_t block1 = _mm256_movemask_epi8(
        _mm256_cmpeq_epi16(_mm256_load_si256((__m256i *)(data + i)), compare));
    uint32_t block2 = _mm256_movemask_epi8(_mm256_cmpeq_epi16(
        _mm256_loadu_si256((__m256i *)(data + i + 1)), compare));
    total += __builtin_popcount(block1);
    total += __builtin_popcount(block2);
  }
  return total / 2;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("specify the byte to look for and how log of the number of bytes to "
           "generate\n");
  }
  uint8_t target = atoi(argv[1]) & 0xFF;
  uint64_t logn = atol(argv[2]);
  uint64_t n = 1UL << logn;
  printf("target byte is %u, creating %lu bytes of data\n", target, 2 * n);
  uint16_t *data = get_random_data(n);
  uint64_t start = get_usecs();
  uint64_t pair_count = count_pairs((uint8_t *)data, n, target);
  uint64_t end = get_usecs();
  printf("took %lu milleseconds, and found %lu unaligned pairs\n",
         (end - start) / 1000, pair_count);
  return 0;
}