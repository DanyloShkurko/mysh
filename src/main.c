#include "../include/executor.h"
#include "../include/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  while (1) {
    char buffer[256];
    printf("mysh> ");
    fflush(stdout);
    if (fgets(buffer, 255, stdin) == NULL) {
      break;
    }
    token *token_list = parse(buffer);
    s_cmd *tokens_head = parse_tokens(token_list);
    execute(tokens_head);
  }
  return 0;
}
