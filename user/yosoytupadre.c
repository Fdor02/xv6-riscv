// user/yosoytupadre.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int me = getpid();
  int p = getppid();
  printf("yo=%d, ppid=%d\n", me, p);

  // (opcional, para Parte II)
  for(int k = 0; k <= 3; k++){
    int a = getancestor(k);
    printf("getancestor(%d) = %d\n", k, a);
  }
  exit(0);
}
