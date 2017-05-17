#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 4096


int main(int argc, char *argv) {
  const char *magic = "ColdBoot";
  unsigned long magic_length = strlen(magic);

  FILE *fd;
  unsigned long addr = 64 * 1024 * 1024;
  char block[BLOCK_SIZE];
  unsigned long i;

  fd = fopen("/dev/mem", "rb");
  if (fd == NULL) {
    fprintf(stderr, "Can't open /dev/mem\n");
    return 1;
  }

  fseek(fd, addr, SEEK_SET);

  while (!feof(fd)) {
    printf("Reading 0x%lx    \n", addr);

    if (fread(block, BLOCK_SIZE, 1, fd) != 1) {
      fprintf(stderr, "Error reading 0x%lx\n", addr);
    }
    
    for (i = 0; i < BLOCK_SIZE - magic_length; i++) {
      if (memcmp(block + i, magic, magic_length) == 0) {
        printf("Magic found at 0x%lx\n", addr + i);
      }
    }

    addr += BLOCK_SIZE;
  }

  fclose(fd);
}

