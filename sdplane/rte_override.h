#ifndef __RTE_OVERRIDE_H__
#define __RTE_OVERRIDE_H__

/* override rte_exit() so that the whole process is not broken. */
#define rte_exit(x, ...)                                                      \
  do                                                                          \
    {                                                                         \
      printf (__VA_ARGS__);                                                   \
      return -1;                                                              \
    }                                                                         \
  while (0)
#define rte_warn(x, ...)                                                      \
  do                                                                          \
    {                                                                         \
      printf (__VA_ARGS__);                                                   \
    }                                                                         \
  while (0)

#endif /*__RTE_OVERRIDE_H__*/
