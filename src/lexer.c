#include "../include/lexer.h"
#include "../include/common.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

token *parse(char buffer[]) {
  size_t len = strlen(buffer);
  token *node = calloc(1, sizeof(token));
  token *head = node;
  char value[4096] = {0};

  for (size_t i = 0; i < len; ++i) {
    if (isspace(buffer[i]) == 0) {
      if (value[0] == 0 && node->value != NULL) {
        node = node->next;
      }
      add_ch(value, buffer[i]);
    } else {
      if (value[0] != '\0') {
        node->value = strdup(value);
        if (!node->type) {
          node->type = WORD;
        }
        memset(value, 0, sizeof(value));
        node->next = calloc(1, sizeof(token));
      }
      continue;
    }

    if (!strcmp(value, "|")) {
      node->type = PIPE;
    } else if (!strcmp(value, "<")) {
      node->type = REDIR_IN;
    } else if (!strcmp(value, ">")) {
      node->type = REDIR_OUT;
    } else if (!strcmp(value, ">>")) {
      node->type = APPEND;
    } else if (!strcmp(value, "\n")) {
      node->type = TOKEN_EOF;
    }
  }

  if (value[0] != '\0') {
    node->value = strdup(value);
    if (!node->type) {
      node->type = WORD;
    }
  }

  return head;
}
