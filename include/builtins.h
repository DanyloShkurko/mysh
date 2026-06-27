#pragma once
#include "parser.h"
#include <stdbool.h>

bool is_builtin(char *argv);

void cd_handler(s_cmd *cmd);
void exit_handler(s_cmd *cmd);
void export_handler(s_cmd *cmd);
