#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  char *addr = sbrk(0);
  sbrk(4096);        // reservar una página
  addr[0] = 'Z';

  printf("Protegiendo memoria...\n");
  if(mrdprotect(addr, 1) < 0){
    printf("mrdprotect falló\n");
    exit(1);
  }

  printf("Escribiendo aún permitida...\n");
  addr[0] = 'A';

  printf("Intentando leer (debería fallar)...\n");
  char c = addr[0]; // esto debería causar un fallo de página
  printf("Valor leído: %c (NO debería imprimirse)\n", c);

  printf("Revirtiendo protección...\n");
  if(munrdprotect(addr, 1) < 0){
    printf("munrdprotect falló\n");
    exit(1);
  }

  printf("Protección revertida correctamente.\n");
  exit(0);
}
