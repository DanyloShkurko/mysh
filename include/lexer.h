#pragma once

typedef enum {
  NONE,
  WORD,
  PIPE,
  REDIR_IN,
  REDIR_OUT,
  APPEND,
  TOKEN_EOF
} token_type;

typedef struct s_token {
  token_type type;
  char *value;

  struct s_token *next;
} token;

token *parse(char buffer[]);
