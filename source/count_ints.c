#include "helpers.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

long count_ints(int *data, long n, int target) {
#ifdef LONG
  long count = 0;
#else
  int count = 0;
#endif
  for (int i = 0; i < n; i++) {
    if (data[i] == target) {
      count += 1;
    }
  }
  return count;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("specify the byte to look for and how log of the number of bytes to "
           "generate\n");
  }
  int target = atoi(argv[1]);
  uint64_t logn = atol(argv[2]);
  uint64_t n = 1UL << logn;
  printf("target int is %u, creating %lu bytes of data\n", target, n);
  n /= 4;
  int *data = get_random_ints(n);
  uint64_t start = get_usecs();
  uint64_t count = count_ints(data, n, target);
  uint64_t end = get_usecs();
  printf("took %lu milleseconds, and found %lu\n", (end - start) / 1000, count);
  free(data);
  return 0;
}