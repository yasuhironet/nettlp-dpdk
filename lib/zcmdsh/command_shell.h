/*
 * Copyright (C) 2007-2023 Yasuhiro Ohara. All rights reserved.
 */

#ifndef __COMMAND_SHELL_H__
#define __COMMAND_SHELL_H__

extern char *prompt_default;
extern struct command_set *cmdset_default;

#define HISTORY_SIZE    128
#define HISTORY_PREV(x) ((x) == 0 ? HISTORY_SIZE - 1 : (x) - 1)
#define HISTORY_NEXT(x) ((x) + 1 == HISTORY_SIZE ? 0 : (x) + 1)
struct command_history
{
  char *array[HISTORY_SIZE];
  int last;
  int current;
};

EXTERN_COMMAND (exit);
EXTERN_COMMAND (quit);
EXTERN_COMMAND (logout);
EXTERN_COMMAND (enable_shell_debugging);
EXTERN_COMMAND (disable_shell_debugging);
EXTERN_COMMAND (show_history);
EXTERN_COMMAND (redirect_stderr_file);
EXTERN_COMMAND (restore_stderr);
EXTERN_COMMAND (redirect_terminal_file);
EXTERN_COMMAND (restore_terminal);

struct shell *command_shell_create ();
void command_shell_delete (struct shell *shell);

void command_shell_install_default (struct shell *shell);

void shell_read_nowait_paging (struct shell *shell);

void command_shell_init ();
void command_shell_finish ();

void command_history_add (char *command_line, struct command_history *history,
                          struct shell *shell);

void timer_init (int duration_limit, char *date_limit);

int dirent_cmp (const void *va, const void *vb);
void file_ls_candidate (struct shell *shell, char *file_path);

#define FUNC_TABLE_SIZE 512
struct funcp_str_map
{
  void *ptr;
  char *str;
};
extern struct funcp_str_map func2str[];
#define FUNC_STR_REGISTER(x)                                                  \
  do                                                                          \
    {                                                                         \
      int i;                                                                  \
      for (i = 0; i < FUNC_TABLE_SIZE; i++)                                   \
        {                                                                     \
          if (! func2str[i].ptr)                                              \
            {                                                                 \
              func2str[i].ptr = x;                                            \
              func2str[i].str = #x;                                           \
              break;                                                          \
            }                                                                 \
        }                                                                     \
    }                                                                         \
  while (0)

#endif /*__COMMAND_SHELL_H__*/
