/*
 * Copyright (C) 2007-2023 Yasuhiro Ohara. All rights reserved.
 */
#include <stdio.h>
#include <string.h>

#include <zcmdsh/flag.h>
#include <zcmdsh/debug.h>
#include <zcmdsh/shell.h>
#include <zcmdsh/command.h>

#include <zcmdsh/debug_log.h>
#include <zcmdsh/debug_category.h>
#include <zcmdsh/debug_zcmdsh.h>
#include <zcmdsh/debug_backtrace.h>

#include <zcmdsh/debug_cmd.h>

#include "debug_sdplane.h"

struct debug_type debug_sdplane_types[] = {
  { DEBUG_SDPLANE_LTHREAD, "lthread" },
  { DEBUG_SDPLANE_CONSOLE, "console" },
  { DEBUG_SDPLANE_TAPHANDLER, "tap-handler" },
  { DEBUG_SDPLANE_L2FWD, "l2fwd" },
  { DEBUG_SDPLANE_L3FWD, "l3fwd" },
  { DEBUG_SDPLANE_VTY_SERVER, "vty-server" },
  { DEBUG_SDPLANE_VTY_SHELL, "vty-shell" },
  { DEBUG_SDPLANE_TELNET_OPT, "telnet-opt" },
  { DEBUG_SDPLANE_STAT_COLLECTOR, "stat-collector" },
  { DEBUG_SDPLANE_SCHED, "sched" },
  { DEBUG_SDPLANE_VTY, "vty" },
  { DEBUG_SDPLANE_PACKET, "packet" },
  { DEBUG_SDPLANE_FDB, "fdb" },
  { DEBUG_SDPLANE_FDB_CHANGE, "fdb-change" },
  { DEBUG_SDPLANE_RCU_READ, "rcu-read" },
  { DEBUG_SDPLANE_RCU_WRITE, "rcu-write" },
  { DEBUG_SDPLANE_L2_REPEATER, "l2-repeater" },
  { DEBUG_SDPLANE_THREAD, "thread" },
  { DEBUG_SDPLANE_RIB, "rib" },
  { DEBUG_SDPLANE_VSWITCH, "vswitch" },
  { DEBUG_SDPLANE_ALL, "all" },
  { DEBUG_SDPLANE_RIB_MESG, "rib-message" },
  { DEBUG_SDPLANE_RIB_CHECK, "rib-check" },
  { DEBUG_SDPLANE_IMESSAGE, "internal-message" },
  { DEBUG_SDPLANE_NETTLP, "nettlp" },
};

struct command_header debug_sdplane_cmd;

/* assume 128 debug items of max-name-len: 16 */
char debug_sdplane_cmdstr[128 * 16];

/* assume 128 debug items of max-helpstr-len: 64 */
char debug_sdplane_helpstr[128 * 64];

void
debug_sdplane_func (void *context, int argc, char **argv)
{
  struct shell *shell = (struct shell *) context;
  int negate = 0;
  int i;
  int debug_type_size;

  if (FLAG_CHECK (DEBUG_CONFIG (ZCMDSH), DEBUG_TYPE (ZCMDSH, COMMAND)))
    {
      DEBUG_LOG_MSG ("%s: argc: %d", __func__, argc);
      for (i = 0; i < argc; i++)
        DEBUG_LOG_MSG ("%s: argv[%d]: %s", __func__, i, argv[i]);
    }

  struct debug_type *debug_types = debug_sdplane_types;
  debug_type_size = sizeof (debug_sdplane_types) / sizeof (struct debug_type);

  if (! strcmp (argv[0], "no"))
    {
      negate++;
      argv++;
      argc--;
    }

  if (! strcmp (argv[2], "all"))
    {
      if (negate)
        {
          FLAG_ZERO (DEBUG_CONFIG (SDPLANE));
          fprintf (shell->terminal, "debug: sdplane: disable all.%s",
                   shell->NL);
        }
      else
        {
          FLAG_SET (DEBUG_CONFIG (SDPLANE), 0xffffffffffffffff);
          fprintf (shell->terminal, "debug: sdplane: enable all.%s",
                   shell->NL);
        }
      return;
    }

  for (i = 0; i < debug_type_size; i++)
    {
      if (! strcmp (argv[2], debug_types[i].name))
        {
          if (negate)
            {
              FLAG_CLEAR (DEBUG_CONFIG (SDPLANE), debug_types[i].flag);
              fprintf (shell->terminal, "debug: sdplane %s (%#x): disabled.%s",
                       debug_types[i].name, debug_types[i].flag, shell->NL);
            }
          else
            {
              FLAG_SET (DEBUG_CONFIG (SDPLANE), debug_types[i].flag);
              fprintf (shell->terminal, "debug: sdplane %s (%#x): enabled.%s",
                       debug_types[i].name, debug_types[i].flag, shell->NL);
            }
        }
    }
}

CLI_COMMAND2 (show_debug_sdplane, "show debugging sdplane", SHOW_HELP,
              "show debugging information.\n", "sdplane\n")
{
  struct shell *shell = (struct shell *) context;
  int i;
  int debug_type_size;
  debug_type_size = sizeof (debug_sdplane_types) / sizeof (struct debug_type);

  for (i = 0; i < debug_type_size; i++)
    {
      fprintf (
          shell->terminal, "debug: sdplane: %s: %s.%s",
          debug_sdplane_types[i].name,
          (FLAG_CHECK (DEBUG_CONFIG (SDPLANE), debug_sdplane_types[i].flag)
               ? "on"
               : "off"),
          shell->NL);
    }
}

void
debug_sdplane_cmd_init ()
{
  int debug_type_size;
  debug_type_size = sizeof (debug_sdplane_types) / sizeof (struct debug_type);

  debug_cmdstr_init ("sdplane", debug_sdplane_cmdstr,
                     sizeof (debug_sdplane_cmdstr), debug_sdplane_types,
                     debug_type_size);
  debug_helpstr_init ("sdplane", debug_sdplane_helpstr,
                      sizeof (debug_sdplane_helpstr), debug_sdplane_types,
                      debug_type_size);

  if (FLAG_CHECK (DEBUG_CONFIG (ZCMDSH), DEBUG_TYPE (ZCMDSH, COMMAND)))
    {
      DEBUG_LOG_MSG ("debug_sdplane_cmdstr: %s\n", debug_sdplane_cmdstr);
      DEBUG_LOG_MSG ("debug_sdplane_helpstr: %s\n", debug_sdplane_helpstr);
    }

  debug_sdplane_cmd.cmdstr = debug_sdplane_cmdstr;
  debug_sdplane_cmd.helpstr = debug_sdplane_helpstr;
  debug_sdplane_cmd.cmdfunc = debug_sdplane_func;
}
