#include "../include/executor.h"
#include "../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void fork_c(s_cmd *cmd, int fd_in, int fd_out) {
  if (fd_in != -1) {
    dup2(fd_in, 0);
    close(fd_in);
  } else if (cmd->in != NULL) {
    int file_desc = open(cmd->in, O_RDONLY);
    if (file_desc < 0) {
      printf("Error opening the file\n");
      exit(1);
    }

    dup2(file_desc, 0);
    close(file_desc);
  }

  if (fd_out != -1) {
    dup2(fd_out, 1);
    close(fd_out);
  } else if (cmd->out != NULL) {
    int file_desc;
    if (cmd->append == 1) {
      file_desc = open(cmd->out, O_WRONLY | O_APPEND | O_CREAT, 0644);
    } else {
      file_desc = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (file_desc < 0) {
      printf("Error opening the file\n");
      exit(1);
    }

    dup2(file_desc, 1);
    close(file_desc);
  }

  char **argv = cmd->argv;
  if (execvp(argv[0], argv) < 0) {
    perror(argv[0]);
    exit(1);
  }
}

void execute(s_cmd *cmd) {
  s_cmd *node = cmd;
  int prev_fd = -1;
  int size = 0;

  pid_t pids[1024];

  while (node != NULL) {
    if (node->argv[0] == NULL)
      return;
    if (is_builtin(node->argv[0])) {
      if (strcmp(node->argv[0], "cd") == 0) {
        cd_handler(node);
      } else if (strcmp(node->argv[0], "exit") == 0) {
        exit_handler(node);
      } else if (strcmp(node->argv[0], "export") == 0) {
        export_handler(node);
      }
      return;
    }
    if (node->next != NULL) {
      int fd[2];
      pipe(fd);
      pid_t p = fork();
      if (p < 0) {
        perror("fork fail");
        exit(1);
      }

      if (p == 0) {
        fork_c(node, prev_fd, fd[1]);
      } else {
        pids[size++] = p;
        prev_fd = fd[0];
        close(fd[1]);
      }
    } else {
      pid_t p = fork();
      if (p < 0) {
        perror("fork fail");
        exit(1);
      }

      if (p == 0) {
        fork_c(node, prev_fd, -1);
      } else {
        pids[size++] = p;
      }
    }

    node = node->next;
  }

  for (int i = 0; i < size; ++i) {
    waitpid(pids[i], NULL, 0);
  }
}
