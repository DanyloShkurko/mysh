#include "../include/common.h"

void add_ch(char *s, char c) {
  while (*s++) {
  };

  *(s - 1) = c;
  *s = '\0';
}
