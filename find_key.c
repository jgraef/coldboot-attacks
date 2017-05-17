#include <stdio.h>


#define BLOCK_SIZE 4096
#define KEY_SIZE 4096

#define MATCH_START 1
#define MATCH_END 2


int main(int argc, char *argv) {
  const char *magic_start = "-----BEGIN RSA PRIVATE KEY-----";
  const char *magic_end = "-----END RSA PRIVATE KEY-----";

  FILE *fd;
  unsigned long addr = 0;
  char block[BLOCK_SIZE];
  unsigned long i;
  int match_state = MATCH_START;
  unsigned long match_pos = 0;
  unsigned long key_pos = 0;
  char key_buf[4096];

  fd = fopen("/dev/mem", "rb");
  if (fd == NULL) {
    fprintf(stderr, "Can't open /dev/mem\n");
    return 1;
  }

  fseek(fd, addr, SEEK_SET);

  while (!feof(fd)) {
    if (fread(block, BLOCK_SIZE, 1, fd) != 1) {
      fprintf(stderr, "Error reading 0x%lx\n", addr);
      break;
    }

    for (i = 0; i < BLOCK_SIZE; i++) {
      key_buf[key_pos] = block[i];
      key_pos++;

      if (match_state == MATCH_START) {
        if (magic_start[match_pos] == 0) {
          match_state = MATCH_END;
          match_pos = 0;
        }
        else if (block[i] == magic_start[match_pos]) {
          match_pos++;
        }
        else {
          match_pos = 0;
          key_pos = 0;
        }
      }
      else {
        if (magic_end[match_pos] == 0) {
          key_buf[key_pos - 1] = 0;
          puts(key_buf);

          match_state = MATCH_START;
          match_pos = 0;
          key_pos = 0;
        }
        else if (block[i] == magic_end[match_pos]) {
          match_pos++;
        }
        else if (key_pos > KEY_SIZE) {
          match_state = MATCH_START;
          match_pos = 0;
          key_pos = 0;
        }        
      }
    }

    addr += BLOCK_SIZE;
  }

  fclose(fd);
}
