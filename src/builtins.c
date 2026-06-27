#include "../include/builtins.h"
#include "../include/common.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUILTINS_CNT 3

bool is_builtin(char *argv) {
  char *builtins[BUILTINS_CNT] = {"cd", "exit", "export"};
  for (size_t i = 0; i < BUILTINS_CNT; ++i) {
    if (strcmp(builtins[i], argv) == 0) {
      return true;
    }
  }
  return false;
}

void cd_handler(s_cmd *cmd) {
  if (cmd->argv[1] == NULL || chdir(cmd->argv[1]) != 0) {
    fprintf(stderr, "cd: argument required\n");
    return;
  }
}

void exit_handler(s_cmd *cmd) {
  if (cmd->argv[1] == NULL) {
    fprintf(stderr, "exit: argument required\n");
    return;
  }
  int status;
  status = atoi(cmd->argv[1]);
  exit(status);
}

void export_handler(s_cmd *cmd) {
  if (cmd->argv[1] == NULL) {
    fprintf(stderr, "export: argument required\n");
    return;
  }

  char name[256] = {0};
  char value[256] = {0};
  char *arg = cmd->argv[1];

  while (*arg != '=' && *arg != '\0') {
    add_ch(name, *arg);
    arg++;
  }
  if (*arg == '=') {
    arg++;
  }
  while (*arg != '\0') {
    add_ch(value, *arg);
    arg++;
  }

  setenv(name, value, 1);
}
