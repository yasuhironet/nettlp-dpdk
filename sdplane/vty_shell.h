#ifndef __VTY_SHELL__
#define __VTY_SHELL__


void shell_keyfunc_clear_terminal (struct shell *shell);
EXTERN_COMMAND (clear_cmd);

void vty_shell (void *arg);

#endif /*__VTY_SHELL__*/
