# soft-dplane

## Prerequisite

- lthread (https://github.com/yasuhironet/lthread)
- liburcu-dev
- DPDK

## Build

```
% sh autogen.sh
% CFLAGS="-g -O0" sh configure
% make

/* run in foreground */
# ./sdplane/sdplane
```

