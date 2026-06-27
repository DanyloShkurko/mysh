#pragma once
#include "lexer.h"

typedef struct s_cmd {
  char *argv[1024];
  char *in;
  char *out;
  int append;
  struct s_cmd *next;
} s_cmd;

s_cmd *parse_tokens(token *token_list);
