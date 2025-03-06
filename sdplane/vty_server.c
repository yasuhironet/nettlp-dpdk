#include "include.h"

#include <lthread.h>

#include <rte_common.h>
#include <rte_launch.h>
#include <rte_ether.h>

#include <zcmdsh/shell.h>
#include <zcmdsh/command.h>
#include <zcmdsh/command_shell.h>

#include <zcmdsh/debug.h>
#include <zcmdsh/debug_cmd.h>
#include <zcmdsh/debug_log.h>
#include <zcmdsh/debug_category.h>
#include <zcmdsh/debug_zcmdsh.h>
#include "debug_sdplane.h"

#include "sdplane.h"

#include "l3fwd_cmd.h"
#include "l2fwd_cmd.h"

#include "vty_server.h"
#include "vty_shell.h"

#include "thread_info.h"

extern int lthread_core;
extern volatile bool force_stop[RTE_MAX_LCORE];

vty_client_t client_info[VTY_CLIENT_MAX];

static __thread uint64_t loop_counter = 0;

void
vty_server (void *arg)
{
  int sockfd;
  int ret;
  int client_fd;

  sockfd = lthread_socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd == -1)
    {
      fprintf (stderr, "lthread_socket() failed.\n");
      return;
    }

  int optval = 1;
  ret =
      setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval));
  if (ret < 0)
    {
      fprintf (stderr, "setsockopt(REUSEADDR) failed: %s.\n",
               strerror (errno));
      return;
    }

  struct sockaddr_in peer_addr;
  struct sockaddr_in sin;
  socklen_t addrlen = sizeof (peer_addr);

  sin.sin_family = PF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons (9882);

  ret = bind (sockfd, (struct sockaddr *) &sin, sizeof (sin));
  if (ret < 0)
    {
      fprintf (stderr, "bind() failed: %s.\n", strerror (errno));
      return;
    }

  DEBUG_SDPLANE_LOG (VTY_SERVER, "Starting vty_server on port 9882.");

  int client_size = 0;
  int i, client_id;
  lthread_t *client_lt = NULL;

  /* initialize */
  for (i = 0; i < VTY_CLIENT_MAX; i++)
    {
      client_info[i].id = i;
      client_info[i].fd = -1;
    }

  listen (sockfd, 128);

  struct pollfd fds[2];

  int thread_id;
  thread_id = thread_lookup (vty_server);
  thread_register_loop_counter (thread_id, &loop_counter);

#if HAVE_LIBURCU_QSBR
  urcu_qsbr_register_thread ();
#endif /*HAVE_LIBURCU_QSBR*/

  while (! force_quit && ! force_stop[lthread_core])
    {
      lthread_sleep (100); // yield.

      fds[0].fd = sockfd;
      fds[0].events = POLLIN;
      poll (fds, 1, 0);
      if ((fds[0].revents & (POLLIN | POLLERR)) == 0)
        continue;

      client_fd =
          lthread_accept (sockfd, (struct sockaddr *) &peer_addr, &addrlen);
      if (client_fd < 0)
        {
          fprintf (stderr, "lthread_accept() failed.\n");
          continue;
        }

      client_id = -1;
      for (i = 0; i < VTY_CLIENT_MAX; i++)
        {
          if (client_info[i].fd == -1)
            {
              client_id = i;
              break;
            }
        }
      if (client_id == -1)
        {
          printf ("%s: can't create new client: already served %d. ignore.\n",
                  __func__, VTY_CLIENT_MAX);
          lthread_close (client_fd);
          continue;
        }

      DEBUG_SDPLANE_LOG (VTY_SERVER, "lthread_accept: client[%d].", client_id);
      client_info[client_id].peer_addr = peer_addr;
      client_info[client_id].fd = client_fd;
      ret = lthread_create (&client_info[client_id].lt,
                            vty_shell, &client_info[client_id]);
      if (client_size < client_id)
        client_size = client_id + 1;

#if HAVE_LIBURCU_QSBR
      urcu_qsbr_quiescent_state ();
#endif /*HAVE_LIBURCU_QSBR*/

      loop_counter++;
    }

  printf ("%s[%d]: %s: terminating.\n", __FILE__, __LINE__, __func__);

#if HAVE_LIBURCU_QSBR
  urcu_qsbr_unregister_thread ();
#endif /*HAVE_LIBURCU_QSBR*/
}
