// user/yosoytupadre.c
// Programa de prueba de las syscalls getppid() y getancestor().
// Compilado como parte de userland; se ejecuta dentro de xv6.

#include "kernel/types.h"  // tipos básicos compartidos
#include "kernel/stat.h"
#include "user/user.h"     // prototipos de syscalls de userland

int
main(void)
{
  // getpid() existe en xv6 y permite mostrar el pid actual.
  int me = getpid();

  // getppid(): nuevo wrapper -> kernel -> retorna pid del padre.
  int p  = getppid();
  printf("yo=%d, ppid=%d\n", me, p);

  // Prueba extendida (opcional, si implementaste getancestor):
  // k=0 => mi pid; k=1 => padre; k=2 => abuelo; k=3 => -1 si no existe.
  for (int k = 0; k <= 3; k++) {
    int a = getancestor(k);
    printf("getancestor(%d) = %d\n", k, a);
  }

  exit(0); // terminar proceso con código 0 (éxito)
}
