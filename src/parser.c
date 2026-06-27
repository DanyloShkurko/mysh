#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>

s_cmd *parse_tokens(token *token_list) {
  s_cmd *node = calloc(1, sizeof(s_cmd));
  s_cmd *head = node;

  token *token_node = token_list;
  int argc = 0;
  while (token_node) {
    if (token_node->type == WORD) {
      if (token_node->value[0] == '$') {
        char *arg = token_node->value + 1;
        char *value = getenv(arg);
        if (value == NULL) {
          node->argv[argc++] = strdup(token_node->value);
        } else {
          node->argv[argc++] = value;
        }
      } else {
        node->argv[argc++] = strdup(token_node->value);
      }
    }

    else if (token_node->type == PIPE) {
      node->argv[argc] = NULL;
      node->next = calloc(1, sizeof(s_cmd));
      node = node->next;
      argc = 0;
    }

    else if (token_node->type == REDIR_IN) {
      token_node = token_node->next;
      node->in = strdup(token_node->value);
    }

    else if (token_node->type == REDIR_OUT) {
      token_node = token_node->next;
      node->out = strdup(token_node->value);
    }

    else if (token_node->type == APPEND) {
      token_node = token_node->next;
      node->out = strdup(token_node->value);
      node->append = 1;
    }

    token_node = token_node->next;
  }

  node->argv[argc] = NULL;

  return head;
}
