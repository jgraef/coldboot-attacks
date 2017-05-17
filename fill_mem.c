#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
  const char *magic = "**ColdBoot**";
  unsigned long block_size = 4096;
  unsigned long magic_length = strlen(magic);
  unsigned long num_blocks = 1024;

  unsigned long bytes_written = 0;
  char *current_block;
  unsigned long i, j;

  printf("Filling memory with string '%s'...\n", magic);

  for (j = 0; j < num_blocks; j++) {
    current_block = (char*)malloc(block_size);
    if (current_block == NULL) {
      printf("\n Failed to allocate memory\n");
      return 1;
    }

    for (i = 0; i < block_size; i++) {
      current_block[i] = magic[i % magic_length];
    }

    bytes_written += block_size;
    printf("%d MB written    \r", bytes_written / 1024 / 1024);
    fflush(stdout);
  }

  return 0;
}
